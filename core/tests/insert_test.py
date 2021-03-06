import dbus


def init():
    bus = dbus.SessionBus()

    remote_object = bus.get_object(
        "com.github.jeysonflores.vault.Core",
        "/com/github/jeysonflores/vault/Core/Note",
    )

    return dbus.Interface(remote_object, "com.github.jeysonflores.Core.Note")


if __name__ == "__main__":
    new_note = input("Enter an note to insert:")

    note_iface = init()

    try:
        if note_iface.Add(new_note):
            print("Note created")
    except Exception as e:
        print(str(e))
