#pragma once

#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <tuple>

namespace Vault {
namespace Daemon {
    namespace Adaptors {

        class Note {
        public:
            static constexpr const char* INTERFACE_NAME = "com.github.jeysonflores.daemon.Note";

        protected:
            Note(sdbus::IObject& object)
                : m_object_(object)
            {
                m_object_.registerMethod("GetAll").onInterface(INTERFACE_NAME).withOutputParamNames("notes").implementedAs([this]() { return this->GetAll(); });
                m_object_.registerMethod("GetById").onInterface(INTERFACE_NAME).withInputParamNames("id").withOutputParamNames("note").implementedAs([this](const int32_t& id) { return this->GetById(id); });
                m_object_.registerMethod("Add").onInterface(INTERFACE_NAME).withInputParamNames("note", "date").withOutputParamNames("was_completed").implementedAs([this](const std::string& note, const std::string& date) { return this->Add(note, date); });
                m_object_.registerMethod("Update").onInterface(INTERFACE_NAME).withInputParamNames("id", "note", "date").withOutputParamNames("was_completed").implementedAs([this](const int32_t& id, const std::string& note, const std::string& date) { return this->Update(id, note, date); });
                m_object_.registerMethod("Delete").onInterface(INTERFACE_NAME).withInputParamNames("id").withOutputParamNames("was_completed").implementedAs([this](const int32_t& id) { return this->Delete(id); });
                m_object_.registerSignal("NoteAdded").onInterface(INTERFACE_NAME).withParameters<int32_t, std::string, std::string>("id", "note", "date");
                m_object_.registerSignal("NoteUpdated").onInterface(INTERFACE_NAME).withParameters<int32_t, std::string, std::string>("id", "note", "date");
                m_object_.registerSignal("NoteDeleted").onInterface(INTERFACE_NAME).withParameters<int32_t>("id");
            }

            ~Note() = default;

        public:
            void emitNoteAdded(const int32_t& id, const std::string& note, const std::string& date)
            {
                m_object_.emitSignal("NoteAdded").onInterface(INTERFACE_NAME).withArguments(id, note, date);
            }

            void emitNoteUpdated(const int32_t& id, const std::string& note, const std::string& date)
            {
                m_object_.emitSignal("NoteUpdated").onInterface(INTERFACE_NAME).withArguments(id, note, date);
            }

            void emitNoteDeleted(const int32_t& id)
            {
                m_object_.emitSignal("NoteDeleted").onInterface(INTERFACE_NAME).withArguments(id);
            }

        private:
            virtual std::vector<sdbus::Struct<int32_t, std::string, std::string>> GetAll() = 0;
            virtual sdbus::Struct<int32_t, std::string, std::string> GetById(const int32_t& id) = 0;
            virtual bool Add(const std::string& note, const std::string& date) = 0;
            virtual bool Update(const int32_t& id, const std::string& note, const std::string& date) = 0;
            virtual bool Delete(const int32_t& id) = 0;

        private:
            sdbus::IObject& m_object_;
        };

    }
}
}
