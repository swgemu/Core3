/*
 * MapFamily.h
 *
 *  Created on: 02/02/2010
 *      Author: victor
 */

#ifndef MAPFAMILY_H_
#define MAPFAMILY_H_

#include "TemplateVariable.h"

#include "Mfrc.h"

class MapFamily : public TemplateVariable<'MFAM'> {
	int var1;
	String var2;
	Mfrc mfrc;
public:
	void parseFromIffStream(engine::util::IffStream* iffStream) {
		iffStream->openChunk('DATA');

		var1 = iffStream->getInt();
		iffStream->getString(var2);

		iffStream->closeChunk('DATA');

		mfrc.readObject(iffStream);
	}

	inline Mfrc* getMfrc() {
		return &mfrc;
	}
};


#endif /* MAPFAMILY_H_ */
