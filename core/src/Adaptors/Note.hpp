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

#pragma once

#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <tuple>

namespace Vault {
namespace Core {
    namespace Adaptors {

        class Note {
        public:
            static constexpr const char* INTERFACE_NAME = "com.github.jeysonflores.vault.Core.Note";

        protected:
            Note(sdbus::IObject& object)
                : m_object_(object)
            {
                m_object_.registerMethod("GetAll").onInterface(INTERFACE_NAME).withOutputParamNames("notes").implementedAs([this]() { return this->get_all(); });
                m_object_.registerMethod("GetById").onInterface(INTERFACE_NAME).withInputParamNames("id").withOutputParamNames("note").implementedAs([this](const int32_t& id) { return this->get_by_id(id); });
                m_object_.registerMethod("Add").onInterface(INTERFACE_NAME).withInputParamNames("note", "date").withOutputParamNames("was_completed").implementedAs([this](const std::string& note, const std::string& date) { return this->add(note, date); });
                m_object_.registerMethod("Update").onInterface(INTERFACE_NAME).withInputParamNames("id", "note", "date").withOutputParamNames("was_completed").implementedAs([this](const int32_t& id, const std::string& note, const std::string& date) { return this->update(id, note, date); });
                m_object_.registerMethod("Remove").onInterface(INTERFACE_NAME).withInputParamNames("id").withOutputParamNames("was_completed").implementedAs([this](const int32_t& id) { return this->remove(id); });
                m_object_.registerSignal("NoteAdded").onInterface(INTERFACE_NAME).withParameters<int32_t, std::string, std::string>("id", "note", "date");
                m_object_.registerSignal("NoteUpdated").onInterface(INTERFACE_NAME).withParameters<int32_t, std::string, std::string>("id", "note", "date");
                m_object_.registerSignal("NoteDeleted").onInterface(INTERFACE_NAME).withParameters<int32_t>("id");
            }

            ~Note() = default;

        public:
            void emit(std::string signal_name, const int32_t& id, const std::string& note = "", const std::string& date = "")
            {
                if (signal_name == "note_added") {
                    m_object_.emitSignal("NoteAdded").onInterface(INTERFACE_NAME).withArguments(id, note, date);
                } else if (signal_name == "note_updated") {
                    m_object_.emitSignal("NoteUpdated").onInterface(INTERFACE_NAME).withArguments(id, note, date);
                } else if (signal_name == "note_deleted") {
                    m_object_.emitSignal("NoteDeleted").onInterface(INTERFACE_NAME).withArguments(id);
                }
            }

        private:
            virtual std::vector<sdbus::Struct<int32_t, std::string, std::string>> get_all() = 0;
            virtual sdbus::Struct<int32_t, std::string, std::string> get_by_id(const int32_t& id) = 0;
            virtual bool add(const std::string& note, const std::string& date) = 0;
            virtual bool update(const int32_t& id, const std::string& note, const std::string& date) = 0;
            virtual bool remove(const int32_t& id) = 0;

        private:
            sdbus::IObject& m_object_;
        };

    }
}
}
