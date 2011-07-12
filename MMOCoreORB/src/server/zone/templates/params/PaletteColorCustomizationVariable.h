/*
 * PaletteColorCustomizationVariable.h
 *
 *  Created on: 23-feb-2009
 *      Author: TheAnswer
 */

#ifndef PALETTECOLORCUSTOMIZATIONVARIABLE_H_
#define PALETTECOLORCUSTOMIZATIONVARIABLE_H_

#include "engine/engine.h"

#include "Param.h"
#include "primitives/StringParam.h"
#include "primitives/IntegerParam.h"
#include "RangedIntCustomizationVariable.h"

class PaletteColorCustomizationVariable : public RangedIntCustomizationVariable{
protected:
	StringParam variableName;
	StringParam palettePathName;
	IntegerParam defaultPaletteIndex;

public:
	PaletteColorCustomizationVariable() {
		setType(PALETTECOLORCUSTOMIZATION);
	}

	PaletteColorCustomizationVariable(int defIndex, const String& fileName) {
		palettePathName = fileName;
		defaultValue = defIndex;
		setType(PALETTECOLORCUSTOMIZATION);
	}

	PaletteColorCustomizationVariable(const PaletteColorCustomizationVariable& p) {
		variableName = p.variableName;
		palettePathName = p.palettePathName;
		defaultPaletteIndex = p.defaultPaletteIndex;

		setType(PALETTECOLORCUSTOMIZATION);
	}

	~PaletteColorCustomizationVariable() {

	}

	PaletteColorCustomizationVariable& operator=(const PaletteColorCustomizationVariable& p) {
		if (this == &p)
			return *this;

		variableName = p.variableName;
		palettePathName = p.palettePathName;
		defaultPaletteIndex = p.defaultPaletteIndex;

		return *this;
	}

	String toString() {
		StringBuffer stream;
		/*stream << "variableName" << " = " << variableName.toString() << "\n";
		stream << "palettePathName" << " = " << palettePathName.toString() << "\n";
		stream << "defaultPaletteIndex" << " = " << defaultPaletteIndex.toString() << "\n";*/

		stream << "{";

		stream << variableName.toString() << ", " << palettePathName.toString()
				<< ", " << defaultPaletteIndex.toString();

		stream << "}";

		return stream.toString();
	}

	bool parse(Chunk* source) {
		IffStream* iffStream = source->getIffStream();

		if (source->getChunkSize() == 0)
			return false;

		Chunk* chunk = iffStream->openChunk('PCNT');

		if (chunk == NULL) {
			//std::cout << "could not open pcnt\n";
			return false;
		}

		int vars = iffStream->getInt();

		iffStream->closeChunk('PCNT');

		for (int j = 0; j < vars; ++j) {
			Chunk* var = iffStream->openChunk('XXXX');

			String varName;
			var->readString(varName);

			//std::cout << "parsing pccv:[" << varName.toStdString() << "]\n";

			if (varName == "variableName") {
				variableName.parse(var);
			} else if (varName == "palettePathName") {
				palettePathName.parse(var);
			} else if (varName == "defaultPaletteIndex") {
				defaultPaletteIndex.parse(var);
			}

			iffStream->closeChunk('XXXX');
		}

		return true;
	}


	inline String getPaletteFileName() {
		return palettePathName.get();
	}

	/*static bool parseFromString(T* address, const sys::lang::String& value, int version = 0) {
		return address->parseFromString(value, version);
	}*/

	String getVariableName() {
		return variableName.get();
	}

};


#endif /* PALETTECOLORCUSTOMIZATIONVARIABLE_H_ */
