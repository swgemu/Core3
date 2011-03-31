/*
 * VendorCreatureTemplate.h
 *
 *  Created on: Mar 22, 2011
 *      Author: polonel
 */

#ifndef VENDORCREATURETEMPLATE_H_
#define VENDORCREATURETEMPLATE_H_

#include "server/zone/templates/tangible/SharedCreatureObjectTemplate.h"

class VendorCreatureTemplate : public SharedCreatureObjectTemplate {

	Vector<uint32> clothes;

	String hairFile;

public:
	VendorCreatureTemplate() {

	}

	~VendorCreatureTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedCreatureObjectTemplate::readObject(templateData);

		hairFile = templateData->getStringField("hair");

		LuaObject clothesTemplate = templateData->getObjectField("clothes");

		for (int i = 1; i <= clothesTemplate.getTableSize(); ++i) {
			String file = clothesTemplate.getStringAt(i);
			uint32 templateCRC = file.hashCode();

			clothes.add(templateCRC);
		}

		clothesTemplate.pop();

    }

	inline String getHairFile() const {
		return hairFile;
	}

	inline Vector<uint32>* getClothes() {
		return &clothes;
	}

	bool isVendorCreatureTemplate() {
		return true;
	}

};

#endif /* VENDORCREATURETEMPLATE_H_ */
