package lab3;

import java.util.List;

public class Main {

    public static void main(String[] args) {
        //compulsory();
        optional();
        bonus();
    }

    public static void compulsory() {
        Item book1 = new Book("Dragon Rising", 3, 5);
        Item book2 = new Book("A Blade in the Dark", 3, 5);

        Item food1 = new Food("Cabbage", 2);
        Item food2 = new Food("Rabbit", 2);

        Item weapon = new Weapon(WeaponType.SWORD, 5, 10);

        Knapsack knapsack = new Knapsack(10);
        knapsack.addItem(book1);
        knapsack.addItem(book2);
        knapsack.addItem(food1);
        knapsack.addItem(food2);
        knapsack.addItem(weapon);

        System.out.println(knapsack);
    }

    public static void optional() {
        ProblemGenerator greedyGenerator = new ProblemGenerator(true);
        double capacity = greedyGenerator.getCapacity();
        List<Item> items = greedyGenerator.getItems();

        Knapsack convenientKnapsack = new Knapsack(items.stream().mapToDouble(item -> item.getWeight()).sum());
        convenientKnapsack.setItems(items);
        System.out.println(convenientKnapsack);

        Knapsack knapsack = new Knapsack(capacity);
        Algorithm greedy = new Greedy(knapsack, items);
        greedy.solve();
        double profitGreedy = knapsack.getProfit();
        double leftGreedy = capacity - knapsack.getOccupied();
        long timeGreedy = greedy.getTime();

        System.out.println(knapsack);
        System.out.println("ellapsed time: " + timeGreedy + " nanoseconds");

        knapsack.clear();
        Algorithm dynamicProgramming = new DynamicProgramming(knapsack, items);
        dynamicProgramming.solve();
        double profitDP = knapsack.getProfit();
        double leftDP = capacity - knapsack.getOccupied();
        long timeDP = dynamicProgramming.getTime();

        System.out.println(knapsack);
        System.out.println("ellapsed time: " + timeDP + " nanoseconds\n");

        System.out.format("%50s%50s%50s%n%50s%50s%50s", "_PROFIT_", "_CAPACITY_LEFT_", "_TIME(NANOSECONDS)_",
                ("Greedy " + profitGreedy + " vs. " + profitDP + " DP"),
                ("Greedy " + leftGreedy + " vs. " + leftDP + " DP"),
                ("Greedy " + timeGreedy + " vs. " + timeDP + " DP"));
    }

    public static void bonus() {

    }
}
