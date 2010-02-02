/*
 * FloraFamily.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef FLORAFAMILY_H_
#define FLORAFAMILY_H_

#include "TemplateVariable.h"

class FloraData {
public:
	String name; // + 8 4byte vars
	float var1;
	uint32 var2;
	float var3;
	float var4;
	uint32 var5;
	int var6;
	float var7;
	float var8;
};

class FloraFamily : public TemplateVariable<'FFAM'> {
	int familyId;
	String familyName;
	byte red, green, blue;
	float weight;
	uint32 isAquatic;

	Vector<FloraData*> data;


public:
	~FloraFamily() {
		while (data.size() > 0)
			delete data.remove(0);
	}

	void readObject(IffStream* iffStream) {
		iffStream->openChunk('FFAM');

		familyId = iffStream->getInt();
		iffStream->getString(familyName);

		red = iffStream->getByte();
		green = iffStream->getByte();
		blue = iffStream->getByte();
		weight = iffStream->getFloat();
		isAquatic = iffStream->getUnsignedInt();

		int var8 = iffStream->getInt();// counter

		for (int i = 0; i < var8; ++i) {
			FloraData* floraData = new FloraData();

			iffStream->getString(floraData->name);
			floraData->var1 = iffStream->getFloat();
			floraData->var2 = iffStream->getUnsignedInt();
			floraData->var3 = iffStream->getFloat();
			floraData->var4 = iffStream->getFloat();
			floraData->var5 = iffStream->getUnsignedInt();
			floraData->var6 = iffStream->getInt();
			floraData->var7 = iffStream->getFloat();
			floraData->var8 = iffStream->getFloat();

			data.add(floraData);
		}

		iffStream->closeChunk('FFAM');
	}
};


#endif /* FLORAFAMILY_H_ */
