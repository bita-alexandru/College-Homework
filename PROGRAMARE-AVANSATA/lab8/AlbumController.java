package lab8;

import java.sql.*;

public class AlbumController {
    private Connection connection;
    private PreparedStatement preparedStatement;
    private String sql;

    public AlbumController(Connection connection) {
        this.connection = connection;
    }

    public void create(String name, int artistId, int releaseYear) {
        sql = "INSERT INTO albums COLUMNS(name,artist_id,release_year) VALUES(?,?,?)";

        try {
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, name);
            preparedStatement.setInt(2, artistId);
            preparedStatement.setInt(3, releaseYear);
            preparedStatement.executeUpdate();
            System.out.println("[\"" + name + "\" by artist_id " + artistId + " from " + releaseYear + " registered]");
        } catch (SQLException e) {
            System.err.println("Failed to create new record: " + e);
        }
    }

    public void findByArtist(int artistId) {
        System.out.println("Request to search albums from artist_id " + artistId);

        sql = "SELECT * FROM albums WHERE artist_id=?";

        try {
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setInt(1, artistId);

            ResultSet resultSet = preparedStatement.executeQuery();
            ResultSetMetaData resultSetMetaData = resultSet.getMetaData();

            if (resultSet.next() == false) {
                System.out.println("Couldn't find any album from artist_id " + artistId);
                return;
            }

            do {
                System.out.println(resultSetMetaData.getColumnName(1) + ":{" + resultSet.getInt(1)
                        + "}\t" + resultSetMetaData.getColumnName(2) + ":{" + resultSet.getString(2)
                        + "}\t" + resultSetMetaData.getColumnName(3) + ":{" + resultSet.getString(3)
                        + "}\t" + resultSetMetaData.getColumnName(4) + ":{" + resultSet.getString(4)
                        + "}");
            } while (resultSet.next());
        } catch (SQLException e) {
            System.err.println("Something went wrong: " + e);
        }
    }
}
