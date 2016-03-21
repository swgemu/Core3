/*
 * ShaderFamily.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef SHADERFAMILY_H_
#define SHADERFAMILY_H_

#include "TemplateVariable.h"

class ShaderVar {
public:
	String name;
	float weight;
};

class ShaderFamily : public TemplateVariable<'SFAM'> {
	int familyId;
	String familyName;
	String fileName;
	byte red, green, blue;
	float var7;
	float weight;

	Vector<ShaderVar*> shaderVars;

public:
	~ShaderFamily() {
		while (shaderVars.size() > 0)
			delete shaderVars.remove(0);

	}

	void readObject(IffStream* iffStream) {
		iffStream->openChunk('SFAM');

		familyId = iffStream->getInt();

		iffStream->getString(familyName);

		iffStream->getString(fileName);

		red = iffStream->getByte();
		green = iffStream->getByte();
		blue = iffStream->getByte();
		var7 = iffStream->getFloat();
		weight = iffStream->getFloat();

		int nLayers = iffStream->getInt();

		for (int i = 0; i < nLayers; ++i) {
			ShaderVar* var = new ShaderVar();
			iffStream->getString(var->name);
			var->weight = iffStream->getFloat();

			shaderVars.add(var);
		}

		iffStream->closeChunk('SFAM');
	}
};


#endif /* SHADERFAMILY_H_ */
