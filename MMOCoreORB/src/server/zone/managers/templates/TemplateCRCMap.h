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
#include "server/zone/templates/TemplateReference.h"

class TemplateCRCMap : public HashTable<uint32, TemplateReference<SharedObjectTemplate*> > {
	int hash(const uint32& k) const {
		return k;
	}

public:
	TemplateCRCMap() : HashTable<uint32, TemplateReference<SharedObjectTemplate*> >(16000) {
		setNullValue(NULL);
	}
};

class ClientTemplateCRCMap : public HashTable<uint32, String> {
	int hash(const uint32& k) const {
		return k;
	}

public:
	ClientTemplateCRCMap() : HashTable<uint32, String>(16000) {
		setNullValue("");
	}
};


#endif /* TEMPLATECRCMAP_H_ */
