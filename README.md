# g2labs-message-bus
Simple C message bus

# Usage
Include the `<message_bus.h>` file for all of its API. Simply `register_listener()` with a specified callback, then `send_message()`. Somewhere in an event loop you should call `notify_listeners()`. The actual notification happens in turns - messages sent in one turn will be dispatched in another turn.

# Compile & Run
Just run `./build.sh`. The sample test code will be under `build/x64/platform/x64/` directory.

If you want to integrate this as a library to your existing code, run CMake and just add the project directory
through `add_subdirectory()` CMake command. Setting the `G2LABS_MESSAGE_BUS_PLATFORM` variable will add the `platform` specific subdirectory containing its own `main()` function.

# Author
&copy; 2022 G2Labs Grzegorz Grzęda