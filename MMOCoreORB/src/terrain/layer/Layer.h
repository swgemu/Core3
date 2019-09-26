/*
 * Layer.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef LAYER_H_
#define LAYER_H_

#include "../TemplateVariable.h"
#include "InformationHeader.h"

/*class Boundary;
class AffectorProceduralRule;
class FilterProceduralRule;*/

#include "boundaries/Boundary.h"
#include "affectors/AffectorProceduralRule.h"
#include "filters/FilterProceduralRule.h"

class Layer : public TemplateVariable<'LAYR'> {
	InformationHeader infoHeader;

	Vector<Layer*> children;
	//Vector<TerrainRule*> rules;

	Vector<Boundary*> boundaries;
	Vector<AffectorProceduralRule*> affectors;
	Vector<FilterProceduralRule*> filters;

	//Vector<AffectorProceduralRule*> heightAffectors;
	//Vector<AffectorProceduralRule*> environmentAffectors;

	Layer* parent;

	int boundariesFlag;
	int filterFlag;

public:
	Layer(Layer* par = nullptr) {
		parent = par;
		boundariesFlag = 0;
		filterFlag = 0;
	}

	~Layer();

	void parseFromIffStream(engine::util::IffStream* iffStream);
	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0003'>);

	IffTemplateVariable* parseAffector(IffStream* iffStream);
	Boundary* parseBoundary(IffStream* iffStream);
	FilterProceduralRule* parseFilter(IffStream* iffStream);

	Vector<Layer*>* getChildren() {
		return &children;
	}

	Vector<Boundary*>* getBoundaries() {
		return &boundaries;
	}

	Vector<AffectorProceduralRule*>* getAffectors() {
		return &affectors;
	}

	Vector<FilterProceduralRule*>* getFilters() {
		return &filters;
	}

	const Vector<Layer*>* getChildren() const {
		return &children;
	}

	const Vector<Boundary*>* getBoundaries() const {
		return &boundaries;
	}

	const Vector<AffectorProceduralRule*>* getAffectors() const {
		return &affectors;
	}

	const Vector<FilterProceduralRule*>* getFilters() const {
		return &filters;
	}

	inline Layer* getParent() {
		return parent;
	}

	inline const Layer* getParent() const {
		return parent;
	}

	inline bool invertBoundaries() const {
		return boundariesFlag != 0;
	}

	inline bool invertFilters() const {
		return filterFlag != 0;
	}

	inline bool isEnabled() const {
		return infoHeader.isEnabled();
	}

	inline const String& getDescription() const {
		return infoHeader.getDescription();
	}
};


#endif /* LAYER_H_ */
