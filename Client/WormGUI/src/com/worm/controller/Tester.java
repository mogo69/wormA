package com.worm.controller;
import com.worm.controller.GUIConstants.states;

public class Tester {

	public static void main(String[] args) {
		MainController controller = MainController.getMainControllerInstance();
		controller.setState(states.DEFAULT);
		controller.getMainFrame().setVisible(true);
	}
}
