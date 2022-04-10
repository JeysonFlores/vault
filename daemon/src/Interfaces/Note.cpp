#include "Note.hpp"

/**
 * @brief Construct a new Vault::Daemon::Interfaces::Note::Note object
 * 
 * @param connection 
 * @param objectPath 
 */
Vault::Daemon::Interfaces::Note::Note(sdbus::IConnection& connection, std::string objectPath)
    : AdaptorInterfaces(connection, std::move(objectPath))
{
    registerAdaptor();
}

/**
 * @brief Destroy the Vault:: Daemon:: Interfaces:: Note:: Note object
 * 
 */
Vault::Daemon::Interfaces::Note::~Note() {
    unregisterAdaptor();
}

/**
 * @brief Sends all the the Notes through the D-Bus service.
 * 
 * @return std::vector<sdbus::Struct<int32_t, std::string, std::string>> 
 */
std::vector<sdbus::Struct<int32_t, std::string, std::string>> Vault::Daemon::Interfaces::Note::GetAll()
{
    int i = 0;
    std::vector<sdbus::Struct<int32_t, std::string, std::string>> result;

    return result;
}

/**
 * @brief Send a specifif Note through the D-Bus service.
 * 
 * @param id 
 * @return sdbus::Struct<int32_t, std::string, std::string> 
 */
sdbus::Struct<int32_t, std::string, std::string> Vault::Daemon::Interfaces::Note::GetById(const int32_t& id)
{
    sdbus::Struct<int32_t, std::string, std::string> result;

    return result;
}

/**
 * @brief Registers a new Note into the Daemon, returns if the operation succeeded or not.
 * 
 * @param note 
 * @return true 
 * @return false 
 */
bool Vault::Daemon::Interfaces::Note::Add(const std::string& note)
{
    int i = 0;
    return true;
}

/**
 * @brief Updates a specified Note's information, returns if the operation succeeded or not.
 * 
 * @param id 
 * @param note 
 * @return true 
 * @return false 
 */
bool Vault::Daemon::Interfaces::Note::Update(const int32_t& id, const std::string& note)
{
    int i = 0;
    return true;
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
    return true;
}