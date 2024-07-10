//
// Created by Asus on 6/22/2024.
//

#include <iostream>
#include <chrono>
#include "Logger.h"

void Log::Logger::logInfo(const std::string &data) const {
    log(LogLevel::Info, data);
}

void Log::Logger::logError(const std::string &data) const {
    log(LogLevel::Error, data);
}

void Log::Logger::logWarning(const std::string &data) const {
    log(LogLevel::Warning, data);
}

void Log::Logger::log(LogLevel logLevel, const std::string &data) const {
    switch (logLevel) {
        case LogLevel::Info:
            std::cout << "[UTC " << std::chrono::utc_clock::now() << ']' << " (Info) : " << data << std::endl;
            break;
        case LogLevel::Warning:
            std::cout << "[UTC " << std::chrono::utc_clock::now() << ']' << " (Warning) : " << data << std::endl;
            break;
        case LogLevel::Error:
            std::cerr << "[UTC " << std::chrono::utc_clock::now() << ']' << " (Error) : " << data << std::endl;
            break;
    }
}
