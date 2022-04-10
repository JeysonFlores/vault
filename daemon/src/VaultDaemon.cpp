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
    auto connection = sdbus::createSessionBusConnection("com.github.jeysonflores.vault.daemon");

    LOG(SUCCESS, "Name requested successfully...");

    std::string env_p;
    if (std::getenv("XPRESSR_CONFIG_FLATPAK"))
        env_p = std::getenv("XPRESSR_CONFIG_FLATPAK");
    else {
        std::string db_path = "/.local/share/com.github.jeysonflores.vault.db";
        env_p = std::getenv("HOME") + db_path;
    }

    std::cout << "Database path is: " << env_p << '\n';

    //XpressrService::Services::DataManager dataManager(env_p.c_str());

    Vault::Daemon::Interfaces::Note server(*connection, "/com/github/jeysonflores/vault/daemon/Note");

    LOG(INFO, "Service Starting...");
    connection->enterEventLoop();
}