import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.WindowEvent;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class ControlPanel extends JPanel {
    final MainFrame frame;
    JButton saveBtn = new JButton("Save");
    //create all buttons (Load, Reset, Exit)
    JButton loadBtn = new JButton("Load");
    JButton resetBtn = new JButton("Reset");
    JButton exitBtn = new JButton("Exit");

    public ControlPanel(MainFrame frame) {
        this.frame = frame;
        init();
    }

    private void init() {
        //change the default layout manager (just for fun)
        setLayout(new GridLayout(1, 4));
        //add all buttons
        add(saveBtn);
        add(loadBtn);
        add(resetBtn);
        add(exitBtn);
        //configure listeners for all buttons
        saveBtn.addActionListener(this::save);
        loadBtn.addActionListener(this::load);
        resetBtn.addActionListener(this::reset);
        exitBtn.addActionListener(this::exit);
    }

    private void save(ActionEvent event) {
        JFileChooser fileChooser = new JFileChooser();

        fileChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        fileChooser.setDialogTitle("Save Drawing");
        fileChooser.setApproveButtonText("Save");
        fileChooser.setAcceptAllFileFilterUsed(false);
        fileChooser.setFileFilter(new FileNameExtensionFilter(".png", "png"));

        int returnValue = fileChooser.showOpenDialog(null);

        if (returnValue == JFileChooser.APPROVE_OPTION) {
            File file = fileChooser.getSelectedFile();
            try {
                for (int i = 0; i < frame.canvas.shapes.size(); i++) {
                    frame.canvas.graphics.setColor(frame.canvas.colors.get(i));
                    frame.canvas.graphics.fill(frame.canvas.shapes.get(i));
                    frame.canvas.graphics.drawImage(frame.canvas.image, 0, 0, frame.canvas);
                }

                ImageIO.write(frame.canvas.image, "PNG", (file.getAbsolutePath().endsWith(".png") ?
                        file : new File(file.getAbsolutePath() + ".png")));
            } catch (IOException exception) {
                System.err.println(exception);
            }
        }
    }

    private void load(ActionEvent event) {
        JFileChooser fileChooser = new JFileChooser();

        int returnValue = fileChooser.showOpenDialog(null);

        if (returnValue == JFileChooser.APPROVE_OPTION) {
            try {
                frame.canvas.image = ImageIO.read(fileChooser.getSelectedFile());
                frame.canvas.revalidate();
                frame.canvas.repaint();
            } catch (IOException exception) {
                System.err.println(exception);
            }
        }
    }

    private void reset(ActionEvent event) {
        frame.canvas.shapes.clear();
        frame.canvas.colors.clear();

        frame.canvas.createOffscreenImage();
        frame.canvas.revalidate();
        frame.canvas.repaint();
    }

    private void exit(ActionEvent event) {
        System.exit(0);
    }
}