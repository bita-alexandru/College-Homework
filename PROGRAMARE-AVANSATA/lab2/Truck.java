package lab2;

/**
 * Instance of Vehicle, belongs to a Depot
 * performs trips
 */
public class Truck extends Vehicle {
    private String name;
    private Depot depot;
    private VehicleType type;

    public Truck() {
    }

    public Truck(String name) {
        this.name = name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    protected void setDepot(Depot depot) {
        this.depot = depot;
    }

    public Depot getDepot() {
        return depot;
    }

    public void setVehicleType() {
        this.type = VehicleType.TRUCK;
    }

    public VehicleType getVehicleType() {
        return type;
    }

    @Override
    public String toString() {
        return name;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null || !(obj instanceof Vehicle)) {
            return false;
        }
        Vehicle other = (Vehicle) obj;
        return name.equals(other.getName());
    }
}
