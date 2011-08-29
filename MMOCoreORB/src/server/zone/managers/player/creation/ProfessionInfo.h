/*
 * SkillInfo.h
 *
 *  Created on: Apr 21, 2011
 *      Author: crush
 */

#ifndef PROFESSIONINFO_H_
#define PROFESSIONINFO_H_

#include "engine/engine.h"
#include "server/zone/templates/IffTemplate.h"

namespace server {
namespace zone {
namespace managers {
namespace player {
namespace creation {

class SkillInfo : public IffTemplate {
	Vector<String> skills;
	VectorMap<String, SortedVector<String> > items;
	Vector<int> attributeMods;

	void addItem(const String& templateName, const String& itemName) {
		if (items.contains(templateName)) {
			SortedVector<String>* itemList = &items.get(templateName);
			itemList->put(itemName);
		} else {
			SortedVector<String> itemList;
			itemList.setNoDuplicateInsertPlan();
			itemList.put(itemName);
			items.put(templateName, itemList);
		}
	}

public:
	SkillInfo() {
		items.setNoDuplicateInsertPlan();

		//initialize values for each attribute
		attributeMods.add(0);
		attributeMods.add(0);
		attributeMods.add(0);
		attributeMods.add(0);
		attributeMods.add(0);
		attributeMods.add(0);
		attributeMods.add(0);
		attributeMods.add(0);
		attributeMods.add(0);
	}

	SkillInfo(const SkillInfo& pi) : Object(), TemplateData(), IffTemplate() {
		skills = pi.skills;
		items = pi.items;
		attributeMods = pi.attributeMods;
	}

	SkillInfo& operator= (const SkillInfo& pi) {
		if (this == &pi)
			return *this;

		skills = pi.skills;
		items = pi.items;
		attributeMods = pi.attributeMods;

		return *this;
	}

	inline void setAttributeMod(int idx, int value) {
		attributeMods.set(idx, value);
	}

	inline int getAttributeMod(int idx) {
		return attributeMods.get(idx);
	}

	void readObject(IffStream* iffStream) {
		iffStream->openForm('PRFI');

		uint32 version = iffStream->getNextFormType();
		Chunk* versionForm = iffStream->openForm(version);

		int totalSubForms = versionForm->getChunksSize();

		switch (version) {
		case '0000':
		{
			Chunk* skls = iffStream->openForm('SKLS');
			Vector<Chunk*> chunks;
			skls->getChildren(chunks);

			for (int i = 0; i < chunks.size(); ++i) {
				Chunk* skil = chunks.get(i);

				String skillName;
				skil->readString(skillName);

				skills.add(skillName);
			}

			iffStream->closeForm('SKLS');

			for (int i = 1; i < totalSubForms; ++i) {
				Chunk* ptmpForm = iffStream->openForm('PTMP');

				chunks.removeAll();
				ptmpForm->getChildren(chunks);

				Chunk* nameChunk = iffStream->openChunk('NAME');
				String templateName;
				nameChunk->readString(templateName);

				iffStream->closeChunk('NAME');

				for (int j = 1; j < chunks.size(); ++j) {
					String itemName;

					Chunk* chunk = chunks.get(j);
					chunk->readString(itemName);

					addItem(templateName, itemName);
				}

				iffStream->closeForm('PTMP');
			}


		}
		break;
		}

		iffStream->closeForm(version);
		iffStream->closeForm('PRFI');
	}
};

}
}
}
}
}

using namespace server::zone::managers::player::creation;

#endif /* PROFESSIONINFO_H_ */
