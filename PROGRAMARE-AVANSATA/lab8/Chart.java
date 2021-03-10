package lab8;

import java.sql.*;
import java.util.List;

public class Chart {
    private Connection connection;
    private List<Album> albums;

    public Chart(Connection connection, List<Album> albums) {
        this.connection = connection;
        this.albums = albums;

        for (int i = 0; i < albums.size(); i++) {
            String sql = "INSERT INTO charts VALUES(?,?,?)";
            PreparedStatement preparedStatement = null;
            try {
                preparedStatement = connection.prepareStatement(sql);
                preparedStatement.setInt(1, albums.get(i).getPoints());
                preparedStatement.setString(2, albums.get(i).getName());
                preparedStatement.setString(3, albums.get(i).getArtistName());
                preparedStatement.executeUpdate();
            } catch (SQLException e) {
                System.err.println("Failed to create chart: " + e);
            }
        }

        System.out.println("[chart created]");
    }

    public void rankings() {
        try {
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery("SELECT * FROM charts ORDER BY points DESC");

            int rank = 0;

            while (resultSet.next()) {
                rank++;

                System.out.println("{" + resultSet.getString("artist_name") + "} is ranked #"
                        + rank + " {" + resultSet.getInt("points") + "p}"
                        + " with their album {" + resultSet.getString("album_name") + "}");
            }
        } catch (SQLException e) {
            System.out.println("Failed to display rankings: " + e);
        }
    }
}
