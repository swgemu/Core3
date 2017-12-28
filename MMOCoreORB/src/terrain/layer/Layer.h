/*
 * Layer.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef LAYER_H_
#define LAYER_H_

#include <stddef.h>
#include <algorithm>

#include "../TemplateVariable.h"
#include "InformationHeader.h"
#include "system/util/Vector.h"

/*class Boundary;
class AffectorProceduralRule;
class FilterProceduralRule;*/

#include "affectors/AffectorProceduralRule.h"
#include "boundaries/Boundary.h"
#include "filters/FilterProceduralRule.h"

class AffectorProceduralRule;
class Boundary;
class FilterProceduralRule;
namespace engine {
namespace util {
class IffStream;
}  // namespace util
}  // namespace engine
namespace sys {
namespace lang {
class String;
}  // namespace lang
}  // namespace sys

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
	Layer(Layer* par = NULL) {
		parent = par;
		boundariesFlag = 0;
		filterFlag = 0;
	}

	~Layer();

	void parseFromIffStream(engine::util::IffStream* iffStream);
	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0003'>);

	IffTemplateVariable* parseAffector(IffStream* iffStream);
	IffTemplateVariable* parseBoundary(IffStream* iffStream);
	IffTemplateVariable* parseFilter(IffStream* iffStream);

	Vector<Layer*>* getChildren() {
		return &children;
	}

	Vector<Boundary*>* getBoundaries() {
		return &boundaries;
	}

	Vector<AffectorProceduralRule*>* getAffectors() {
		return &affectors;
	}

	/*Vector<AffectorProceduralRule*>* getHeightAffectors() {
		return &heightAffectors;
	}*/

	Vector<FilterProceduralRule*>* getFilters() {
		return &filters;
	}

	inline Layer* getParent() {
		return parent;
	}

	inline bool invertBoundaries() {
		return boundariesFlag != 0;
	}

	inline bool invertFilters() {
		return filterFlag != 0;
	}

	inline bool isEnabled() {
		return infoHeader.isEnabled();
	}

	inline String& getDescription() {
		return infoHeader.getDescription();
	}
};


#endif /* LAYER_H_ */
