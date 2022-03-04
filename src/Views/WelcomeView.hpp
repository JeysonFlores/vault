#pragma once

#include <gtkmm.h>

namespace Vault {
namespace Views {
    class WelcomeView : public Gtk::Grid {
    public:
        WelcomeView();

    private:
        Gtk::Label m_title;
        Gtk::Button m_next;
    };
};
}