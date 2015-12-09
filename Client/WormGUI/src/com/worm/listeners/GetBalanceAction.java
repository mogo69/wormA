package com.worm.listeners;

import java.awt.event.ActionEvent;

import javax.swing.AbstractAction;

import com.worm.controller.GUIConstants.states;
import com.worm.controller.MainController;
import com.worm.jni.AtmJniProxy;

public class GetBalanceAction extends AbstractAction{

	@Override
	public void actionPerformed(ActionEvent e) {
		if (MainController.getMainControllerInstance().getUser() != null){
			MainController.getMainControllerInstance().setState(states.GET_BALANCE);
			MainController.getMainControllerInstance().getMainFrame().getScreenPanel().getScreen().setLabelOnArea("<html><center>Your balance is:<br>" + Double.toString(AtmJniProxy.getInstance().getBalance()) + " UAH</center></html>");
		}
	}

}
