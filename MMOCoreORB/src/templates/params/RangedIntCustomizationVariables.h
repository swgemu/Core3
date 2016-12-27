/*
 * RangedIntCustomizationVariables.h
 *
 *  Created on: 16-abr-2009
 *      Author: TheAnswer
 */

#ifndef RANGEDINTCUSTOMIZATIONVARIABLES_H_
#define RANGEDINTCUSTOMIZATIONVARIABLES_H_

#include "engine/util/iffstream/IffStream.h"
#include "templates/params/RangedIntCustomizationVariable.h"

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
