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

#include "Interfaces/Note.hpp"
#include "Services/DataManager.hpp"
#include "Utils/Logger.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <type_traits>

INIT_LOGGER;

int main(int /*argc*/, char* /*argv*/[])
{
    std::unique_ptr<sdbus::IConnection> connection;

    try {
        connection = sdbus::createSessionBusConnection("com.github.jeysonflores.vault.Daemon");
    } catch (std::exception& e) {
        LOG(ERROR, "Name already taken. Aborting...");
        exit(1);
    }

    LOG(SUCCESS, "Name requested successfully...");

    std::string db_path;
    if (std::getenv("VAULT_DATABASE_PATH"))
        db_path = std::getenv("VAULT_DATABASE_PATH") + std::string("com.github.jeysonflores.vault.db");
    else {
        std::string file_path = "/.local/share/com.github.jeysonflores.vault.db";
        db_path = std::getenv("HOME") + file_path;
    }

    LOG(INFO, "Database path is: " + db_path);

    Vault::Daemon::Services::DataManager data_manager(db_path.c_str());

    Vault::Daemon::Interfaces::Note server(*connection, "/com/github/jeysonflores/vault/Daemon/Note", data_manager);

    LOG(INFO, "Service Starting...");
    connection->enterEventLoop();
}