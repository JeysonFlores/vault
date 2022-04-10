#include "Logger.hpp"

void Logger::LOG(Logger::LoggerLevel level, const std::string& message)
{
    std::time_t t = std::time(nullptr);
    std::tm time = *std::localtime(&t);
    std::string code = "";

    switch (level) {
    case (Logger::LoggerLevel::ALERT):
        code = "\u001b[31;1mALERT\u001b[0m";
        break;
    case (Logger::LoggerLevel::ERROR):
        code = "\u001b[31mERROR\u001b[0m";
        break;
    case (Logger::LoggerLevel::INFO):
        code = "\u001b[36mINFO\u001b[0m";
        break;
    case (Logger::LoggerLevel::SUCCESS):
        code = "\u001b[32mSUCCESS\u001b[0m";
        break;
    case (Logger::LoggerLevel::WARNING):
        code = "\u001b[33mWARNING\u001b[0m";
        break;
    default:
        code = "\u001b[30;1mNO SPECIFIED\u001b[0m";
    }

    std::cout << "\u001b[33;1m[" << std::put_time(&time, "%c %Z") << "]\u001b[0m - " << code << " - " << message << "\n";
}