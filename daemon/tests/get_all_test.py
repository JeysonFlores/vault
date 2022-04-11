import dbus

def init():
    bus = dbus.SessionBus()

    remote_object = bus.get_object("com.github.jeysonflores.vault.daemon", "/com/github/jeysonflores/vault/daemon/Note")

    return dbus.Interface(remote_object, "com.github.jeysonflores.daemon.Note")

if __name__ == "__main__":
    note_iface = init()

    notes = note_iface.GetAll()

    for note in notes:
        print("ID: " + str(note[0]))
        print("NOTE: " + str(note[1]))
        print("DATE: " + str(note[2]))
