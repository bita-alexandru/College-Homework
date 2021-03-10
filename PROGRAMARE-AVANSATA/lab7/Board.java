import java.util.*;

public class Board {
    private Vector<Token> tokens;
    private int nTokens;
    private boolean hasWinner;

    public Board(int size) {
        this.nTokens = size;
        tokens = new Vector<>();
        hasWinner = false;
    }

    public void addTokens(int maxValue) {
        Set<Integer> distinctValues = new HashSet<>();

        while (distinctValues.size() < nTokens) {
            distinctValues.add((int) (Math.random() * maxValue + 1));
        }

        for (Integer integer : distinctValues) {
            tokens.add(new Token(integer));
        }
    }

    public synchronized Token getFirstToken(String name) {
        System.out.println("[ " + name + " begins extraction.");

        if (hasWinner || tokens.isEmpty()) {
            return null;
        }
        return tokens.firstElement();
    }

    public synchronized boolean removeFirstToken(String name) {
        System.out.println(name + " finishes extraction.");

        if (hasWinner || tokens.isEmpty()) {
            return false;
        }
        return tokens.remove(tokens.firstElement());
    }

    public void setHasWinner() {
        hasWinner = true;
    }

    public int getSize() {
        return nTokens;
    }

    public boolean getHasWinner() {
        return hasWinner;
    }
}
