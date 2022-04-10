
/*
 * This file was automatically generated by sdbus-c++-xml2cpp; DO NOT EDIT!
 */

#ifndef __sdbuscpp____generated_note_gen_h__adaptor__H__
#define __sdbuscpp____generated_note_gen_h__adaptor__H__

#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <tuple>

namespace com {
namespace github {
    namespace jeysonflores {
        namespace daemon {

            class Note_adaptor {
            public:
                static constexpr const char* INTERFACE_NAME = "com.github.jeysonflores.daemon.Note";

            protected:
                Note_adaptor(sdbus::IObject& object)
                    : object_(object)
                {
                    object_.registerMethod("GetAll").onInterface(INTERFACE_NAME).withOutputParamNames("notes").implementedAs([this]() { return this->GetAll(); });
                    object_.registerMethod("GetById").onInterface(INTERFACE_NAME).withInputParamNames("id").withOutputParamNames("note").implementedAs([this](const int32_t& id) { return this->GetById(id); });
                    object_.registerMethod("Add").onInterface(INTERFACE_NAME).withInputParamNames("note").withOutputParamNames("was_completed").implementedAs([this](const std::string& note) { return this->Add(note); });
                    object_.registerMethod("Update").onInterface(INTERFACE_NAME).withInputParamNames("id", "note").withOutputParamNames("was_completed").implementedAs([this](const int32_t& id, const std::string& note) { return this->Update(id, note); });
                    object_.registerMethod("Delete").onInterface(INTERFACE_NAME).withInputParamNames("id").withOutputParamNames("was_completed").implementedAs([this](const int32_t& id) { return this->Delete(id); });
                    object_.registerSignal("NoteAdded").onInterface(INTERFACE_NAME).withParameters<int32_t, std::string, std::string>("id", "note", "date");
                    object_.registerSignal("NoteUpdated").onInterface(INTERFACE_NAME).withParameters<int32_t, std::string, std::string>("id", "note", "date");
                    object_.registerSignal("NoteDeleted").onInterface(INTERFACE_NAME).withParameters<int32_t>("id");
                }

                ~Note_adaptor() = default;

            public:
                void emitNoteAdded(const int32_t& id, const std::string& note, const std::string& date)
                {
                    object_.emitSignal("NoteAdded").onInterface(INTERFACE_NAME).withArguments(id, note, date);
                }

                void emitNoteUpdated(const int32_t& id, const std::string& note, const std::string& date)
                {
                    object_.emitSignal("NoteUpdated").onInterface(INTERFACE_NAME).withArguments(id, note, date);
                }

                void emitNoteDeleted(const int32_t& id)
                {
                    object_.emitSignal("NoteDeleted").onInterface(INTERFACE_NAME).withArguments(id);
                }

            private:
                virtual std::vector<sdbus::Struct<int32_t, std::string, std::string>> GetAll() = 0;
                virtual sdbus::Struct<int32_t, std::string, std::string> GetById(const int32_t& id) = 0;
                virtual bool Add(const std::string& note) = 0;
                virtual bool Update(const int32_t& id, const std::string& note) = 0;
                virtual bool Delete(const int32_t& id) = 0;

            private:
                sdbus::IObject& object_;
            };

        }
    }
}
} // namespaces

#endif
