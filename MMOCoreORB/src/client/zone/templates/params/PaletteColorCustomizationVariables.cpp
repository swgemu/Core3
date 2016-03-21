/*
 * PaletteColorCustomizationVariables.cpp
 *
 *  Created on: 15-abr-2009
 *      Author: TheAnswer
 */

#include "PaletteColorCustomizationVariables.h"

bool PaletteColorCustomizationVariables::parse(Chunk* source) {
	//std::cout << "parsing PaletteColorCustomizationVariables\n";

	uint8 unk = source->readByte();
	uint32 num = source->readInt();

	if (num == 0) {
		//std::cout << "0 PCCVs\n";
		return false;
	} else {
		//std::cout << num << " PCCVs\n";
		//return;
	}

	for (int i = 0; i < variables.size(); ++i)
		delete variables.get(i);

	variables.removeAll();

	IffStream* iffStream = source->getIffStream();

	if (iffStream == NULL) {
		//std::cout << "iffstream null\n";
		return false;
	}

	for (int i = 0; i < num; ++i) {
		//try {
			uint8 unk2 = iffStream->getByte();

			switch (unk2) {
			case 0:
				continue;
			case 1:
				parseType1(iffStream);
				continue;
			case 2: {
				StringBuffer stream;

				stream << "unhandled PaletteColorCustomizationVariables type! in ";
				stream << iffStream->getFileName() << "\n";
				//SWGForensics::instance->printToConsole(text);
				Logger::console.error(stream.toString());
				// throw unhandled type!
				continue;
			}
			}
		/*} catch (...) {
			continue;
		}*/
	}

	return true;
}

void PaletteColorCustomizationVariables::parseType1(IffStream* iffStream) {
	uint32 type = iffStream->getUnsignedInt();

	iffStream->closeChunk();

	Chunk* chunk = iffStream->openForm('PCCV');

	if (chunk == NULL) {
		//std::cout << "could not open shit\n";
		return;
	}

	PaletteColorCustomizationVariable* pccv = new PaletteColorCustomizationVariable();
	pccv->parse(chunk);

	/*String name = pccv.getVariableName();

	if (!name.isEmpty() && !variables.contains(name))
		variables[name] = pccv;*/

	variables.add(pccv);

	iffStream->closeForm('PCCV');

	iffStream->openChunk('XXXX');

}

String PaletteColorCustomizationVariables::toString() {
	StringBuffer stream;

	stream << "{";

	/*for (int i = 0; i < variables.size(); ++i) {
			stream << i + 1 << ":\n" << variables[i].toString() << "\n";
		}*/

	for (int i = 0; i < variables.size(); ++i) {
		stream << variables.get(i)->toString();

		if (i + 1 < variables.size())
			stream << ", \n\t\t\t";
	}

	stream << "}";

	return stream.toString();
}
