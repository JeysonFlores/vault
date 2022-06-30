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

#include "DataManager.hpp"

/**
 * @brief Construct a new Vault::Core::Services::Data Manager::DataManager object
 * 
 * @param database_path 
 */
Vault::Core::Services::DataManager::DataManager(const char* database_path)
    : m_connection(sqlite::database(database_path))
{
    m_connection << "CREATE table IF NOT EXISTS notes ("
                    "   id integer primary key autoincrement not null,"
                    "   note text,"
                    "   date text"
                    ");";
}

/**
 * @brief Destroy the Vault::Core::Services::Data Manager::DataManager object
 * 
 */
Vault::Core::Services::DataManager::~DataManager()
{
}

/**
 * @brief Returns all the notes inside the database.
 * 
 * @return std::vector<sdbus::Struct<int32_t, std::string, std::string>> 
 */
std::vector<sdbus::Struct<int32_t, std::string, std::string>> Vault::Core::Services::DataManager::get_notes()
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
sdbus::Struct<int32_t, std::string, std::string> Vault::Core::Services::DataManager::get_note_by_id(int id)
{
    sdbus::Struct<int32_t, std::string, std::string> queried_note;

    m_connection << "SELECT id, note, date FROM notes WHERE id = ? ;"
                 << id
        >> [&](int32_t _id, std::string note, std::string date) {
              std::get<0>(queried_note) = _id;
              std::get<1>(queried_note) = note;
              std::get<2>(queried_note) = date;
          };

    return queried_note;
}

/**
 * @brief Adds a new note to the database.
 * 
 * @param note 
 * @param date
 * @return int 
 */
int Vault::Core::Services::DataManager::add(std::string note, std::string date)
{
    m_connection << "INSERT INTO notes (id, note, date) VALUES (NULL, ?, ?);"
                 << note
                 << date;

    return m_connection.last_insert_rowid();
}

/**
 * @brief Updates a Note's information.
 * 
 * @param id 
 * @param note 
 */
void Vault::Core::Services::DataManager::update(int id, std::string note)
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
void Vault::Core::Services::DataManager::remove(int id)
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
bool Vault::Core::Services::DataManager::exists(int id)
{
    int rows = 0;

    m_connection << "SELECT COUNT(*) FROM notes WHERE id = ?;"
                 << id
        >> rows;

    return rows;
}