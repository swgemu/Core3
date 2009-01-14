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

#ifndef SUISLICINGIMPLEMENTATIONBOX_H_
#define SUISLICINGIMPLEMENTATIONBOX_H_

#include "../listbox/SuiListBox.h"
#include "../SuiWindowType.h"

#include "../../../tangible/tools/smuggler/PrecisionLaserKnife.h"

/// Fail messages - have to do this way because SOE is retarded and can't create patterns
static const char* SlicingFailStrings[6] = {
		"@slicing/slicing:fail_armor",
		"@slicing/slicing:fail_weapon",
		"@slicing/slicing:container_fail",
		"@slicing/slicing:terminal_fail",
		"@slicing/slicing:hq_terminal_fail",
		"@slicing/slicing:keypad_fail"
};

class SuiSlicingBoxImplementation : public SuiSlicingBoxServant {
	TangibleObject* slicingObject;
	PrecisionLaserKnife* precisionLaserKnife;

	uint8 firstCable;
	bool cable[2];

	bool usedNode;
	bool usedClamp;

public:
	static const uint8 CABLE_BLUE = 0;
	static const uint8 CABLE_RED = 1;

	static const uint8 SLICE_ARMOR = 0;
	static const uint8 SLICE_WEAPON = 1;
	static const uint8 SLICE_CONTAINER = 2;
	static const uint8 SLICE_TERMINAL = 3;
	static const uint8 SLICE_HQ_TERMINAL = 4;
	static const uint8 SLICE_KEYPAD = 5;

public:
	SuiSlicingBoxImplementation(Player* player, TangibleObject* tano)
		: SuiSlicingBoxServant(player, SuiWindowType::SLICING_MENU, MSGSELECTED) {

		boxType = SLICINGBOX;

		setSlicingObject(tano);

		setPromptTitle("@slicing/slicing:title");

		//Which cable should be cut first.
		firstCable = System::random(1);

		//Initialize both cables to false, since neither have been cut.
		cable[CABLE_BLUE] = false;
		cable[CABLE_RED] = false;

		usedNode = false;
		usedClamp = false;

		generateMenu();
	}

	/**
	 * This method is used to handle the menu selections from the sui to progress the slicing process.
	 * \param index The index that was selected on the listbox.
	 * \return bool Should the menu be resent after being handled.
	 */
	bool handleMenuChoice(uint8 index) {
		TangibleObject* obj = getSlicingObject();

		if (obj == NULL || !obj->isSliced())
			return false;

		uint8 progress = getProgress();

		if (progress == 0) {
			//No wires have been cut yet.
			switch (index) {
			case CABLE_BLUE:
			case CABLE_RED:
				if (firstCable != index) {
					obj->onSlicingFailure(player);
					return false;
				} else {
					cable[index] = true;
				}
				break;
			case 2:
				useClamp();
				usedClamp = true;
				break;
			case 3:
				useNode();
				usedNode = true;
				break;
			}

		} else {
			//One wire has been cut already. Can't fail now...
			if (firstCable != index) {
				//Slice has been a success.
				obj->slice(player);
				return false;
			}
		}

		generateMenu();

		return true;
	}

	void generateMenu() {
		uint8 slicingType = getSlicingType();
		uint8 progress = getProgress();

		removeAllMenuItems();

		StringBuffer prompt;
		prompt << "@slicing/slicing:";

		prompt << getPrefix(slicingType);

		if (progress == 0) {
			//No cables have been cut yet.

			if (usedClamp)
				prompt << "clamp_" << firstCable;
			else if (usedNode)
				prompt << "analyze_" << firstCable;
			else
				prompt << progress;

			//menu stuff
			addMenuItem("@slicing/slicing:blue_cable");
			addMenuItem("@slicing/slicing:red_cable");

			if (!usedClamp && !usedNode) {
				addMenuItem("@slicing/slicing:use_clamp");
				addMenuItem("@slicing/slicing:use_analyzer");
			}

		} else if (progress == 1) {
			//Only one cable has been cut so far.
			prompt << progress;

			addMenuItem((cable[CABLE_BLUE]) ? "@slicing/slicing:blue_cable_cut" : "@slicing/slicing:blue_cable");
			addMenuItem((cable[CABLE_RED]) ? "@slicing/slicing:red_cable_cut" : "@slicing/slicing:red_cable");
		}

		setPromptText(prompt.toString());
	}

	uint8 getSlicingType() {
		if (slicingObject->isWeapon())
			return SLICE_WEAPON;
		if (slicingObject->isContainer())
			return SLICE_CONTAINER;
		if (slicingObject->isTerminal())
			return SLICE_TERMINAL;

		//TODO: Add in hq_terminal and keypad

		return SLICE_ARMOR;
	}

	String getPrefix(uint8 slicingType) {
		switch (slicingType) {
		case SLICE_WEAPON:
			return "weapon_";
		case SLICE_CONTAINER:
			return "container_";
		case SLICE_TERMINAL:
			return "terminal_";
		case SLICE_ARMOR:
		default:
			return "armor_";
		}

		//TODO: Add in hq_terminal and keypad
	}

	void useClamp() {
		//TODO: Search for one.
		player->sendSystemMessage("slicing/slicing", "used_clamp"); //A Molecular Clamp has been used up.
		//player->sendSystemMessage("slicing/slicing", "no_clamp"); //You need to have a Molecular Clamp to perform that action.
		usedClamp = true;
	}

	void useNode() {
		player->sendSystemMessage("slicing/slicing", "used_node"); //A Flow Analyzer Node has been used up.
		//player->sendSystemMessage("slicing/slicing", "no_node"); //You need to have a Flow Analyzer Node to perform that action.
		usedNode = true;
	}

	//Setters
	void setPrecisionLaserKnife(PrecisionLaserKnife* knife) {
		precisionLaserKnife = knife;
	}

	void setSlicingObject(TangibleObject* tano) {
		slicingObject = tano;
	}

	//Getters
	PrecisionLaserKnife* getPrecisionLaserKnife() {
		return precisionLaserKnife;
	}

	TangibleObject* getSlicingObject() {
		return slicingObject;
	}

	uint8 getProgress() {
		return ((uint8) cable[CABLE_BLUE] + (uint8) cable[CABLE_RED]);
;	}
};

#endif /* SUISLICINGIMPLEMENTATIONBOX_H_ */
