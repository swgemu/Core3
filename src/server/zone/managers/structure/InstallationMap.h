/*
 * StructureMap.h
 *
 *  Created on: Oct 25, 2008
 *      Author: swgemu
 */

#ifndef INSTALLATIONMAP_H_
#define INSTALLATIONMAP_H_

#include "system/lang.h"

#include "../../objects/installation/InstallationObject.h"

class InstallationMap : public HashTable<uint64, ManagedReference<InstallationObject> >
		, public HashTableIterator<uint64, ManagedReference<InstallationObject> > {

	int hash(const uint64& key) {
        return Long::hashCode(key);
	}

public:
	InstallationMap(int initsize) : HashTable<uint64, ManagedReference<InstallationObject> >(initsize)
			, HashTableIterator<uint64, ManagedReference<InstallationObject> >(this) {
		setNullValue(NULL);
	}

	void put(uint64 oid, ManagedReference<InstallationObject> obj) {
		if (HashTable<uint64, ManagedReference<InstallationObject> >::put(oid, obj) != NULL)
			System::out << "INSTALLATIONMAP OID CONFLICT\n";
	}

};
#endif /* INSTALLATIONMAP_H_ */
