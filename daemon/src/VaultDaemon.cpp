#include "Interfaces/Note.hpp"
//#include "Services/DataManager.h"
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

    std::string dbPath;
    if (std::getenv("VAULT_DATABASE_PATH"))
        dbPath = std::getenv("VAULT_DATABASE_PATH");
    else {
        std::string filePath = "/.local/share/com.github.jeysonflores.vault.db";
        dbPath = std::getenv("HOME") + filePath;
    }

    LOG(INFO, "Database path is: " + dbPath);

    //XpressrService::Services::DataManager dataManager(dbPath.c_str());

    Vault::Daemon::Interfaces::Note server(*connection, "/com/github/jeysonflores/vault/daemon/Note");

    LOG(INFO, "Service Starting...");
    connection->enterEventLoop();
}