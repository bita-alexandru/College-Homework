package lab4;

import java.util.ArrayList;
import java.util.List;

public class Resident {
    private String name;
    private List<Hospital> preferences;
    private Hospital assigned;

    public Resident(String name) {
        this.name = name;
        preferences = new ArrayList<>();
        assigned = null;
    }

    public String getName() {
        return name;
    }

    public List<Hospital> getPreferences() {
        return preferences;
    }

    public Hospital getAssigned() {
        return assigned;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setPreferences(List<Hospital> preferences) {
        this.preferences = preferences;
    }

    public void addPrefence(Hospital hospital) {
        preferences.add(hospital);
    }

    public void assign(Hospital hospital) {
        assigned = hospital;
    }

    @Override
    public String toString() {
        return name;
    }
}
