import com.github.javafaker.Faker;

import java.util.*;

public class Game {
    private Board board;
    private List<Player> players;
    private List<Thread> threads;

    public Game(int nPlayers, int nTokens, int maxValue, int maxProgress) {
        board = new Board(nTokens);
        board.addTokens(maxValue);

        Faker faker = new Faker();

        players = new ArrayList<>();
        for (int i = 0; i < nPlayers; i++) {
            players.add(new Player(faker.name().fullName(), board, maxProgress));
        }

        threads = new ArrayList<>();
    }

    public void start() {
        for (Player player : players) {
            threads.add(new Thread(player));
        }

        for (Thread thread : threads) {
            thread.start();
        }

        for (Thread thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException exception) {
                System.err.println(exception);
            }
        }
    }

    public void showResults() {
        if (!board.getHasWinner()) {
            for (Player player : players) {
                player.setFinalPoints();
            }
        }

        players.sort(Comparator.comparing(Player::getFinalPoints).reversed());

        System.out.println("\n[FINAL RESULTS]");

        for (Player player : players) {
            System.out.print("\"" + player.getName() + "\"" + " scored " + player.getFinalPoints()
                    + " with the following tokens: [ ");

            for (Token token : player.getTokens()) {
                System.out.print(token.getValue() + " ");
            }

            System.out.println("]");
        }
    }
}