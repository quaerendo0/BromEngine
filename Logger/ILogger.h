#pragma once

#include <string>
#include <any>
#include <concepts>

namespace Log {

    enum LogLevel {
        Info,
        Warning,
        Error
    };

    class ILogger {
    public:

        virtual ~ILogger() = default;

        virtual void log(LogLevel logLevel, const std::string &data) const = 0;

        virtual void logInfo(const std::string &data) const = 0;

        virtual void logWarning(const std::string &data) const = 0;

        virtual void logError(const std::string &data) const = 0;
    };

    template<class T>
    concept StringLike =
    requires(T a) {
        {*a} -> std::convertible_to<std::string_view>;
    };

    template<class T>
    concept ConvetribleToString =
    requires(T a) {
        {std::to_string(*a)} -> std::same_as<std::string>;
    };

    template<StringLike T>
    void prettyLog(const std::string &collectionName, T begin, T end, const ILogger &logger, LogLevel level) {
        unsigned int count = 0;
        std::string out{};
        while (begin != end) {
            out += std::string(*begin) + "; ";
            count++;
            begin++;
        }
        out = collectionName + " (total " + std::to_string(count) + ") { " + out + " }";
        logger.log(level, out);
    }

    template<ConvetribleToString T>
    void prettyLog(const std::string &collectionName, T begin, T end, const ILogger &logger, LogLevel level) {
        unsigned int count = 0;
        std::string out{};
        while (begin != end) {
            out += std::to_string(*begin) + "; ";
            count++;
            begin++;
        }
        out = collectionName + " (total " + std::to_string(count) + ") { " + out + " }";
        logger.log(level, out);
    }
}