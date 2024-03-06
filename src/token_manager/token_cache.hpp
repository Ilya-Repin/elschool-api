#pragma once

#include <chrono>
#include <optional>
#include <string>
#include <unordered_map>
#include <optional>
#include <userver/engine/shared_mutex.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "utils/constants_storage.h"

namespace token_manager {

struct Token {
  std::string token;
  uint64_t seconds_since_epoch;
};

class TokenCache {
 public:
  static TokenCache& GetInstance();

  void SetInvalidationTime(const uint64_t& time);

  bool IsInvalidatingOldTokens();

  void HeatCache(const std::unordered_map<std::string, Token>& firewood);
  void AddToken(const boost::uuids::uuid& uuid, const std::string& token);

  std::optional<std::string> FindToken(const boost::uuids::uuid& uuid);

  std::size_t InvalidateOldTokens();
  std::size_t InvalidateAllTokens();
  void InvalidateToken(const boost::uuids::uuid& uuid);

 private:
  TokenCache() = default;
  ~TokenCache() = default;

  TokenCache(const TokenCache &) = delete;
  TokenCache& operator= (const TokenCache &) = delete;


  std::unordered_map<std::string, Token> tokens_;
  userver::engine::SharedMutex mutex_;
  std::atomic<bool> is_invalidating_old_{false};
  uint64_t token_lifetime_{172800};
};
}  // namespace token_manager