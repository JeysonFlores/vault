#include "Note.hpp"

/**
 * @brief Construct a new Vault::Daemon::Interfaces::Note::Note object
 * 
 * @param connection 
 * @param objectPath 
 */
Vault::Daemon::Interfaces::Note::Note(sdbus::IConnection& connection, std::string objectPath, Vault::Daemon::Services::DataManager dbM)
    : AdaptorInterfaces(connection, std::move(objectPath))
    , m_dbManager(dbM)
{
    registerAdaptor();
}

/**
 * @brief Destroy the Vault::Daemon::Interfaces::Note::Note object
 * 
 */
Vault::Daemon::Interfaces::Note::~Note()
{
    unregisterAdaptor();
}

/**
 * @brief Sends all the the Notes through the D-Bus service.
 * 
 * @return std::vector<sdbus::Struct<int32_t, std::string, std::string>> 
 */
std::vector<sdbus::Struct<int32_t, std::string, std::string>> Vault::Daemon::Interfaces::Note::GetAll()
{
    LOG(INFO, "GetAll method called...");

    try {
        return m_dbManager.GetNotes();
    } catch (const std::exception& e) {
        LOG(ERROR, "There was an error retrieving all Notes");
        throw sdbus::Error("com.github.jeysonflores.vault.daemon.Error", e.what());
    }
}

/**
 * @brief Send a specifif Note through the D-Bus service.
 * 
 * @param id 
 * @return sdbus::Struct<int32_t, std::string, std::string> 
 */
sdbus::Struct<int32_t, std::string, std::string> Vault::Daemon::Interfaces::Note::GetById(const int32_t& id)
{
    LOG(INFO, "GetById method called...");

    if (m_dbManager.Exists(id)) {
        try {
            return m_dbManager.GetNoteById(id);
        } catch (const std::exception& e) {
            LOG(ERROR, "There was an error retrieving a Note");
            throw sdbus::Error("com.github.jeysonflores.vault.daemon.Error", e.what());
        }
    }

    throw sdbus::Error("com.github.jeysonflores.vault.daemon.Error", "There's no note that matches the given ID");
}

/**
 * @brief Registers a new Note into the Daemon, returns if the operation succeeded or not.
 * 
 * @param note 
 * @return true 
 * @return false 
 */
bool Vault::Daemon::Interfaces::Note::Add(const std::string& note, const std::string& date)
{
    LOG(INFO, "Add method called");

    try {
        int id = m_dbManager.Add(note, date);
        this->emitNoteAdded(id, note, date);
        return true;
    } catch (const std::exception& e) {
        LOG(ERROR, "There was an error setting a Note");
        throw sdbus::Error("com.github.jeysonflores.vault.daemon.Error", e.what());
    }
}

/**
 * @brief Updates a specified Note's information, returns if the operation succeeded or not.
 * 
 * @param id 
 * @param note 
 * @return true 
 * @return false 
 */
bool Vault::Daemon::Interfaces::Note::Update(const int32_t& id, const std::string& note, const std::string& date)
{
    LOG(INFO, "Update method called");

    if (m_dbManager.Exists(id)) {
        try {
            m_dbManager.Update(id, note);
            this->emitNoteUpdated(id, note, date);
            return true;
        } catch (const std::exception& e) {
            LOG(ERROR, "There was an error updating a Note");
            throw sdbus::Error("com.github.jeysonflores.vault.daemon.Error", e.what());
        }
    }

    throw sdbus::Error("com.github.jeysonflores.vault.daemon.Error", "There's no note that matches the given ID");
}

/**
 * @brief Deletes a specific Note, returns if the operation succeeded or not.
 * 
 * @param id 
 * @return true 
 * @return false 
 */
bool Vault::Daemon::Interfaces::Note::Delete(const int32_t& id)
{
    LOG(INFO, "Delete method called");

    if (m_dbManager.Exists(id)) {
        try {
            m_dbManager.Remove(id);
            this->emitNoteDeleted(id);
            return true;
        } catch (const std::exception& e) {
            LOG(ERROR, "There was an error deleting a Note");
            throw sdbus::Error("com.github.jeysonflores.vault.daemon.Error", e.what());
        }
    }

    throw sdbus::Error("com.github.jeysonflores.vault.daemon.Error", "There's no note that matches the given ID");
}