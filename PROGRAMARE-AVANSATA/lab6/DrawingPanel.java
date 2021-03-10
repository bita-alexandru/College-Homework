import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.geom.Point2D;
import java.awt.geom.RectangularShape;
import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.List;

public class DrawingPanel extends JPanel {
    final MainFrame frame;
    final static int W = 800, H = 600;
    BufferedImage image; //the offscreen image
    Graphics2D graphics; //the "tools" needed to draw in the image
    List<Shape> shapes;
    List<Color> colors;

    public DrawingPanel(MainFrame frame) {
        this.frame = frame;
        shapes = new ArrayList<>();
        colors = new ArrayList<>();
        createOffscreenImage();
        init();
    }

    void createOffscreenImage() {
        image = new BufferedImage(W, H, BufferedImage.TYPE_INT_ARGB);
        graphics = image.createGraphics();
        graphics.setColor(Color.WHITE); //fill the image with white
        graphics.fillRect(0, 0, W, H);
    }

    private void init() {
        setPreferredSize(new Dimension(W, H)); //don’t use setSize. Why?
        setBorder(BorderFactory.createEtchedBorder()); //for fun
        this.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent event) {
                switch (event.getButton()) {
                    case MouseEvent.BUTTON1: // leftclick -> draw shape
                        drawShape(event.getX(), event.getY());
                        repaint();
                        break;
                    case MouseEvent.BUTTON3: // rightclick -> remove shape
                        removeShape(event.getX(), event.getY());
                        repaint();
                    default:
                        break;
                }
            } //Can’t use lambdas, JavaFX does a better job in these cases
        });
    }

    private void removeShape(int x, int y) {
        for (int i = 0; i < shapes.size(); i++) {
            if (shapes.get(i).contains(new Point(x, y))) {
                shapes.remove(i);
                colors.remove(i);
                break;
            }
        }
    }

    private void drawShape(int x, int y) {
        int radius = (int) frame.configPanel.radiusField.getValue();
        int sides = (int) frame.configPanel.sidesField.getValue(); //get the value from UI (in ConfigPanel)

        int R = (int) (Math.random() * 256);
        int G = (int) (Math.random() * 256);
        int B = (int) (Math.random() * 256);
        Color color = new Color(R, G, B, 50);
        //create a transparent random Color.

        if (frame.configPanel.colorCombo.getSelectedIndex() == 1) {
            color = Color.BLACK;
        }

        RegularPolygon polygon = new RegularPolygon(x, y, radius, sides);
        shapes.add(polygon);
        colors.add(color);
    }

    @Override
    public void update(Graphics graphics) {

    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.drawImage(image, 0, 0, this);
        for (int i = 0; i < shapes.size(); i++) {
            g.setColor(colors.get(i));
            g.fillPolygon((Polygon) shapes.get(i));
        }
    }
}
