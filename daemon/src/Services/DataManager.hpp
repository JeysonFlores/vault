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

#pragma once

#include <sdbus-c++/sdbus-c++.h>
#include <sqlite_modern_cpp.h>
#include <vector>

namespace Vault {
namespace Daemon {
    namespace Services {
        class DataManager {
        public:
            DataManager(const char* database_path);
            ~DataManager();

        private:
            sqlite::database m_connection;

        public:
            std::vector<sdbus::Struct<int32_t, std::string, std::string>> get_notes();
            sdbus::Struct<int32_t, std::string, std::string> get_note_by_id(int id);
            int add(std::string note, std::string date);
            void update(int id, std::string note);
            void remove(int id);
            bool exists(int id);
        };
    }
}
}