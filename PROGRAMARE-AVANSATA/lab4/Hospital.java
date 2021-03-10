package lab4;

import java.util.ArrayList;
import java.util.List;

public class Hospital implements Comparable<Hospital> {
    private String name;
    private int capacity;
    private List<Resident> preferences;
    private List<Resident> assigned;

    public Hospital(String name, int capacity) {
        this.name = name;
        this.capacity = capacity;
        preferences = new ArrayList<>();
        assigned = new ArrayList<>();
    }

    public String getName() {
        return name;
    }

    public int getCapacity() {
        return capacity;
    }

    public List<Resident> getAssigned() {
        return assigned;
    }

    public List<Resident> getPreferences() {
        return preferences;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setCapacity(int capacity) {
        this.capacity = capacity;
    }

    public void setPreferences(List<Resident> preferences) {
        this.preferences = preferences;
    }

    public void setAssigned(List<Resident> assigned) {
        this.assigned = assigned;
    }

    public void addPreference(Resident resident) {
        preferences.add(resident);
    }

    public void assign(Resident resident) {
        assigned.add(resident);
    }

    @Override
    public String toString() {
        return name;
    }

    @Override
    public int compareTo(Hospital hospital) {
        return this.getName().compareTo(hospital.getName());
    }
}
