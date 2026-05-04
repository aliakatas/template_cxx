#include <iostream>
#include <filesystem>

int main(int argc, char** argv)
{
    bool errors_occured = false;
    std::cout << "\n Starting the application " << std::filesystem::path(argv[0]).stem() << "..." << std::endl;

    const int N = 1000;
    int i = 0;
    while (i < N)
    {
        std::cout << "\n Working..." << std::endl;
        ++i;
    }

    //----------------------------------------
    // Exit success/failure - more info in logs generated at runtime
    return errors_occured ? EXIT_FAILURE : EXIT_SUCCESS;
}
