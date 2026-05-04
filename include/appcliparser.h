#include "boost/program_options/options_description.hpp"
#include "boost/program_options/variables_map.hpp"
#include "boost/program_options/parsers.hpp"
#include "boost/program_options/positional_options.hpp"

#include <string>

namespace bpo = boost::program_options;

class AppCliParser
{
public:
    AppCliParser();
    void parse(int argc, char** argv,std::string& s);
    const bpo::variables_map& get_variables_map() const;
private:

    bpo::options_description desc_;
    bpo::variables_map vm_;
};