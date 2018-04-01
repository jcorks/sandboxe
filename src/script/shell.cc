#include <sandboxe/script/shell.h>
#include <sandboxe/script/runtime.h>
#include <Dynacoe/Library.h>

class sandboxe_interpreter_command : public Dynacoe::Interpreter::Command {
  public:
      std::string operator()(const std::vector<std::string> & argvec) {
          std::string code;
          for(uint32_t i = 1; i < argvec.size(); ++i) {
              code += argvec[i] + " ";
          }
          return Sandboxe::Script::Runtime::Execute(code);
      }
      
      std::string Help() const {}
    
};


void Sandboxe::Script::Shell::Initialize() {
    Dynacoe::Console::AddCommand("js", new sandboxe_interpreter_command);
    Dynacoe::Console::Clear();
}