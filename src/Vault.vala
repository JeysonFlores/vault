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
            return new Vault.Application ().run (args);
        }
    }
}
