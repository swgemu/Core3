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
	String var1;
	float var2;
};

class ShaderFamily : public TemplateVariable<'SFAM'> {
	int var1;
	String var2;
	String var3;
	int var4, var5, var6;
	float var7, var8;

	Vector<ShaderVar*> shaderVars;

public:
	~ShaderFamily() {
		while (shaderVars.size() > 0)
			delete shaderVars.remove(0);

	}

	void readObject(IffStream* iffStream) {
		iffStream->openChunk('SFAM');

		var1 = iffStream->getInt();

		iffStream->getString(var2);

		iffStream->getString(var3);

		var4 = iffStream->getByte();
		var5 = iffStream->getByte();
		var6 = iffStream->getByte();
		var7 = iffStream->getFloat();
		var8 = iffStream->getFloat();

		int var9 = iffStream->getInt();

		for (int i = 0; i < var9; ++i) {
			ShaderVar* var = new ShaderVar();
			iffStream->getString(var->var1);
			var->var2 = iffStream->getFloat();
		}

		iffStream->closeChunk('SFAM');
	}
};


#endif /* SHADERFAMILY_H_ */
