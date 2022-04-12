class Vault.Views.WelcomeView : Gtk.Grid {

    public WelcomeView() {
        Object(
            orientation: Gtk.Orientation.VERTICAL
        );
    }

    construct {
        var label = new Gtk.Label ("Page 1");
        var label2 = new Gtk.Label ("Page 2");
        var label3 = new Gtk.Label ("Page 3");

        this.add (label2);
    }
}