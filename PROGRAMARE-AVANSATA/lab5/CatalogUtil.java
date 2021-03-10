package lab5;

import java.awt.*;
import java.io.*;
import java.net.URI;

public class CatalogUtil {
    public static void save(Catalog catalog) throws IOException {
        try (var objectOutputStream = new ObjectOutputStream(new FileOutputStream(catalog.getPath()))) {
            objectOutputStream.writeObject(catalog);
        }
    }

    public static Catalog load(String path) throws InvalidCatalogException {
        Object catalog;

        try (var objectInputStream = new ObjectInputStream(new FileInputStream(path))) {
            catalog = objectInputStream.readObject();
        } catch (IOException | ClassNotFoundException exception) {
            throw new InvalidCatalogException(exception);
        }

        return (Catalog) catalog;
    }

    public static void view(Document document) {
        Desktop desktop = Desktop.getDesktop();

        String location = document.getLocation();

        if (location.contains("http:") || location.contains("https:")) {
            try {
                URI uri = new URI(document.getLocation());
                desktop.browse(uri);
            } catch (Exception exception) {
                exception.printStackTrace();
            }
        } else {
            try {
                File file = new File(document.getLocation());
                desktop.open(file);
            } catch (Exception exception) {
                exception.printStackTrace();
            }
        }
    }
}