#include "Executable.h"

int main(int argc,  char **argv)
{
    if(argc>1)
    {
        std::string filename=argv[1];

        Executable executable(filename);
    }
    else
    {
        std::cout << "No executable provided."<< std::endl;
    }

    return 0;
}
