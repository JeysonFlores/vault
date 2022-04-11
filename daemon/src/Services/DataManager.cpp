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
                    "   date text"
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
sdbus::Struct<int32_t, std::string, std::string> Vault::Daemon::Services::DataManager::GetNoteById(int id)
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

/**
 * @brief Adds a new note to the database.
 * 
 * @param note 
 * @return int 
 */
std::tuple<int, std::string> Vault::Daemon::Services::DataManager::Add(std::string note)
{
    std::tuple<int, std::string> newData;
    std::string date;

    m_connection << "INSERT INTO notes (id, note, date) VALUES (NULL, ?, datetime('now'));"
                 << note;

    int id = m_connection.last_insert_rowid();

    m_connection << "SELECT date FROM notes WHERE id = ? ;"
                 << id
        >> [&](std::string _date) {
              date = _date;
          };

    newData = { id, date };

    return newData;
}

/**
 * @brief Updates a Note's information.
 * 
 * @param id 
 * @param note 
 */
void Vault::Daemon::Services::DataManager::Update(int id, std::string note)
{
    m_connection << "UPDATE notes SET note = ? WHERE id = ? ;"
                 << note
                 << id;
}

/**
 * @brief Deletes a Note from the database.
 * 
 * @param id 
 */
void Vault::Daemon::Services::DataManager::Remove(int id)
{
    m_connection << "DELETE FROM notes WHERE id = ? ;"
                 << id;
}

/**
 * @brief Check if a note exits according to the given id.
 * 
 * @param id 
 * @return true 
 * @return false 
 */
bool Vault::Daemon::Services::DataManager::Exists(int id)
{
    int rows = 0;

    m_connection << "SELECT COUNT(*) FROM notes WHERE id = ?;"
                 << id
        >> rows;

    return rows;
}