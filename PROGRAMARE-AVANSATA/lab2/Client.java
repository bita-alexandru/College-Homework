package lab2;

public class Client {
    private String name;
    private int order;

    public Client() {
    }

    public Client(String name, int order) {
        this.name = name;
        this.order = order;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setOrder(int order) {
        this.order = order;
    }

    public int getOrder() {
        return order;
    }

    @Override
    public String toString() {
        return name;
    }
}
