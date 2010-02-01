/*
 * RadialFamily.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef RADIALFAMILY_H_
#define RADIALFAMILY_H_


#include "TemplateVariable.h"

class RadialData {
public:
	String ascii; // + 8 4byte vars
	float var1;
	float var2;
	float var3;
	float var4;
	int var5;
	float var6;
	float var7;
	int var8;
	uint32 var9;
};

class RadialFamily : public TemplateVariable<'RFAM'> {
	int var1;
	String var2;
	int var3, var4, var5;
	float var6;

	Vector<RadialData*> data;


public:
	~RadialFamily() {
		while (data.size() > 0)
			delete data.remove(0);
	}

	void readObject(IffStream* iffStream) {
		iffStream->openChunk('RFAM');

		var1 = iffStream->getInt();

		iffStream->getString(var2);

		var3 = iffStream->getByte();
		var4 = iffStream->getByte();
		var5 = iffStream->getByte();
		var6 = iffStream->getFloat();

		int var7 = iffStream->getInt(); // counter


		for (int i = 0; i < var7; i++) {
			RadialData* rdata = new RadialData();

			iffStream->getString(rdata->ascii);
			rdata->var1 = iffStream->getFloat();
			rdata->var2 = iffStream->getFloat();
			rdata->var3 = iffStream->getFloat();
			rdata->var4 = iffStream->getFloat();
			rdata->var5 = iffStream->getInt();
			rdata->var6 = iffStream->getFloat();
			rdata->var7 = iffStream->getFloat();
			rdata->var8 = iffStream->getInt();
			rdata->var9 = iffStream->getUnsignedInt();

			data.add(rdata);
		}

		iffStream->closeChunk('RFAM');
	}
};


#endif /* RADIALFAMILY_H_ */
