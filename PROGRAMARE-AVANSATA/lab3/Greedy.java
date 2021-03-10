package lab3;

import java.sql.Time;
import java.util.Comparator;
import java.util.List;
import java.util.concurrent.TimeUnit;

public class Greedy implements Algorithm {
    private String name;
    private long time;
    private Knapsack knapsack;
    private List<Item> items;

    public Greedy(Knapsack knapsack, List<Item> items) {
        name = "Greedy";

        this.knapsack = knapsack;
        this.items = items;
    }

    public String getName() {
        return name;
    }

    public long getTime() {
        return time;
    }

    public void solve() {
        time = System.nanoTime();

        items.sort(Comparator.comparing(Item::getValue));

        items.forEach(item -> knapsack.addItem(item));

        time = System.nanoTime() - time;
    }
}
