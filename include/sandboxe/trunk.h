#ifndef h_sandboxe_trunk_included
#define h_sandboxe_trunk_included
#include <string>
#include <vector>
namespace Sandboxe {
namespace Trunk {
    
void Initialize(const char * sourceName);
    
// Stages the given file for a trunk commit.
void Stage(const std::string & filePath);

// Removes the given file from staging
void Remove(const std::string & filePath);

// Commits all staged files in the trunk to a new version of 
// the executables where each file is included inline.
std::string Commit(const std::string & outputPath);

// Queries all staged files.
std::vector<std::string> Query();

// Removes all staged files
void Clear();





// returns whether the given item is within this executables trunk
bool ItemExists(const std::string & item);

// returns the given item's raw data
const std::vector<uint8_t> & ItemGet(const std::string & item);

// adds an item as if it were read from the real trunk
void AddItem(const std::string & name, const std::vector<uint8_t> & data);

// returns the number of known items
uint32_t ItemCount();

// returns the accessible names of all items stored
std::vector<std::string> GetItemNames();
    
}    
}


#endif