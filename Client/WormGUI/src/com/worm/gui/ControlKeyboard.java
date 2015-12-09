package com.worm.gui;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.LinkedHashMap;
import java.util.Map;

import javax.swing.AbstractAction;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.border.SoftBevelBorder;

import com.worm.controller.MainController;
import com.worm.listeners.DigitKeyListener;
import com.worm.listeners.LogoutAction;

public class ControlKeyboard extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	private ControlKeyboard(int width, int height) {
		this.setPreferredSize(new Dimension(width, height));
	}

	public static ControlKeyboard getControlKeyboardInstance(int width, int height) {
		if (control_keyboard == null) {
			control_keyboard = new ControlKeyboard(width, height);
			control_keyboard.configure();
		}
		return control_keyboard;
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
		}
		buttons.get(2).setAction(new AbstractAction() {

			/**
			 * 
			 */
			private static final long serialVersionUID = 1L;

			@Override
			public void actionPerformed(ActionEvent e) {
				JTextField field = MainController.getMainControllerInstance().getMainFrame().getScreenPanel()
						.getScreen().getTextField();
				if ((field.isEnabled()) && (field.isVisible()) && (field.getText().length() > 0)) {
					MainController.getMainControllerInstance().getMainFrame().getScreenPanel().getScreen()
							.getTextField().setText(field.getText().substring(0, field.getText().length() - 1));
				}
			}

		});
		buttons.get(3).setAction(new LogoutAction());
	}

	private void addButtons() {
		/*
		 * for (int i = 1; i <= 10; ++i){ this.add(buttons.get(i)); //
		 * System.out.println(entry.getValue().getText()); }
		 * this.add(buttons.get(0)); this.add(buttons.get(11)); //
		 * System.out.println("Size: " + buttons.size());
		 */ 
		for (Map.Entry<Integer, JButton> entry : buttons.entrySet()) {
			this.add(entry.getValue());
		}
	}

	Map<Integer, JButton> buttons;

	private static ControlKeyboard control_keyboard;
}
