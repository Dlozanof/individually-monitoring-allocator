
// I want to provide ID of element working with memory, how much and current total
// [ID | +/- | XXX | XXX ]

#ifndef AF665DE1_3DEB_44D3_8FDF_D8725DDB519F
#define AF665DE1_3DEB_44D3_8FDF_D8725DDB519F
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <string>
#include <fstream>
#include <chrono>
#include "../IClient.h"

auto start = std::chrono::steady_clock::now();

class IPCClient : public IClient
{
    public:
        IPCClient();
        ~IPCClient();
        void NewData(std::string id, bool data, int local, int global);
    
    private:
        std::string myfifo = "/tmp/AllocatorFifo";
        
};

IPCClient::IPCClient()
{
    mkfifo(myfifo.c_str(), 0666);
}

void IPCClient::NewData(std::string id, bool data, int local, int global)
{
    auto now = std::chrono::steady_clock::now();
    auto timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(now - start).count();
    std::ofstream ofs (myfifo, std::ofstream::out);
    ofs << timestamp << "," << id << "," << data << "," << local << "," << global << "\n";
}

IPCClient::~IPCClient()
{
    std::ofstream ofs (myfifo, std::ofstream::out);
    ofs << "Ended";
}
#endif /* AF665DE1_3DEB_44D3_8FDF_D8725DDB519F */
