/*
 * ProfessionDataForm.h
 *
 *  Created on: Apr 22, 2011
 *      Author: crush
 */

#ifndef PROFESSIONDATAFORM_H_
#define PROFESSIONDATAFORM_H_

#include "engine/engine.h"
#include "server/zone/templates/IffTemplate.h"

class ProfessionDataForm : public IffTemplate {
	VectorMap<String, String> professionInfoPaths;

public:
	ProfessionDataForm() {

	}

	~ProfessionDataForm() {

	}

	void readObject(IffStream* iffStream) {
		iffStream->openForm('PFDT');

		uint32 version = iffStream->getNextFormType();
		Chunk* versionChunk = iffStream->openForm(version);

		switch (version) {
		case '0000':
		{
			Vector<Chunk*> chunks;
			versionChunk->getChildren(chunks);

			for (int i = 0; i < chunks.size(); ++i) {
				Chunk* data = chunks.get(i);

				String key;
				String value;

				data->readString(key);
				data->readString(value);

				professionInfoPaths.put(key, value);
			}
		}
			break;
		}

		iffStream->closeForm(version);
		iffStream->closeForm('PFDT');
	}

	inline int getTotalPaths() {
		return professionInfoPaths.size();
	}

	inline String getPathByProfessionName(const String& professionName) {
		return professionInfoPaths.get(professionName);
	}

	inline String getProfessionNameAt(int idx) {
		VectorMapEntry<String, String>* entry = &professionInfoPaths.elementAt(idx);

		return entry->getKey();
	}
};

#endif /* PROFESSIONDATAFORM_H_ */
