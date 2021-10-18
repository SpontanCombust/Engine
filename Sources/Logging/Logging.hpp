#include <cstdio>
#include <string>

class Logging
{
public:
    static Logging & create(bool log_to_console = true, bool log_to_file = true, std::string filename = "Engine.log");
    void log(std::string message);
    ~Logging();


private:
    Logging(bool log_to_console, bool log_to_file, std::string filename);
    
    bool log_to_console;
    bool log_to_file;
    std::string filename;
    FILE * file;

    static bool has_instance;
};