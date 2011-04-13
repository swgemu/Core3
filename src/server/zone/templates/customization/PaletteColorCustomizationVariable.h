/*
 * PaletteColorCustomizationVariable.h
 *
 *  Created on: 01/04/2011
 *      Author: victor
 */

#ifndef PALETTECOLORCUSTOMIZATIONVARIABLE_H_
#define PALETTECOLORCUSTOMIZATIONVARIABLE_H_

#include "RangedIntCustomizationVariable.h"

class PaletteColorCustomizationVariable : public RangedIntCustomizationVariable {
	String paletteFileName;

public:
	PaletteColorCustomizationVariable(int defIndex, const String& fileName) {
		paletteFileName = fileName;
		defaultValue = defIndex;
	}

	PaletteColorCustomizationVariable(const PaletteColorCustomizationVariable& m) : RangedIntCustomizationVariable(m){
		paletteFileName = m.paletteFileName;
		defaultValue = m.defaultValue;
	}

	inline String& getPaletteFileName() {
		return paletteFileName;
	}

};

#endif /* PaletteCOLORCUSTOMIZATIONVARIABLE_H_ */
