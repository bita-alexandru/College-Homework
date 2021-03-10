package lab3;

import java.util.*;

public class Knapsack {
    private double capacity;
    private double occupied;
    private List<Item> items;

    public Knapsack(double capacity) {
        items = new ArrayList<>();
        occupied = 0.;

        this.capacity = capacity;
    }

    public void setCapacity(double capacity) {
        this.capacity = capacity;
    }

    public void setItems(List<Item> items) {
        this.items = items;
        occupied = items.stream().mapToDouble(item -> item.getWeight()).sum();
    }

    public double getCapacity() {
        return capacity;
    }

    public double getOccupied() {
        return occupied;
    }

    public List<Item> getItems() {
        return items;
    }

    public double getProfit() {
        return items.stream().mapToDouble(item -> item.getValue()).sum();
    }

    public void clear() {
        items = new ArrayList<>();
    }

    public boolean addItem(Item item) {
        if (item != null) {
            if (item.getWeight() + occupied > capacity) {
                return false;
            }

            items.add(item);
            occupied += item.getWeight();

            return true;
        }

        return false;
    }

    @Override
    public String toString() {
        StringBuilder problemDescription = new StringBuilder();

        problemDescription.append("capacity of the knapsack: " + capacity + "\n");
        problemDescription.append("available items(" + items.size() + "):\n");

        Collections.sort(items, new Comparator() {
                    public int compare(Object object1, Object object2) {
                        Item item1 = (Item) object1;
                        Item item2 = (Item) object2;
                        return item1.getName().compareTo(item2.getName());
                    }
                }
        );

        for (Item item : items) {
            problemDescription.append("\t");

            if (item instanceof Book) {
                problemDescription.append("book: ");
            } else if (item instanceof Food) {
                problemDescription.append("food: ");
            } else if (item instanceof Weapon) {
                problemDescription.append("weapon: ");
            }

            problemDescription.append(item.getName() + ", weight = " + item.getWeight()
                    + ", value = " + item.getValue() + " (profit factor = " + item.profitFactor() + ")\n");
        }

        problemDescription.append("total value: " + getProfit() + "\ncapacity left: " + (capacity - occupied) + "\n");

        return problemDescription.toString();
    }
}