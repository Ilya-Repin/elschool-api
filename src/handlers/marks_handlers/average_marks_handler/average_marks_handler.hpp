#pragma once

#include <userver/clients/http/client.hpp>
#include <userver/clients/http/component.hpp>
#include <userver/components/component_context.hpp>
#include <userver/components/component_list.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/yaml_config/merge_schemas.hpp>

#include "handlers/marks_handlers/marks_base.hpp"
#include "parser/parser.hpp"
#include "token_manager/token_manager.hpp"
#include "utils/constants_storage.h"
#include "utils/exceptions.h"

namespace average_marks_handler {

using namespace std::literals;

class AverageMarksHandler final
    : public userver::server::handlers::HttpHandlerBase,
      marks_base::MarksBase {
 public:
  static constexpr std::string_view kName = "handler-average-marks"sv;

  using HttpHandlerBase::HttpHandlerBase;

  AverageMarksHandler(const userver::components::ComponentConfig& config,
                      const userver::components::ComponentContext& context);

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext&) const override;

  static userver::yaml_config::Schema GetStaticConfigSchema();

 private:
  userver::clients::http::Client& http_client_;
  token_manager::TokenManager& token_manager_;
  parser::Parser parser_;
  const std::string elschool_url_;
};

void AppendAverageMarksHandler(
    userver::components::ComponentList& component_list);

}  // namespace average_marks_handler