#include "caf/config.hpp"
#include "caf/string_view.hpp"

CAF_PUSH_DEPRECATED_WARNING

#include "caf/flow/observer_state.hpp"

#include <string>

namespace caf::flow {

std::string to_string(observer_state x) {
  switch (x) {
    default:
      return "???";
    case observer_state::idle:
      return "caf::flow::observer_state::idle";
    case observer_state::subscribed:
      return "caf::flow::observer_state::subscribed";
    case observer_state::completed:
      return "caf::flow::observer_state::completed";
    case observer_state::aborted:
      return "caf::flow::observer_state::aborted";
  }
}

bool from_string(string_view in, observer_state& out) {
  if (in == "caf::flow::observer_state::idle") {
    out = observer_state::idle;
    return true;
  }
  if (in == "caf::flow::observer_state::subscribed") {
    out = observer_state::subscribed;
    return true;
  }
  if (in == "caf::flow::observer_state::completed") {
    out = observer_state::completed;
    return true;
  }
  if (in == "caf::flow::observer_state::aborted") {
    out = observer_state::aborted;
    return true;
  }
  return false;
}

bool from_integer(std::underlying_type_t<observer_state> in,
                  observer_state& out) {
  auto result = static_cast<observer_state>(in);
  switch (result) {
    default:
      return false;
    case observer_state::idle:
    case observer_state::subscribed:
    case observer_state::completed:
    case observer_state::aborted:
      out = result;
      return true;
  }
}

} // namespace caf::flow

