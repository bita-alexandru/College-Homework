package lab8;

public class Album {
    private String name;
    private String artistName;
    private int artistId;
    private int releaseYear;
    private int points;

    public Album(String name, String artistName, int artistId, int releaseYear, int points) {
        this.name = name;
        this.artistName = artistName;
        this.artistId = artistId;
        this.releaseYear = releaseYear;
        this.points = points;
    }

    public String getName() {
        return name;
    }

    public String getArtistName() {
        return artistName;
    }

    public int getArtistId() {
        return artistId;
    }

    public int getReleaseYear() {
        return releaseYear;
    }

    public int getPoints() {
        return points;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setArtistName(String artistName) {
        this.name = artistName;
    }

    public void setArtistId(int artistId) {
        this.artistId = artistId;
    }

    public void setReleaseYear(int releaseYear) {
        this.releaseYear = releaseYear;
    }

    public void setPoints(int points) {
        this.points = points;
    }
}
