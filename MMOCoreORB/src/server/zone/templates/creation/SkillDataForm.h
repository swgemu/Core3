/*
 * SkillDataForm.h
 *
 *  Created on: Apr 22, 2011
 *      Author: crush
 */

#ifndef SKILLDATAFORM_H_
#define SKILLDATAFORM_H_

#include "engine/engine.h"
#include "server/zone/templates/IffTemplate.h"

class SkillDataForm : public IffTemplate {
	VectorMap<String, String> professionInfoPaths;

public:
	SkillDataForm() {

	}

	~SkillDataForm() {

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

	inline String getPathBySkillName(const String& professionName) {
		return professionInfoPaths.get(professionName);
	}

	inline String getSkillNameAt(int idx) {
		VectorMapEntry<String, String>* entry = &professionInfoPaths.elementAt(idx);

		return entry->getKey();
	}
};

#endif /* SKILLDATAFORM_H_ */
