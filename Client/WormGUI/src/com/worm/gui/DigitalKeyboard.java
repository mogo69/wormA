package com.worm.gui;

import javax.swing.JPanel;
import javax.swing.border.SoftBevelBorder;

import com.worm.listeners.DigitKeyListener;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.util.LinkedHashMap;
import java.util.Map;
import javax.swing.JButton;

public class DigitalKeyboard extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	private DigitalKeyboard(int width, int height) {
		this.setPreferredSize(new Dimension(width, height));
	}

	public static DigitalKeyboard getDigitalKeyBoard(int width, int height) {
		if (digital_keyboard == null) {
			digital_keyboard = new DigitalKeyboard(width, height);
			digital_keyboard.configure();
		}
		return digital_keyboard;
	}

	private void configure() {
		setPanelProperties();
		initializeButtons();
		configureButtons();
		addButtons();
	}

	private void setPanelProperties() {
		GridLayout grid = new GridLayout(4, 3, 3, 3);
		this.setLayout(grid);
		this.setBackground(Color.darkGray);
	}
	
	private void initializeButtons() {
		buttons = new LinkedHashMap<Integer, JButton>();
		for (int i = 1; i <= 9; ++i) {
			buttons.put(i, new JButton(Integer.toString(i)));
		}
		buttons.put(10, new JButton(""));
		buttons.put(0, new JButton("0"));
		buttons.put(11, new JButton(""));

		return;
	}

	private void configureButtons() {
		Font bfont = new Font("Arial", Font.BOLD, 40);
		for (Map.Entry<Integer, JButton> entry : buttons.entrySet()) {
			entry.getValue().setBorder(new SoftBevelBorder(SoftBevelBorder.RAISED));
			entry.getValue().setFont(bfont);
			entry.getValue().setFocusPainted(false);
			entry.getValue().addActionListener(new DigitKeyListener(entry.getKey().toString()));
		}
	}

	private void addButtons() {
		/*
		 * for (int i = 1; i <= 10; ++i){ this.add(buttons.get(i)); //
		 * System.out.println(entry.getValue().getText()); }
		 * this.add(buttons.get(0)); this.add(buttons.get(11)); //
		 * System.out.println("Size: " + buttons.size());
		 */ for (Map.Entry<Integer, JButton> entry : buttons.entrySet()) {
			this.add(entry.getValue());
		}
	}

	private static DigitalKeyboard digital_keyboard;
	Map<Integer, JButton> buttons;
}
