#include "appconfig.h"
#include "appmanager.h"

#include "boost/program_options/options_description.hpp"
#include "boost/program_options/variables_map.hpp"
#include "boost/program_options/parsers.hpp"

#include <iostream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <stdexcept>

namespace bpo = boost::program_options;

int main(int argc, char** argv)
{
    //----------------------------------------
    // Start with some information...
    auto now = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(now);
    struct tm *localTime = localtime(&tt);
    char time_buffer_str[80];

    strftime(time_buffer_str, sizeof(time_buffer_str), "%Y-%m-%d %H:%M:%S", localTime);
    
    std::cout << "\nStarting " << std::filesystem::path(argv[0]).stem().string() 
        << " at " << time_buffer_str << std::endl;
    std::cout << "Version " << APP_VERSION_MAJOR << "."
              << APP_VERSION_MINOR << "." << APP_VERSION_PATCH << std::endl;

    //----------------------------------------
    // Declare the supported options for the command line
    bpo::options_description desc("Valid options");
    desc.add_options()
        ("help", "produce help message")
        ("compression", bpo::value<int>(), "set compression level")
    ;
    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);    

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return EXIT_FAILURE;
    }

    if (vm.count("compression")) 
        std::cout << "Compression level was set to " << vm["compression"].as<int>() << ".\n";
    else 
        std::cout << "Compression level was not set.\n";
    
    //----------------------------------------
    // Start work...
    bool all_good = true;
    AppManager* appmanager = new AppManager;

    try
    {
        all_good = !static_cast<bool>(appmanager->run());
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << "\n" << std::endl;
        all_good = false;
    }
    
    if (all_good)
        std::cout << "\nDone\n" << std::endl;

    //----------------------------------------
    // Exit success/failure - more info in logs generated at runtime
    return all_good ? EXIT_SUCCESS : EXIT_FAILURE;
}