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

#ifndef CLIENTCREATECHARACTER_H_
#define CLIENTCREATECHARACTER_H_

#include "engine/engine.h"

#include "../../objects/player/Player.h"
#include "../../objects/player/Races.h"

class ClientCreateCharacter : public BaseMessage {
public:
	ClientCreateCharacter(const unicode& name) {
		insertShort(12);
		insertInt(0xB97F3074);

		insertAscii("");
		insertUnicode(name);
		insertAscii("");
		insertAscii("");
		insertAscii("");
		insertAscii("");
		insertAscii("");
		insertByte(0);
		insertInt(1);
		insertInt(0);
		insertByte(0);
	}

	static void parse(Packet* pack, Player* player) {
		string customization;
		pack->parseAscii(customization);

		player->setCharacterAppearance(customization);

		unicode characterName;
		pack->parseUnicode(characterName); //get unicode name
		player->setCharacterName(characterName);

		int idx = characterName.indexOf(' ');
		if (idx != -1) {
			player->setFirstName(characterName.substring(0, idx).c_str());
			player->setLastName(characterName.substring(idx + 1, characterName.size()).c_str());
		}
		else {
			player->setFirstName(characterName.c_str());
			player->setLastName("");
		}


		string racefile;
		pack->parseAscii(racefile);
		player->setRaceFileName(racefile);

		int raceid = Races::getRaceID(racefile);
		player->setRaceID(raceid);
		player->setRaceName(Races::getRace(raceid));
		player->setSpeciesName(Races::getSpecies(raceid));
		player->setGender(Races::getGender(raceid));

		player->makeCharacterMask();

		string location;
		pack->parseAscii(location);
		player->setStartingLocation(location);

		string hairobj;
		pack->parseAscii(hairobj);
		if (!hairobj.empty()) {
			int idx = hairobj.find("hair_", 0);
			if (idx != -1) {
				hairobj.replace(idx, 5, "shared_hair_");
				player->setHairObject(hairobj);
			}
		}

		string haircust;
		pack->parseAscii(haircust); //grab the hair cust data
		player->setHairAppearance(haircust);

		string profession;
		pack->parseAscii(profession);
		player->setStartingProfession(profession);

		pack->shiftOffset(1); //move past some unknown byte

		float height = pack->parseFloat();
		if (height < 0.7 || height > 1.5)
			height = 1;

		player->setHeight(height);

		unicode bio;
		pack->parseUnicode(bio); //get the biography.
		player->setBiography(bio);

		uint8 tutflag = pack->parseByte(); //tutorial bool.
	}

};

#endif /*CLIENTCREATECHARACTER_H_*/
