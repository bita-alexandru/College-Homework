import javax.swing.*;
import javax.swing.event.ListSelectionEvent;

public class ShapesPanel extends JPanel {
    final MainFrame frame;
    JList list;

    public ShapesPanel(MainFrame frame) {
        this.frame = frame;
        init();
    }

    private void init() {
        list = new JList(new String[]{"Free Form", "Triangle", "Square", "Circle"});
        list.setSelectedIndex(0);
        add(list);

        list.addListSelectionListener(this::selection);
    }

    private void selection(ListSelectionEvent listSelectionEvent) {
        switch (list.getSelectedIndex()) {
            case 1:
                frame.configPanel.sidesField.setValue(3);
                break;
            case 2:
                frame.configPanel.sidesField.setValue(4);
                break;
            case 3:
                frame.configPanel.sidesField.setValue(100);
                break;
            default:
                break;
        }
    }
}
