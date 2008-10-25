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

#include "SuiListBoxImplementation.h"

#include "../../../../packets.h"

#include "../SuiBoxImplementation.h"
#include "../../PlayerImplementation.h"

SuiListBoxImplementation::SuiListBoxImplementation(Player* player, uint32 boxType, int listBoxType) :
	SuiListBoxServant(player, boxType, LISTBOX) {
	init();

	type = listBoxType;
}

SuiListBoxImplementation::~SuiListBoxImplementation() {
	for (int i = 0; i < menuItems.size(); ++i) {
		delete menuItems.get(i);
	}
}

void SuiListBoxImplementation::init(){
	previous = 0;
	next = 0;
}

void SuiListBoxImplementation::generateHeader(BaseMessage* msg) {
	msg->insertAscii("Script.listBox");

	switch(type) {
	case HANDLESTATUSUI:
		msg->insertInt(7 + (2 * menuItems.size()));
		break;
	case HANDLEDESTROYUI:
		msg->insertInt(7 + (2 * menuItems.size()));
		break;
	default:
		if (cancelButton || backButton)
			msg->insertInt(7 + (2 * menuItems.size()));
		else
			msg->insertInt(8 + (2 * menuItems.size()));
	}

	for (int i = 0; i < 2; i++) {  // If these are not added twice it crashes the client
		msg->insertByte(5);
		msg->insertInt(0);
		msg->insertInt(7);
		msg->insertShort(0); // 1
		msg->insertShort(1); // 2
		msg->insertByte(9 + i);

		switch(type) {
		case HANDLESTATUSUI:
			msg->insertAscii("handleStatusUi");
			break;
		case HANDLEDESTROYUI:
			msg->insertAscii("handleDestroyUi");
			break;
		default:
			msg->insertAscii("msgSelected");
		}

		msg->insertAscii("List.lstList"); // 4
		msg->insertAscii("SelectedRow"); // 5
		msg->insertAscii("bg.caption.lblTitle"); // 6
		msg->insertAscii("Text"); // 7
	}
}

BaseMessage* SuiListBoxImplementation::generateMessage() {
	SuiCreatePageMessage* msg = new SuiCreatePageMessage(boxID);
	generateHeader(msg);

	msg->insertOption(3, promptTitle, "bg.caption.lblTitle", "Text");
	msg->insertOption(3, promptText, "Prompt.lblPrompt", "Text");

	switch(type) {
	case HANDLESTATUSUI:
		if(!backButton)
			msg->insertOption(3, "@cancel", "btnCancel", "Text");
		else
			msg->insertOption(3, "@back", "btnCancel", "Text");
		msg->insertOption(3, "@refresh", "btnOk", "Text");
		break;
	case HANDLEDESTROYUI:
		msg->insertOption(3, "@no", "btnCancel", "Text");
		msg->insertOption(3, "@yes", "btnOk", "Text");
		break;
	default:
		if (cancelButton)
			msg->insertOption(3, "@cancel", "btnCancel", "Text");
		else if(backButton)
			msg->insertOption(3, "@back", "btnCancel", "Text");
		else {
			msg->insertOption(3, "False", "btnCancel", "Enabled");
			msg->insertOption(3, "False", "btnCancel", "Visible");
		}

		msg->insertOption(3, "@ok", "btnOk", "Text");
	}

	msg->insertByte(1);
	msg->insertInt(0);
	msg->insertInt(1);
	msg->insertAscii("List.dataList");

	for (int i = 0; i < menuItems.size(); i++) {
		char tempStr[30];
		sprintf(tempStr, "%d", i);

		msg->insertOption(4, tempStr, "List.dataList", "Name");

		sprintf(tempStr, "List.dataList.%d", i);

		msg->insertOption(3, menuItems.get(i)->getOptionName(), tempStr, "Text");
	}

	msg->insertLong(0);
	msg->insertInt(0);
	msg->insertLong(0);

	return msg;
}


