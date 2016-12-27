/*
 * PaletteColorCustomizationVariables.h
 *
 *  Created on: 23-feb-2009
 *      Author: TheAnswer
 */

#ifndef PALETTECOLORCUSTOMIZATIONVARIABLES_H_
#define PALETTECOLORCUSTOMIZATIONVARIABLES_H_

#include "templates/params/PaletteColorCustomizationVariable.h"
#include "templates/params/Param.h"

class PaletteColorCustomizationVariables : public Param {
protected:
	//QMap<QString, PaletteColorCustomizationVariable*> variables;
	Vector<PaletteColorCustomizationVariable*> variables;

public:
	PaletteColorCustomizationVariables() : Param() {
	}

	PaletteColorCustomizationVariables(const PaletteColorCustomizationVariables& p) : Param() {
		variables = p.variables;
	}

	~PaletteColorCustomizationVariables() {
		/*QMap<QString, PaletteColorCustomizationVariable*>::const_iterator i;

		for (i = variables.constBegin(); i != variables.constEnd(); ++i)
			delete i.value();*/

		for (int i = 0; i < variables.size(); ++i)
			delete variables.get(i);

		//std::cout << "DELETING PaletteColorCustomizationVariables\n";
	}

	String toString();

	void toString(String& str) {
		//std::cout << "entering void toString(QString& str)\n";
		//str = test;
	}

	bool parse(Chunk* source);

	void parseType1(IffStream* source);
};

#endif /* PALETTECOLORCUSTOMIZATIONVARIABLES_H_ */
