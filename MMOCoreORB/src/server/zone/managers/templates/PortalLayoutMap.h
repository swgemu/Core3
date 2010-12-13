/*
 * PortalLayoutMap.h
 *
 *  Created on: 03/12/2010
 *      Author: victor
 */

#ifndef PORTALLAYOUTMAP_H_
#define PORTALLAYOUTMAP_H_

#include "engine/engine.h"

class PortalLayout;
class FloorMesh;
class AppearanceTemplate;

class PortalLayoutMap : public HashTable<String, Reference<PortalLayout*> > {
	int hash(const String& k) {
		return k.hashCode();
	}

public:
	PortalLayoutMap() {
		setNullValue(NULL);
	}
};

class FloorMeshMap : public HashTable<String, Reference<FloorMesh*> > {
	int hash(const String& k) {
		return k.hashCode();
	}

public:
	FloorMeshMap() {
		setNullValue(NULL);
	}
};

class AppearanceMap : public HashTable<String, Reference<AppearanceTemplate*> > {
	int hash(const String& k) {
		return k.hashCode();
	}

public:
	AppearanceMap() {
		setNullValue(NULL);
	}
};

#endif /* PORTALLAYOUTMAP_H_ */
