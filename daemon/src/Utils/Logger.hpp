#pragma once

#include <iomanip>
#include <iostream>

#define INIT_LOGGER         \
    using namespace Logger; \
    using Logger::LoggerLevel;

namespace Logger {

enum LoggerLevel {
    ALERT,
    ERROR,
    INFO,
    SUCCESS,
    WARNING
};

void LOG(Logger::LoggerLevel level, const std::string& message);

}