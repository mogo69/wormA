package com.worm.jni;

public class Teester {
	
	public static void main(String[] args) {
		AtmJniProxy atm_jni = new AtmJniProxy();
		System.out.println(atm_jni.isBlocked());
	}
}
