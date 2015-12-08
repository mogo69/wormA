package com.worm.gui;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.dnd.DropTarget;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.border.SoftBevelBorder;

import com.worm.listeners.CardDragAndDropListener;

public class CardReader extends JPanel{
	
	private static final long serialVersionUID = 1L;

	public static CardReader getCardReaderInstance(){
		if (cardreader == null){
			cardreader = new CardReader();
			cardreader.configure();
		}
		return cardreader;
	}
	
	public void disableListener(){
//		this.droptarget = null;
//		this.cardDnDListener = null;
		return;
	}
	
	private void configure(){
		setCardReaderProperties();
		createCardNumField();
		addElements();
		return;
	}
	
	public void setReaderText(String text){
		this.card_num_field.setText(text);
		return;
	}
	
	
	
	public JLabel getCardNumField() {
		return card_num_field;
	}

	private void setCardReaderProperties(){
		cardDnDListener = new CardDragAndDropListener();
		droptarget = new DropTarget(this, cardDnDListener);
		this.setPreferredSize(new Dimension(225, 100));
		this.setBorder(new SoftBevelBorder(SoftBevelBorder.RAISED));
		return;
	}
	
	private void createCardNumField(){
		card_num_field = new JLabel("<html><center>Drag N' Drop<br>your card here!</center>", SwingConstants.CENTER);
		card_num_field.setPreferredSize(new Dimension(200, 30));
	}
	
	private void addElements(){
		this.add(card_num_field, BorderLayout.CENTER);
	}
	
	private JLabel card_num_field;
	private CardDragAndDropListener cardDnDListener;
	private DropTarget droptarget;
	
	private static CardReader cardreader;
}
