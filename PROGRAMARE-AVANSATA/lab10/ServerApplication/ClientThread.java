package ServerApplication;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class ClientThread {
    private Socket socket;

    public ClientThread(Socket socket) {
        this.socket = socket;
    }

    enum returnValues {
        OK,
        EXCEPTION,
        STOP
    }

    public int start() {
        try {
            System.out.println("New client.");

            while (true) {
                BufferedReader in = new BufferedReader(
                        new InputStreamReader(socket.getInputStream()));
                String request = in.readLine();

                PrintWriter out = new PrintWriter(socket.getOutputStream());
                String response;

                System.out.println(request);

                if (request.equals("exit")) {
                    break;
                } else if (request.equals("stop")) {
                    response = "Server stopped";

                    out.println(response);
                    out.flush();

                    return returnValues.STOP.ordinal();
                } else {
                    response = "Server received the request ...";

                    out.println(response);
                    out.flush();
                }
            }

            return returnValues.OK.ordinal();
        } catch (IOException e) {
            System.out.println("Buffer error: " + e);
            return returnValues.EXCEPTION.ordinal();
        } finally {
            try {
                socket.close();
            } catch (IOException e) {
                System.out.println("Socket error: " + e);
            }
        }
    }
}
