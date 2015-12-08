package com.worm.model;

public class User {
	
	private User(long cardN){
		this.cardN = cardN;
	}
	
	public static User getUserInstance(long cardN){
		if (user == null){
			user = new User(cardN);
		}
		return user;
	}
	
	public void setCardN(long cardN){
		this.cardN = cardN;
		return;
	}
	
	public long getCardN(){
		return this.cardN;
	}
	
	public void setBalance(double balance){
		this.balance = balance;
		return;
	}
	
	public double getBalance(){
		return this.balance;
	}
	
	private long cardN;
	private boolean isBlocked = false;
	private double balance;
	
	private static User user;
}
