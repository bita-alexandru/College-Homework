package lab3;

public class Weapon implements Item {
    private WeaponType type;
    private double weight;
    private double value;

    public Weapon(WeaponType type, double weight, double value) {
        this.type = type;
        this.weight = Math.round(weight * 100.0) / 100.0;
        this.value = Math.round(value * 100.0) / 100.0;
    }

    public void setType(WeaponType type) {
        this.type = type;
    }

    public void setWeight(double weight) {
        this.weight = weight;
    }

    public void setValue(double value) {
        this.value = value;
    }

    public double getWeight() {
        return weight;
    }

    public String getName() {
        return type.name();
    }

    public double getValue() {
        return value;
    }
}