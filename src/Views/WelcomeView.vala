class Vault.Views.WelcomeView : Gtk.Grid {

    public signal void next ();

    public WelcomeView () {
        Object (

        );
    }

    construct {
        this.orientation = Gtk.Orientation.VERTICAL;

        var headerbar = new Hdy.HeaderBar () {
            decoration_layout = "close:",
            has_subtitle = false,
            show_close_button = true,
            can_focus = false,
            hexpand = true
        };
        //headerbar.get_style_context ().add_class (Gtk.STYLE_CLASS_FLAT);

        var label = new Gtk.Label ("Page 1");
        var label2 = new Gtk.Label ("Page 2");
        var label3 = new Gtk.Label ("Page 3");
        var wel_btn = new Vault.Widgets.WelcomeButton ("Welcome to uwu", "oso", "folder-symbolic");
        this.add (headerbar);
        this.add (label);
        this.add (wel_btn);
    }
}
