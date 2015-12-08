package com.worm.listeners;

import java.awt.datatransfer.DataFlavor;

import java.awt.datatransfer.Transferable;
import java.awt.dnd.DnDConstants;
import java.awt.dnd.DropTargetDragEvent;
import java.awt.dnd.DropTargetDropEvent;
import java.awt.dnd.DropTargetEvent;
import java.awt.dnd.DropTargetListener;
import java.io.File;
import java.util.List;

import com.worm.controller.MainController;
import com.worm.controller.GUIConstants.states;

public class CardDragAndDropListener implements DropTargetListener {

	@Override
	public void dragEnter(DropTargetDragEvent dtde) {
		// TODO Auto-generated method stub

	}

	@Override
	public void dragOver(DropTargetDragEvent dtde) {
		// TODO Auto-generated method stub

	}

	@Override
	public void dropActionChanged(DropTargetDragEvent dtde) {
		// TODO Auto-generated method stub

	}

	@Override
	public void dragExit(DropTargetEvent dte) {
		// TODO Auto-generated method stub

	}

	@SuppressWarnings("unchecked")
	@Override
	public void drop(DropTargetDropEvent event) {
		event.acceptDrop(DnDConstants.ACTION_COPY_OR_MOVE);
		Transferable transferable = event.getTransferable();
		// DataFlavor[] flavors = transferable.getTransferDataFlavors();
		// for (DataFlavor flavor : flavors) {
		// try {
		// if (flavor.isFlavorJavaFileListType()) {
		// List<File> files = (List<File>) transferable.getTransferData(flavor);
		// for (File file : files) {
		// System.out.println(file.getPath());
		// }
		// }
		// } catch (Exception e) {
		// e.printStackTrace();
		// }
		// }
		DataFlavor flavor = transferable.getTransferDataFlavors()[0];
		try {
			if (flavor.isFlavorJavaFileListType()) {
				File file = ((List<File>) transferable.getTransferData(flavor)).get(0);
				MainController.getMainControllerInstance().getMainFrame().getCardReaderPanel().getCardReader().setReaderText("<html><center>Your card number:<br>" + file.getName() + "</center>"); 
				MainController.getMainControllerInstance().setState(states.LOGIN);
				MainController.getMainControllerInstance().getMainFrame().getCardReaderPanel().getCardReader().disableListener();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		event.dropComplete(true);
	}
	
}
