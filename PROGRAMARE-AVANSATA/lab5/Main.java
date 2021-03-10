package lab5;

import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        Main application = new Main();

        try {
            application.testCreateSave();
            application.testLoadView();
        } catch (Exception exception) {
            exception.printStackTrace();
        }
    }

    private void testCreateSave() {
        Catalog catalog = new Catalog("Java Resources", "D:/java/catalog.ser");

        Document document1 = new Document("java1", "Java Course 1", "https://profs.info.uaic.ro/~acf/java/slides/en/intro_slide_en.pdf");
        document1.addTag("type", "Slides");

        Document document2 = new Document("java2", "Same Java Course", "D:/java/intro_slide_en.pdf");
        document2.addTag("author", "Ion Creanga");

        catalog.add(document1);
        catalog.add(document2);

        try {
            CatalogUtil.save(catalog);
        } catch (IOException exception) {
            exception.printStackTrace();
        }
    }

    private void testLoadView() {
        try {
            Catalog catalog = CatalogUtil.load("d:/java/catalog.ser");

            Document document = catalog.findById("java1");
            CatalogUtil.view(document);

            document = catalog.findById("java2");
            CatalogUtil.view(document);
        } catch (Exception exception) {
            exception.printStackTrace();
        }
    }
}