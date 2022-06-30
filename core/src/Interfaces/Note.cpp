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

#include "Note.hpp"

/**
 * @brief Construct a new Vault::Core::Interfaces::Note::Note object
 * 
 * @param connection 
 * @param object_path
 * @param dbm
 */
Vault::Core::Interfaces::Note::Note(sdbus::IConnection& connection, std::string object_path, Vault::Core::Services::DataManager dbm)
    : AdaptorInterfaces(connection, std::move(object_path))
    , m_db_manager(dbm)
{
    registerAdaptor();
}

/**
 * @brief Destroy the Vault::Core::Interfaces::Note::Note object
 * 
 */
Vault::Core::Interfaces::Note::~Note()
{
    unregisterAdaptor();
}

/**
 * @brief Sends all the the Notes through the D-Bus service.
 * 
 * @return std::vector<sdbus::Struct<int32_t, std::string, std::string>> 
 */
std::vector<sdbus::Struct<int32_t, std::string, std::string>> Vault::Core::Interfaces::Note::get_all()
{
    LOG(INFO, "GetAll method called...");

    try {
        return m_db_manager.get_notes();
    } catch (const std::exception& e) {
        LOG(ERROR, "There was an error retrieving all Notes");
        throw sdbus::Error("com.github.jeysonflores.vault.Core.Error", e.what());
    }
}

/**
 * @brief Send a specifif Note through the D-Bus service.
 * 
 * @param id 
 * @return sdbus::Struct<int32_t, std::string, std::string> 
 */
sdbus::Struct<int32_t, std::string, std::string> Vault::Core::Interfaces::Note::get_by_id(const int32_t& id)
{
    LOG(INFO, "GetById method called...");

    if (m_db_manager.exists(id)) {
        try {
            return m_db_manager.get_note_by_id(id);
        } catch (const std::exception& e) {
            LOG(ERROR, "There was an error retrieving a Note");
            throw sdbus::Error("com.github.jeysonflores.vault.Core.Error", e.what());
        }
    }

    throw sdbus::Error("com.github.jeysonflores.vault.Core.Error", "There's no note that matches the given ID");
}

/**
 * @brief Registers a new Note into the Core, returns if the operation succeeded or not.
 * 
 * @param note 
 * @param date
 * @return true 
 * @return false 
 */
bool Vault::Core::Interfaces::Note::add(const std::string& note, const std::string& date)
{
    LOG(INFO, "Add method called");

    try {
        int id = m_db_manager.add(note, date);
        this->emit("note_added", id, note, date);
        return true;
    } catch (const std::exception& e) {
        LOG(ERROR, "There was an error setting a Note");
        throw sdbus::Error("com.github.jeysonflores.vault.Core.Error", e.what());
    }
}

/**
 * @brief Updates a specified Note's information, returns if the operation succeeded or not.
 * 
 * @param id 
 * @param note 
 * @param date
 * @return true 
 * @return false 
 */
bool Vault::Core::Interfaces::Note::update(const int32_t& id, const std::string& note, const std::string& date)
{
    LOG(INFO, "Update method called");

    if (m_db_manager.exists(id)) {
        try {
            m_db_manager.update(id, note);
            this->emit("note_updated", id, note, date);
            return true;
        } catch (const std::exception& e) {
            LOG(ERROR, "There was an error updating a Note");
            throw sdbus::Error("com.github.jeysonflores.vault.Core.Error", e.what());
        }
    }

    throw sdbus::Error("com.github.jeysonflores.vault.Core.Error", "There's no note that matches the given ID");
}

/**
 * @brief Deletes a specific Note, returns if the operation succeeded or not.
 * 
 * @param id 
 * @return true 
 * @return false 
 */
bool Vault::Core::Interfaces::Note::remove(const int32_t& id)
{
    LOG(INFO, "Delete method called");

    if (m_db_manager.exists(id)) {
        try {
            m_db_manager.remove(id);
            this->emit("note_deleted", id);
            return true;
        } catch (const std::exception& e) {
            LOG(ERROR, "There was an error deleting a Note");
            throw sdbus::Error("com.github.jeysonflores.vault.Core.Error", e.what());
        }
    }

    throw sdbus::Error("com.github.jeysonflores.vault.Core.Error", "There's no note that matches the given ID");
}