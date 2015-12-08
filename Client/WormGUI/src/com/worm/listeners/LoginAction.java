package com.worm.listeners;

import java.awt.event.ActionEvent;

import javax.swing.AbstractAction;

import com.worm.controller.MainController;
import com.worm.controller.GUIConstants.states;

public class LoginAction extends AbstractAction{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	@Override
	public void actionPerformed(ActionEvent e) {
//		if (atm.logIn(new SWIGTYPE_p_string(456, true), 567657)){
//			MainController.getMainControllerInstance().setState(states.MAIN_MENU);
//		}
		MainController.getMainControllerInstance().setState(states.MAIN_MENU);
	}

}
