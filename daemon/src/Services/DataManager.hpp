#pragma once

#include <sdbus-c++/sdbus-c++.h>
#include <sqlite_modern_cpp.h>
#include <vector>

namespace Vault {
namespace Daemon {
    namespace Services {
        class DataManager {
        public:
            DataManager(const char* databasePath);
            ~DataManager();

        private:
            sqlite::database m_connection;

        public:
            std::vector<sdbus::Struct<int32_t, std::string, std::string>> GetNotes();
            sdbus::Struct<int32_t, std::string, std::string> GetNoteById(int id);
            std::tuple<int, std::string> Add(std::string note);
            void Update(int id, std::string note);
            void Remove(int id);
            bool Exists(int id);
        };
    }
}
}