/*
 * RangedIntCustomizationVariable.h
 *
 *  Created on: 16-abr-2009
 *      Author: TheAnswer
 */

#ifndef RANGEDINTCUSTOMIZATIONVARIABLE_H_
#define RANGEDINTCUSTOMIZATIONVARIABLE_H_

#include "Param.h"
#include "primitives/StringParam.h"
#include "primitives/IntegerParam.h"
#include "../customization/CustomizationVariable.h"


class RangedIntCustomizationVariable : public CustomizationVariable, public Param {
protected:
	StringParam variableName;
	IntegerParam minValueInclusive;
	IntegerParam defaultValue;
	IntegerParam maxValueExclusive;

public:
	RangedIntCustomizationVariable() : Param() {
		setType(RANGEDINTCUSTOMIZATIONVARIABLE);
	}

	RangedIntCustomizationVariable(const RangedIntCustomizationVariable& m) : CustomizationVariable() , Param() {
		setType(RANGEDINTCUSTOMIZATIONVARIABLE);

		variableName = m.variableName;
		minValueInclusive = m.minValueInclusive;
		defaultValue = m.defaultValue;
		maxValueExclusive = m.maxValueExclusive;
	}

	~RangedIntCustomizationVariable() {
	}

	inline int getDefaultValue() {
		return defaultValue;
	}

	String toString() {
		StringBuffer stream;
		/*stream << "variableName" << " = " << variableName.toString() << "\n";
		stream << "minValueInclusive" << " = " << minValueInclusive.toString() << "\n";
		stream << "defaultValue" << " = " << defaultValue.toString() << "\n";
		stream << "maxValueExclusive" << " = " << maxValueExclusive.toString() << "\n";*/

		stream << "{";

		stream << variableName.toString() << ", "
				<< minValueInclusive.toString() << ", "
				<< defaultValue.toString() << ", "
				<< maxValueExclusive.toString();

		stream << "}";

		return stream.toString();
	}

	bool parse(Chunk* source) {
		IffStream* iffStream = source->getIffStream();

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

			//std::cout << "parsing RICV:[" << varName.toStdString() << "]\n";

			if (varName == "variableName") {
				variableName.parse(var);
			} else if (varName == "minValueInclusive") {
				minValueInclusive.parse(var);
			} else if (varName == "defaultValue") {
				defaultValue.parse(var);
			} else if (varName == "maxValueExclusive") {
				maxValueExclusive.parse(var);
			}

			iffStream->closeChunk('XXXX');
		}

		return true;
	}

	String getVariableName() {
		return variableName.get();
	}

};


#endif /* RANGEDINTCUSTOMIZATIONVARIABLE_H_ */
