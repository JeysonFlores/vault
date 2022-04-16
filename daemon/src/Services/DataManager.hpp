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