package com.worm.gui;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.util.LinkedHashMap;
import java.util.Map;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.border.SoftBevelBorder;

import com.worm.listeners.DigitKeyListener;

public class ControlKeyboard extends JPanel{

	private ControlKeyboard(int width, int height) {
		this.setPreferredSize(new Dimension(width, height));
	}
	
	public static ControlKeyboard getControlKeyboardInstance(int width, int height){
		if (control_keyboard == null){
			control_keyboard = new ControlKeyboard(width, height);
			control_keyboard.configure();
		}
		return control_keyboard;
	}
	
	private void configure(){
		setPanelProperties();
		initializeButtons();
		configureButtons();
		addButtons();
	}
	
	private void setPanelProperties(){
		GridLayout grid = new GridLayout(4, 3, 3, 3);
		this.setLayout(grid);
		this.setBackground(Color.darkGray);
	}
	
	private void initializeButtons() {
		buttons = new LinkedHashMap<Integer, JButton>();
		buttons.put(1, new JButton("Enter"));
		buttons.put(2, new JButton("Clear"));
		buttons.put(3, new JButton("Cancel"));
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
	
	Map<Integer, JButton> buttons;
	
	private static ControlKeyboard control_keyboard;
}
