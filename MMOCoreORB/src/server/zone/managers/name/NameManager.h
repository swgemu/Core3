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

#ifndef NAMEMANAGER_H_
#define NAMEMANAGER_H_

#include "engine/lua/Lua.h"
#include "engine/lua/LuaObject.h"
#include "engine/core/ManagedReference.h"
#include "server/zone/managers/templates/TemplateManager.h"

namespace server {
	namespace zone {

	class ZoneProcessServer;

	}
}

using namespace server::zone;

namespace server {
	namespace zone {
		namespace objects {
			namespace creature {

				class CreatureObject;
			}
		}
	}
}

using namespace server::zone::objects::creature;

class BannedNameSet : public HashSet<String> {
	int hash(const String& str) {
		return str.hashCode();
	}

public:
	BannedNameSet() : HashSet<String>() {
	}
};

class NameManagerResult {
public:
	static const uint8 DECLINED_EMPTY = 0;
	static const uint8 DECLINED_DEVELOPER = 1;
	static const uint8 DECLINED_FICT_RESERVED = 2;
	static const uint8 DECLINED_PROFANE = 3;
	static const uint8 DECLINED_RACE_INAPP = 4;
	static const uint8 DECLINED_SYNTAX = 5;
	static const uint8 DECLINED_RESERVED = 6;
	static const uint8 ACCEPTED	= 7;
};

namespace server {
	namespace zone {
		namespace managers {
			namespace name {

class NameManager : public Singleton<NameManager>, public Logger, public Object {
	ManagedReference<ZoneProcessServer*> server;

	Lua* lua;

	Vector<String>* profaneNames;
	BannedNameSet* developerNames;
	BannedNameSet* fictionNames;
	BannedNameSet* reservedNames;

	VectorMap<String, String> letterMappings;

	Vector<String> organicPrefixes;
	Vector<String> organicSuffixes;

	Vector<String> inorganicPrefixes;
	Vector<String> inorganicSuffixes;

	Vector<String> npcFirstNames;
	Vector<String> npcSurnames;

private:

	void initialize();

	bool loadConfigFile();

	bool loadConfigData();

	void loadDefaultConfig();

	void fillNames();

	char chooseNextLetter(const char, const char);

	inline bool isReserved(String);

	inline bool isDeveloper(String);

	inline bool isFiction(String);

	inline bool isVowel(const char);

	inline void addPrefix(String& name, bool isOrganic);

	inline void addSuffix(String& name, bool isOrganic);

	char chooseLetterInclusive(String include);

	String makeName(int nameLength);

public:
	NameManager();
	NameManager(ZoneProcessServer* serv);

	~NameManager();

	void test();

	bool isProfane(String name);

	int validateName(CreatureObject * obj);
	int validateName(const String& name, int species);

	const String makeCreatureName(bool surname = true);

	const String makeResourceName(bool isOrganic);
};

			}
		}
	}
}

using namespace server::zone::managers::name;

#endif /*NAMEMANAGER_H_*/
