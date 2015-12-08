package com.worm.gui;

import java.awt.BorderLayout;
import java.awt.Dimension;

import javax.swing.BoxLayout;
import javax.swing.JPanel;
import javax.swing.border.Border;
import javax.swing.border.SoftBevelBorder;

public class CardReaderPanel extends JPanel{

	private static final long serialVersionUID = 1L;

	public static CardReaderPanel getCardReaderPanelInstance(){
		if (cardreader_panel == null){
			cardreader_panel = new CardReaderPanel();
			cardreader_panel.configure();
		}
		return cardreader_panel;
	}
	
	private void configure(){
		setCardReaderPanelProperties();
		createCardReader();
		addElements();
		return;
	}
	
	public CardReader getCardReader(){
		return this.card_reader;
	}
	
	private void setCardReaderPanelProperties(){
		this.setPreferredSize(new Dimension(250, 400));
		this.setBorder(new SoftBevelBorder(SoftBevelBorder.RAISED));
		return;
	}
	
	private void createCardReader(){
		card_reader = CardReader.getCardReaderInstance();
		return;
	}
	
	private void addElements(){
		cardreader_panel.add(card_reader, BorderLayout.CENTER);
	}
	
	private CardReader card_reader;
	
	private static CardReaderPanel cardreader_panel;
}
