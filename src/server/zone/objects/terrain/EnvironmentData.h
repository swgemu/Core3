/*
 * EnvironmentData.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef ENVIRONMENTDATA_H_
#define ENVIRONMENTDATA_H_

class EnvironmentData : public TemplateVariable<'EFAM'> {
	int var1;
	String var2;

	byte var3;
	byte var4;
	byte var5;
	float var6;
public:

	EnvironmentData() {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		iffStream->openChunk('DATA');

		var1 = iffStream->getInt();

		iffStream->getString(var2);

		var3 = iffStream->getByte();
		var4 = iffStream->getByte();
		var5 = iffStream->getByte();
		var6 = iffStream->getFloat();

		iffStream->closeChunk('DATA');
	}

};

#endif /* ENVIRONMENTDATA_H_ */
