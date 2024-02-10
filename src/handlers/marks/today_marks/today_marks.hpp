#pragma once

#include "userver/clients/http/client.hpp"
#include "userver/clients/http/component.hpp"
#include "userver/components/component_list.hpp"
#include "userver/components/minimal_server_component_list.hpp"
#include "userver/server/handlers/http_handler_base.hpp"

#include "../../../parser/parser.hpp"
#include "../../../token_manager/token_manager.hpp"
#include "../../../utils/constants_storage.h"
#include "../marks_base.hpp"

namespace today_marks {

using namespace userver;
using namespace std::literals;

class TodayMarks final : public server::handlers::HttpHandlerBase, marks_base::MarksBase {
 public:
  static constexpr std::string_view kName = "handler-today-marks"sv;

  using HttpHandlerBase::HttpHandlerBase;

  TodayMarks(const components::ComponentConfig& config,
               const components::ComponentContext& context);

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext& context) const override;

 private:

  userver::clients::http::Client& http_client_;
  token_manager::TokenManager& token_manager_;
  parser::Parser parser_;
};

void AppendTodayMarks(userver::components::ComponentList& component_list);

}  // namespace service_template