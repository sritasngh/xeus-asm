#include "xasm/xasm_interpreter.hpp"

std::string asm ::output = "";

namespace xasm {

nl::json xasm_interpreter::execute_request_impl(int execution_counter,
                                                const std::string &code,
                                                bool silent, bool store_history,
                                                nl::json user_expressions,
                                                bool allow_stdin) {
    // write your logic here
}

nl::json xasm_interpreter::complete_request_impl(const std::string &code,
                                                 int cursor_pos) {
  nl::json result;
  result["status"] = "ok";
  return result;
}

// 
nl::json xasm_interpreter::inspect_request_impl(const std::string &code,
                                                int cursor_pos,
                                                int detail_level) {
  nl::json result;
  result["status"] = "ok";
  return result;
}

//syntax check
nl::json xasm_interpreter::is_complete_request_impl(const std::string &code) {
  nl::json result;
  result["status"] = "complete";
  return result;
} 

void xasm_interpreter::configure_impl() {}

nl::json xasm_interpreter::kernel_info_request_impl() {
  nl::json info;
  info["implementation"] = "xasm";
  info["implementation_version"] = "0.1.0";
  std::string banner = R"V0G0N(                                                             
      xeus-asm: a Jupyter Kernel for asm Language
      xASM Version: 0.1.0")V0G0N";
  info["banner"] = banner;
  info["language_info"]["name"] = "asm";
  info["langauge_info"]["codemirror_mode"] = "vb";
  info["language_info"]["version"] = "0.1.0";
  info["language_info"]["mimetype"] = "text/x-vb";
  info["language_info"]["file_extension"] = ".bas";
  return info;
}

void xasm_interpreter::shutdown_request_impl() {}
} // namespace xasm
