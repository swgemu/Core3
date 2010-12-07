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
class MeshAppearanceTemplate;

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

class MeshAppearanceMap : public HashTable<String, Reference<MeshAppearanceTemplate*> > {
	int hash(const String& k) {
		return k.hashCode();
	}

public:
	MeshAppearanceMap() {
		setNullValue(NULL);
	}
};

#endif /* PORTALLAYOUTMAP_H_ */
