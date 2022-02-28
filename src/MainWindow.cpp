#include "MainWindow.hpp"

Vault::MainWindow::MainWindow() {
    this->show_all();
}

bool Vault::MainWindow::on_delete_event(GdkEventAny* event)
{
    int width, height;
    int pos_x, pos_y;

    auto settings = Gio::Settings::create("com.github.jeysonflores.vault");

    this->get_size((int&)width, (int&)height);
    this->get_position((int&)pos_x, (int&)pos_y);

    settings->set_int("window-width", width);
    settings->set_int("window-height", height);

    settings->set_int("pos-x", pos_x);
    settings->set_int("pos-y", pos_y);

    return false;
}