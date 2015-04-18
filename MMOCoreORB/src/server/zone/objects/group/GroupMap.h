/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GROUPMAP_H_
#define GROUPMAP_H_

#include "system/lang.h"

#include "GroupObject.h"

class GroupMap : public HashTable<uint64, GroupObject*> {

	int hash(const uint64& key) {
        return Long::hashCode(key);
	}

public:
	GroupMap(int initsize) : HashTable<uint64, GroupObject*>(initsize) {
		setNullValue(NULL);
	}

};

#endif /*GROUPMAP_H_*/
