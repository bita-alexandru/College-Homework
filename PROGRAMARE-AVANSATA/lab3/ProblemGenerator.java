package lab3;

import java.util.ArrayList;
import java.util.List;

public class ProblemGenerator {
    private List<Item> items;
    private double capacity;
    private boolean isInteger;

    public ProblemGenerator(boolean isInteger) {
        this.isInteger = isInteger;

        final int MIN_CAPACITY = 50;
        final int MAX_CAPACITY = 100;

        final int MIN_ITEMS = 5;
        final int MAX_ITEMS = 10;

        final double MIN_WEIGHT = 10.;
        final double MAX_WEIGHT = 20.;

        final double MIN_VALUE = 5.;
        final double MAX_VALUE = 10.;

        final int MIN_PAGE_NUMBER = 5;
        final int MAX_PAGE_NUMBER = 10;

        final int WEAPON_TYPES_LENGTH = WeaponType.values().length;

        int nOfBooks = 0;
        int nOfFoods = 0;
        int nOfItems = (int) (Math.random() * (MAX_ITEMS - MIN_ITEMS) + MIN_ITEMS);

        Item item = null;

        items = new ArrayList<>();

        capacity = (int) (Math.random() * (MAX_CAPACITY - MIN_CAPACITY) + MIN_CAPACITY);

        for (int i = 0; i < nOfItems; i++) {
            int randomItem = (int) (Math.random() * 3);

            switch (randomItem) {
                case 0: { // add Book
                    double value = (Math.random() * (MAX_VALUE - MIN_VALUE) + MIN_VALUE);

                    if (isInteger) {
                        value = Math.round(value);
                    }

                    item = new Book("book" + nOfBooks++,
                            (int) (Math.random() * (MAX_PAGE_NUMBER - MIN_PAGE_NUMBER) + MIN_PAGE_NUMBER),
                            value);

                    break;
                }
                case 1: { // add Food
                    double weight = (Math.random() * (MAX_WEIGHT - MIN_WEIGHT) + MIN_WEIGHT);

                    if (isInteger) {
                        weight = Math.round(weight);
                    }

                    item = new Food("food" + nOfFoods++,
                            weight);
                    break;
                }
                case 2: { // add Weapon
                    double weight = (Math.random() * (MAX_WEIGHT - MIN_WEIGHT) + MIN_WEIGHT);
                    double value = (Math.random() * (MAX_VALUE - MIN_VALUE) + MIN_VALUE);

                    if (isInteger) {
                        weight = Math.round(weight);
                        value = Math.round(value);
                    }

                    item = new Weapon(WeaponType.values()[(int) (Math.random() * WEAPON_TYPES_LENGTH)],
                            weight,
                            value);
                    break;
                }
            }

            items.add(item);
        }
    }

    public List<Item> getItems() {
        return items;
    }

    public double getCapacity() {
        return capacity;
    }
}
