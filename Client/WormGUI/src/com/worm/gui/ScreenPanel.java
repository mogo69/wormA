package com.worm.gui;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionListener;
import java.util.LinkedHashMap;
import java.util.Map;

import javax.swing.Box;
import javax.swing.JButton;
import javax.swing.JPanel;

public class ScreenPanel extends JPanel{

	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	public static  ScreenPanel getScreenPanel() /*throws Exception*/{
		if (screen_panel == null){
			screen_panel = new ScreenPanel();
			screen_panel.configureScreenPanel();
		}
		return screen_panel;
	}
	
	private void configureScreenPanel() /*throws Exception*/{
		this.setScreenPanelProperties();
		this.createButtons();
		this.configureButtons();
		this.createScreen();
		this.addElements();
	}
	
	public Screen getScreen(){
		return this.screen;
	}
	
	public void setButtonListener(boolean side, int numberOfButton, ActionListener listener){
		if (side){
			this.left_buttons.get(numberOfButton).addActionListener(listener);
		} else {
			this.right_buttons.get(numberOfButton).addActionListener(listener);
		}
	}
	
	private void createButtons(){
		left_buttons_panel = Box.createVerticalBox();
		right_buttons_panel = Box.createVerticalBox();
		left_buttons = new LinkedHashMap<Integer, JButton>();
		right_buttons = new LinkedHashMap<Integer, JButton>();
		for (int i = 0; i < 4; ++i){
			left_buttons.put(i, new JButton("      >"));
			right_buttons.put(i, new JButton("<      "));
		}
		return;
	}
	
	private void configureButtons(){
		Font bfont = new Font("Arial", Font.BOLD, 20);
		Dimension buttons_dim = new Dimension(80, 50);
		Dimension panels_dim = new Dimension(120, 60);
		for (int i = 0; i < 4; ++i){
			left_buttons.get(i).setPreferredSize(buttons_dim);
			right_buttons.get(i).setPreferredSize(buttons_dim);
			left_buttons.get(i).setAlignmentX(Component.CENTER_ALIGNMENT);
			right_buttons.get(i).setAlignmentX(Component.CENTER_ALIGNMENT);
			left_buttons.get(i).setFocusPainted(false);
			right_buttons.get(i).setFocusPainted(false);
			left_buttons.get(i).setFont(bfont);
			right_buttons.get(i).setFont(bfont);
		}
		left_buttons_panel.setPreferredSize(panels_dim);
		right_buttons_panel.setPreferredSize(panels_dim);
		left_buttons_panel.add(Box.createVerticalGlue());
		right_buttons_panel.add(Box.createVerticalGlue());
		return;
	}
	
	private void createScreen() /*throws Exception*/{
		screen = Screen.getScreen();
		String[] left_captions = {"", "Get cash", "Change PIN", "Exit"};
		String[] right_captions = {"", "", "Check balanse", "Confirm"};
		screen.setLeftCaptions(left_captions);
		screen.setRightCaptions(right_captions);
		screen.setLabelOnArea("Welcome to ATM!");
	}
	
	private void addElements(){
		this.add(screen, BorderLayout.CENTER);
		for (Map.Entry<Integer, JButton> entry : left_buttons.entrySet()) {
			left_buttons_panel.add(entry.getValue());
			left_buttons_panel.add(Box.createRigidArea(new Dimension(0, 20)));
		}
		this.add(left_buttons_panel, BorderLayout.LINE_START);
		for (Map.Entry<Integer, JButton> entry : right_buttons.entrySet()) {
			right_buttons_panel.add(entry.getValue());
			right_buttons_panel.add(Box.createRigidArea(new Dimension(0, 20)));
		}
		this.add(right_buttons_panel, BorderLayout.LINE_END);
	}
	
	private void setScreenPanelProperties() {
		BorderLayout border_layout = new BorderLayout();
		this.setLayout(border_layout);
		this.setPreferredSize(new Dimension(850, 400));
	}
	
	private static ScreenPanel screen_panel;
	
	private Screen screen;
	private Box left_buttons_panel;
	private Box right_buttons_panel;
	private Map<Integer, JButton> left_buttons;
	private Map<Integer, JButton> right_buttons;
}
