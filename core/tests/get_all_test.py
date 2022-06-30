import dbus


def init():
    bus = dbus.SessionBus()

    remote_object = bus.get_object(
        "com.github.jeysonflores.vault.Core",
        "/com/github/jeysonflores/vault/Core/Note",
    )

    return dbus.Interface(remote_object, "com.github.jeysonflores.Core.Note")


if __name__ == "__main__":
    note_iface = init()

    notes = note_iface.GetAll()

    for note in notes:
        print("ID: " + str(note[0]))
        print("NOTE: " + str(note[1]))
        print("DATE: " + str(note[2]))
