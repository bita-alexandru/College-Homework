import javax.swing.*;
import java.awt.*;

public class MainFrame extends JFrame {

    ConfigPanel configPanel;
    ControlPanel controlPanel;
    ShapesPanel shapesPanel;
    DrawingPanel canvas;

    public MainFrame() {
        super("My Drawing Application");
        init();
    }

    private void init() {
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        //create the components
        configPanel = new ConfigPanel(this);
        canvas = new DrawingPanel(this);
        shapesPanel = new ShapesPanel(this);
        controlPanel = new ControlPanel(this);

        //arrange the components in the container (frame)
        //JFrame uses a BorderLayout by default
        add(configPanel, BorderLayout.NORTH);
        add(canvas, BorderLayout.CENTER); //this is BorderLayout.CENTER
        add(shapesPanel, BorderLayout.EAST);
        add(controlPanel, BorderLayout.SOUTH);

        //invoke the layout manager
        pack();
    }
}