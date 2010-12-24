/*
 * TerrainRule.h
 *
 *  Created on: 01/02/2010
 *      Author: victor
 */

#ifndef TERRAINRULE_H_
#define TERRAINRULE_H_


#include "engine/engine.h"

#include "../TemplateVariable.h"
#include "InformationHeader.h"

class ProceduralTerrainAppearance;

/*
class TerrainRule : public virtual IffTemplateVariable {
protected:
	int ruleType;

public:
	const static int AFFECTOR = 0x00000100;

	const static int BOUNDARY = 0x00001000;
	const static int BOUNDARYCIRCLE = 0x00001001;
	const static int BOUNDARYPOLYGON = 0x00001002;
	const static int BOUNDARYPOLYLINE = 0x00001003;
	const static int BOUNDARYRECTANGLE = 0x00001004;


	const static int FILTER =   0x00010000;

public:
	TerrainRule() {
		ruleType = 0;
	}

	virtual void executeRule(ProceduralTerrainAppearance* generator) {

	}

	inline bool isBoundary() {
		return ruleType & BOUNDARY;
	}

	inline bool isBoundaryCircle() {
		return ruleType == BOUNDARYCIRCLE;
	}

	inline bool isBoundaryPolygon() {
		return ruleType == BOUNDARYPOLYGON;
	}

	inline bool isBoundaryPolyline() {
		return ruleType == BOUNDARYPOLYLINE;
	}

	inline bool isBoundaryRectangle() {
		return ruleType == BOUNDARYRECTANGLE;
	}

};

*/

#endif /* TERRAINRULE_H_ */
