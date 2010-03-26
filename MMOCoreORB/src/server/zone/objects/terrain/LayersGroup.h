/*
 * Layers.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef LAYERS_H_
#define LAYERS_H_

#include "TemplateVariable.h"
#include "layer/Layer.h"

class LayersGroup : public TemplateVariable<'LYRS'> {
	Vector<Layer*> layers;
public:

	LayersGroup() {

	}

	~LayersGroup() {
		for (int i = 0; i < layers.size(); ++i)
			delete layers.get(i);

		layers.removeAll();
	}

	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		parseFromIffStream(iffStream, Version<'0000'>());
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0000'>) {
		int number = iffStream->getSubChunksNumber();

		for (int i = 0; i < number; ++i) {
			Layer* layer = new Layer();
			layer->readObject(iffStream);

			layers.add(layer);
		}
	}

	Vector<Layer*>* getLayers() {
		return &layers;
	}
};

#endif /* LAYERS_H_ */
