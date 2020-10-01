# individually-monitoring-allocator
C++ Custom Allocator for monitoring individual elements

# Basic usage
If you are using bazel, add this to your WORKSPACE:

```
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
  name = "individually-monitoring-allocator",
  branch = "main",
  remote = "https://github.com/Dlozanof/individually-monitoring-allocator.git",
)
```

And then you can just add dependencies to the kind of allocator you want:
```
deps = ["@individually-monitoring-allocator//:individual-monitoring-allocator-IPC"],
```

From this point you can use it by including "CustomAllocator/allocator.h" to your code:

```c++
// file main.cpp
#include "CustomAllocator/allocator.h"
#include <vector>
#include <iostream>
#include <string>
#include <scoped_allocator>

int main()
{
    VECTOR(int, myVector)
    myVector.push_back(2)
}
```