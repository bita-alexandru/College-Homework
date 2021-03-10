package lab4;

import java.util.*;
import java.util.function.*;
import java.util.stream.*;

public class Main {

    public static void main(String[] args) {
        var residents = IntStream.rangeClosed(0, 3).mapToObj(i -> new Resident("R" + i)).toArray(Resident[]::new);

        List<Resident> residentList = new ArrayList<>();
        residentList.addAll(Arrays.asList(residents));

        Collections.sort(residentList, Comparator.comparing(Resident::getName));

        var hospitals = IntStream.rangeClosed(0, 2).mapToObj(i -> new Hospital("H" + i, Math.min(i + 1, 2))).toArray(Hospital[]::new);

        Set<Hospital> hospitalSet = new TreeSet<>();
        hospitalSet.addAll(Arrays.asList(hospitals));

        Map<Resident, List<Hospital>> residentPreferences = new HashMap<>();
        residentPreferences.put(residents[0], Arrays.asList(hospitals[0], hospitals[1], hospitals[2]));
        residentPreferences.put(residents[1], Arrays.asList(hospitals[0], hospitals[1], hospitals[2]));
        residentPreferences.put(residents[2], Arrays.asList(hospitals[0], hospitals[1]));
        residentPreferences.put(residents[3], Arrays.asList(hospitals[0], hospitals[2]));

        for (int i = 0; i < residents.length; i++) {
            residents[i].setPreferences(residentPreferences.get(residents[i]));
        }

        Map<Hospital, List<Resident>> hospitalPreferences = new TreeMap<>();
        hospitalPreferences.put(hospitals[0], Arrays.asList(residents[3], residents[0], residents[1], residents[2]));
        hospitalPreferences.put(hospitals[1], Arrays.asList(residents[0], residents[2], residents[1]));
        hospitalPreferences.put(hospitals[2], Arrays.asList(residents[0], residents[1], residents[3]));

        for (int i = 0; i < hospitals.length; i++) {
            hospitals[i].setPreferences(hospitalPreferences.get(hospitals[i]));
        }

        Arrays.stream(residents).filter(resident -> !resident.getPreferences().isEmpty() && resident.getPreferences().contains(hospitals[0]) && resident.getPreferences().contains(hospitals[2])).forEach(System.out::println);
        Arrays.stream(hospitals).filter(hospital -> !hospital.getPreferences().isEmpty() && hospital.getPreferences().get(0).getName().equals("R0")).forEach(System.out::println);
    }
}
