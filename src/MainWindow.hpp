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
    Gtk::Paned m_header_paned;
    Gtk::HeaderBar m_left_side_header;
    Gtk::HeaderBar m_right_side_header;
    Gtk::Grid m_grid;
    Glib::RefPtr<Gtk::Clipboard> m_clipboard;
    Glib::DateTime m_last_copy_date;
    std::string m_last_copy_hash;
};
}