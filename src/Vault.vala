namespace Vault {
    public class Application : Gtk.Application {

        public Application () {
            Object (
                application_id: "com.github.jeysonflores.vault",
                flags: ApplicationFlags.FLAGS_NONE
            );
        }

        protected override void activate () {
            var granite_settings = Granite.Settings.get_default ();
            var gtk_settings = Gtk.Settings.get_default ();

            gtk_settings.gtk_application_prefer_dark_theme = (
                granite_settings.prefers_color_scheme == Granite.Settings.ColorScheme.DARK
            );

            granite_settings.notify["prefers-color-scheme"].connect (() => {
                gtk_settings.gtk_application_prefer_dark_theme = (
                    granite_settings.prefers_color_scheme == Granite.Settings.ColorScheme.DARK
                );
            });

            var main_window = new Vault.MainWindow (this);
            main_window.show_all ();
        }

        public static int main (string[] args) {
            var date = new GLib.DateTime.now_local ();
            print (date.to_string ());
            print ("\n");
            print (date.format_iso8601 ());
            var date2 = new GLib.DateTime.from_iso8601 (date.format_iso8601 (), null);
            print ("\n");
            print (date2.format_iso8601 ());

            return new Vault.Application ().run (args);
        }
    }
}