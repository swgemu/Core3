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

#include "SuiBoxImplementation.h"
#include "../../../packets.h"
#include "../PlayerImplementation.h"

SuiBoxImplementation::SuiBoxImplementation(Player* play, uint32 windowType, uint32 boxType) :
	SuiBoxServant() {

	player = play;

	this->boxType = boxType;

	boxID = player->getNewSuiBoxID(windowType);

	this->windowType = windowType;

	cancelButton = false;

	backButton = false;

	hdrOptCount = 0; //header option count
}

//Use when building the UI. This should be called to add option setting's BEFORE the packet build
void SuiBoxImplementation::addSetting(const String& optType, const String& variable, const String& setting, const String& value) {
	String setName = "", setVal = "";
	setName = setting;
	setVal = value;

	//These checks and settings ensure parsing of the optStr wont screw up in generateBody()
	if((variable.length() == 0) || (optType.length() == 0))
		return;

	if(setName.length() == 0)
		setName = " ";

	if(setVal.length() == 0)
		setVal = " ";

	String optStr = "";
	int optTypeInt = 0;
	optStr+=(optType+"~"+variable);
	optTypeInt = Integer::valueOf(optType);

	//OptionType 3 & 4 have variable settings and values (see documentation for packet)
	if((optTypeInt == 3) || (optTypeInt == 4)) {
		optStr+=("~"+setName+"~"+setVal);
	}

	// Insert the option into the list:
	optionSets.add(optStr);
}

//Use when building the UI. This should be called to add header's BEFORE the packet build
void SuiBoxImplementation::addHeader(const String& variable, const String& type) {
	if((variable.length() == 0) || (type.length() == 0))
		return;

	//Add's the header option to the list
	String headerStr = "";
	headerStr+=(variable+"~"+type);
	headerSets.add(headerStr);

	//The header count increases by 2. 1 for the variable name, 1 for the data type.
	hdrOptCount+=2;
}

//Called after all Header Settings have been added. See SuiCreatePageMessage docs for more info
void SuiBoxImplementation::generateHeader(SuiCreatePageMessage* msg, const String& handlerStr) {
	//[UI DECLARATION HEADER]
	String hdrVar = "";
	String hdrType = "";

	//The header needs to be repeated twice. (Why SOE?)
	for (int i = 0; i < 2; ++i) {
		msg->insertByte(5); //# of vars to follow, not inc strings
		msg->insertInt(0);
		msg->insertInt(3+hdrOptCount); //# of shorts (inc ascii string size shorts), excluding the counter
		msg->insertShort(0); // 1
		msg->insertShort(1); // 2
		msg->insertByte(9 + i); //counter

		msg->insertAscii(handlerStr);

		for(int k = 0; k < headerSets.size(); k++) {
			StringTokenizer hdrTok(headerSets.get(k)); //ex. List.lstList~SelectedRow
			hdrTok.setDelimeter("~"); //Split & parse
			hdrTok.getStringToken(hdrVar);
			hdrTok.getStringToken(hdrType);
			msg->insertHeaderOption(hdrVar, hdrType, (i > 0));
		}
	}
}

//Called after all Option Settings have been added. See SuiCreatePageMessage docs for more info
void SuiBoxImplementation::generateBody(SuiCreatePageMessage* msg) {
	//[UI BODY]
	String bdyTypeStr = "";
	int bdyType = 0;
	String bdyVar = "";
	String bdySetting = "";
	String bdyValue = "";
	for(int k = 0; k < optionSets.size(); k++) {
		StringTokenizer bdyTok(optionSets.get(k)); //ex. 3~Prompt.lblTitle~Text~LOL
		bdyTok.setDelimeter("~"); //Split & parse
		bdyTok.getStringToken(bdyTypeStr);
		bdyType = Integer::valueOf(bdyTypeStr);
		bdyTok.getStringToken(bdyVar);
		if((bdyType == 3) || (bdyType == 4)) {
			bdyTok.getStringToken(bdySetting);
			bdyTok.getStringToken(bdyValue);
		}
		msg->insertOption(bdyType, bdyValue, bdyVar, bdySetting);
	}
}

//Called to complete the SuiCreatePageMessage packet
void SuiBoxImplementation::generateFooter(SuiCreatePageMessage* msg, int type) {
	msg->insertFooter(type);
}

//This will return the packet to close the UI page on the client.
//Make sure to remove the suibox from the suiBoxes map
BaseMessage* SuiBoxImplementation::generateCloseMessage() {
	SuiForceClosePage* msg = new SuiForceClosePage(boxID);
	return msg;
}

SuiBoxImplementation::~SuiBoxImplementation() {
	headerSets.removeAll();
	optionSets.removeAll();
}
