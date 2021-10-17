#ifndef XBASIC_INTERPRETER_HPP_
#define XBASIC_INTERPRETER_HPP_

#include "interpreter.hpp"
#include "nlohmann/json.hpp"
#include "xeus/xinterpreter.hpp"

using xeus::xinterpreter;
namespace nl = nlohmann;

// TODO: magic command to load starting address

namespace xasm {

/**
 * @brief a class xasm_interpreter inheriting from the base interpreter class
 * xeus::xinterpreter and implement the private virtual methods
 */
class xasm_interpreter : public xinterpreter {
private:
  Interpreter *code_runner = nullptr;

public:
  xasm_interpreter() = default;

  virtual ~xasm_interpreter() = default;

  void configure_impl() override;

  /**
   * @brief Code execution request from the client
   */
  nl::json execute_request_impl(int execution_counter, const std::string &code,
                                bool silent, bool store_history,
                                nl::json user_expressions,
                                bool allow_stdin) override;

  /**
   * Code completion request from the client
   */
  nl::json complete_request_impl(const std::string &code,
                                 int cursor_pos) override;

  /**
   * Code inspection request (using a question mark on a type for example)
   */
  nl::json inspect_request_impl(const std::string &code, int cursor_pos,
                                int detail_level) override;

  /**
   * Called before code execution (terminal mode) in order to check
   * if the code is complete and can be executed
   */
  nl::json is_complete_request_impl(const std::string &code) override;

  /**
   * Information request about the kernel
   */
  nl::json kernel_info_request_impl() override;

  /**
   * Shutdown request from the client,
   * this allows you to do some extra work before the kernel is shut down
   * (e.g. free allocated memory)
   */
  void shutdown_request_impl() override;
};
} // namespace xasm

#endif // XASM_INTERPRETER_HPP_