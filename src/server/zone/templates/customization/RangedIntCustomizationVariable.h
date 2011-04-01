/*
 * RangedIntCustomizationVariable.h
 *
 *  Created on: 01/04/2011
 *      Author: victor
 */

#ifndef RANGEDINTCUSTOMIZATIONVARIABLE_H_
#define RANGEDINTCUSTOMIZATIONVARIABLE_H_

#include "CustomizationVariable.h"

class RangedIntCustomizationVariable : public CustomizationVariable {
protected:
	int defaultValue;

public:
	RangedIntCustomizationVariable() {
		defaultValue = 0;
	}

	RangedIntCustomizationVariable(const RangedIntCustomizationVariable& v) : CustomizationVariable(v) {
		defaultValue = v.defaultValue;
	}

	inline int getDefaultValue() {
		return defaultValue;
	}
};

#endif /* RANGEDINTCUSTOMIZATIONVARIABLE_H_ */
