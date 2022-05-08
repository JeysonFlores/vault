class Vault.Widgets.Welcome : Gtk.Grid {

    public GLib.Icon? icon { get; construct; }

    public Welcome () {
        Object (

        );
    }

    public Welcome.from_icon (string icon_name) {
        Object (
            //icon: new Gtk.Icon
        );
    }


}