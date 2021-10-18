#include "Logging.hpp"

#include <iostream>

bool Logging::has_instance = false;

Logging & Logging::create(bool log_to_console, bool log_to_file, std::string filename)
{
    static Logging logging(log_to_console, log_to_file, filename);
    has_instance = true;

    return logging;
}

Logging::Logging(bool log_to_console, bool log_to_file, std::string filename)
{
    if (!has_instance)
    {
        this->log_to_console = log_to_console;
        this->log_to_file = log_to_file;
        this->filename = filename;

        if (log_to_file && !filename.empty())
        {
            file = fopen(filename.c_str(), "a");
            if (!file)
            {
                exit(EXIT_FAILURE);
            }
        }
    }
}

void Logging::log(std::string message)
{
    if (log_to_console)
    {
        std::cout << message << std::endl;
    }

    if (log_to_file)
    {
        fwrite(message.c_str(), 1, message.size(), file);
    }
}

Logging::~Logging()
{
    fclose(file);
}