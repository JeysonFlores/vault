[DBus (name = "com.github.jeysonflores.vault.Core.Note")]
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
    
public static int main (string[] args) {
    Vault.Proxies.Note iface;
    try {
        iface = Bus.get_proxy_sync (BusType.SESSION, "com.github.jeysonflores.vault.Core",
                                                            "/com/github/jeysonflores/vault/Core/Note");


        //iface.add ("#include <stdlib.h>", new GLib.DateTime.now_local ().format_iso8601 ());
        //iface.remove (7);
        //var the_note = iface.get_by_id (10);
        //var the_rel_date = Granite.DateTime.get_relative_datetime (new GLib.DateTime.from_iso8601 (the_note.date, null));
        //    print ("ID: %i\nNote: %s\nDate: %s\n\n", the_note.id, the_note.note, the_rel_date);
        //iface.update (10, "#pragma once", the_note.date);

        iface.note_added.connect ((id, note, date) => {
            var rel_date = Granite.DateTime.get_relative_datetime (new GLib.DateTime.from_iso8601 (date, null));
            print ("--NOTE ADDED--\nID: %i\nNote: %s\nDate: %s\n\n", id, note, rel_date);
        });

        iface.note_deleted.connect ((id) => {
            print ("--NOTE DELETED--\nID: %i", id);
        });

        iface.note_updated.connect ((id, note, date) => {
            var rel_date = Granite.DateTime.get_relative_datetime (new GLib.DateTime.from_iso8601 (date, null));
            print ("--NOTE UPDATED--\nID: %i\nNote: %s\nDate: %s\n\n", id, note, rel_date);
        });

        var notes = iface.get_all ();

        foreach (var note in notes) {
            var rel_date = Granite.DateTime.get_relative_datetime (new GLib.DateTime.from_iso8601 (note.date, null));
            print ("ID: %i\nNote: %s\nDate: %s\n\n", note.id, note.note, rel_date);
        }
        
        
    } catch (GLib.Error e) {
        warning ("Error trying to connect to the DBus service: [%s]\n", e.message);
    }

    print("%s\n", new GLib.DateTime.now_local ().format_iso8601 ());

    Gtk.main();
    return 0;
}

