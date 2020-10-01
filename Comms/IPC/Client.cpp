#include "Client.h"

IPCClient myClient;

auto start = std::chrono::steady_clock::now();

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