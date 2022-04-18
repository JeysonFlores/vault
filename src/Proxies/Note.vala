[DBus (name = "com.github.jeysonflores.vault.Daemon.Note")]
interface Vault.Proxies.Note : Object {
    public abstract Vault.Models.Note[] get_all () throws GLib.Error;
    public abstract Vault.Models.Note get_by_id (int id) throws GLib.Error;
    public abstract bool add (string note, string date) throws GLib.Error;
    public abstract bool update (int id, string note, string date) throws GLib.Error;
    public abstract bool remove (int id) throws GLib.Error;

    public signal void note_added (int id, string note, string date);
    public signal void note_deleted (int id);
    public signal void note_updated (int id, string note, string date);
}
