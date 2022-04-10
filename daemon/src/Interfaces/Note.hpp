#pragma once

#include "../Adaptors/Note.hpp"
#include "../Utils/Logger.hpp"
#include <iostream>
#include <sdbus-c++/sdbus-c++.h>

INIT_LOGGER;

namespace Vault {
namespace Daemon {
    namespace Interfaces {

        class Note final : public sdbus::AdaptorInterfaces<Vault::Daemon::Adaptors::Note> {
        public:
            Note(sdbus::IConnection& connection, std::string objectPath);
            ~Note();

        private:
            virtual std::vector<sdbus::Struct<int32_t, std::string, std::string>> GetAll() override;
            virtual sdbus::Struct<int32_t, std::string, std::string> GetById(const int32_t& id) override;
            virtual bool Add(const std::string& note) override;
            virtual bool Update(const int32_t& id, const std::string& note) override;
            virtual bool Delete(const int32_t& id) override;
        };
    }
}
}