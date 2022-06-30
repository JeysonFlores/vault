/*
* Copyright (c) 2022 Jeyson Antonio Flores Deras
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public
* License as published by the Free Software Foundation; either
* version 2 of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public
* License along with this program; if not, write to the
* Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
* Boston, MA 02110-1301 USA
*
* Authored by: Jeyson Antonio Flores Deras <jeyson.flores@protonmail.com>
*/

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