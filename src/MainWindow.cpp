#include "MainWindow.hpp"

Vault::MainWindow::MainWindow()
    : m_clipboard(Gtk::Clipboard::get())
    , m_last_copy_date(Glib::DateTime::create_now_local())
    , m_last_copy_hash("")
{
    m_clipboard->signal_owner_change().connect(sigc::mem_fun(this, &Vault::MainWindow::on_clipboard_owner_change));

    m_headerbar.set_title("Vault");
    m_headerbar.set_show_close_button(true);
    m_headerbar.set_decoration_layout("close:");
    m_headerbar.get_style_context()->add_class(Vault::Style::FLAT);

    this->get_style_context()->add_class(Vault::Style::ROUNDED);
    this->set_titlebar(m_headerbar);
    this->show_all();
}

bool Vault::MainWindow::on_delete_event(GdkEventAny* event)
{
    int width, height;
    int pos_x, pos_y;

    auto settings = Gio::Settings::create(Vault::ID);

    this->get_size((int&)width, (int&)height);
    this->get_position((int&)pos_x, (int&)pos_y);

    settings->set_int("window-width", width);
    settings->set_int("window-height", height);

    settings->set_int("pos-x", pos_x);
    settings->set_int("pos-y", pos_y);

    return false;
}

void Vault::MainWindow::on_clipboard_owner_change(GdkEventOwnerChange* event)
{
    fmt::print("Clipboard event triggered\n");

    Glib::DateTime dt_now { Glib::DateTime::create_now_local() };

    std::string copied_text { m_clipboard->wait_for_text() };
    std::string copied_text_hash { Glib::Checksum::compute_checksum(Glib::Checksum::ChecksumType::CHECKSUM_MD5, copied_text) };

    fmt::print("Time difference: {}\n", dt_now.difference(m_last_copy_date));

    if (dt_now.difference(m_last_copy_date) <= 180000 && m_last_copy_hash == copied_text_hash) {
        fmt::print("Copied text will be saved. Content is: {}\n", copied_text);
        auto notification = Gio::Notification::create("Text Saved!");
        notification->set_body(copied_text);
        notification->set_icon(Gio::Icon::create("process-completed"));
        this->get_application()->send_notification(Vault::ID, notification);
    }

    m_last_copy_date = dt_now;
    m_last_copy_hash = copied_text_hash;
}