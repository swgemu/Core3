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

/**
 * \class SuiCreatePageMessage
 * Packet. See trac documentation for detailed variable information.
 * Manipulated and built heavily in SuiBoxImplementation
 */

#ifndef SUICREATEPAGEMESSAGE_H_
#define SUICREATEPAGEMESSAGE_H_

#include "engine/engine.h"

class SuiCreatePageMessage : public BaseMessage {
	int optionOffset;
	int optionCount;

public:
   SuiCreatePageMessage(uint32 pageID, const String& scriptClass) : BaseMessage() {
	   optionOffset = 0;
	   optionCount = 2; // Header and footer

	   insertShort(0x02);
	   insertInt(0xD44B7259);  // CRC
	   insertInt(pageID);
	   insertAscii(scriptClass);
	   insertInt(0); //option count

	   //Calculate the offset for the optionCount (priority+crc+pageid+asciiSize+ascii+4):
	   optionOffset = 16+scriptClass.length();

	   setCompression(true);
   }

	/**
	 * Insert's a UI-Body option into the packet. Should only be accessed by methods in SuiBoxImplementation
	 * See packet trac docs for more info.
	 * \param optionType Type of UI option to add
	 * \param value Value to set the setting to.
	 * \param variable SWG-UI Classpath to access
	 * \param setting SWG-UI setting within the UI class to modify
	 */
	void insertOption(uint8 optionType, const String& value, const String& variable, const String& setting) {

	   insertByte(optionType); //Option Type. 1=Data Container Option. 3=Data Value Option. 4=Container Data Header Option
	   optionCount++;

	   //System::out << "Adding Option, OptCount[" << optionCount << "]." << variable << "." << setting << "=" << value << endl;
	   //Data Value Option and Header Option are the same
	   if((optionType == 3) || (optionType == 4)) {
		   insertInt(1); // number of Unicodes
		   UnicodeString val = UnicodeString(value);
		   insertUnicode(val);

		   insertInt(2); // number of ASCIIS
		   insertAscii(variable.toCharArray());
		   insertAscii(setting.toCharArray());



	   } else { //For type #1, Data Container Option (used to delcare a list of options, like in dataList)
			insertInt(0); //0 unicodes
			insertInt(1); // 1 ascii
			insertAscii(variable.toCharArray()); //ex. List.dataList
	   }

	   //Update the option count
	   insertInt(optionOffset, optionCount);
	}

	/**
	 * Insert's a UI-Header option into the packet. Should only be accessed by methods in SuiBoxImplementation
	 * See packet trac docs for more info
	 * \param variable SWG-UI Class var to access
	 * \param type Datatype of the UI var
	 * \param noCount Internal packet variable used to determine weather or not to count the option towards the total packet options
	 */
	void insertHeaderOption(const String& variable, const String& type) {

	   //System::out << "Adding Header Option, OptCount[" << optionCount << "]." << variable << " with type " << type << endl;

	   insertAscii(variable.toCharArray());
	   insertAscii(type.toCharArray());
	}

	/**
	 * Insert's a UI-Footer option into the packet. Should only be accessed by methods in SuiBoxImplementation
	 * \param type Type of footer to insert.
	 */
	void insertFooter(uint64 usingObjectID, float distance = 10, int type = 0) {

		insertLong(usingObjectID);
		if(type == 0) {
			insertFloat(distance);
			insertLong(0);
		} else if(type == 1){
			insertInt(0x7F7FFFFF);
			insertInt(0x7F7FFFFF);
			insertInt(0x7F7FFFFF);
			insertInt(0);
		}
	}

	void setOptionCount(int optCnt) {
	   optionCount = optCnt;
	}

	int getOptionCount() {
		return optionCount;
	}

   /*SuiCreatePageMessage() {
	   insertShort(0x02);
	   insertInt(0xD44B7259);  // CRC
	   insertInt(0x00F85E88); //I'm gonna guess this is an ID of sorts.
	   insertAscii("Script.listBox");
	   insertInt(0x11);  //


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

	   //--------------------------- 1
	   insertByte(3);
	   insertInt(1); //I think this is a counter.
	   UnicodeString test = "Character Builder Terminal";
	   insertUnicode(test);

	   insertInt(2); //Counter I think
	   insertAscii("bg.caption.lblTitle");
	   insertAscii("Text");

	   //--------------------------- 2
	   insertByte(3);
	   insertInt(1); //counter I think.
	   UnicodeString test2 = "Select the desired Roadmap option";
	   insertUnicode(test2);

	   insertInt(2); //counter I think.
	   insertAscii("Prompt.lblPrompt");
	   insertAscii("Text");


	   //--------------------------- 3
	   insertByte(3);
	   insertInt(1); //counter I think
	   UnicodeString test99 = "true";
	   insertUnicode(test99);

	   insertInt(2); //counter I think
	   insertAscii("btnOther");
	   insertAscii("visible");


	   //--------------------------- 4
	   insertByte(3);
	   insertInt(1); //counter I think
	   UnicodeString test3 = "@refresh";
	   insertUnicode(test3);

	   insertInt(2); //counter I think
	   insertAscii("btnOther");
	   insertAscii("visible");

	   //--------------------------- 5
	   insertByte(3);
	   insertInt(1); //counter I think
	   UnicodeString test4 = "@cancel";
	   insertUnicode(test4);

	   insertInt(2); //counter I think
	   insertAscii("btnCancel");
	   insertAscii("Text");

	   //--------------------------- 6
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

	   //--------------------------- 7
	   insertByte(4);
	   insertInt(1);
	   UnicodeString test6 = "0";
	   insertUnicode(test6);
	   insertInt(2); //counter I think
	   insertAscii("List.dataList");
	   insertAscii("Name");

	   //--------------------------- 8
	   insertByte(3);
	   insertInt(1);
	   UnicodeString test7 = "Select Roadmap";
	   insertUnicode(test7);
	   insertInt(2); //counter I think
	   insertAscii("List.dataList.0");
	   insertAscii("Text");

	   //--------------------------- 9
	   insertByte(4);
	   insertInt(1);
	   UnicodeString test8 = "1";
	   insertUnicode(test8);
	   insertInt(2); //counter I think
	   insertAscii("List.dataList");
	   insertAscii("Name");

	   //--------------------------- 10
	   insertByte(3);
	   insertInt(1);
	   UnicodeString test9 = "Earn Current Skill";
	   insertUnicode(test9);
	   insertInt(2); //counter I think
	   insertAscii("List.dataList.1");
	   insertAscii("Text");


	   //--------------------------- 11
	   insertByte(4);
	   insertInt(1);
	   UnicodeString test10 = "2";
	   insertUnicode(test10);
	   insertInt(2); //counter I think
	   insertAscii("List.dataList");
	   insertAscii("Name");


	   //--------------------------- 12
	   insertByte(3);
	   insertInt(1);
	   UnicodeString test11 = "Set Combat Level";
	   insertUnicode(test11);
	   insertInt(2); //counter I think
	   insertAscii("List.dataList.2");
	   insertAscii("Text");


	   //--------------------------- 13
	   insertByte(3);
	   insertInt(1);
	   UnicodeString test12 = "true";
	   insertUnicode(test12);
	   insertInt(2); //counter I think
	   insertAscii("btnOther");
	   insertAscii("visible");


	   //--------------------------- 14
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
