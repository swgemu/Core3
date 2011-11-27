/*
 * ProfessionDefaultsInfo.h
 *
 *  Created on: Aug 26, 2011
 *      Author: crush
 */

#ifndef PROFESSIONDEFAULTSINFO_H_
#define PROFESSIONDEFAULTSINFO_H_

#include "engine/engine.h"
#include "server/zone/objects/creature/variables/Skill.h"
#include "server/zone/managers/skill/SkillManager.h"

namespace server {
namespace zone {
namespace managers {
namespace player {
namespace creation {

class ProfessionDefaultsInfo : public Object {
	Reference<Skill*> skill;
	VectorMap<String, SortedVector<String> > professionItems;
	VectorMap<uint8, int> professionMods;
	Vector<String> startingItems;

public:
	ProfessionDefaultsInfo() : Object() {
		skill = NULL;

		professionItems.setNoDuplicateInsertPlan();
		professionMods.setNoDuplicateInsertPlan();
	}

	void readObject(IffStream* iffStream) {
		iffStream->openForm('PRFI');

		uint32 version = iffStream->getNextFormType();
		Chunk* chunk = iffStream->openForm(version);
		switch (version) {
		case '0000':
		{
			String skillName;
			iffStream->openForm('SKLS');
			Chunk* skil = iffStream->openChunk('SKIL');
			skil->readString(skillName);
			iffStream->closeChunk('SKIL');
			iffStream->closeForm('SKLS');

			SkillManager* skillManager = SkillManager::instance();
			skill = skillManager->getSkill(skillName);

			//Load the individual clothing templates.
			for (int i = 1; i < chunk->getChunksSize(); ++i) {
				Chunk* chunkPTMP = iffStream->openForm('PTMP');
				Chunk* chunkName = iffStream->openChunk('NAME');
				String ptmpName;
				chunkName->readString(ptmpName);
				iffStream->closeChunk('NAME');

				SortedVector<String> items;

				for (int j = 1; j < chunkPTMP->getChunksSize() - 1; ++j) {
					Chunk* chunkItem = iffStream->openChunk('ITEM');
					int unk1 = chunkItem->readInt();
					String itemTemplate;
					chunkItem->readString(itemTemplate);
					itemTemplate = itemTemplate.replaceFirst("shared_", "");
					iffStream->closeChunk('ITEM');
					items.put(itemTemplate);
				}

				professionItems.put(ptmpName, items);
				iffStream->closeChunk('PTMP');
			}
		}
			break;
		}

		iffStream->closeForm(version);
		iffStream->closeForm('PRFI');
	}

	void setAttributeMod(uint8 idx, int value) {
		professionMods.put(idx, value);
	}

	SortedVector<String>* getProfessionItems(const String& clientTemplate) {
		if (!professionItems.contains(clientTemplate))
			return NULL;

		return &professionItems.get(clientTemplate);
	}

	Skill* getSkill() {
		return skill;
	}

	int getAttributeMod(uint8 idx) {
		return professionMods.get(idx);
	}

	inline Vector<String>* getStartingItems() {
		return &startingItems;
	}
};

}
}
}
}
}

using namespace server::zone::managers::player::creation;


#endif /* PROFESSIONDEFAULTSINFO_H_ */
