#pragma once

#include <granite.h>
#include <gtkmm.h>
#include "MainWindow.hpp"

namespace Vault {
class Application : public Gtk::Application {
protected:
    Application();

public:
    static Glib::RefPtr<Application> create();

protected:
    void on_activate() override;

private:
    static void on_prefers_color_scheme_changed();
};

}
