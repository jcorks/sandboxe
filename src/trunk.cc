#include <sandboxe/trunk.h>
#include <map>
#include <set>
#include <cstring>
#include <cstdio>
#include <Dynacoe/Library.h>
class TrunkImporter;
static std::set<std::string> files;
TrunkImporter * imported = nullptr;;
const int trunk_tag_size_c = 128;
const char * trunk_tag_plaintext_key_c = "|S|A|N|D|B|O|X|E|T|R|U|N|K|JLC18|";
const int trunk_implementation_version_minor = 1;
const int trunk_implementation_version_major = 0;
static std::string path_to_source_executable;

class TrunkImporter {
  public:
    TrunkImporter() {
        std::vector<uint8_t> trunk;
        std::vector<uint8_t> srcBinary;
        std::vector<uint8_t> footer;

        
        ReadSelf(&srcBinary, &trunk, &footer);
        if(!trunk.size()) return;
        
        // next go to the registry footer section and use that 
        // info to populate each item
        Dynacoe::InputBuffer footerBuffer;
        footerBuffer.OpenBuffer(footer); 
        uint32_t numItems = footerBuffer.Read<uint32_t>();
        uint32_t current;
        for(uint32_t i = 0; i < numItems; ++i) {
            if (footerBuffer.ReachedEnd()) break;
            
            
            uint32_t nameLen = footerBuffer.Read<uint32_t>();
            std::string name = footerBuffer.ReadString(nameLen);
            
            uint32_t offset = footerBuffer.Read<uint32_t>();
            uint32_t size = footerBuffer.Read<uint32_t>();
            current = footerBuffer.Size() - footerBuffer.BytesLeft();
            
            

            std::vector<uint8_t> * ref = &sections[name];
            ref->resize(size);
            memcpy(
                &(*ref)[0],
                &trunk[offset],
                size
            );
            footerBuffer.GoToByte(current);
        }
        
        
    }
    
    
    void ReadSelf(std::vector<uint8_t> * srcBinary, std::vector<uint8_t> * trunk, std::vector<uint8_t> * footer) {
        
        
        // first, load existing trunk
        Dynacoe::InputBuffer in;
        in.Open(path_to_source_executable);
        if (in.Size() <= trunk_tag_size_c) return;
        in.GoToByte(in.Size() - trunk_tag_size_c);
        std::string tag = in.ReadString(trunk_tag_size_c);

        
        
        // take apart the tag for more info
        int versionMinor = -1;
        int versionMajor = -1;
        uint32_t footerBegin = 0;
        uint32_t trunkSize = 0;
        char key[trunk_tag_size_c];
        
        sscanf(
            tag.c_str(), 
            "%s %d %d %d %d",
            key,
            &versionMinor,
            &versionMajor,
            &footerBegin,
            &trunkSize
        );
        
        if (srcBinary) {
            in.GoToByte(0);
            *srcBinary = in.ReadBytes(in.Size() - trunkSize);
        }
            
        
        if (!strstr(key, trunk_tag_plaintext_key_c)) {
            // error! either no trunk or trunk tag is corrupt / could not be read
            return;
        }
        
        
        if (versionMajor != trunk_implementation_version_major) {
            // uh oh, cant support it yet
            return;
        }
        
        

        if (trunk) {
            in.GoToByte(in.Size() - trunkSize);
            *trunk = in.ReadBytes(trunkSize);
        } 

        if (footer) {
            in.GoToByte(in.Size() - footerBegin);
            *footer = in.ReadBytes(trunkSize);
        }
    }
    
    bool ItemExists(const std::string & name) const {
        return sections.find(name) != sections.end();
    }
    
    std::vector<std::string> ListItems() const {
        std::vector<std::string> items;
        for(auto i = sections.begin(); i != sections.end(); ++i) {
            items.push_back(i->first);
        }
        return items;
    }
    
    uint32_t ItemCount() const {
        return sections.size();
    }
    
    const std::vector<uint8_t> & GetItem(const std::string & name) const {
        if (!ItemExists(name)) {
            static std::vector<uint8_t> error;
            return error = {};
        }
        return sections.find(name)->second;
    }
    
  private:
    std::map<std::string, std::vector<uint8_t>> sections;
    
};


// assist in trunk exportation 
class TrunkExporter {
  public:

    void PushItem(const std::string & name, const std::vector<uint8_t> & in) {
        offsets.push_back(data.size());
        sizes.push_back(in.size());
        uint32_t oldSize = data.size();
        data.resize(data.size() + in.size());
        memcpy(&data[oldSize], &in[0], in.size());
        names.push_back(name);
    }
    
    void Export(const std::string & outName) {
        Dynacoe::OutputBuffer out;
        
        // first, copy this executable
        std::vector<uint8_t> binary;
        imported->ReadSelf(&binary, nullptr, nullptr);
        out.WriteBytes(binary);
        
        // then the existing itme section of the trunk
        out.WriteBytes(data);




        uint32_t beginOfFooter = out.Size();
        // write footer
        //format:
        // number of items, uint32,
        // then for each item:
        //  uint32_t namelen, std::string name, uint32_t offset, uint32_t size 
        
        out.Write<uint32_t>(names.size());
        for(uint32_t i = 0; i < offsets.size(); ++i) {
            out.Write<uint32_t>(names[i].size());
            out.WriteString(names[i]);
            out.Write<uint32_t>(offsets[i]);
            out.Write<uint32_t>(sizes[i]);
        }
        
        out.WriteString(
            GenerateTag(
                (out.Size()+trunk_tag_size_c) - beginOfFooter,
                out.Size()-binary.size()
            )
        );
        out.CommitToFile(outName, false);
    }
    
    
    std::string GenerateTag(uint32_t startOfFooterFromEnd, uint32_t size) {
        
        // tag format:
        // [parity string] [minor version] [major version] [byte of footer from end] [size of the trunk]
        char tagSrc[trunk_tag_size_c]; tagSrc[0] = 0;
        sprintf(
            tagSrc, "%s %d %d %d %d",
            trunk_tag_plaintext_key_c,
            trunk_implementation_version_minor,
            trunk_implementation_version_major,
            startOfFooterFromEnd, 
            size + trunk_tag_size_c
        );
        std::string s = std::string(tagSrc);
        while(s.length() != trunk_tag_size_c)
            s+='~';
        
        return s;
    }
    
  private:
    std::vector<std::string> names;
    std::vector<uint32_t> offsets;
    std::vector<uint32_t> sizes;
    std::vector<uint8_t> data;
        
};









void Sandboxe::Trunk::Initialize(const char * sourceName) {
    path_to_source_executable = sourceName;
    imported = new TrunkImporter;
}

void Sandboxe::Trunk::Stage(const std::string & path) {
    files.insert(path);
}

void Sandboxe::Trunk::Remove(const std::string & path) {
    auto it = files.find(path);
    if (it == files.end()) return;
    files.erase(it);
}


std::string Sandboxe::Trunk::Commit(const std::string & output) {
    TrunkExporter exporter;
    for(auto it = files.begin(); it != files.end(); ++it) {
        Dynacoe::InputBuffer buffer;
        buffer.Open(*it);
        if (buffer.Size() == 0) {
            return Dynacoe::Chain() << "Error committing trunk: " << *it << " could not be accessed or is empty.";
        }
        
        exporter.PushItem(*it, buffer.ReadBytes(buffer.Size()));
    }
    exporter.Export(output);
    return "";
}

std::vector<std::string> Sandboxe::Trunk::Query() {
    std::vector<std::string> out;
    for(auto i = files.begin(); i != files.end(); ++i) {
        out.push_back(*i);
    }
    return out;
}

void Sandboxe::Trunk::Clear() {
    files.clear();
}



bool Sandboxe::Trunk::ItemExists(const std::string & item) {
    return imported->ItemExists(item);
}

const std::vector<uint8_t> & Sandboxe::Trunk::ItemGet(const std::string & item) {
    return imported->GetItem(item);
}

uint32_t Sandboxe::Trunk::ItemCount() {
    return imported->ItemCount();
}


