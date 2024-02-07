#include "token_cache.hpp"
#include <boost/uuid/uuid_io.hpp>
#include <optional>
#include "../utils/constants_storage.h"

namespace token_manager {

TokenCache& TokenCache::GetInstance() {
  static TokenCache token_cache;

  return token_cache;
}

std::optional<std::string> TokenCache::FindToken(boost::uuids::uuid uuid) {
  using namespace std::chrono;

  std::lock_guard<engine::Mutex> lock(mutex_);

  std::string id = boost::uuids::to_string(uuid);

  if (tokens_.find(id) != tokens_.end()) {
    auto token = tokens_.find(id);

    uint64_t seconds_since_epoch =
        duration_cast<seconds>(system_clock::now().time_since_epoch()).count();

    if (seconds_since_epoch - token->second.seconds_since_epoch < 172800) {
      return token->second.token;
    }
  }

  return std::nullopt;
}

void TokenCache::AddToken(boost::uuids::uuid uuid, std::string token) {
  using namespace std::chrono;

  std::lock_guard<engine::Mutex> lock(mutex_);

  uint64_t seconds_since_epoch =
      duration_cast<seconds>(system_clock::now().time_since_epoch()).count();

  std::string id = boost::uuids::to_string(uuid);

  tokens_[id] = Token{token, seconds_since_epoch};
}

void TokenCache::InvalidateToken(boost::uuids::uuid uuid) {
  std::lock_guard<engine::Mutex> lock(mutex_);
  std::string id = boost::uuids::to_string(uuid);
  tokens_.erase(id);
 }

std::size_t TokenCache::InvalidateOldTokens() {
  using namespace std::chrono;

  std::lock_guard<engine::Mutex> lock(mutex_);
  uint64_t seconds_since_epoch =
      duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
  std::size_t counter = 0;

  for (auto i : tokens_) {
    if (seconds_since_epoch - i.second.seconds_since_epoch >
        constants::tokens::two_days_in_seconds) {
      tokens_.erase(i.first);
      ++counter;
    }
  }

  return counter;
}

std::size_t TokenCache::InvalidateAllTokens() {
  std::lock_guard<engine::Mutex> lock(mutex_);
  std::size_t size = tokens_.size();
  tokens_.clear();

  return size;
}
}  // namespace token_manager