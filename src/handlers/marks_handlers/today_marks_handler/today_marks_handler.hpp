#pragma once

#include <userver/clients/http/client.hpp>
#include <userver/clients/http/component.hpp>
#include <userver/components/component_list.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/components/component_context.hpp>
#include <userver/yaml_config/merge_schemas.hpp>

#include "handlers/marks_handlers/marks_base.hpp"
#include "parser/parser.hpp"
#include "token_manager/token_manager.hpp"
#include "utils/constants_storage.h"
#include "utils/exceptions.h"

namespace today_marks_handler {

using namespace std::literals;

class TodayMarksHandler final : public userver::server::handlers::HttpHandlerBase, marks_base::MarksBase {
 public:
  static constexpr std::string_view kName = "handler-today-marks"sv;

  using HttpHandlerBase::HttpHandlerBase;

  TodayMarksHandler(const userver::components::ComponentConfig& config,
               const userver::components::ComponentContext& context);

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext& context) const override;

  static userver::yaml_config::Schema GetStaticConfigSchema();

 private:
  token_manager::TokenManager& token_manager_;
  userver::clients::http::Client& http_client_;
  parser::Parser parser_;
  const std::string elschool_url_;
};

void AppendTodayMarksHandler(userver::components::ComponentList& component_list);

}  // namespace today_marks_handler