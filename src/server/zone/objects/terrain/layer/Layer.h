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
#include "TerrainRule.h"

class Layer : public TemplateVariable<'LAYR'> {
	InformationHeader infoHeader;

	Vector<Layer*> children;
	Vector<TerrainRule*> rules;

	Layer* parent;
	/*Vector<Boundary*> boundaries;
	Vector<Affector*> affectors;
	Vector<Rule*> filters;*/

public:
	Layer(Layer* par = NULL) {
		parent = par;
	}

	~Layer() {
		while (children.size() > 0) {
			delete children.remove(0);
		}

		while (rules.size() > 0) {
			delete rules.remove(0);
		}
	}

	void parseFromIffStream(engine::util::IffStream* iffStream);
	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0003'>);

	TerrainRule* parseAffector(IffStream* iffStream);
	TerrainRule* parseBoundary(IffStream* iffStream);
	TerrainRule* parseFilter(IffStream* iffStream);

	Vector<Layer*>* getChildren() {
		return &children;
	}

	Vector<TerrainRule*>* getRules() {
		return &rules;
	}
};


#endif /* LAYER_H_ */
