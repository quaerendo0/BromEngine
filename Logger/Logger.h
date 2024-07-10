#pragma once


#include "ILogger.h"

namespace Log {
    class Logger : public ILogger {
    public:
        void log(LogLevel logLevel, const std::string &data) const override;

        void logInfo(const std::string &data) const override;

        void logError(const std::string &data) const override;

        void logWarning(const std::string &data) const override;
    };
}
