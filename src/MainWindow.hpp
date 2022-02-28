#pragma once

#include <gtkmm.h>

namespace Vault {
class MainWindow : public Gtk::Window {
public:
    MainWindow();

protected:
    bool on_delete_event(GdkEventAny* event) override;

private:
    Gtk::HeaderBar m_headerbar;
    Gtk::Label m_label;
    Glib::RefPtr<Gtk::Clipboard> m_clipboard;
};
}