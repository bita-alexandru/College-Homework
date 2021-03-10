package ServerApplication;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class GameServer {
    private ServerSocket serverSocket;
    private final int PORT = 1234;

    enum returnValues {
        OK,
        EXCEPTION,
        STOP
    }

    public GameServer() {

        try {
            serverSocket = new ServerSocket(PORT);

            while (true) {
                System.out.println("Waiting for a client...");

                Socket socket = serverSocket.accept();

                if (new ClientThread(socket).start() == returnValues.STOP.ordinal()) {
                    System.out.println("Server is stopping...");
                    break;
                }
            }
        } catch (IOException e) {
            System.out.println("Socket error: " + e);
        }
    }
}
