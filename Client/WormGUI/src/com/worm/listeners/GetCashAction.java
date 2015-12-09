package com.worm.listeners;

import java.awt.event.ActionEvent;

import javax.swing.AbstractAction;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

import com.worm.controller.MainController;
import com.worm.jni.AtmJniProxy;

public class GetCashAction extends AbstractAction {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	@Override
	public void actionPerformed(ActionEvent e) {
		JTextField field = MainController.getMainControllerInstance().getMainFrame().getScreenPanel().getScreen()
				.getTextField();
		if (field.getText().length() > 0) {
			int sum = Integer.parseInt(field.getText());
			if (sum != 0) {
				boolean withdraw = AtmJniProxy.getInstance().canWithdraw(sum);
				System.out.println("Withdraw: " + withdraw);
				if (withdraw) {
					double balance = AtmJniProxy.getInstance().getBalance();
					if (balance >= sum) {
						AtmJniProxy.getInstance().withdraw(sum, false);
					} else {
						int result = JOptionPane.showConfirmDialog(
								MainController.getMainControllerInstance().getMainFrame().getScreenPanel().getScreen(),
								"<html><center>You have not enough money on your account.<br>Do you want to use credit money?</center></html>",
								"Not enough", JOptionPane.YES_NO_OPTION);
						if (result == JOptionPane.YES_OPTION) {
							AtmJniProxy.getInstance().withdraw(sum, true);
						}
					}
					JOptionPane.showMessageDialog(
							MainController.getMainControllerInstance().getMainFrame().getScreenPanel().getScreen(),
							"<html><center>Operation success.<br>You had: " + balance + "UAH.<br>You have taken: " + sum
									+ "UAH.<br>Now your account sum is: " + (balance - sum) + "</center></html>",
							"Cheque", JOptionPane.INFORMATION_MESSAGE, null);
				} else {
					JOptionPane.showMessageDialog(
							MainController.getMainControllerInstance().getMainFrame().getScreenPanel().getScreen(),
							"<html><center>Sorry, ATM cannot give you this sum. <br>(Not enough money or no necessary notes).<br>Please, choose less sum.</center></html>",
							"Not enough money in ATM", JOptionPane.WARNING_MESSAGE, null);
				}
			}
		}
	}
}
