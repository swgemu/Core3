/*
 * CustomizationIdManager.h
 *
 *  Created on: 28/03/2012
 *      Author: victor
 */

#ifndef CUSTOMIZATIONIDMANAGER_H_
#define CUSTOMIZATIONIDMANAGER_H_

#include "engine/engine.h"

class CustomizationIdManager : public Object, public Logger, public Singleton<CustomizationIdManager> {
	HashTable<String, int> customizationIds;
public:
	CustomizationIdManager() {
		setLoggingName("CustomizationIdManager");
	}


	void readObject(IffStream* iffStream) {
		iffStream->openForm('CIDM');
		iffStream->openForm('0001');

		Chunk* data = iffStream->openChunk('DATA');

		while (data->hasData()) {
			int id = data->readShort();
			String var;
			data->readString(var);

			customizationIds.put(var, id);
		}

		iffStream->closeChunk('DATA');

		iffStream->closeForm('0001');
		iffStream->closeForm('CIDM');

		info("loaded " + String::valueOf(customizationIds.size()) + " customization ids", true);
	}

	int getCustomizationId(const String& var) {
		return customizationIds.get(var);
	}
};


#endif /* CUSTOMIZATIONIDMANAGER_H_ */
