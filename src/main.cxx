#include "appconfig.h"
#include "appmanager.h"

#include <iostream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <stdexcept>

int main(int argc, char** argv)
{
    auto now = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(now);
    struct tm *localTime = localtime(&tt);
    char time_buffer_str[80];

    strftime(time_buffer_str, sizeof(time_buffer_str), "%Y-%m-%d %H:%M:%S", localTime);
    
    std::cout << "\nStarting " << std::filesystem::path(argv[0]).stem().string() 
        << " at " << time_buffer_str << std::endl;
    std::cout << "Version " << APP_VERSION_MAJOR << "."
              << APP_VERSION_MINOR << "." << APP_VERSION_PATCH << std::endl;
    
    bool all_good = true;
    AppManager* appmanager = new AppManager;

    try
    {
        all_good = !static_cast<bool>(appmanager->run());
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        all_good = false;
    }
    
    std::cout << "\nDone\n" << std::endl;
    return all_good ? EXIT_SUCCESS : EXIT_FAILURE;
}