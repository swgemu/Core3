/*
 * InformationHeader.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef INFORMATIONHEADER_H_
#define INFORMATIONHEADER_H_

#include "../TemplateVariable.h"

class InformationHeader : public TemplateVariable<'IHDR'> {
	int var1;
	String description;

public:
	InformationHeader() : IffTemplateVariable(), var1(0) {

	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0001':
			parseFromIffStream(iffStream, Version<'0001'>());
			break;
		default:
			System::out << "unknown InformationHeader version " << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0001'>) {
		iffStream->openChunk('DATA');

		var1 = iffStream->getInt();
		iffStream->getString(description);

		iffStream->closeChunk('DATA');
	}

	inline bool isEnabled() {
		return var1 != 0;
	}

	inline String& getDescription() {
		return description;
	}
};


#endif /* INFORMATIONHEADER_H_ */
