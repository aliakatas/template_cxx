#pragma once

#include "get_os_error.h"

#ifdef _WIN32 || _WIN64 
#include <windows.h>
#define Dlopen(name, flags) LoadLibraryA(name)
#define Dlclose FreeLibrary
#define Dlerror GetLastError
#else if __linux__
#include <dlfcn.h>
#define Dlopen(name, flags) dlopen(name, flags)
#define Dlclose dlclose
#define Dlerror dlerror
#endif

#include <stdexcept>
#include <string>

/**
 * @brief Cross-platform loader for dynamic libraries.
*/
template <typename T>
class DynLibLoader
{
private:
    void* p_lib_handle;
    std::string m_libname;
    int m_load_options;
public:

    /**
     * @brief Loads the dynamic library in memory.
     * 
     * @param libname [in]
     * @param load_options [in] Ignored for Windows.
    */
    explicit DynLibLoader(const char* libname, const int load_options) noexcept :
        m_libname(libname),
        m_load_options(load_options)
    {}

    /**
     * @brief Loads the dynamic library in memory.
     * 
     * @param libname [in]
     * @param load_options [in] Ignored for Windows.
    */
    explicit DynLibLoader(const std::string& libname, const int load_options) noexcept :
        m_libname(libname),
        m_load_options(load_options)
    {}

    /**
     * @brief Releases the handle to the library.
    */
    ~DynLibLoader() noexcept
    {   
        if (p_lib_handle != nullptr)
        {
            Dlclose(p_lib_handle);
            p_lib_handle = nullptr;
        }
    }

    /**
     * @brief Deleted copy constructor and copy assignment operator to prevent copying of the loader.
    */
    DynLibLoader(const DynLibLoader&) = delete;
    DynLibLoader& operator=(const DynLibLoader&) = delete;

    /**
     * @brief Move constructor and move assignment operator to allow moving of the loader.
    */
    DynLibLoader(DynLibLoader&& other) noexcept :
        p_lib_handle(other.p_lib_handle),
        m_libname(std::move(other.m_libname)),
        m_load_options(other.m_load_options)
    {
        other.p_lib_handle = nullptr; // Prevent the moved-from object from closing the library
    }

    /**
     * @brief Loads the dynamic library in memory. 
     * 
     * @throws std::runtime_error if loading fails.
    */
    void Load()
    {
        p_lib_handle = Dlopen(m_libname.c_str(), m_load_options);
        if (p_lib_handle == nullptr)
        {   // Error handling for loading the library
            std::string message = std::string("Failed to open library: ") + m_libname + std::string(" (");

            std::string what_happened = get_os_error();

            message += what_happened + std::string(")");

            throw std::runtime_error(message);
        }
    }

    /**
     * @brief Returns the handle to the dynamic library.
     * 
     * @throws std::runtime_error if the library has not been loaded yet.
    */
    void* Handle() const noexcept(false)
    {
        if (p_lib_handle == nullptr)
        {
            throw std::runtime_error("Library not loaded. Call Load() before accessing the handle.");
        }
        return p_lib_handle;
    }

    /** 
     * @brief Get the name of the library being loaded. 
    */
    const std::string& LibraryName() const noexcept
    {
        return m_libname;
    }

};

