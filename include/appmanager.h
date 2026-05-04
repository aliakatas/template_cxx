#pragma once

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
    int m_argc;
    char** m_argv;
    std::string m_banner_message;

    std::string _create_banner_message();
};
