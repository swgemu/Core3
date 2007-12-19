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

#ifndef INPUTBOX_H_
#define INPUTBOX_H_

#include "engine/engine.h"
#include "SuiCreatePageMessage.h"

class InputBox : public SuiCreatePageMessage {
	string title;
	string promptContent;
	
	int maxLength;
	
	bool enableCancelButton;
	
public:
	InputBox(uint32 boxID, const string& boxtitle, const string& promptcontent, int maxlength, bool cancelButton) : 
		SuiCreatePageMessage(boxID) {
		
		title = boxtitle;
		promptContent = promptcontent;
		
		maxLength = maxlength;
		
		enableCancelButton = cancelButton;
		
		generateMessage();
	}
	
	
	void generateMessage() {
		insertAscii("Script.inputBox");
		
		if (enableCancelButton)
			insertInt(0x0C);
		else
			insertInt(0x0D);

		for (int i = 0; i < 2; ++i) { 
			insertByte(5);
			insertInt(0);
			insertInt(7); // number of shorts(asciis?)

			insertShort(0); // 1
			insertShort(1); // 2
			insertByte(9 + i);
			insertAscii("handleAutoLevelSelect"); // 3
			insertAscii("txtInput"); // 4
			insertAscii("LocalText"); // 5
			insertAscii("cmbInput"); // 6
			insertAscii("SelectedText"); // 7
		}

		insertOption(3, promptContent, "Prompt.lblPrompt", "Text");
		insertOption(3, title, "bg.caption.lblTitle", "Text");

		if (enableCancelButton) {
			insertOption(3, "@cancel", "btnCancel", "Text");
		} else {
			insertOption(3, "False", "btnCancel", "Enabled");
			insertOption(3, "False", "btnCancel", "Visible");
		}

		insertOption(3, "@ok", "btnOk", "Text");

		insertOption(3, "true", "txtInput", "Enabled");
		insertOption(3, "true", "txtInput", "Visible");

		insertOption(3, "false", "cmbInput", "Enabled");
		insertOption(3, "false", "cmbInput", "Visible");

		char tempStr[10];
		sprintf(tempStr, "%d", maxLength);
		
		insertOption(3, tempStr, "txtInput", "MaxLength");
		insertOption(3, tempStr, "cmbInput", "MaxLength");

		insertLong(0);
		insertInt(0);
		insertLong(0);
	}
	
};

#endif /*INPUTBOX_H_*/
