/*
 * MapFamily.h
 *
 *  Created on: 02/02/2010
 *      Author: victor
 */

#ifndef MAPFAMILY_H_
#define MAPFAMILY_H_

#include "TemplateVariable.h"

#include "MapFractal.h"

class MapFamily : public TemplateVariable<'MFAM'> {
	int var1;
	String var2;
	MapFractal mfrc;
public:
	MapFamily() : var1(0) {
	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		iffStream->openChunk('DATA');

		var1 = iffStream->getInt();
		iffStream->getString(var2);

		iffStream->closeChunk('DATA');

		mfrc.readObject(iffStream);
	}

	inline MapFractal* getMfrc() {
		return &mfrc;
	}

	inline int getVar1() {
		return var1;
	}

	inline String& getName() {
		return var2;
	}
};


#endif /* MAPFAMILY_H_ */
