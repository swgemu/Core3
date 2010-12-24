/*
 * ProceduralRule.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef PROCEDURALRULE_H_
#define PROCEDURALRULE_H_

#include "engine/engine.h"

#include "../TemplateVariable.h"
#include "InformationHeader.h"

#include "TerrainRule.h"

template<int formType>
class ProceduralRule : public TemplateVariable<formType> {

protected:
	InformationHeader informationHeader;

public:
	ProceduralRule() {

	}

	inline bool isEnabled() {
		return informationHeader.isEnabled();
	}

};

#endif /* PROCEDURALRULE_H_ */
