package com.worm.listeners;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import com.worm.controller.MainController;

public class DigitKeyListener implements ActionListener{

	public DigitKeyListener(String number) {
		this.number = number;
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		MainController.getMainControllerInstance().getMainFrame().getScreenPanel().getScreen().addTextToField(number);
	}
	
	private String number;
	
}
