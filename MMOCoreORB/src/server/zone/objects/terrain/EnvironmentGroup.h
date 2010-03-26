/*
 * EnvironmentGroup.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef ENVIRONMENTGROUP_H_
#define ENVIRONMENTGROUP_H_

#include "EnvironmentData.h"

class EnvironmentGroup : public TemplateVariable<'EGRP'> {
	Vector<EnvironmentData*> data;

public:

	EnvironmentGroup() {

	}

	~EnvironmentGroup() {
		for (int i = 0; i < data.size(); ++i)
			delete data.get(i);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0002':
			parseFromIffStream(iffStream, Version<'0002'>());
			break;
		default:
			System::out << "unknown EGRP version 0x" << hex << version;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0002'>) {
		int number = iffStream->getSubChunksNumber();

		for (int i = 0; i < number; ++i) {
			EnvironmentData* efamData = new EnvironmentData();
			efamData->readObject(iffStream);

			data.add(efamData);
		}

	}
};


#endif /* ENVIRONMENTGROUP_H_ */
