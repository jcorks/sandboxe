#include <Dynacoe/Library.h>


namespace Sandboxe {
namespace Script {


// the script object handles: 
// basic console IO for debugging
// error reporting and forwarding
class Terminal : public Dynacoe::Entity {
  public:
    
    
    void ReportError(const std::string & str) {
        Dynacoe::Console::Error() << "Sandboxe Error:\n" << str << "\n";
        
    }
    
    
    
    
};
    
    
}
}