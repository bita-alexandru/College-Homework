package lab3;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class DynamicProgramming implements Algorithm {
    private String name;
    private long time;
    private Knapsack knapsack;
    private List<Item> items;

    public DynamicProgramming(Knapsack knapsack, List<Item> items) {
        name = "DynamicProgramming";

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

        int nOfItems = items.size();
        int capacity = (int) knapsack.getCapacity();

        List<Item>[][] dpMatrix = new ArrayList[nOfItems + 1][capacity + 1];

        for (int i = 0; i <= nOfItems; i++) {
            for (int j = 0; j <= capacity; j++) {
                dpMatrix[i][j] = new ArrayList<>();
            }
        }

        for (int i = 1; i <= nOfItems; i++) {
            Item currItem = items.get(i - 1);
            int itemWeight = (int) currItem.getWeight();

            for (int j = 1; j <= capacity; j++) {
                if (itemWeight > j) {
                    dpMatrix[i][j] = new ArrayList<>(dpMatrix[i - 1][j]);
                } else {
                    List<Item> noAddition = new ArrayList<>(dpMatrix[i - 1][j]);
                    List<Item> yesAddition = new ArrayList<>(dpMatrix[i - 1][j - itemWeight]);
                    yesAddition.add(currItem);

                    int sumNoAddition = (noAddition.isEmpty()) ? 0 :
                            noAddition.stream().mapToInt(item -> (int) item.getValue()).sum();
                    int sumYesAddition = (yesAddition.isEmpty()) ? (int) currItem.getValue() :
                            (int) (yesAddition.stream().mapToInt(item -> (int) item.getValue()).sum() + currItem.getValue());

                    if (sumNoAddition >= sumYesAddition) {
                        dpMatrix[i][j] = new ArrayList<>(noAddition);
                    } else {
                        dpMatrix[i][j] = new ArrayList<>(yesAddition);
                    }
                }
            }
        }

        knapsack.setItems(dpMatrix[nOfItems][capacity]);

        time = System.nanoTime() - time;
    }
}
