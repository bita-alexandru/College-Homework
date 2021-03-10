package lab2;

import java.util.HashMap;
import java.util.Map;

/**
 * Stores vehicles, can't store duplicates
 */
public class Depot {
    private String name;
    private Vehicle[] vehicles;

    public Depot() {
    }

    public Depot(String name, Vehicle[] vehicles) {
        this.name = name;
        setVehicles(vehicles);
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setVehicles(Vehicle... vehicles) {
        this.vehicles = vehicles;
        Map<String, Boolean> hashMapVechicles = new HashMap<String, Boolean>();

        for (Vehicle vehicle : vehicles) {
            if (hashMapVechicles.get(vehicle.getName()) == null) {
                vehicle.setDepot(this);
                hashMapVechicles.put(vehicle.getName(), true);
            } else {
                System.out.println("Attempt to insert a duplicate vehicle denied.");
            }
        }
    }

    public Vehicle[] getVehicles() {
        return vehicles;
    }

    @Override
    public String toString() {
        return name;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null || !(obj instanceof Depot)) {
            return false;
        }
        Depot other = (Depot) obj;
        return name.equals(other.getName());
    }
}
