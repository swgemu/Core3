/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLAYERMAP_H_
#define PLAYERMAP_H_

#include "engine/engine.h"

namespace server {
namespace zone {
	namespace objects {
		namespace creature {
			class CreatureObject;
		}
	}
namespace managers {
namespace player {

using namespace server::zone::objects::creature;

class PlayerMap : public Mutex, public Object {
	HashTable<String, Reference<CreatureObject*> > players;
	HashTableIterator<String, Reference<CreatureObject*> > iter;

public:
	PlayerMap(int initsize);

	void put(const String& name, CreatureObject* player, bool doLock = true);

	CreatureObject* get(const String& name, bool doLock = true);
	CreatureObject* remove(const String& name, bool doLock = true);

	CreatureObject* getNextValue(bool doLock = true);

	CreatureObject* next(bool doLock = true);

	bool hasNext(bool doLock = true);

	void resetIterator(bool doLock = true);

	int size(bool doLock = true);

};


}
}
}
}

using namespace server::zone::managers::player;


#endif /*PLAYERMAPIMPLEMENTATION_H_*/
