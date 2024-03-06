#include "token_cache.hpp"

namespace token_manager {

TokenCache& TokenCache::GetInstance() {
  static TokenCache token_cache;

  return token_cache;
}

void TokenCache::SetInvalidationTime(const uint64_t& time) {
  std::unique_lock<userver::engine::SharedMutex> lock(mutex_);
  token_lifetime_ = time;
}

std::optional<std::string> TokenCache::FindToken(const boost::uuids::uuid& uuid) {
  using namespace std::chrono;

  std::shared_lock<userver::engine::SharedMutex> lock(mutex_);

  const std::string id = boost::uuids::to_string(uuid);

  if (tokens_.find(id) != tokens_.end()) {
    const auto token = tokens_.find(id);

    const uint64_t seconds_since_epoch =
        duration_cast<seconds>(system_clock::now().time_since_epoch()).count();

    if (seconds_since_epoch - token->second.seconds_since_epoch < 172800) {
      return token->second.token;
    }
  }

  return std::nullopt;
}

void TokenCache::AddToken(const boost::uuids::uuid& uuid, const std::string& token) {
  using namespace std::chrono;

  std::unique_lock<userver::engine::SharedMutex> lock(mutex_);

  const uint64_t seconds_since_epoch =
      duration_cast<seconds>(system_clock::now().time_since_epoch()).count();

  const std::string id = boost::uuids::to_string(uuid);

  tokens_[id] = Token{token, seconds_since_epoch};
}

void TokenCache::InvalidateToken(const boost::uuids::uuid& uuid) {
  std::unique_lock<userver::engine::SharedMutex> lock(mutex_);
  const std::string id = boost::uuids::to_string(uuid);
  tokens_.erase(id);
 }

std::size_t TokenCache::InvalidateOldTokens() {
  using namespace std::chrono;

  is_invalidating_old_ = true;

  std::unique_lock<userver::engine::SharedMutex> lock(mutex_);
  uint64_t seconds_since_epoch =
      duration_cast<seconds>(system_clock::now().time_since_epoch()).count();

  std::vector<std::string> keys_to_delete;

  for (const auto& token : tokens_) {
    if (seconds_since_epoch - token.second.seconds_since_epoch >
        token_lifetime_) {
      keys_to_delete.push_back(token.first);
      }
  }

  for (const auto& key : keys_to_delete) {
    tokens_.erase(key);
  }

  is_invalidating_old_ = false;

  return keys_to_delete.size();
}

std::size_t TokenCache::InvalidateAllTokens() {
  std::unique_lock<userver::engine::SharedMutex> lock(mutex_);

  const std::size_t size = tokens_.size();
  tokens_.clear();

  return size;
}

bool TokenCache::IsInvalidatingOldTokens() {
  return is_invalidating_old_;
}

void TokenCache::HeatCache(const std::unordered_map<std::string, Token>& firewood) {
  std::unique_lock<userver::engine::SharedMutex> lock(mutex_);

  tokens_.insert(firewood.begin(), firewood.end());
}

}  // namespace token_manager