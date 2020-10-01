cc_library(
    name = "individual-monitoring-allocator-IPC",
    srcs = [
        "CustomAllocator/allocator.h",
        "Comms/IPC/Client.cpp",
        "Comms/IPC/Client.h",
        "Comms/IClient.h"
    ],
    hdrs = ["CustomAllocator/allocator.h"],
)

cc_binary(
    name = "server-IPC",
    srcs = [
        "Server/IPCServer.cpp",
    ],
)

cc_binary(
    name = "test-allocator",
    srcs = [
        "main.cpp",
    ],
    deps = [":individual-monitoring-allocator-IPC"],
)