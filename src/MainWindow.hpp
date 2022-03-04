#pragma once

#include "Style.hpp"
#include "Vault.hpp"
#include <fmt/core.h>
#include <gtkmm.h>

namespace Vault {
class MainWindow : public Gtk::Window {
public:
    MainWindow();

protected:
    bool on_delete_event(GdkEventAny* event) override;
    void on_clipboard_owner_change(GdkEventOwnerChange* event);

private:
    Gtk::HeaderBar m_headerbar;
    Gtk::Stack m_stack;
    Gtk::Button m_label;
    Gtk::Button m_label2;
    Glib::RefPtr<Gtk::Clipboard> m_clipboard;
    Glib::DateTime m_last_copy_date;
    std::string m_last_copy_hash;
};
}