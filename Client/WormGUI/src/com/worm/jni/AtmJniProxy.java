package com.worm.jni;

public class AtmJniProxy {

	public native boolean isBlocked();
	public native boolean logIn(String cardN, int PIN);
	public native boolean logOut();
	public native boolean changePIN(int PIN);
	public native String getAdvert();
	public native double getBalance();
	public native boolean canWithdraw(int sum);
	public native boolean withdraw(long amount, boolean useCreditMoney);
	public native boolean getDataAbout(int cardN);
	public native boolean sendMoneyTo(int cardN);

}
