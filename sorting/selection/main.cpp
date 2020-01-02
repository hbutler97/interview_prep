#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>
#include <vector>
#include "tclap/CmdLine.h"
#include "RANDOM_GENERATOR.h"
#include "SORTER.h"


int main(int argc, char* argv[]) {
    try {
        std::unique_ptr<TCLAP::CmdLine> cmd = std::make_unique<TCLAP::CmdLine>("Usage", ' ', "1.0");
        TCLAP::ValueArg<uint32_t>  size("s","size","Size of input array",
                                        true,1,"Integer",*cmd,nullptr);
        TCLAP::ValueArg<std::string>  algorithm("a","algorithm","Name of sorting algorithm",
                                                true,"","String",*cmd,nullptr);
        cmd->parse( argc, argv );

        std::vector<uint32_t> buffer(size.getValue());
        RANDOM_GENERATOR random_number(1,size.getValue());

        for(std::size_t i = 0; i<size.getValue(); i++)
            buffer[i] = random_number.getNumber();
        
        SORTER_SELECTOR sorter;
        sorter.sort(algorithm.getValue(),buffer);
        std::string result = (sorter.checkSorted(buffer))?"PASS":"FAIL";
        std::cout << result << std::endl;
    }
    catch (TCLAP::ArgException &e)
    { std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; return EXIT_FAILURE;}
    catch (std::exception& e)
    { std::cerr << "std::exception caught: " << e.what() << std::endl; return EXIT_FAILURE;}
    catch(SORT_EXCEPT& e)
    { std::cerr << "SORTER exception caught: " << e.getMessage() << std::endl; return EXIT_FAILURE;}
    catch(...)
    { std::cerr << "Unhandled Exception" << std::endl; return EXIT_FAILURE;}
    return EXIT_SUCCESS;
}
