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

#ifndef LISTBOX_H_
#define LISTBOX_H_

#include "engine/engine.h"
#include "SuiCreatePageMessage.h"

class ListBox : public SuiCreatePageMessage {
	Vector<string> menuItems;
		
	string boxTitle;
	string boxText;
public:
	ListBox(uint32 selectionBoxId, const string& title, const string& bodyText) :
		SuiCreatePageMessage(selectionBoxId) {

		boxTitle = title;
		boxText = bodyText;
	}
	
	void addItem(const string& itemText) {
		menuItems.add(itemText);
	}

	void generateMessage() {
		insertAscii("Script.listBox");
		insertInt(7 + (2 * menuItems.size()));

		for (int i = 0; i < 2; i++) {  // If these are not added twice it crashes the client
			insertByte(5);
			insertInt(0);
			insertInt(7);
			insertShort(0); // 1
			insertShort(1); // 2
			insertByte(9 + i);

			insertAscii("msgSelected"); // 3
			insertAscii("List.lstList"); // 4
			insertAscii("SelectedRow"); // 5
			insertAscii("bg.caption.lblTitle"); // 6
			insertAscii("Text"); // 7
		}
		
		insertOption(3, boxTitle, "bg.caption.lblTitle", "Text");
		insertOption(3, boxText, "Prompt.lblPrompt", "Text");
		insertOption(3, "@cancel", "btnCancel", "Text");
		insertOption(3, "@ok", "btnOk", "Text");

		insertByte(1);
		insertInt(0);
		insertInt(1);
		insertAscii("List.dataList");

		for (int i = 0; i < menuItems.size(); i++) {
			char tempStr[30];
			sprintf(tempStr, "%d", i);
			
			insertOption(4, tempStr, "List.dataList", "Name");
			
			sprintf(tempStr, "List.dataList.%d", i);

			insertOption(3, menuItems.get(i), tempStr, "Text");
		}

		insertLong(0);
		insertInt(0);
		insertLong(0);
	}
};

#endif /*LISTBOX_H_*/
