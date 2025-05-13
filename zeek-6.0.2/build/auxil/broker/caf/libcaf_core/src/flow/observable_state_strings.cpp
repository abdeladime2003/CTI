#include "caf/config.hpp"
#include "caf/string_view.hpp"

CAF_PUSH_DEPRECATED_WARNING

#include "caf/flow/observable_state.hpp"

#include <string>

namespace caf::flow {

std::string to_string(observable_state x) {
  switch (x) {
    default:
      return "???";
    case observable_state::idle:
      return "caf::flow::observable_state::idle";
    case observable_state::running:
      return "caf::flow::observable_state::running";
    case observable_state::completing:
      return "caf::flow::observable_state::completing";
    case observable_state::completed:
      return "caf::flow::observable_state::completed";
    case observable_state::aborted:
      return "caf::flow::observable_state::aborted";
    case observable_state::disposed:
      return "caf::flow::observable_state::disposed";
  }
}

bool from_string(string_view in, observable_state& out) {
  if (in == "caf::flow::observable_state::idle") {
    out = observable_state::idle;
    return true;
  }
  if (in == "caf::flow::observable_state::running") {
    out = observable_state::running;
    return true;
  }
  if (in == "caf::flow::observable_state::completing") {
    out = observable_state::completing;
    return true;
  }
  if (in == "caf::flow::observable_state::completed") {
    out = observable_state::completed;
    return true;
  }
  if (in == "caf::flow::observable_state::aborted") {
    out = observable_state::aborted;
    return true;
  }
  if (in == "caf::flow::observable_state::disposed") {
    out = observable_state::disposed;
    return true;
  }
  return false;
}

bool from_integer(std::underlying_type_t<observable_state> in,
                  observable_state& out) {
  auto result = static_cast<observable_state>(in);
  switch (result) {
    default:
      return false;
    case observable_state::idle:
    case observable_state::running:
    case observable_state::completing:
    case observable_state::completed:
    case observable_state::aborted:
    case observable_state::disposed:
      out = result;
      return true;
  }
}

} // namespace caf::flow

