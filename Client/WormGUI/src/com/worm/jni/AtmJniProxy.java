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

	public static AtmJniProxy getInstance(){
		if (atm_jni_proxy == null){
			System.loadLibrary("AtmJniProxy");
			System.out.println(System.getProperty("java.library.path"));
			atm_jni_proxy = new AtmJniProxy();
		}
		return atm_jni_proxy;
	}
	
	public static void main(String[] args){
//		System.setProperty("java.library.path", "/home/michael/Documents/Programming/C++/MOOP/Project/wormA/Client");
//		System.loadLibrary("AtmJniProxy");
		AtmJniProxy atmj = AtmJniProxy.getInstance();	
//		System.out.println(atmj.logIn("6771909456273272", 7709));
//		System.out.println(atmj.getBalance());
		System.out.println(atmj.logOut());
	}

	private static AtmJniProxy atm_jni_proxy;
}
