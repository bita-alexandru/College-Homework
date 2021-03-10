package ClientApplication;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class GameClient {
    private String serverAddress = "127.0.0.1";
    private final int PORT = 1234;

    public GameClient() {
        try {
            Socket socket = new Socket(serverAddress, PORT);

            System.out.println("Connected to the server.");

            while (true) {
                System.out.print("> ");

                BufferedReader console = new BufferedReader(new InputStreamReader(System.in));
                PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
                String request = console.readLine();

                if (request.equals("exit")) {
                    out.println(request);
                    break;
                } else {
                    out.println(request);
                }

                BufferedReader in = new BufferedReader(
                        new InputStreamReader(socket.getInputStream())
                );
                String response = in.readLine();
                System.out.println(response);
            }
        } catch (IOException e) {
            System.out.println("Socket error: " + e);
        }
    }
}
