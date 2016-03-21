/*
 * SharedShipObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDSHIPOBJECTTEMPLATE_H_
#define SHAREDSHIPOBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class SharedShipObjectTemplate : public SharedTangibleObjectTemplate {
	StringParam interiorLayoutFileName;
	StringParam cockpitFilename;
	BoolParam hasWings;
	BoolParam playerControlled;
public:
	SharedShipObjectTemplate() {

	}

	~SharedShipObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);
	}

	void parseVariableData(const String& varName, Chunk* data) {
		if (varName == "interiorLayoutFileName") {
			interiorLayoutFileName.parse(data);
		} else if (varName == "cockpitFilename") {
			cockpitFilename.parse(data);
		} else if (varName == "hasWings") {
			hasWings.parse(data);
		} else if (varName == "playerControlled") {
			playerControlled.parse(data);
		}
	}

	void parseFileData(IffStream* iffStream) {
		iffStream->openChunk('PCNT');

		int variableCount = iffStream->getInt();

		iffStream->closeChunk('PCNT');

		for (int i = 0; i < variableCount; ++i) {
			//while (iffStream->getRemainingSubChunksNumber() > 0) {
			Chunk* chunk = iffStream->openChunk('XXXX');

			if (chunk == NULL)
				continue;

			String varName;

			iffStream->getString(varName);

			//std::cout << "parsing wtf shit:[" << varName.toStdString() << "]\n";
			parseVariableData(varName, chunk);

			iffStream->closeChunk();
		}
	}

	void readObject(IffStream* iffStream) {
		uint32 nextType = iffStream->getNextFormType();

		if (nextType != 'SSHP') {
			//Logger::console.error("expecting SHOT got " + String::hexvalueOf((int)nextType));

			SharedTangibleObjectTemplate::readObject(iffStream);

			return;
		}

		iffStream->openForm('SSHP');

		uint32 derv = iffStream->getNextFormType();

		if (derv == 'DERV') {
			loadDerv(iffStream);

			derv = iffStream->getNextFormType();
		}

		iffStream->openForm(derv);

		try {
			parseFileData(iffStream);
		} catch (Exception& e) {
			String msg;
			msg += "exception caught parsing file data ->";
			msg += e.getMessage();

			Logger::console.error(msg);
		}

		iffStream->closeForm(derv);

		if (iffStream->getRemainingSubChunksNumber() > 0) {
			readObject(iffStream);
		}

		iffStream->closeForm('SSHP');
	}
};

#endif /* SHAREDSHIPOBJECTTEMPLATE_H_ */
