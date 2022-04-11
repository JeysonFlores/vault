class Vault.MainWindow : Hdy.Window {

    public MainWindow(Gtk.Application application) {
        Object (
            application: application
        );
    }

    construct { 
        Hdy.init();

        var deck = new Hdy.Deck () {
            can_swipe_back = true,
            can_swipe_forward = true,
            vhomogeneous = true,
            hhomogeneous = true,
            expand = true,
            transition_type = Hdy.DeckTransitionType.SLIDE
        };

        var welcome_view = new Vault.Views.WelcomeView ();
        var main_view = new Vault.Views.MainView (this);

        deck.add (welcome_view);
        deck.add (main_view);
        
        this.add (deck);
    }
}