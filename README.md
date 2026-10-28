# keyple-plugin-storagecard-cpp-api

## Overview

The **Keyple Plugin Storage Card** C++ API is dedicated to the development of Keyple plugins supporting
contactless storage cards (e.g. NXP Mifare Ultralight, NXP Mifare Classic, STMicroelectronics ST25/SRT512).

This library **should not be imported explicitly** by the main application.

## User Guide & Download Information

The full documentation, including download information is available in the **Documentation** section of the
official Keyple website [keyple.org](https://keyple.org)

## Build the Code

The code is built with CMake and dependencies (GoogleTest) are resolved via CMake's `FetchContent`, downloaded at
configure time. A toolchain file is required for every build; see `toolchain/` for the profiles used in CI
(`gcc-linux`, `clang-macos`, `clang-windows`, etc.), for example:

```bash
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain/clang-macos.cmake
cmake --build .
./bin/keypluginstoragecardcppapi_ut
```

## Code Contributions

We welcome code contributions through merge requests.
