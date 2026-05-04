#pragma once

#include <appcliparser.h>

#include <string>

class AppManager
{
public:
    AppManager(int argc, char** argv);

    ~AppManager();

    AppManager(const AppManager&) = delete;
    AppManager& operator=(const AppManager&) = delete;
    AppManager(AppManager&&) = delete;

    int configure() noexcept(false);

    int run() noexcept(false);

private:
    //  Variables
    int m_argc;
    char** m_argv;
    std::string m_banner_message;
    std::string m_cli_input_summary;
    AppCliParser m_cli_parser;

    // Methods
    std::string _create_banner_message();
    std::string _create_version_string();
};
