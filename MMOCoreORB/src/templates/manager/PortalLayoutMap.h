/*
 * PortalLayoutMap.h
 *
 *  Created on: 03/12/2010
 *      Author: victor
 */

#ifndef PORTALLAYOUTMAP_H_
#define PORTALLAYOUTMAP_H_

#include "templates/appearance/PortalLayout.h"
#include "templates/appearance/FloorMesh.h"
#include "templates/appearance/AppearanceTemplate.h"
#include "templates/building/InteriorLayoutTemplate.h"

class PortalLayoutMap : public HashTable<String, Reference<PortalLayout*> > {
public:
	PortalLayoutMap() {
		setNullValue(NULL);
	}
};

class FloorMeshMap : public HashTable<String, Reference<FloorMesh*> > {
public:
	FloorMeshMap() {
		setNullValue(NULL);
	}
};

class AppearanceMap : public HashTable<String, Reference<AppearanceTemplate*> > {
public:
	AppearanceMap() {
		setNullValue(NULL);
	}
};

class InteriorMap : public HashTable<String, Reference<InteriorLayoutTemplate*> > {
public:
	InteriorMap() {
		setNullValue(NULL);
	}
};

#endif /* PORTALLAYOUTMAP_H_ */
