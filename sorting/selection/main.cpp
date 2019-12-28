#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>
#include "tclap/CmdLine.h"
#include "RANDOM_GENERATOR.h"
#include "SORTER.h"

int main(int argc, char* argv[]) {

    std::unique_ptr<TCLAP::CmdLine> cmd = std::make_unique<TCLAP::CmdLine>("Usage", ' ', "1.0");
    TCLAP::ValueArg<uint32_t>  size("s","size","Size of input array",
                                     true,1,"Integer",*cmd,NULL);
    cmd->parse( argc, argv );
    std::vector<uint32_t> buffer(size.getValue());
    RANDOM_GENERATOR random_number(1,size.getValue());
    for(std::size_t i = 0; i<size.getValue(); i++)
        buffer[i] = random_number.getNumber();

    SORTER sorter;
    sorter.sort(buffer);

    std::string result = (sorter.checkSorted(buffer))?"PASS":"FAIL";
    std::cout << result << std::endl;
    return EXIT_SUCCESS;
}
