package com.worm.jni;

public class Teester {

	static {
//		System.setProperty("java.library.path", "/home/michael/Documents/Programming/C++/MOOP/Project/wormA/Client");
	}
	
	public static void main(String[] args) {
		System.out.println(System.getProperty("java.library.path"));
		System.load("/home/michael/Documents/Programming/C++/MOOP/Project/wormA/Client/libatmjniproxy.so");
//		AtmJniProxy atm_jni = new AtmJniProxy();
//		System.out.println(atm_jni.isBlocked());
	}
}
