/*
 * AffectorProceduralRule.h
 *
 *  Created on: 21/12/2010
 *      Author: victor
 */

#ifndef AFFECTORPROCEDURALRULE_H_
#define AFFECTORPROCEDURALRULE_H_

class TerrainGenerator;

class AffectorProceduralRule {
protected:
	int affectorType;

public:
	AffectorProceduralRule() : affectorType(0) {
	}

	const static int HEIGHTTYPE = 0x100;
	const static int HEIGHTFRACTAL = 0x101;
	const static int HEIGHTTERRACE = 0x102;
	const static int HEIGHTCONSTANT = 0x103;
	const static int ENVIRONMENT = 0x200;

	virtual ~AffectorProceduralRule() {

	}

	virtual void process(float x, float y, float transformValue, float& baseValue, TerrainGenerator* terrainGenerator) {

	}

	inline bool isHeightTypeAffector() {
		return affectorType & HEIGHTTYPE;
	}

	inline bool isEnvoronmentTypeAffector() {
		return affectorType & ENVIRONMENT;
	}

	inline int getAffectorType() {
		return affectorType;
	}

	virtual bool isEnabled() {
		return false;
	}

};

#endif /* AFFECTORPROCEDURALRULE_H_ */
