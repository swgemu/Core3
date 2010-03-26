/*
 * TemplateCRCMap.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef TEMPLATECRCMAP_H_
#define TEMPLATECRCMAP_H_

#include "engine/engine.h"

class TemplateCRCMap : public HashTable<uint32, String> {
	int hash(const uint32& k) {
		return k;
	}

public:
	TemplateCRCMap() : HashTable<uint32, String>(16000) {

	}
};


#endif /* TEMPLATECRCMAP_H_ */
