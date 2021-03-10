import javax.swing.*;
import javax.swing.event.ChangeEvent;

public class ConfigPanel extends JPanel {
    final MainFrame frame;
    JLabel sidesLabel; // we’re drawing regular polygons
    JSpinner sidesField; // number of sides
    JComboBox colorCombo; // the color of the shape

    JLabel radiusLabel;
    JSpinner radiusField;

    public ConfigPanel(MainFrame frame) {
        this.frame = frame;
        init();
    }

    private void init() {
        //create the label and the spinner
        sidesLabel = new JLabel("Number of sides:");
        sidesField = new JSpinner(new SpinnerNumberModel(6, 3, 100, 1));
        sidesField.addChangeListener(this::changeSides);

        radiusLabel = new JLabel("Radius:");
        radiusField = new JSpinner(new SpinnerNumberModel(50, 50, 300, 10));

        //create the colorCombo, containing the values: Random and Black
        colorCombo = new JComboBox(new String[]{"Random", "Black"});

        add(radiusLabel);
        add(radiusField);
        add(sidesLabel); //JPanel uses FlowLayout by default
        add(sidesField);
        add(colorCombo);
    }

    private void changeSides(ChangeEvent changeEvent) {
        int selectedShape = frame.shapesPanel.list.getSelectedIndex();
        int sidesValue = (int) sidesField.getValue();

        if (selectedShape != 0) {
            if (selectedShape == 1 && sidesValue != 3) frame.shapesPanel.list.setSelectedIndex(0);
            else if (selectedShape == 2 && sidesValue != 4) frame.shapesPanel.list.setSelectedIndex(0);
            else if (selectedShape == 3 && sidesValue != 100) frame.shapesPanel.list.setSelectedIndex(0);
        }
    }
}