package com.worm.gui;

public class StaticElements {

	public StaticElements() {
		
	}
	
	public static String[] getLoginLeftCaptions(){
		return login_captions[0];
	}
	
	public static String[] getLoginRightCaptions(){
		return login_captions[1];
	}
	
	public static String[] getMainMenuLeftCaptions(){
		return main_menu_captions[0];
	}
	
	public static String[] getMainMenuRightCaptions(){
		return main_menu_captions[1];
	}
	
	private static final String[][] login_captions = {{"", "", "", "Exit"}, {"", "", "", "Confirm"}};
	private static final String[][] main_menu_captions = {{"", "Change PIN", "Donate", "Exit"}, {"", "Check balance", "Send money", "Get cash"}};
}
