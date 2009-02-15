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

#ifndef BLUEFROGCREATUREIMPLEMENTATION_H_
#define BLUEFROGCREATUREIMPLEMENTATION_H_

class Player;
class Profession;
class SceneObject;
class SkillBox;

#include "BlueFrogCreature.h"
#include "../../../managers/player/ProfessionManager.h"
#include "../../player/professions/SkillBox.h"

class BlueFrogCreatureImplementation : public BlueFrogCreatureServant {
	Profession* profession;

public:
	BlueFrogCreatureImplementation(uint64 oid);
	~BlueFrogCreatureImplementation();

	static const int JAWA = 0x00;
	static const int GUNGAN = 0x01;
	static const int MEDDROID	= 0x02;
	static const int BARTENDER	= 0x03;
	static const int EWOK = 0x04;
	static const int JEDI = 0x05;

	void sendConversationStartTo(SceneObject* obj);
	void sendMessage1(Player* player);
	void sendChoices1(Player* player);
	void sendSelectProfessionMessage(Player* player);
	void sendProfessionChoices(Player* player);
	void sendSelectItemMessage(Player* player);
	void sendWoundTerminalMessage(Player* player);
	void sendStateTerminalMessage(Player* player);
	void sendFactionPointTerminalMessage(Player * player);

	void selectConversationOption(int option, SceneObject* obj);

	bool trainProfession(Player * player, String prof);
	bool trainSkill(Player * player, SkillBox * skill);
	void dropSkills(Player * player);

	void setBFType(int type);
};


#endif
