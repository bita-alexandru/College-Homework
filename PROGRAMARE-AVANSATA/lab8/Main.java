package lab8;

import com.github.javafaker.Faker;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Main {
    private static ArtistController artistController;
    private static AlbumController albumController;

    public static void main(String[] args) {
        artistController = new ArtistController(Database.get());
        albumController = new AlbumController(Database.get());

        compulsory();
        optional();

        if (Database.get() != null) {
            try {
                Database.get().close();
                System.out.println("[connection closed]");
            } catch (SQLException e) {
                System.err.println("Failed to close database: " + e);
            }
        }
    }

    public static void compulsory() {
        System.out.println("---COMPULSORY---");

        Database.clear();

        System.out.println();
        artistController.create("Andrei", "Romania");
        artistController.create("Mike", "SUA");
        System.out.println();

        albumController.create("album_Andrei_1", 1, 2007);
        albumController.create("album_Andrei_2", 1, 2010);
        albumController.create("album_Andrei_3", 1, 2016);
        System.out.println();

        albumController.create("album_Mike_1", 2, 2011);
        albumController.create("album_Mike_2", 2, 2018);
        albumController.create("album_Mike_3", 2, 2020);
        System.out.println();

        artistController.findByName("Andrei");
        artistController.findByName("Stefan");
        System.out.println();

        albumController.findByArtist(1);
        albumController.findByArtist(10);
        System.out.println();
    }

    public static void optional() {
        System.out.println("---OPTIONAL---");

        Database.clear();

        System.out.println();

        Faker faker = new Faker();
        List<Artist> artists = new ArrayList<>();
        List<Album> albums = new ArrayList<>();

        final int MAX_ARTISTS = 10;

        for (int i = 1; i <= MAX_ARTISTS; i++) {
            Artist artist = new Artist(faker.name().fullName(), faker.country().name());
            Album album = new Album(faker.food().dish()
                    , artist.getName(),
                    i,
                    faker.number().numberBetween(2000, 2020),
                    faker.number().numberBetween(0, 100));

            artists.add(artist);
            albums.add(album);

            artistController.create(artist.getName(), artist.getCountry());
            albumController.create(album.getName(), album.getArtistId(), album.getReleaseYear());

            System.out.println();
        }

        Chart chart = new Chart(Database.get(), albums);
        chart.rankings();

        System.out.println();
    }
}
