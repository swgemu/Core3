/*
 * RangedIntCustomizationVariables.h
 *
 *  Created on: 16-abr-2009
 *      Author: TheAnswer
 */

#ifndef RANGEDINTCUSTOMIZATIONVARIABLES_H_
#define RANGEDINTCUSTOMIZATIONVARIABLES_H_

#include <algorithm>

#include "engine/util/iffstream/IffStream.h"
#include "system/lang/String.h"
#include "system/util/Vector.h"
#include "templates/params/Param.h"
#include "templates/params/RangedIntCustomizationVariable.h"

namespace engine {
namespace util {
class Chunk;
class IffStream;
}  // namespace util
}  // namespace engine

class RangedIntCustomizationVariables : public Param {
protected:
	//QMap<QString, PaletteColorCustomizationVariable*> variables;
	Vector<RangedIntCustomizationVariable*> variables;


public:
	RangedIntCustomizationVariables() : Param() {
	}

	~RangedIntCustomizationVariables() {
		/*QMap<QString, PaletteColorCustomizationVariable*>::const_iterator i;

		for (i = variables.constBegin(); i != variables.constEnd(); ++i)
			delete i.value();*/

		for (int i = 0; i < variables.size(); ++i)
			delete variables.get(i);

		//std::cout << "DELETING RangedIntCustomizationVariables\n";
	}

	String toString();

	void toString(String& str) {
		//std::cout << "entering void toString(QString& str)\n";
		//str = test;
	}

	bool parse(Chunk* source);

	void parseType1(IffStream* source);
};

#endif /* RANGEDINTCUSTOMIZATIONVARIABLES_H_ */
