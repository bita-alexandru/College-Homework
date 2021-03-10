package lab2;

import java.util.ArrayList;
import java.util.List;

/**
 * Represents the trips made by a vehicle
 */
public class Tour {
    private Vehicle vehicle;
    private List<Client> clients;

    public Tour() {
    }

    public Tour(Vehicle vehicle, List<Client> clients) {
        this.vehicle = vehicle;
        this.clients = clients;
    }

    public void setVehicle(Vehicle vehicle) {
        this.vehicle = vehicle;
    }

    public Vehicle getVehicle() {
        return vehicle;
    }

    public void setClients(List<Client> clients) {
        this.clients = clients;
    }

    public List<Client> getClients() {
        return clients;
    }
}
