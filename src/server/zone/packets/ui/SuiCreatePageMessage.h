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

#ifndef SUICREATEPAGEMESSAGE_H_
#define SUICREATEPAGEMESSAGE_H_

#include "engine/engine.h"

#include "../object/StfParameter.h"

class SuiCreatePageMessage : public BaseMessage {
public:
   SuiCreatePageMessage(uint32 pageID) : BaseMessage() {
		insertShort(0x02);
		insertInt(0xD44B7259);  // CRC
		
		insertInt(pageID);
   }
   
   void insertOption(uint8 option, const String& value, const String& variable, const String& type) {
	   insertByte(option); // 3 Strings?
	   
	   insertInt(1); // number of Unicodes
	   UnicodeString val = UnicodeString(value);
	   insertUnicode(val);
	   
	   insertInt(2); // number of ASCIIS
	   insertAscii(variable.toCharArray());
	   insertAscii(type.toCharArray());
   }
   
   /*void frogMenu() {
	   insertInt(0x00F85E88); //I'm gonna guess this is an ID of sorts.
	   insertAscii("Script.listBox");
	   insertInt(0x11);


	   insertInt(5);
	   insertByte(0);
	   insertInt(0x0B);
	   insertShort(0);
	   insertShort(1);
	   insertByte(9); //Counter
	   insertAscii("handleRoadmapSelect");
	   insertAscii("this");
	   insertAscii("otherPressed");
	   insertAscii("List.lstList");
	   insertAscii("SelectedRow");
	   insertAscii("bg.caption.lblTitle");
	   insertAscii("Text");
	   insertAscii("this");
	   insertAscii("otherPressed");
	   //end of list.

	   insertInt(5);
	   insertByte(0);
	   insertInt(0x0B);
	   insertShort(0);
	   insertShort(1);
	   insertByte(0x0A); //Counter?
	   insertAscii("handleRoadmapSelect");
	   insertAscii("this");
	   insertAscii("otherPressed");
	   insertAscii("List.lstList");
	   insertAscii("SelectedRow");
	   insertAscii("bg.caption.lblTitle");
	   insertAscii("Text");
	   insertAscii("this");
	   insertAscii("otherPressed");
	   //end of list?

	   //---------------------------
	   insertByte(3);
	   insertInt(1); //I think this is a counter.
	   UnicodeString test = "Character Builder Terminal";
	   insertUnicode(test);

	   insertInt(2); //Counter I think
	   insertAscii("bg.caption.lblTitle");
	   insertAscii("Text");

	   //---------------------------
	   insertByte(3);
	   insertInt(1); //counter I think.
	   UnicodeString test2 = "Select the desired Roadmap option";
	   insertUnicode(test2);

	   insertInt(2); //counter I think.
	   insertAscii("Prompt.lblPrompt");
	   insertAscii("Text");


	   //---------------------------
	   insertByte(3);
	   insertInt(1); //counter I think
	   UnicodeString test99 = "true";
	   insertUnicode(test99);

	   insertInt(2); //counter I think
	   insertAscii("btnOther");
	   insertAscii("visible");


	   //---------------------------
	   insertByte(3);
	   insertInt(1); //counter I think
	   UnicodeString test3 = "@refresh";
	   insertUnicode(test3);

	   insertInt(2); //counter I think
	   insertAscii("btnOther");
	   insertAscii("visible");

	   //---------------------------
	   insertByte(3);
	   insertInt(1); //counter I think
	   UnicodeString test4 = "@cancel";
	   insertUnicode(test4);

	   insertInt(2); //counter I think
	   insertAscii("btnCancel");
	   insertAscii("Text");

	   //---------------------------
	   insertByte(3);
	   insertInt(1); //counter I think
	   UnicodeString test5 = "@ok";
	   insertUnicode(test5);

	   insertInt(2); //counter I think
	   insertAscii("btnOk");
	   insertAscii("Text");

	   //---------------------------


	   //Start New Section?
	   insertInt(1);
	   insertByte(0);

	   insertInt(1); //counter I think
	   insertAscii("List.dataList");

	   //---------------------------
	   insertByte(4);
	   insertInt(1);
	   UnicodeString test6 = "0";
	   insertUnicode(test6);
	   insertInt(2); //counter I think
	   insertAscii("List.dataList");
	   insertAscii("Name");

	   //---------------------------
	   insertByte(3);
	   insertInt(1);
	   UnicodeString test7 = "Select Roadmap";
	   insertUnicode(test7);
	   insertInt(2); //counter I think
	   insertAscii("List.dataList.0");
	   insertAscii("Text");

	   //---------------------------
	   insertByte(4);
	   insertInt(1);
	   UnicodeString test8 = "1";
	   insertUnicode(test8);
	   insertInt(2); //counter I think
	   insertAscii("List.dataList");
	   insertAscii("Name");

	   //---------------------------
	   insertByte(3);
	   insertInt(1);
	   UnicodeString test9 = "Earn Current Skill";
	   insertUnicode(test9);
	   insertInt(2); //counter I think
	   insertAscii("List.dataList.1");
	   insertAscii("Text");


	   //---------------------------
	   insertByte(4);
	   insertInt(1);
	   UnicodeString test10 = "2";
	   insertUnicode(test10);
	   insertInt(2); //counter I think
	   insertAscii("List.dataList");
	   insertAscii("Name");


	   //---------------------------
	   insertByte(3);
	   insertInt(1);
	   UnicodeString test11 = "Set Combat Level";
	   insertUnicode(test11);
	   insertInt(2); //counter I think
	   insertAscii("List.dataList.2");
	   insertAscii("Text");


	   //---------------------------
	   insertByte(3);
	   insertInt(1);
	   UnicodeString test12 = "true";
	   insertUnicode(test12);
	   insertInt(2); //counter I think
	   insertAscii("btnOther");
	   insertAscii("visible");


	   //---------------------------
	   insertByte(3);
	   insertInt(1);
	   UnicodeString test13 = "Back";
	   insertUnicode(test13);
	   insertInt(2); //counter I think
	   insertAscii("btnOther");
	   insertAscii("Text");


	   //I dunno what these are/do.
	   insertLong(0);
	   insertInt(0);
	   insertLong(0);
   }*/    
	
};

#endif /*BADGESRESPONSEMESSAGE_H_*/
