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

class AppearanceMap : public HashTable<String, AppearanceTemplate* > {
public:
	AppearanceMap() {
		setNullValue(NULL);
	}
	
	String getKeyForValue(const AppearanceTemplate* tmpl) {
		auto iter = iterator();
		while(iter.hasNext()) {
			String key;
			AppearanceTemplate *value = NULL;
			iter.getNextKeyAndValue(key, value);
			if(value == tmpl)
				return key;
		}
		return "";
		
	}
};

#endif /* PORTALLAYOUTMAP_H_ */
