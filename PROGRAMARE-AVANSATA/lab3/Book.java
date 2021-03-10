package lab3;

public class Book implements Item {
    private String name;
    private int pageNumber; //→ getWeight
    private double value;

    public Book(String name, int pageNumber, double value) {
        this.name = name;
        this.pageNumber = pageNumber;
        this.value = Math.round(value * 100.0) / 100.0;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setPageNumber(int pageNumber) {
        this.pageNumber = pageNumber;
    }

    public void setValue(double value) {
        this.value = value;
    }

    public String getName() {
        return name;
    }

    public double getValue() {
        return value;
    }

    public double getWeight() {
        return pageNumber;
    }
}
