package com.worm.listeners;

import java.awt.event.ActionEvent;

import javax.swing.AbstractAction;

import com.worm.controller.MainController;
import com.worm.jni.AtmJniProxy;
import com.worm.model.User;
import com.worm.controller.GUIConstants.states;

public class LoginAction extends AbstractAction {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	@Override
	public void actionPerformed(ActionEvent e) {
		cardN = MainController.getMainControllerInstance().getMainFrame().getCardReaderPanel().getCardReader()
				.getCardNumField().getText();
		PIN = Integer.parseInt(MainController.getMainControllerInstance().getMainFrame().getScreenPanel().getScreen()
				.getTextField().getText());
		boolean login_flag = AtmJniProxy.getInstance().logIn(cardN, PIN);
		System.out.println(cardN);
		System.out.println(PIN);
		System.out.println(login_flag);
		if (login_flag) {
			MainController.getMainControllerInstance().setUser(new User(cardN));
			MainController.getMainControllerInstance().setState(states.MAIN_MENU);
		}
	}

	private String cardN = "";
	private int PIN = 0;

}
