package lab2;

/**
 * The Multi Depot Vehicle Scheduling Problem (MDVSP)
 * An instance of MDVSP consists of depots, vehicles and clients (trips).
 *
 * Each vehicle belongs to a single depot. It starts from there and it may return there at any time.
 * Each client has a name and a visiting time (a number of order, starting with 1).
 * Each vehicle will perform a single tour, consisting of one or more trips with strictly ascending visiting times, starting from its depot and ending in it.
 * Each trip in the timetable must be covered by a single vehicle.
 * A vehicle cannot be assigned to more than one trip at any point in time.
 */
public class Main {
    public static void main(String[] args) {
        optional(compulsory());
        bonus();
    }

    public static Problem compulsory() {
        Client[] clients = {
                new Client("C1", 1),
                new Client("C2", 1),
                new Client("C3", 2),
                new Client("C4", 2),
                new Client("C5", 3)
        };

        Vehicle[] vehicles = {
                new Car("V1"),
                new Truck("V2"),
                new Drone("V3")
        };

        Depot[] depots = {
                new Depot("D1", new Vehicle[]{vehicles[0], vehicles[1]}),
                new Depot("D2", new Vehicle[]{vehicles[2]})
        };

        Problem problem = new Problem(depots, clients);

        System.out.println(problem);

        return problem;
    }

    public static void optional(Problem problem) {
        Solution solution = new Solution();

        solution.solve(problem);

        System.out.println(solution);
    }

    public static void bonus() {

    }
}