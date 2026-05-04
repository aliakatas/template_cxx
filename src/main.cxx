#include "appmanager.h"

#include <cstdlib>
#include <iostream>

int main(int argc, char** argv)
{
    AppManager app_manager(argc, argv);
    int errors_occured = 0;
    
    try
    {
        app_manager.configure();
        errors_occured = app_manager.run();
    }
    catch (const std::exception& ex)
    {
        errors_occured = 1;
        std::cerr << "An error occurred: " << ex.what() << std::endl;
    }
    
    //----------------------------------------
    // Exit success/failure - more info in logs generated at runtime
    return errors_occured ? EXIT_FAILURE : EXIT_SUCCESS;
}
