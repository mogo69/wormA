package com.worm.model;

public class User {
	
	public User(String cardN){
		this.cardN = cardN;
	}
	
	public static User getUserInstance(String cardN){
		if (user == null){
			user = new User(cardN);
		}
		return user;
	}
	
	public void setCardN(String cardN){
		this.cardN = cardN;
		return;
	}
	
	public String getCardN(){
		return this.cardN;
	}
	
	public void setBalance(double balance){
		this.balance = balance;
		return;
	}
	
	public double getBalance(){
		return this.balance;
	}
	
	private String cardN;
	private boolean isBlocked = false;
	private double balance;
	
	private static User user;
}
