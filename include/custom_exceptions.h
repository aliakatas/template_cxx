#include <stdexcept>

namespace custom_exceptions
{
    class ShowHelpException : public std::runtime_error
    {
    public:
        explicit ShowHelpException(const std::string& message)
            : std::runtime_error(message) {}
    };

    class ShowVersionException : public std::runtime_error
    {
    public:
        explicit ShowVersionException(const std::string& message)
            : std::runtime_error(message) {}
    };
}