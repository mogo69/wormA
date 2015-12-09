package com.worm.controller;

public class GUIConstants {

	public GUIConstants() {
		
	}
	
	public static String[] getDefaultLeftCaptions(){
		return default_captions[0];
	}
	
	public static String[] getDefaultRightCaptions(){
		return default_captions[1];
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
	
	public static String[] getGetBalanceLeftCaptions(){
		return get_balance_captions[0];
	}
	
	public static String[] getGetBalanceRightCaptions(){
		return get_balance_captions[1];
	}
	
	public static String[] getGetCashLeftCaptions(){
		return get_cash_captions[0];
	}
	
	public static String[] getGetCashRightCaptions(){
		return get_cash_captions[1];
	}
	
	private static final String[][] default_captions = {{"", "", "", ""}, {"", "", "", ""}};
	private static final String[][] login_captions = {{"", "", "", "Exit"}, {"", "", "", "Confirm"}};
	private static final String[][] main_menu_captions = {{"", "Change PIN", "Donate", "Exit"}, {"", "Send money", "Check balance", "Get cash"}};
	private static final String[][] blocked_captions = {{"", "", "", "Exit"}, {"", "", "", ""}};
	private static final String[][] get_balance_captions = {{"", "", "", "Exit"}, {"", "", "", "Back"}};
	private static final String[][] get_cash_captions = {{"", "", "", "Exit"}, {"", "", "Back", "Get this sum"}}; 
	
	public enum states {DEFAULT, LOGIN, MAIN_MENU, GET_CASH, GET_BALANCE, BLOCKED};
}
