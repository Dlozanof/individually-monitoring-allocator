cc_library(
    name = "individual-monitoring-allocator-IPC",
    srcs = [
        "Comms/IClient.h",
        "Comms/IPC/Client.cpp",
        "Comms/IPC/Client.h",
        "CustomAllocator/allocator.h",
    ],
    hdrs = ["CustomAllocator/allocator.h"],
    visibility = ["//visibility:public"],
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
