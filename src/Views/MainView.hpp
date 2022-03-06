#pragma once

#include <gtkmm.h>

namespace Vault {
namespace Views {
    class MainView : public Gtk::Grid {
    public:
        MainView();

    private:
        Gtk::Label m_title;
        Gtk::Button m_next;
    };
};
}