/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATUREMAP_H_
#define CREATUREMAP_H_

#include "system/lang.h"

#include "server/zone/objects/creature/CreatureObject.h"

class CreatureMap : public HashTable<uint64, ManagedReference<CreatureObject*>  >
		, public HashTableIterator<uint64, ManagedReference<CreatureObject*> > {

public:
	CreatureMap() : HashTable<uint64, ManagedReference<CreatureObject*> >(3000)
			, HashTableIterator<uint64, ManagedReference<CreatureObject*> >(this) {
	}

	void put(uint64 oid, CreatureObject* creature) {
		CreatureObject* creo = HashTable<uint64, ManagedReference<CreatureObject*> >::put(oid, creature);
		if (creo != NULL && creo != creature)
			System::out << "CREATUREMAP OID CONFLICT\n";
	}

};

#endif /*CREATUREMAP_H_*/
