class Vault.Views.MainView : Gtk.Grid {

    public Gtk.Clipboard clipboard;
    public GLib.DateTime last_copy_date;
    public string last_copy_hash;
    public weak Vault.MainWindow parent_window { get; construct; }

    public MainView (Vault.MainWindow window) {
        Object(
            orientation: Gtk.Orientation.VERTICAL,
            parent_window: window
        );
    }

    construct {
        this.clipboard = Gtk.Clipboard.get_for_display (Gdk.Display.get_default (), Gdk.SELECTION_CLIPBOARD);
        this.last_copy_date = new GLib.DateTime.now_local ();
        this.last_copy_hash = "";

        this.clipboard.owner_change.connect ((event) => {
            var dt_now = new GLib.DateTime.now_local ();

            var copied_text = this.clipboard.wait_for_text ();
            var copied_text_hash = GLib.Checksum.compute_for_string (GLib.ChecksumType.MD5, copied_text, -1);

            print(dt_now.difference (this.last_copy_date).to_string() + "\n");

            if (dt_now.difference (this.last_copy_date) <= 180000 && copied_text_hash == this.last_copy_hash) {
                print("Copied text will be saved. Contend: " + copied_text + "\n");
                var notification = new GLib.Notification ("Text saved!");
                notification.set_body (copied_text);
                notification.set_icon (new ThemedIcon ("process-completed"));

                this.parent_window.get_application ().send_notification ("com.github.jeysonflores.vault", notification);
            }

            this.last_copy_date = dt_now;
            this.last_copy_hash = copied_text_hash;
        });
    }
}