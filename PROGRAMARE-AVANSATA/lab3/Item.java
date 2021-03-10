package lab3;

public interface Item {
    String getName();

    double getValue();

    double getWeight();

    default double profitFactor() {
        return Math.round(getValue() / getWeight() * 100.0) / 100.0;
    }
}