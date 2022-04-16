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
        connection = sdbus::createSessionBusConnection("com.github.jeysonflores.vault.daemon");
    } catch (std::exception& e) {
        LOG(ERROR, "Name already taken. Aborting...");
        exit(1);
    }

    LOG(SUCCESS, "Name requested successfully...");

    std::string db_path;
    if (std::getenv("VAULT_DATABASE_PATH"))
        db_path = std::getenv("VAULT_DATABASE_PATH");
    else {
        std::string file_path = "/.local/share/com.github.jeysonflores.vault.db";
        db_path = std::getenv("HOME") + file_path;
    }

    LOG(INFO, "Database path is: " + db_path);

    Vault::Daemon::Services::DataManager data_manager(db_path.c_str());

    Vault::Daemon::Interfaces::Note server(*connection, "/com/github/jeysonflores/vault/daemon/Note", data_manager);

    LOG(INFO, "Service Starting...");
    connection->enterEventLoop();
}