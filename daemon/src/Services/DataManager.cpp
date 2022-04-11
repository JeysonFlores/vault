#include "DataManager.hpp"

/**
 * @brief Construct a new Vault::Daemon::Services::Data Manager::DataManager object
 * 
 * @param databasePath 
 */
Vault::Daemon::Services::DataManager::DataManager(const char* databasePath)
    : m_connection(sqlite::database(databasePath))
{
    m_connection << "CREATE table IF NOT EXISTS notes ("
                    "   id integer primary key autoincrement not null,"
                    "   note text,"
                    "   date date"
                    ");";
}

/**
 * @brief Destroy the Vault::Daemon::Services::Data Manager::DataManager object
 * 
 */
Vault::Daemon::Services::DataManager::~DataManager()
{
}

/**
 * @brief Returns all the notes inside the database.
 * 
 * @return std::vector<sdbus::Struct<int32_t, std::string, std::string>> 
 */
std::vector<sdbus::Struct<int32_t, std::string, std::string>> Vault::Daemon::Services::DataManager::GetNotes()
{
    std::vector<sdbus::Struct<int32_t, std::string, std::string>> result;

    m_connection << "SELECT id, note, date FROM notes ;"
        >> [&](int32_t id, std::string note, std::string date) {
              sdbus::Struct<int32_t, std::string, std::string> row = { id, note, date };
              result.push_back(row);
          };

    return result;
}

/**
 * @brief Returns a Note with a specified id.
 * 
 * @param id 
 * @return sdbus::Struct<int32_t, std::string, std::string> 
 */
sdbus::Struct<int32_t, std::string, std::string> Vault::Daemon::Services::DataManager::GetNoteById(int& id)
{
    sdbus::Struct<int32_t, std::string, std::string> queriedNote;

    m_connection << "SELECT id, note, date FROM notes WHERE id = ? ;"
                 << id
        >> [&](int32_t _id, std::string note, std::string date) {
              std::get<0>(queriedNote) = _id;
              std::get<1>(queriedNote) = note;
              std::get<2>(queriedNote) = date;
          };

    return queriedNote;
}