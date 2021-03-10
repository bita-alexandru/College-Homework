import java.util.*;

public class Player implements Runnable {
    private String name;
    private Board board;
    private int maxProgress;
    private Vector<Token> tokens;
    private int finalPoints;
    private int currPoints;

    public Player(String name, Board board, int maxProgress) {
        this.name = name;
        this.board = board;
        this.maxProgress = maxProgress;
        tokens = new Vector<>();
        finalPoints = 0;
        currPoints = 0;
    }

    @Override
    public void run() {
        Token token;

        boolean ok = true;

        while (ok) {
            synchronized (board) {
                token = board.getFirstToken(name);
                board.removeFirstToken(name);

                if (token == null) {
                    System.out.println(name + " had nothing to extract anymore. ]");
                    ok = false;
                } else {
                    tokens.add(token);
                    tokens.sort(Comparator.comparingInt(myToken -> myToken.getValue()));

                    System.out.println(name + " extracted token " + token.getValue() + ". ]");
                }
            }

            Vector<Vector<Integer>> indexes = new Vector<>();

            // get indexes pairs (i1,i2),(i1,i3),(i1,i4),...,(in-1,in);
            for (int i = 0; i < tokens.size() - 1; i++) {
                for (int j = i + 1; j < tokens.size(); j++) {
                    Vector<Integer> pair = new Vector<>();
                    pair.add(i);
                    pair.add(j);
                    indexes.add(pair);
                }
            }

            // iterate through pairs; if (token[i2]-token[i1] = token[i3]) then increase currProgress
            beginLoop:
            for (int i = 0; i < indexes.size(); i++) {
                int currProgress = 2;
                int lastIndex = indexes.get(i).get(indexes.get(i).size() - 1);
                int value1 = tokens.get(lastIndex - 1).getValue();
                int value2 = tokens.get(lastIndex).getValue();
                int difference = value2 - value1;

                for (int j = lastIndex + 1; j < tokens.size(); j++) {
                    int value3 = tokens.get(j).getValue();
                    if (value3 == value2 + difference) {
                        indexes.get(i).add(j);
                        currProgress++;

                        if (currProgress == maxProgress) {
                            finalPoints = board.getSize(); // won the game -> gets 'n'(number of tokens) points (number of tokens, idk why this number but whatever the assignment says)
                            board.setHasWinner();

                            break beginLoop;
                        }

                        value2 = value3;
                    } else {
                        break;
                    }
                }

                if (currProgress > 2) {
                    currPoints = Math.max(currPoints, currProgress);
                }
            }
        }
    }


    public String getName() {
        return name;
    }

    public Vector<Token> getTokens() {
        return tokens;
    }

    public int getFinalPoints() {
        return finalPoints;
    }

    public void setFinalPoints() {
        finalPoints = currPoints;
    }
}
