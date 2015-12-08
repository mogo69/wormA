package com.worm.listeners;

import java.awt.event.ActionEvent;

import javax.swing.AbstractAction;

import com.worm.controller.*;
import com.worm.controller.GUIConstants.states;

public class GetCashAction extends AbstractAction{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	@Override
	public void actionPerformed(ActionEvent e) {
		MainController.getMainControllerInstance().setState(states.GET_CASH);
	}

}