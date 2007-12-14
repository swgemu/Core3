/*
Copyright (C) 2007 <SWGEmu>
 
This File is part of Core3.
 
This program is free software; you can redistribute 
it and/or modify it under the terms of the GNU Lesser 
General Public License as published by the Free Software
Foundation; either version 2 of the License, 
or (at your option) any later version.
 
This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Lesser General Public License for
more details.
 
You should have received a copy of the GNU Lesser General 
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
Linking Engine3 statically or dynamically with other modules 
is making a combined work based on Engine3. 
Thus, the terms and conditions of the GNU Lesser General Public License 
cover the whole combination.
 
In addition, as a special exception, the copyright holders of Engine3 
give you permission to combine Engine3 program with free software 
programs or libraries that are released under the GNU LGPL and with 
code included in the standard release of Core3 under the GNU LGPL 
license (or modified versions of such code, with unchanged license). 
You may copy and distribute such a system following the terms of the 
GNU LGPL for Engine3 and the licenses of the other code concerned, 
provided that you include the source code of that other code when 
and as the GNU LGPL requires distribution of source code.
 
Note that people who make modified versions of Engine3 are not obligated 
to grant this special exception for their modified versions; 
it is their choice whether to do so. The GNU Lesser General Public License 
gives permission to release a modified version without this exception; 
this exception also makes it possible to release a modified version 
which carries forward this exception.
*/

#ifndef SELECTIONBOX_H_
#define SELECTIONBOX_H_

#include "engine/engine.h"

class SelectionBox : public Message {
	Vector<string> menuItems;
	
	string boxTitle;
	string boxText;
	
public:
	SelectionBox(string& title, int selectionBoxId, string& bodyText) {
		boxTitle = title;
		boxText = bodyText;
		
		insertShort(0x02);
		insertInt(0xD44B7259);
		insertInt(selectionBoxId);
	}
	
	void addItem(string& itemText) {
		menuItems.add(itemText);
	}

	void generateMessage() {
		insertAscii("Script.listBox");
		insertInt(7 + (2 * menuItems.size()));
		
		for (int i = 0; i < 2; i++) {  // If these are not added twice it crashes the client
			insertInt(5);
			insertByte(0);
			insertInt(7);
			insertShort(0);
			insertShort(1);
			insertByte(9);
		
			insertAscii("msgSelected");
			insertAscii("List.lstList");
			insertAscii("SelectedRow");
			insertAscii("bg.caption.lblTitle");
			insertAscii("Text");
		}
		
		insertByte(3);
		insertInt(1);
		
		unicode uni;
		
		uni = unicode(boxTitle);
		insertUnicode(uni);
		
		insertInt(2);
		
		insertAscii("bg.caption.lblTitle");
		insertAscii("Text");
		
		insertByte(3);
		insertInt(1);
		
		uni = unicode(boxText);
		insertUnicode(uni);
		
		insertInt(2);
		
		insertAscii("Prompt.lblPrompt");
		insertAscii("Text");
		
		insertByte(3);
		insertInt(1);
		
		uni = unicode("@cancel");
		insertUnicode(uni); // Button label @ are predefined strings

		insertInt(2);
		
		insertAscii("btnCancel"); // Button type
		insertAscii("Text");
		
		insertByte(3);
		insertInt(1);
		
		uni = unicode("@ok");
		insertUnicode(uni);
		
		insertInt(2);
		
		insertAscii("btnOk");
		insertAscii("Text");
		
		insertInt(1);
		insertByte(0);
		insertInt(1);
		
		insertAscii("List.dataList");
		
		//vector<string>::iterator iter;
		//for (iter = menuItems.begin(); iter != menuItems.end(); iter++) {
		for (int i = 0; i < menuItems.size(); i++) {
			insertByte(4);
			insertInt(1);
			
			char tempStr[30];
			sprintf(tempStr, "%d", i);

			uni = unicode(tempStr);
			insertUnicode(uni);
			
			insertInt(2);
			
			insertAscii("List.dataList");
			insertAscii("Name");
			
			insertByte(3);
			insertInt(1);
			
			uni = unicode(menuItems.get(i));
			insertUnicode(uni);
			
			insertInt(2);
			
			sprintf(tempStr, "List.dataList.%d");
			
			insertAscii(tempStr);
			insertAscii("Text");
		}
			
		insertLong(0);
		insertLong(0);
		insertInt(0);
	}
	
};

#endif /*SELECTIONBOX_H_*/
