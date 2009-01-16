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

#ifndef WEARABLEIMPLEMENTATION_H_
#define WEARABLEIMPLEMENTATION_H_

#include "../../creature/CreatureObject.h"

#include "Wearable.h"

class WearableImplementation : public WearableServant {
private:

	int skillMod0Type;
	int skillMod0Value;

	int skillMod1Type;
	int skillMod1Value;

	int skillMod2Type;
	int skillMod2Value;

	int sockets;

	int socket0Type;
	int socket0Value;

	int socket1Type;
	int socket1Value;

	int socket2Type;
	int socket2Value;

	int socket3Type;
	int socket3Value;

public:

	WearableImplementation(uint64 objid, uint32 tempCRC, const UnicodeString& n, const String& tempn, bool eqp = false);
	WearableImplementation(CreatureObject* creature, uint64 oid, uint32 tempCRC, const UnicodeString& n, const String& tempn, bool eqp = false);
	WearableImplementation(CreatureObject* creature, uint32 tempCRC, const UnicodeString& n, const String& tempn, bool eqp = false);


	void parseItemAttributes();
	void init();

	void sendTo(Player* player, bool doClose = true);

	void sendRadialResponseTo(Player* player, ObjectMenuResponse* omr);

	void updateCraftingValues(DraftSchematic* draftSchematic);

	void generateAttributes(SceneObject* obj);

	void addAttributes(AttributeListMessage* alm);

	int addSkillMod(int skillModType, int skillModValue);

	void setSocket(int index, int type, int value);
	void setSocketType(int index, int type);
	void setSocketValue(int index, int type);

	int getSocketType(int index);
	int getSocketValue(int index);

	inline void setSkillMod0Type(int skillModType) {
		skillMod0Type = skillModType;
		String name = "skillMod0Type";
		itemAttributes->setIntAttribute(name, skillModType);
	}

	inline void setSkillMod1Type(int skillModType) {
		skillMod1Type = skillModType;
		String name = "skillMod1Type";
		itemAttributes->setIntAttribute(name, skillModType);
	}


	inline void setSkillMod2Type(int skillModType) {
		skillMod2Type = skillModType;
		String name = "skillMod2Type";
		itemAttributes->setIntAttribute(name, skillModType);
	}

	inline void setSkillMod0Value(int skillModValue) {
		skillMod0Value = skillModValue;
		String name = "skillMod0Value";
		itemAttributes->setIntAttribute(name, skillModValue);
	}

	inline void setSkillMod1Value(int skillModValue) {
		skillMod1Value = skillModValue;
		String name = "skillMod1Value";
		itemAttributes->setIntAttribute(name, skillModValue);
	}

	inline void setSkillMod2Value(int skillModValue) {
		skillMod2Value = skillModValue;
		String name = "skillMod2Value";
		itemAttributes->setIntAttribute(name, skillModValue);
	}

	inline void setSockets(int socket) {
		sockets = socket;
		String key = "sockets";
		itemAttributes->setIntAttribute(key, socket);
	}

	inline void setSocket0Type(int socketType) {
		socket0Type = socketType;
		String key = "socket0Type";
		itemAttributes->setIntAttribute(key, socketType);
	}

	inline void setSocket1Type(int socketType) {
		socket1Type = socketType;
		String key = "socket1Type";
		itemAttributes->setIntAttribute(key, socketType);
	}

	inline void setSocket2Type(int socketType) {
		socket2Type = socketType;
		String key = "socket2Type";
		itemAttributes->setIntAttribute(key, socketType);
	}

	inline void setSocket3Type(int socketType) {
		socket3Type = socketType;
		String key = "socket3Type";
		itemAttributes->setIntAttribute(key, socketType);
	}

	inline void setSocket0Value(int socketValue) {
		socket0Value = socketValue;
		String key = "socket0Value";
		itemAttributes->setIntAttribute(key, socketValue);
	}

	inline void setSocket1Value(int socketValue) {
		socket1Value = socketValue;
		String key = "socket1Value";
		itemAttributes->setIntAttribute(key, socketValue);
	}

	inline void setSocket2Value(int socketValue) {
		socket2Value = socketValue;
		String key = "socket2Value";
		itemAttributes->setIntAttribute(key, socketValue);
	}

	inline void setSocket3Value(int socketValue) {
		socket3Value = socketValue;
		String key = "socket3Value";
		itemAttributes->setIntAttribute(key, socketValue);
	}

	inline int getSkillMod0Type() {
		return skillMod0Type;
	}

	inline int getSkillMod1Type() {
		return skillMod1Type;
	}

	inline int getSkillMod2Type() {
		return skillMod2Type;
	}

	inline int getSkillMod0Value() {
		return skillMod0Value;
	}

	inline int getSkillMod1Value() {
		return skillMod1Value;
	}

	inline int getSkillMod2Value() {
		return skillMod2Value;
	}

	inline int getSockets() {
		return sockets;
	}

	inline int getSocket0Type() {
		return socket0Type;
	}

	inline int getSocket1Type() {
		return socket1Type;
	}

	inline int getSocket2Type() {
		return socket2Type;
	}

	inline int getSocket3Type() {
		return socket3Type;
	}

	inline int getSocket0Value() {
		return socket0Value;
	}

	inline int getSocket1Value() {
		return socket1Value;
	}

	inline int getSocket2Value() {
		return socket2Value;
	}

	inline int getSocket3Value() {
		return socket3Value;
	}
};

#endif /*WEARABLEIMPLEMENTATION_H_*/
