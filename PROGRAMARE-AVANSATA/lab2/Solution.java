package lab2;

import java.util.*;

/**
 * Implements a Greedy method to solve the problem
 */
public class Solution {
    private List<Tour> tours = new ArrayList<Tour>();
    private List<Vehicle> unusedVehicles = new ArrayList<Vehicle>();
    private List<Client> unvisitedClients = new ArrayList<Client>();

    public void solve(Problem problem) {
        Depot[] depots = problem.getDepots();
        Client[] clients = problem.getClients();
        List<Vehicle> vehicles = problem.getVehicles();

        for (Client client : clients) {
            unvisitedClients.add(client);
        }

        Arrays.sort(clients, Comparator.comparingInt(Client::getOrder)); // orders clients by priority

        Map<String, Boolean> visitedClients = new HashMap<String, Boolean>();

        for (Vehicle vehicle : vehicles) { // greedy algorithm to allocate trips to vehicles
            unusedVehicles.add(vehicle);

            Tour tour = new Tour();
            List<Client> clientsVisited = new ArrayList<Client>();

            tour.setVehicle(vehicle);

            boolean wasUsed = false;
            int time = -1;

            for (Client client : clients) {

                if (client.getOrder() != time && visitedClients.containsKey(client.toString()) == false) { // respects time schedule, client not visited -> visit
                    unvisitedClients.remove(client);

                    clientsVisited.add(client);
                    visitedClients.put(client.toString(), true);

                    wasUsed = true;
                    time = client.getOrder();
                }
            }

            if (wasUsed == true) {
                unusedVehicles.remove(vehicle);

                tour.setClients(clientsVisited);
                tours.add(tour);
            }
        }
    }

    @Override
    public String toString() {
        StringBuilder solutionDescription = new StringBuilder();

        if (tours.isEmpty() == true) {
            solutionDescription.append("Greedy method failed to allocate any trips.");
        } else {
            for (Tour tour : tours) {
                solutionDescription.append(tour.getVehicle() + ": " + tour.getVehicle().getDepot() + " - ");

                for (Client client : tour.getClients()) {
                    solutionDescription.append(client + " - ");
                }

                solutionDescription.append(tour.getVehicle().getDepot() + "\n");
            }

            solutionDescription.append("Unused vehicles: ");
            if (unusedVehicles.isEmpty()) {
                solutionDescription.append("none\n");
            } else {
                for (Vehicle vehicle : unusedVehicles) {
                    solutionDescription.append(vehicle + ", ");
                }
                solutionDescription.append("\n");
            }

            solutionDescription.append("Unvisited clients: ");
            if (unvisitedClients.isEmpty()) {
                solutionDescription.append("none\n");
            } else {
                for (Client client : unvisitedClients) {
                    solutionDescription.append(client + ", ");
                }
                solutionDescription.append("\n");
            }
        }

        return solutionDescription.toString();
    }
}
