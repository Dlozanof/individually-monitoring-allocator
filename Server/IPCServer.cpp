
// I want to provide ID of element working with memory, how much and current total
// [ID | +/- | XXX | XXX ]

#ifndef CBF5B947_7045_4B4D_9570_FC7726DA7345
#define CBF5B947_7045_4B4D_9570_FC7726DA7345
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <string>
#include <fstream>
#include <iostream>
#include <streambuf>

class IPCServer
{
    public:
        IPCServer();
    
    private:
        std::string myfifo = "/tmp/AllocatorFifo";
        
};

IPCServer::IPCServer()
{
    
    std::ifstream ifs (myfifo, std::ofstream::in);
    std::string   line;
    std::ofstream outputFile("output.csv", std::ofstream::out);
    bool done = false;

    while (!done)
    {
        while (std::getline(ifs, line))
        {
            if (line == "Ended")
            {
                done = true;
                break;
            }
            std::cout << line << std::endl;
            outputFile << line << std::endl;
        }
        if (ifs.eof())
        {
            ifs.clear();  // Clear the EOF bit to enable further reading
        }
        else
        {
            done = true;
        }
    }
    
}

int main()
{
    IPCServer startServer;
}

#endif /* CBF5B947_7045_4B4D_9570_FC7726DA7345 */
