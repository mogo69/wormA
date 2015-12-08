package com.worm.gui;

import javax.swing.text.AttributeSet;
import javax.swing.text.BadLocationException;
import javax.swing.text.PlainDocument;

public class TextFieldLimit extends PlainDocument{

	private static final long serialVersionUID = 1L;

	public TextFieldLimit(int limit){
		super();
		this.limit = limit;
	}
	
	public void insertString(int offset, String str, AttributeSet attr) throws BadLocationException{
		if (str != null){
			if (this.getLength() + str.length() <= limit){
				super.insertString(offset, str, attr);
			}
		}
		return;
	}
	
	private int limit;
}
