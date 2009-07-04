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

#ifndef ATTACHMENTIMPLEMENTATION_H_
#define ATTACHMENTIMPLEMENTATION_H_

#include "engine/engine.h"
#include "Attachment.h"
#include "../../player/Player.h"
#include "../wearables/Wearable.h"
#include "../wearables/WearableSkillModMap.h"
#include "../wearables/WearableSkillMods.h"

class AttachmentImplementation : public AttachmentServant {
protected:
	int attachmentType;

	int maxmods;

	VectorMap<String, int> skillModMap;
	Vector<String> skillModIndex;

	WearableSkillMods wearableSkillMods;

public:
	static const int CLOTHINGATTACHMENT =  0x01;
	static const int ARMORATTACHMENT = 0x02;

public:
	AttachmentImplementation(uint64 objID, int attachmentType);

	virtual ~AttachmentImplementation();

	void init();

	void parseItemAttributes();
	void generateAttributes(SceneObject* obj);
	void addAttributes(AttributeListMessage* alm);

	void parseSkillModAttributeString(String attribute);
	void parseSkillModIndexString(String attribute);

	void saveSkillModAttributes();
	void saveSkillModIndex();

	void remove(Player* player);

	void generateSkillMods(Player* player, int modifier);
	void generateSkillMods(int modifier);

	void addSkillMod(String skillModType, int skillModValue);
	void setSkillMod(String name, int value);

	int getRandomModValue(int luck, int creatureLevel);

	inline void setSkillModCount(int value) {
		maxmods = value;
	}

	inline String& getSkillModName(int index) {
		return (&(skillModMap.elementAt(index)))->getKey();
	}
	inline int getSkillModValue(int index) {
		return (&(skillModMap.elementAt(index)))->getValue();
	}

	inline int getSkillModValue(String name) {
		return skillModMap.get(name);
	}

	int getSkillModCount() {
		return skillModMap.size();
	}

	int getAttachmentType() {
		return attachmentType;
	}
};

#endif /*ATTACHMENTIMPLEMENTATION_H_*/
