class Vault.Widgets.WelcomeButton : Gtk.Button {
    
    public Gtk.Label? title { get; construct; }
    public Gtk.Label? description { get; construct; }
    public Gtk.Image? icon { get; construct; }

    public WelcomeButton (string title, string description, string icon_name) {
        Object (
            title: new Gtk.Label (title),
            description: new Gtk.Label (description),
            icon: new Gtk.Image.from_icon_name (icon_name, Gtk.IconSize.DIALOG)
        );
    }

    construct {
        var grid = new Gtk.Grid ();
        title.get_style_context ().add_class (Granite.STYLE_CLASS_H3_LABEL);
        title.halign = Gtk.Align.START;
        title.valign = Gtk.Align.END;

        // Description label
        description.halign = Gtk.Align.START;
        description.valign = Gtk.Align.START;
        description.set_line_wrap (true);
        description.set_line_wrap_mode (Pango.WrapMode.WORD);
        description.get_style_context ().add_class (Gtk.STYLE_CLASS_DIM_LABEL);

        get_style_context ().add_class (Gtk.STYLE_CLASS_FLAT);

        // Button contents wrapper
        grid = new Gtk.Grid ();
        grid.column_spacing = 12;

        grid.attach (title, 1, 0, 1, 1);
        grid.attach (description, 1, 1, 1, 1);
        grid.attach (icon, 0, 0, 1, 2);
        this.add (grid);
    }
}