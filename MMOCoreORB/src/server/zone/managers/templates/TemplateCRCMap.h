/*
 * TemplateCRCMap.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef TEMPLATECRCMAP_H_
#define TEMPLATECRCMAP_H_

#include "engine/engine.h"

#include "server/zone/templates/SharedObjectTemplate.h"

class TemplateCRCMap : public HashTable<uint32, SharedObjectTemplate*> {
	int hash(const uint32& k) {
		return k;
	}

public:
	TemplateCRCMap() : HashTable<uint32, SharedObjectTemplate*>(16000) {
		setNullValue(NULL);
	}
};


#endif /* TEMPLATECRCMAP_H_ */
