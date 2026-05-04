#include "appmanager.h"
#include "common_utils.h"
#include "build_version_utils.h"
#include "custom_exceptions.h"

#if __has_include("appconfig.h")
#include "appconfig.h"
#else
#define APP_NAME "example-project"
#define APP_VERSION_MAJOR 0
#define APP_VERSION_MINOR 0
#define APP_VERSION_PATCH 0
#endif // appconfig.h

#include <iostream>
#include <chrono>
#include <thread>
#include <filesystem>
#include <cmath>
#include <array>

// =====================================================
AppManager::AppManager(int argc, char** argv)
    : m_argc(argc), m_argv(argv)
{
#ifdef _DEBUG
    std::cout << __FUNCTION__ << " created " << std::endl;
#endif // _DEBUG
}

// =====================================================
AppManager::~AppManager()
{
#ifdef _DEBUG
    std::cout << __FUNCTION__ << " is being destroyed " << std::endl;
#endif // _DEBUG
}

// =====================================================
int AppManager::configure() noexcept(false)
{
    m_banner_message = _create_banner_message();

    try
    {
       m_cli_parser.parse(m_argc, m_argv, m_cli_input_summary); 
    }
    catch(const custom_exceptions::ShowVersionException& e)
    {
        std::string v = std::string(APP_NAME) + std::string(" version: ") + 
            _create_version_string() + std::string("\n");
        throw custom_exceptions::ShowVersionException(v);
    }
    
    std::cout << m_banner_message << std::endl;
    return 0;
}

// =====================================================
int AppManager::run() noexcept(false)
{
    std::cout << "Operating..." << std::endl;
    std::cout << "Started " << std::filesystem::path(m_argv[0]).stem().string() << " at: " << apputils::get_time_now() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    if (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) < 0.1f)
        throw std::runtime_error("Example error during runtime");

    std::cout << "All good!" << std::endl;

    if (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) < 0.1f)
        return 1;

    return 0;
}

// =====================================================
std::string AppManager::_create_banner_message()
{
    std::string start_time = apputils::get_time_now();
    
    std::string version_num = _create_version_string();
    
    std::string start_message = std::string("           ") + std::string(APP_NAME) + std::string(" ") + 
        version_num + std::string("\n");

    std::string compiler_info = std::string("Compiler: ") + build_info::get_compiler_info();
    std::string build_date = std::string("Build date: ") + build_info::get_build_date_time();
    std::string cuda_support = std::string("CUDA support: ") + build_info::get_nvidia_cuda_version();

    const std::array<int, 4> message_lengths = {
        static_cast<int>(start_message.length()), 
        static_cast<int>(compiler_info.length()), 
        static_cast<int>(build_date.length()), 
        static_cast<int>(cuda_support.length())
    };

    int nstars = *std::max_element(message_lengths.begin(), message_lengths.end()) + 1;
    std::string star_buffer;
    for (auto i = 0; i < nstars; ++i)
        star_buffer += std::string("*");
    star_buffer += std::string("\n");
    
    std::string banner_message = std::string("\n") + star_buffer + 
        start_message + std::string("\n") +
        compiler_info + std::string("\n") +
        build_date + std::string("\n") +
        cuda_support + std::string("\n") +
        star_buffer;

    return banner_message;
}

// =====================================================
std::string AppManager::_create_version_string()
{
    return std::to_string(APP_VERSION_MAJOR) + std::string(".") + 
        std::to_string(APP_VERSION_MINOR) + std::string(".") + std::to_string(APP_VERSION_PATCH);
}