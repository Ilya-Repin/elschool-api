#include <userver/clients/http/component.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/server/handlers/ping.hpp>
#include <userver/server/handlers/tests_control.hpp>
#include <userver/testsuite/testsuite_support.hpp>
#include <userver/utils/daemon_run.hpp>

#include "handlers/marks/average_marks/average_marks.hpp"
#include "handlers/marks/today_marks/today_marks.hpp"
#include "handlers/token_handler/token_handler.hpp"
#include "handlers/users_handler/users_handler.hpp"
#include "token_manager/token_manager.hpp"
#include "user_manager/user_manager.hpp"

int main(int argc, char* argv[]) {
  auto component_list = userver::components::MinimalServerComponentList()
                            .Append<userver::server::handlers::Ping>()
                            .Append<userver::components::TestsuiteSupport>()
                            .Append<userver::components::HttpClient>()
                            .Append<userver::server::handlers::TestsControl>();

  token_manager::AppendTokenManager(component_list);
  token_handler::AppendTokenHandler(component_list);
  user_manager::AppendUserManager(component_list);
  average_marks::AppendAverageMarks(component_list);
  today_marks::AppendTodayMarks(component_list);
  users_handler::AppendUsersHandler(component_list);

  return userver::utils::DaemonMain(argc, argv, component_list);
}
