public class Main {

    public static void main(String[] args) {
        if (args.length != 4) {
            System.out.println("Syntax: <size_players> <size_tokens> <value_limit> <size_progression>");
        } else {
            Game game = new Game(Integer.parseInt(args[0])
                    , Integer.parseInt(args[1])
                    , Integer.parseInt(args[2])
                    , Integer.parseInt(args[3]));

            game.start();
            game.showResults();
        }
    }
}
