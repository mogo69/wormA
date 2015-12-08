package com.worm.gui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Map.Entry;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.border.Border;
import javax.swing.border.SoftBevelBorder;

public class Screen extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public Screen() {
	}

	public static Screen getScreen() {
		if (screen == null) {
			screen = new Screen();
			screen.configure();
		}
		return screen;
	}

	public void addTextToField(String text){
		if (this.textfield != null && this.textfield.isEnabled()){
			textfield.setText(textfield.getText().concat(text));
		}
	}
	
	private void configure() {
		this.setScreenProperties();
		this.createCaptions();
		this.configureCaptions();
		this.createCentralArea();
		this.configureCentralArea();
		this.addElements();
	}

	private void setScreenProperties() {
		BorderLayout border_layout = new BorderLayout();
		this.setLayout(border_layout);
		this.add(Box.createHorizontalGlue());
		this.setPreferredSize(new Dimension(450, 350));
		this.setBorder(new SoftBevelBorder(SoftBevelBorder.LOWERED));
//		this.setBackground(Color.pink);
	}

	private void createCaptions() {
		left_panel = Box.createVerticalBox();
		right_panel = Box.createVerticalBox();
		left_captions = new LinkedHashMap<Integer, JLabel>();
		right_captions = new LinkedHashMap<Integer, JLabel>();
		for (int i = 3; i >= 0; --i) {
			left_captions.put(i, new JLabel());
			right_captions.put(i, new JLabel());
		}
		return;
	}

	private void configureCaptions() /* throws Exception */ {
		Font bfont = new Font("Arial", Font.BOLD, 12);
		for (int i = 3; i >= 0; --i) {
			this.left_captions.get(i).setText("");
			this.right_captions.get(i).setText("");
			this.left_captions.get(i).setFont(bfont);
			this.right_captions.get(i).setFont(bfont);
			this.left_captions.get(i).setAlignmentX(Component.LEFT_ALIGNMENT);
			this.right_captions.get(i).setAlignmentX(Component.RIGHT_ALIGNMENT);
		}
		/*
		 * else { throw new Exception("Your captions lists ara not correct!"); }
		 */
		left_panel.add(Box.createVerticalGlue());
		right_panel.add(Box.createVerticalGlue());
		left_panel.setPreferredSize(new Dimension(130, 450));
		right_panel.setPreferredSize(new Dimension(130, 450));
		left_panel.setAlignmentX(Component.LEFT_ALIGNMENT);
		right_panel.setAlignmentX(Component.RIGHT_ALIGNMENT);
		// left_panel.add(Box.createRigidArea(new Dimension(0, 10)));
		// right_panel.add(Box.createRigidArea(new Dimension(0, 10)));
		return;
	}

	public void setLeftCaptions(String[] left_captions) {
		int i = 0;
		for (Map.Entry<Integer, JLabel> entry : this.left_captions.entrySet()) {
			if (left_captions[i] == null) {
				break;
			} else {
				entry.getValue().setText(left_captions[i]);
				++i;
				continue;
			}
		}
		return;
	}

	public void setRightCaptions(String[] right_captions) {
		int i = 0;
		for (Map.Entry<Integer, JLabel> entry : this.right_captions.entrySet()) {
			if (right_captions[i] == null) {
				break;
			} else {
				entry.getValue().setText(right_captions[i]);
				++i;
				continue;
			}
		}
		return;
	}

	/**
	 * IDs of captions, which user want to make invisible.
	 * 
	 * @param left_captions;
	 * @param right_captions;
	 */
	// public void setCaptionsVisibility(int[] left_captions, int[]
	// right_captions, boolean visibility){
	// for (int i : left_captions){
	// if (this.left_captions.containsKey(i)){
	// this.left_captions.get(i).setVisible(visibility);
	// }
	// }
	// for (int i : right_captions){
	// if (this.right_captions.containsKey(i)){
	// this.right_captions.get(i).setVisible(visibility);
	// }
	// }
	// return;
	// }

	// public void setAllCaptionsVisibility(boolean visibility){
	// for (int i = 0; i < 4; ++i){
	// this.left_captions.get(i).setVisible(visibility);
	// this.right_captions.get(i).setVisible(visibility);
	// }
	// return;
	// }

	private void createCentralArea() {
		central_area = new JPanel();
		return;
	}

	@SuppressWarnings("unused")
	private void configureCentralArea() {
		central_area.setAlignmentX(Component.CENTER_ALIGNMENT);
		central_area.setAlignmentY(Component.CENTER_ALIGNMENT);
		central_text = new JLabel("");
		textfield = new JTextField();
		// Textfield configuration
		central_area.add(central_text, BorderLayout.CENTER);
		central_area.add(textfield, BorderLayout.CENTER);
		central_text.setAlignmentX(Component.CENTER_ALIGNMENT);
		central_text.setAlignmentY(Component.CENTER_ALIGNMENT);
		textfield.setAlignmentX(Component.CENTER_ALIGNMENT);
		textfield.setAlignmentY(Component.CENTER_ALIGNMENT);
		textfield.setEditable(false);
		textfield.setDocument(new TextFieldLimit(4));
		Font bfont = new Font("Arial", Font.BOLD, 40);
		textfield.setFont(bfont);
		textfield.setHorizontalAlignment(SwingConstants.CENTER);
		textfield.setBorder(BorderFactory.createLineBorder(Color.green));
//		central_text.setVisible(false);
//		central_text.setEnabled(false);
	}

	public void setLabelOnArea(String text) {
		textfield.setVisible(false);
		textfield.setEnabled(false);
		central_text.setPreferredSize(new Dimension(250, 50));
		central_text.setText(text);
		return;
	}

	public void setLabelAndTextFieldOnArea(String text) {
		if (text != null){
			central_text.setText(text);
		}
		textfield.setPreferredSize(new Dimension(150, 50));
		textfield.setEnabled(true);
		textfield.setVisible(true); 
		return;
	}

	private void addElements() {
		this.add(central_area, BorderLayout.CENTER);
		for (Map.Entry<Integer, JLabel> entry : left_captions.entrySet()) {
			left_panel.add(Box.createRigidArea(new Dimension(0, 55)));
			left_panel.add(entry.getValue());
		}
		for (Map.Entry<Integer, JLabel> entry : right_captions.entrySet()) {
			right_panel.add(Box.createRigidArea(new Dimension(0, 55)));
			right_panel.add(entry.getValue());
		}
		left_panel.add(Box.createRigidArea(new Dimension(0, 35)));
		right_panel.add(Box.createRigidArea(new Dimension(0, 35)));
		this.add(left_panel, BorderLayout.LINE_START);
		this.add(right_panel, BorderLayout.LINE_END);
		return;
	}

	private JPanel central_area;
	private JLabel central_text;
	private JTextField textfield;

	private Box left_panel;
	private Box right_panel;
	private Map<Integer, JLabel> left_captions;
	private Map<Integer, JLabel> right_captions;

	private static Screen screen;
}
