package lab8;

import java.sql.*;

public class ArtistController {
    private Connection connection;
    private PreparedStatement preparedStatement;
    private String sql;

    public ArtistController(Connection connection) {
        this.connection = connection;
    }

    public void create(String name, String country) {
        sql = "INSERT INTO artists COLUMNS(name,country) VALUES(?,?)";

        try {
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, name);
            preparedStatement.setString(2, country);
            preparedStatement.executeUpdate();

            preparedStatement = connection.prepareStatement("SELECT artists_seq.currval FROM DUAL");
            ResultSet resultSet = preparedStatement.executeQuery();
            resultSet.next();
            System.out.println("[" + name + " from " + country + " registered with id " + resultSet.getInt(1) + "]");
        } catch (SQLException e) {
            System.err.println("Failed to create new record: " + e);
        }
    }

    public void findByName(String name) {
        System.out.println("Request to search for " + name);

        sql = "SELECT * FROM artists WHERE name LIKE ?";

        try {
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, name);

            ResultSet resultSet = preparedStatement.executeQuery();
            ResultSetMetaData resultSetMetaData = resultSet.getMetaData();

            if (resultSet.next() == false) {
                System.out.println("Couldn't find " + name);
                return;
            }

            do {
                System.out.println(resultSetMetaData.getColumnName(1) + ":{" + resultSet.getInt(1)
                        + "}\t" + resultSetMetaData.getColumnName(2) + ":{" + resultSet.getString(2)
                        + "}\t" + resultSetMetaData.getColumnName(3) + ":{" + resultSet.getString(3)
                        + "}");
            } while (resultSet.next());
        } catch (SQLException e) {
            System.err.println("Something went wrong: " + e);
        }
    }
}
