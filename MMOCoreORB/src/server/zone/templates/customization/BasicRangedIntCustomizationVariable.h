/*
 * BasicRangedIntCustomizationVariable.h
 *
 *  Created on: 01/04/2011
 *      Author: victor
 */

#ifndef BASICRANGEDINTCUSTOMIZATIONVARIABLE_H_
#define BASICRANGEDINTCUSTOMIZATIONVARIABLE_H_

#include "../params/RangedIntCustomizationVariable.h"

class BasicRangedIntCustomizationVariable : public RangedIntCustomizationVariable {
	int minValueInclusive;
	int maxValueExclusive;

public:
	BasicRangedIntCustomizationVariable(int min, int max, int def) {
		minValueInclusive = min;
		maxValueExclusive = max;
		defaultValue = def;
	}

	BasicRangedIntCustomizationVariable(const BasicRangedIntCustomizationVariable& m) : RangedIntCustomizationVariable(m){
		minValueInclusive = m.minValueInclusive;
		maxValueExclusive = m.maxValueExclusive;
		defaultValue = m.defaultValue;
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
