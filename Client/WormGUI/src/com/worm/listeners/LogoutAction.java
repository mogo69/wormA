package com.worm.listeners;

import java.awt.event.ActionEvent;
import java.io.IOException;

import javax.swing.AbstractAction;

import com.worm.controller.MainController;
import com.worm.jni.AtmJniProxy;
import com.worm.controller.GUIConstants.states;

public class LogoutAction extends AbstractAction {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	@Override
	public void actionPerformed(ActionEvent e) {
		if (AtmJniProxy.getInstance().logOut()) {
			if (MainController.getMainControllerInstance().getUser() != null) {
				MainController.getMainControllerInstance().setUser(null);
			}
		}
//		try {
//			Runtime.getRuntime().exec("eject");
//		} catch (IOException e1) {
//			// TODO Auto-generated catch block
//			e1.printStackTrace();
//		}
		MainController.getMainControllerInstance().setState(states.DEFAULT);
	}

}
