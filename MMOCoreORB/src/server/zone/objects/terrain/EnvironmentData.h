/*
 * EnvironmentData.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef ENVIRONMENTDATA_H_
#define ENVIRONMENTDATA_H_

class EnvironmentData : public TemplateVariable<'EFAM'> {
	int environmentId;
	String environmentName;

	byte var3;
	byte var4;
	byte var5;
	float var6;
public:

	EnvironmentData() : environmentId(0), var3(0), var4(0), var5(0), var6(0) {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		iffStream->openChunk('DATA');

		environmentId = iffStream->getInt();

		iffStream->getString(environmentName);

		var3 = iffStream->getByte();
		var4 = iffStream->getByte();
		var5 = iffStream->getByte();
		var6 = iffStream->getFloat();

		iffStream->closeChunk('DATA');
	}

};

#endif /* ENVIRONMENTDATA_H_ */
