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