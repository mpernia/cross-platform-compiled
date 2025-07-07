#include "../includes/common.h"
#include "../includes/logger.h"
#include "../includes/build_info.h"
#include <iostream>
#include <string>
#include <csignal>

using namespace std;

#ifdef _WIN32
    #include <windows.h>
    bool shouldExit = false;
#else
    #include <mutex>
    #include <condition_variable>
    condition_variable exitSignal;
    mutex exitMutex;
    bool shouldExit = false;
#endif

void signalHandler(int signal)
{
    cout << "\nReceived signal " << signal << ", shutting down application..." << endl;
    shouldExit = true;
#ifndef _WIN32
    exitSignal.notify_one();
#endif
}

#ifndef _WIN32
void setupSignalHandlers()
{
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGPIPE, &sa, NULL);

    sa.sa_handler = signalHandler;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
}
#else
void setupSignalHandlers()
{
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
}
#endif

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--version" || arg == "-v") {
            cout << "Version: " << VERSION_STR << " (Build: " << BUILD_TIMESTAMP << ")" << endl;
            return 0;
        }
        else if (arg == "--help" || arg == "-h") {
            cout << "Usage: " << argv[0] << " [options]" << endl;
            cout << "Options:" << endl;
            cout << "  --help, -h     Show this help message" << endl;
            cout << "  --version, -v  Show application version" << endl;
            return 0;
        }
    }

    setupSignalHandlers();
    
    Logger::info("Starting cross-platform application");
    Logger::info("Platform: " + getPlatformName());
    Logger::info("Version: " + string(VERSION_STR));
    
    // Your initialization code here
    // ...
    
    Logger::info("Application started successfully. Press Ctrl+C to stop.");

    #ifdef _WIN32
        while (!shouldExit) {
            Sleep(100);
        }
    #else
        {
            unique_lock<mutex> lock(exitMutex);
            exitSignal.wait(lock, []{ return shouldExit; });
        }
    #endif
    
    Logger::info("Shutting down application...");
    
    // Your finalization code here
    // ...
    
    Logger::info("Application stopped successfully");
    
    return 0;
}
