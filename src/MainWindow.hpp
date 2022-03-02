#pragma once

#include "Utils/Styles.hpp"
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
    Gtk::Label m_label;
    Glib::RefPtr<Gtk::Clipboard> m_clipboard;
    Glib::DateTime m_last_copy_date;
    std::string m_last_copy_hash;
};
}