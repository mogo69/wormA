package com.worm.gui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class MainFrame extends JFrame{

	private MainFrame() {
		
	}
	
	public static MainFrame getMainFrameInstance() /*throws Exception*/{
		if (mainframe == null){
			mainframe = new MainFrame();
			mainframe.configure();
		}
		return mainframe;
	}
	
	public ScreenPanel getScreenPanel(){
		return this.screen_panel;
	}
	
	public CardReaderPanel getCardReaderPanel(){
		return this.cardreader_panel;
	}
	
	private void configure() /*throws Exception*/{
		this.createElements();
		this.addElements();
		this.setMainFrameProperties();
	}
	
	private void setMainFrameProperties(){
//		this.setLayout(new CardLayout(3, 2));
		this.setResizable(false);
		this.setMaximumSize(new Dimension(WIDTH, HEIGHT));
		this.setSize(WIDTH, HEIGHT);
//		this.setBackground(Color.pink);
		this.setLocationRelativeTo(null);
		this.pack();
		this.setVisible(true);
		this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
	}
	
	private void createElements() /*throws Exception*/{
		this.createScreen();
		this.createCardReaderPanel();
		this.createKeyboardPanel();
	}
	
	private void addElements(){
		GridBagLayout gblayout = new GridBagLayout();
		this.setLayout(gblayout);
		GridBagConstraints gbconsts = new GridBagConstraints();
		gbconsts.insets = new Insets(5, 5, 5, 5);
		gbconsts.gridx = 0;
		gbconsts.gridy = 0;
		gbconsts.gridwidth = 2;
		gbconsts.gridheight = 2;
		gbconsts.weightx = gbconsts.weighty = 1.0;
		this.add(screen_panel, gbconsts);
		gbconsts.gridx = 0;
		gbconsts.gridy = 4;
		gbconsts.gridheight = 2;
		gbconsts.gridwidth = 2;
		gbconsts.weightx = gbconsts.weighty = 0.0;
		this.add(digital_panel, gbconsts);
		gbconsts.gridx = 3;
		gbconsts.gridy = 0;
		gbconsts.gridheight = 1;
		gbconsts.gridwidth = 2;
		this.add(cardreader_panel, gbconsts);
		
	}
	
	private void createKeyboardPanel(){
		digital_keyboard = DigitalKeyboard.getDigitalKeyBoard(200, 200);
		control_keyboard = ControlKeyboard.getControlKeyboardInstance(200, 200);
		digital_panel = new JPanel();
		digital_panel.setLayout(new BoxLayout(digital_panel, BoxLayout.X_AXIS));
		digital_panel.add(Box.createHorizontalGlue());
		digital_panel.add(digital_keyboard);
		digital_panel.add(Box.createRigidArea(new Dimension(20, 0)));
		digital_panel.add(control_keyboard);
	}
	
	private void createScreen() /*throws Exception*/{
		screen_panel = ScreenPanel.getScreenPanel();
//		screen_panel.setBackground(Color.pink);
	}
	
	private void createCardReaderPanel(){
		cardreader_panel = CardReaderPanel.getCardReaderPanelInstance();
		return;
	}
	
//	public static void main(String[] args) /*throws Exception*/ {
//		MainFrame mainframe = MainFrame.getMainFrameInstance();
//		mainframe.setVisible(true);
//	}
	
	private final int WIDTH = 950;
	private final int HEIGHT = (int) (WIDTH*0.5);
	private ScreenPanel screen_panel;
	private CardReaderPanel cardreader_panel;
	private ControlKeyboard control_keyboard;
	private DigitalKeyboard digital_keyboard;
	
	private JPanel digital_panel;
	private static MainFrame mainframe;
}
