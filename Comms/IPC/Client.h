// I want to provide ID of element working with memory, how much and current total
// [ID | +/- | XXX | XXX ]

#ifndef COMMS_IPC_CLIENT
#define COMMS_IPC_CLIENT
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <string>
#include <fstream>
#include <chrono>

class IPCClient
{
    public:
        IPCClient();
        ~IPCClient();
        void NewData(std::string id, bool data, int local, int global);
    
    private:
        std::string myfifo = "/tmp/AllocatorFifo";
        
};


#endif /* COMMS_IPC_CLIENT */
