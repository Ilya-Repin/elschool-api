#pragma once

#include <boost/uuid/uuid.hpp>
#include <chrono>
#include <optional>
#include <string>
#include <unordered_map>
#include <userver/engine/shared_mutex.hpp>

namespace token_manager {

using namespace userver;

struct Token {
  std::string token;
  uint64_t seconds_since_epoch;
};

class TokenCache {
 public:
  static TokenCache& GetInstance();

  void HeatCache(std::unordered_map<std::string, Token> firewood);
  std::optional<std::string> FindToken(boost::uuids::uuid uuid);
  void AddToken(boost::uuids::uuid uuid, std::string token);
  void InvalidateToken(boost::uuids::uuid uuid);
  std::size_t InvalidateOldTokens();
  std::size_t InvalidateAllTokens();
  bool IsInvalidatingOldTokens();

 private:
  TokenCache() = default;
  ~TokenCache() = default;

  TokenCache(const TokenCache &) = delete;
  TokenCache& operator= (const TokenCache &) = delete;


  std::unordered_map<std::string, Token> tokens_;
  engine::SharedMutex mutex_;
  std::atomic<bool> invalidating_old_{false};
};
}  // namespace token_manager