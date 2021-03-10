package lab8;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;

public class Database {
    private  static Connection connection;
    private static Statement statement;

    public static Connection get() {
        if (connection != null) {
            return connection;
        }

        String url = "jdbc:oracle:thin:@localhost:1521:XE";
        String username = "alex";
        String password = "sql";

        try {
            connection = DriverManager.getConnection(url, username, password);
            statement = connection.createStatement();

            System.out.println("[connection succes]");

            return connection;
        } catch (SQLException e) {
            System.err.println("Failed to connect: " + e);
            return null;
        }
    }

    public static void clear() {
        if (connection != null) {
            try {
                // disable constraint so to clear the tables and enable it again after
                statement.executeUpdate("ALTER TABLE albums DISABLE CONSTRAINT SYS_C007004");
                statement.executeUpdate("TRUNCATE TABLE artists");
                statement.executeUpdate("TRUNCATE TABLE albums");
                statement.executeUpdate("TRUNCATE TABLE charts");
                statement.executeUpdate("ALTER TABLE albums ENABLE CONSTRAINT SYS_C007004");

                // delete sequences so the id's restart from 1
                statement.executeUpdate("DROP SEQUENCE artists_seq");
                statement.executeUpdate("DROP SEQUENCE albums_seq");
                statement.executeUpdate("CREATE SEQUENCE artists_seq START WITH 1");
                statement.executeUpdate("CREATE SEQUENCE albums_seq START WITH 1");

                System.out.println("[tables cleared]");
            } catch (SQLException e) {
                System.err.println("Failed to clear tables: " + e);
            }
        }
    }
}
