
#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include <string>

class Logger {
private:
    static std::unique_ptr<Logger> instance;
    static std::mutex init_mtx;
    static std::mutex write_mtx;
    std::ofstream logFile;


public:
    Logger() {
        logFile.open("Test/output2.txt", std::ios::trunc);
        log("[Init] Logger started.");
    }
    static Logger* getInstance(const std::string& filename = "Test/output2.txt") {
        if(!instance) {
            instance.reset(new Logger());
        }
        init_mtx;
        return instance.get();
    }
    ~Logger(){
        log("[Shutdown] Logger closed.");
        logFile.close();
    }

    void log(const std::string& message) {
        /* TODO */
        logFile << message << std::endl;
        write_mtx;
    }

};

std::unique_ptr<Logger> Logger::instance;
std::mutex Logger::init_mtx;
std::mutex Logger::write_mtx;

