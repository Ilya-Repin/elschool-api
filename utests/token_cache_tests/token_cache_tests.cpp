#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <chrono>
#include <thread>
#include <userver/utest/utest.hpp>
#include "token_manager/token_cache.hpp"
#include "userver/engine/sleep.hpp"

UTEST(TokenCacheTestSuite, AddInvalidateTokenTest) {
  token_manager::TokenCache& cache = token_manager::TokenCache::GetInstance();

  boost::uuids::uuid test_uuid = boost::uuids::random_generator()();
  std::string test_token = "test_token";

  cache.AddToken(test_uuid, test_token);

  ASSERT_TRUE(cache.FindToken(test_uuid).has_value());
  ASSERT_EQ(cache.FindToken(test_uuid), test_token);

  cache.InvalidateToken(test_uuid);

  ASSERT_FALSE(cache.FindToken(test_uuid).has_value());

  cache.InvalidateAllTokens();
}

UTEST(TokenCacheTestSuite, InvalidateOldTokensTest) {
  using namespace std::literals;

  token_manager::TokenCache& cache = token_manager::TokenCache::GetInstance();

  cache.InvalidateAllTokens();

  auto now = std::chrono::system_clock::now();

  std::string first_token = "first_token"s;
  boost::uuids::uuid first_token_uuid = boost::uuids::random_generator()();
  uint64_t first_token_time =
      std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch() -
                                                       std::chrono::hours(24))
          .count();

  std::string second_token = "second_token"s;
  boost::uuids::uuid second_token_uuid = boost::uuids::random_generator()();
  uint64_t second_token_time =
      std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch() -
                                                       std::chrono::hours(49))
          .count();

  std::string third_token = "third_token"s;
  boost::uuids::uuid third_token_uuid = boost::uuids::random_generator()();
  uint64_t third_token_time =
      std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch() -
                                                       std::chrono::hours(72))
          .count();

  std::unordered_map<std::string, token_manager::Token> tokens = {
      {boost::uuids::to_string(first_token_uuid),
       {first_token, first_token_time}},
      {boost::uuids::to_string(second_token_uuid),
       {second_token, second_token_time}},
      {boost::uuids::to_string(third_token_uuid),
       {third_token, third_token_time}},
  };

  cache.HeatCache(tokens);

  std::size_t amount = cache.InvalidateOldTokens();

  ASSERT_EQ(amount, 2);
  ASSERT_TRUE(cache.FindToken(first_token_uuid).has_value());
  ASSERT_FALSE(cache.FindToken(second_token_uuid).has_value());
  ASSERT_FALSE(cache.FindToken(third_token_uuid).has_value());

  cache.InvalidateAllTokens();
}

UTEST(TokenCacheTestSuite, InvalidateAllTokensTest) {
  using namespace std::literals;
  token_manager::TokenCache& cache = token_manager::TokenCache::GetInstance();

  cache.InvalidateAllTokens();

  for (std::size_t i = 0; i < 30; ++i) {
    boost::uuids::uuid test_uuid = boost::uuids::random_generator()();

    std::string test_token = "test_token"s + std::to_string(i);

    cache.AddToken(test_uuid, test_token);

    ASSERT_TRUE(cache.FindToken(test_uuid).has_value());
    ASSERT_EQ(cache.FindToken(test_uuid), test_token);
  }

  std::size_t amount = cache.InvalidateAllTokens();

  ASSERT_EQ(amount, 30);
}

UTEST_MT(TokenCacheTestSuite, MultiThreadedAddTokenTest, 4) {
  using namespace std::literals;

  boost::uuids::uuid test_uuid = boost::uuids::random_generator()();

  const std::chrono::milliseconds ms{rand() % 500 + 100};
  userver::engine::SleepFor(ms);

  token_manager::TokenCache& cache = token_manager::TokenCache::GetInstance();
  cache.AddToken(test_uuid,
                 "token_with_uuid_"s + boost::uuids::to_string(test_uuid));

  auto token = cache.FindToken(test_uuid);

  UASSERT(token);
  ASSERT_EQ(token, "token_with_uuid_"s + boost::uuids::to_string(test_uuid));

  cache.InvalidateToken(test_uuid);
  ASSERT_FALSE(cache.FindToken(test_uuid).has_value());
}