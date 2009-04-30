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

#include "PetCommandHelper.h"
#include "system/lang.h"
#include "system/platform.h"

PetCommandHelper::PetCommandHelper() {
	//Vector<String>* commandList = new Vector<String>(17);

	add(PETATTACK,"attack");
	add("follow");
	add("store");
	add("");
	add("");
	add("");
	add("");
	add("");
	add("");
	add("");
	add("");
	add("");
	add("");
	add("");
	add("");
	add("");
	add("");
	add("");
	add("");
	add("");
	add("");
	add("");
}

PetCommandHelper::~PetCommandHelper() {
	//delete commandList;
	//commandList = NULL;
}


String& PetCommandHelper::getBaseCommand(int command) {
	return get(command);
}
void PetCommandHelper::trainCommand(int command, String& commandMessage) {
	if (command >= size()) {
		return;
	}
	setElementAt(command, commandMessage);
}

void PetCommandHelper::trainName(CreaturePet* pet) {
	VectorMap<String,int>* nameCandidates = new VectorMap<String,int>();
	nameCandidates->setInsertPlan(SortedVector<String>::ALLOW_OVERWRITE);
	nameCandidates->setNullValue(0);

	for (int i = 0 ; i < size(); i++) {
		String cmd = get(i);
		String tempName;
		for (int j = 0 ; j < cmd.length() ; j++) {
			char c = cmd.charAt(j);
			if (c == ' ') {
				nameCandidates->put(tempName,nameCandidates->get(tempName) + 1);
				tempName += c;
			} else {
				tempName += c;
			}

		}
	}

	String key;
	int counter;

	String nameFound = "";
	int maxCounter = 0;

	for (int i = 0 ; i < nameCandidates->size(); i++) {
		VectorMapEntry<String, int>* entry = ((SortedVector<VectorMapEntry<String, int>*>*)nameCandidates)->get(i);

		key = entry->getKey();
		counter =  entry->getValue();

		if (counter > 3 && counter > maxCounter) {
			maxCounter = counter;
			nameFound = key;
		}
	}

	if (!nameFound.isEmpty()) {
		//System::out << "Found name: " << nameFound << "\n";
		pet->setPetName(nameFound);

		for (int i = 0 ; i < size() ; i++) {
			String cmd = getBaseCommand(i);
			if (cmd.indexOf(nameFound) == 0) {
				String newCmd = cmd.subString(nameFound.length()+1,cmd.length());
				trainCommand(i,newCmd);
			}
		}
	}

	delete nameCandidates;
	nameCandidates = NULL;
}

String PetCommandHelper::getStfDesc(int command) {
	String stfDesc = "";
	switch(command) {
		case PETATTACK :
			stfDesc = "@pet/pet_menu:menu_attack";
			break;
		case PETFOLLOW :
			stfDesc = "@pet/pet_menu:menu_follow";
			break;
		case PETSTORE :
			stfDesc = "@pet/pet_menu:menu_store";
			break;
		case PETRELEASE :
			stfDesc = "@pet/pet_menu:menu_release";
			break;
		case PETSPECIALATTACK1 :
			stfDesc = "@pet/pet_menu:menu_specialattack_one";
			break;
		case PETSPECIALATTACK2 :
			stfDesc = "@pet/pet_menu:menu_specialattack_two";
			break;
		case PETSTAY :
			stfDesc = "@pet/pet_menu:menu_stay";
			break;
		case PETGUARD :
			stfDesc = "@pet/pet_menu:menu_guard";
			break;
		case PETPATROL :
			stfDesc = "@pet/pet_menu:menu_patrol";
			break;
		case PETPATROLPOINTADD :
			stfDesc = "@pet/pet_menu:menu_get_patrol_point";
			break;
		case PETPATROLPOINTCLEAR :
			stfDesc = "@pet/pet_menu:menu_clear_patrol_points";
			break;
		case PETFORMATION1:
			stfDesc = "@pet/pet_menu:menu_assume_formation_1";
			break;
		case PETFORMATION2:
			stfDesc = "@pet/pet_menu:menu_assume_formation_2";
			break;
		case PETTRICK1 :
			stfDesc = "@pet/pet_menu:menu_trick_1";
			break;
		case PETTRICK2 :
			stfDesc = "@pet/pet_menu:menu_trick_2";
			break;
		case PETGROUP :
			stfDesc = "@pet/pet_menu:menu_group";
			break;
		case PETFOLLOWOTHER :
			stfDesc = "@pet/pet_menu:menu_follow_other";
			break;
		case PETFRIEND :
			stfDesc = "@pet/pet_menu:menu_friend";
			break;
		case PETRANGEDATTACK :
			stfDesc = "@pet/pet_menu:menu_ranged_attack";
			break;
		case PETTRANSFER :
			stfDesc = "@pet/pet_menu:menu_transfer";
			break;
	}
	return stfDesc;
}
