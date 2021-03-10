package lab2;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;


/**
 * Outputs the problem description
 * Uses instances of Depot and Client
 */
public class Problem {
    private Depot[] depots;
    private Client[] clients;

    public Problem() {
    }

    public Problem(Depot[] depots, Client[] clients) {
        setDepots(depots);
        setClients(clients);
    }

    public void setDepots(Depot[] depots) {
        Map<String, Boolean> hashMapDepots = new HashMap<String, Boolean>();
        for (Depot depot : depots) {
            if (hashMapDepots.get(depot.getName()) != null) {
                System.out.println("Attempt to insert a duplicate depot denied.");
                return;
            }
            hashMapDepots.put(depot.getName(), true);
        }
        this.depots = depots;
    }

    public Depot[] getDepots() {
        return depots;
    }

    public void setClients(Client[] clients) {
        Map<String, Boolean> hashMapClients = new HashMap<String, Boolean>();
        for (Client client : clients) {
            if (hashMapClients.get(client.getName()) != null) {
                System.out.println("Attempt to insert a client depot denied.");
                return;
            }
            hashMapClients.put(client.getName(), true);
        }
        this.clients = clients;
    }

    public Client[] getClients() {
        return clients;
    }

    public ArrayList<Vehicle> getVehicles() {
        ArrayList<Vehicle> vehicles = new ArrayList<>();

        for (Depot depot : depots) {
            for (Vehicle vehicle : depot.getVehicles()) {
                vehicles.add(vehicle);
            }
        }

        return vehicles;
    }

    @Override
    public String toString() {
        StringBuilder problemDescription = new StringBuilder();

        problemDescription.append("There are " + depots.length + " depots: ");
        for (Depot depot : depots) {
            problemDescription.append(depot + ", ");
        }
        problemDescription.append("\n");

        for (Depot depot : depots) {
            problemDescription.append(depot + " has " + depot.getVehicles().length + " vehicle(s): ");
            for (Vehicle vehicle : depot.getVehicles()) {
                problemDescription.append(vehicle + ", ");
            }
            problemDescription.append("\n");
        }

        problemDescription.append("There are " + clients.length + " clients: ");
        for (Client client : clients) {
            problemDescription.append(client + "(" + client.getOrder() + "), ");
        }
        problemDescription.append("\n");

        return problemDescription.toString();
    }
}
