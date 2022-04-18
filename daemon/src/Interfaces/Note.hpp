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

#include "../Adaptors/Note.hpp"
#include "../Services/DataManager.hpp"
#include "../Utils/Logger.hpp"
#include <iostream>
#include <sdbus-c++/sdbus-c++.h>

INIT_LOGGER;

namespace Vault {
namespace Daemon {
    namespace Interfaces {

        class Note final : public sdbus::AdaptorInterfaces<Vault::Daemon::Adaptors::Note> {
        public:
            Note(sdbus::IConnection& connection, std::string object_path, Vault::Daemon::Services::DataManager dbm);
            ~Note();

        private:
            virtual std::vector<sdbus::Struct<int32_t, std::string, std::string>> get_all() override;
            virtual sdbus::Struct<int32_t, std::string, std::string> get_by_id(const int32_t& id) override;
            virtual bool add(const std::string& note, const std::string& date) override;
            virtual bool update(const int32_t& id, const std::string& note, const std::string& date) override;
            virtual bool remove(const int32_t& id) override;

        private:
            Vault::Daemon::Services::DataManager m_db_manager;
        };
    }
}
}