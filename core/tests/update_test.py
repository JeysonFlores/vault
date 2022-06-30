import dbus


def init():
    bus = dbus.SessionBus()

    remote_object = bus.get_object(
        "com.github.jeysonflores.vault.Core",
        "/com/github/jeysonflores/vault/Core/Note",
    )

    return dbus.Interface(remote_object, "com.github.jeysonflores.Core.Note")


if __name__ == "__main__":
    id = int(input("Enter an ID to modify:"))
    new_note = input("Enter the new content of the note to update:")

    note_iface = init()

    try:
        if note_iface.Update(id, new_note):
            print("Note updated")
    except Exception as e:
        print(str(e))
