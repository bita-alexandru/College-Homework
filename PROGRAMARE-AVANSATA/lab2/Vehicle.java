package lab2;

/**
 * Vehicle abstractization
 * see Main.java
 */
public abstract class Vehicle {
    private String name;
    private Depot depot;
    private VehicleType type;

    abstract void setName(String name);

    abstract String getName();

    abstract void setDepot(Depot depot);

    abstract Depot getDepot();

    abstract void setVehicleType();

    abstract VehicleType getVehicleType();

    @Override
    public abstract String toString();

    @Override
    public abstract boolean equals(Object obj);
}
