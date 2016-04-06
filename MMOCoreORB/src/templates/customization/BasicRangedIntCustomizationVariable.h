/*
 * BasicRangedIntCustomizationVariable.h
 *
 *  Created on: 01/04/2011
 *      Author: victor
 */

#ifndef BASICRANGEDINTCUSTOMIZATIONVARIABLE_H_
#define BASICRANGEDINTCUSTOMIZATIONVARIABLE_H_

#include "templates/params/RangedIntCustomizationVariable.h"

class BasicRangedIntCustomizationVariable : public RangedIntCustomizationVariable {

public:
	BasicRangedIntCustomizationVariable(int min, int max, int def) {
		minValueInclusive = min;
		maxValueExclusive = max;
		defaultValue = def;
	}

	BasicRangedIntCustomizationVariable(const BasicRangedIntCustomizationVariable& m) : RangedIntCustomizationVariable(m){
	}

	inline int getMinValueInclusive() {
		return minValueInclusive;
	}

	inline int getMaxValueExclusive() {
		return maxValueExclusive;
	}

	inline int getDefaultValue() {
		return defaultValue;
	}
};


#endif /* BASICRANGEDINTCUSTOMIZATIONVARIABLE_H_ */
