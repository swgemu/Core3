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
	message = NULL;
}

/**
 * Use to add a UI-body option that will be included in UI generation
 * See trac documentation of SuiCreatePageMessage for when to use
 * Variables are concated into a string and placed in a vector (optionSets) of all the body settings
 * for the SuiBoxImplementation object. Each string separates variables with a tilde (~) character.
 * \param optType Type of setting to add. See packet docs for info
 * \param variable UI Classpath in the script to access
 * \param setting SWG UI setting to modify
 * \param value The value of the setting being modified
 */
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

/**
 * Use to add a UI-Header that will eventually be included in the UI generation.
 * See trac documentation of SuiCreatePageMessage for when to use
 * Variables are concated into a string and placed in a vector (headerSets) of all the header settings
 * for the SuiBoxImplementation object. Each string separates variables with a tilde (~) character.
 * \param variable UI Variable to declare header for
 * \param type Data type of the UI variable being declared
 */
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

/**
 * Call after all Header settings have been added with addHeader()
 * Generates the UI-Header of the packet, SuiCreatePageMessage, based on the headerSets vector.
 * If you are reusing the SuiBox and rebuilding with different variables, make sure you reset
 * the object with clearOptions()
 * \sa addHeader(), clearOptions()
 */
void SuiBoxImplementation::generateHeader(const String& handlerStr) {
	if(message == NULL)
		return;

	//[UI DECLARATION HEADER]
	String hdrVar = "";
	String hdrType = "";

	//The header needs to be repeated twice. (Why SOE?)
	for (int i = 0; i < 2; ++i) {
		message->insertByte(5); //# of vars to follow, not inc strings
		message->insertInt(0);
		message->insertInt(3+hdrOptCount); //# of shorts (inc ascii string size shorts), excluding the counter
		message->insertShort(0); // 1
		message->insertShort(1); // 2
		message->insertByte(9 + i); //counter

		message->insertAscii(handlerStr);

		for(int k = 0; k < headerSets.size(); k++) {
			StringTokenizer hdrTok(headerSets.get(k)); //ex. List.lstList~SelectedRow
			hdrTok.setDelimeter("~"); //Split & parse
			hdrTok.getStringToken(hdrVar);
			hdrTok.getStringToken(hdrType);
			message->insertHeaderOption(hdrVar, hdrType, (i > 0));
		}
	}
}

/**
 * Call after all Body Settings have been added with addSetting() and the header has been generated
 * Generates the UI-Body of the packet, SuiCreatePageMessage, based on the optionSets vector.
 * If you are reusing the SuiBox and rebuilding with different variables, make sure you
 * reset the object with clearOptions()
 * \sa addSetting(), clearOptions()
 */
void SuiBoxImplementation::generateBody() {
	if(message == NULL)
		return;

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
		message->insertOption(bdyType, bdyValue, bdyVar, bdySetting);
	}
}

/**
 * Call after generating both the header and body.
 * Footer of SuiCreatePageMessage is largely unknown. Subject to change based on research. See trac
 * \param type Type of footer to place into packet
 */
void SuiBoxImplementation::generateFooter(int type) {
	if(message == NULL)
		return;

	message->insertFooter(type);
}

/**
 * Use to close the UI object on the client.
 * Sends the SuiForceClosePage packet to the client.
 */
BaseMessage* SuiBoxImplementation::generateCloseMessage() {
	SuiForceClosePage* msg = new SuiForceClosePage(boxID);
	clearOptions();
	return msg;
}

/**
 * Returns the instanced SuiCreatePageMessage packet object, in whatever state it is in.
 * \warning May be incomplete or null. Do not use this method unless absolutely necessary.
 * \deprecated Function will be removed when SUI facilities are complete.
 */
BaseMessage* SuiBoxImplementation::getCurrentMessage() {
	return message;
}

SuiBoxImplementation::~SuiBoxImplementation() {
	headerSets.removeAll();
	optionSets.removeAll();
}
