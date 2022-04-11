#include "Application.hpp"

Vault::Application::Application()
    : Gtk::Application(Vault::ID)
{
}

Glib::RefPtr<Vault::Application> Vault::Application::create()
{
    return Glib::RefPtr<Vault::Application>(new Vault::Application());
}

void Vault::Application::on_prefers_color_scheme_changed()
{
    auto granite_settings = granite_settings_get_default();
    auto gtk_settings = Gtk::Settings::get_default();
    auto color_scheme = granite_settings_get_prefers_color_scheme(granite_settings);

    gtk_settings->property_gtk_application_prefer_dark_theme().set_value(color_scheme == GRANITE_SETTINGS_COLOR_SCHEME_DARK);
}

void Vault::Application::on_activate()
{
    on_prefers_color_scheme_changed();

    auto granite_settings = granite_settings_get_default();
    g_signal_connect(granite_settings, "notify::prefers-color-scheme", G_CALLBACK(&on_prefers_color_scheme_changed), NULL);

    auto app_window = new Vault::MainWindow();
    add_window(*app_window);

    auto settings = Gio::Settings::create(Vault::ID);

    int window_width { settings->get_int("window-width") };
    int window_height { settings->get_int("window-height") };
    int pos_x { settings->get_int("pos-x") };
    int pos_y { settings->get_int("pos-y") };

    app_window->resize(window_width, window_height);
    app_window->move(pos_x, pos_y);
}

int main(int argc, char* argv[])
{
    auto application = Vault::Application::create();
    return application->run(argc, argv);
}