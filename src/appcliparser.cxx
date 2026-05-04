#include "appcliparser.h"
#include "custom_exceptions.h"

#include <string>
#include <vector>
#include <sstream>

// =======================================================
AppCliParser::AppCliParser()
    : desc_("Allowed options")
{
}

// =======================================================
void AppCliParser::parse(int argc, char** argv, std::string& s)
{
    int opt;
    bpo::options_description desc("Valid options");
    desc.add_options()
        ("help,h", "produce help message")
        ("version,v", "print version string")
        ("compression,c", bpo::value<int>(), "set compression level")
        ("optimisation,o", bpo::value<int>(&opt)->default_value(10), "optimisation level")
        ("include-path,I", bpo::value<std::vector<std::string>>(), "include path")
        ("input-file", bpo::value<std::vector<std::string>>(), "input file")
    ;

    bpo::positional_options_description p;
    p.add("input-file", -1);

    bpo::store(bpo::command_line_parser(argc, argv).options(desc).positional(p).run(), vm_);
    bpo::notify(vm_);

    if (vm_.count("help")) 
    {
        std::ostringstream oss;
        oss << desc;
        throw custom_exceptions::ShowHelpException(oss.str());
    }

    if (vm_.count("version")) 
    {
        throw custom_exceptions::ShowVersionException("Show version");
    }

    if (vm_.count("compression")) 
        s += std::string("Compression level was set to ") + std::to_string(vm_["compression"].as<int>()) + std::string(".\n");
    else 
        s += std::string("Compression level was not set.\n");

    if (vm_.count("include-path"))
    {
        s += std::string("Include paths are: \n"); 
        for (auto& incp : vm_["include-path"].as<std::vector<std::string>>())
            s += std::string("  ") + incp + std::string("\n");
    }

    if (vm_.count("input-file"))
    {
        s += std::string("Input files are: \n");
        for (auto& inpf : vm_["input-file"].as<std::vector<std::string>>())
            s += std::string("  ") + inpf + std::string("\n");
    }

    s += std::string("Optimization level is ") + std::to_string(opt) + std::string("\n"); 
}

