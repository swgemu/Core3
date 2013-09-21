
#ifndef SKILLBUFFATTRIBUTELISTCOMPONENT_H_
#define SKILLBUFFATTRIBUTELISTCOMPONENT_H_

#include "server/zone/objects/tangible/skill_buff/SkillBuff.h"
#include "server/zone/objects/scene/components/AttributeListComponent.h"
#include "server/zone/objects/tangible/TangibleObject.h"

class SkillBuffObjectAttributeListComponent: public AttributeListComponent {
public:

	/**
	 * Fills the Attributes
	 * @pre { this object is locked }
	 * @post { this object is locked, menuResponse is complete}
	 * @param menuResponse ObjectMenuResponse that will be sent to the client
	 */
	void fillAttributeList(AttributeListMessage* alm, CreatureObject* creature, SceneObject* object) {

		ManagedReference<SkillBuff*> schematicData = cast<SkillBuff*> (object);
		if (schematicData == NULL) {
			return;
		}

		VectorMap<String,float>* modifiers = schematicData->getModifiers();

		for (int i = 0; i < modifiers->size(); ++i) {
			VectorMapEntry<String, float>* entry = &modifiers->elementAt(i);
			alm->insertAttribute("skill", "@stat_n:" + entry->getKey());
		}

		StringBuffer durationstring;
		int minutes = (int) floor(schematicData->getDuration() / 60.0f);
		int seconds = schematicData->getDuration() % 60;

		if (minutes > 0){
			durationstring << minutes << "m ";
		}

		durationstring << seconds << "s";

		alm->insertAttribute("duration", durationstring.toString());
	}

};

#endif /* SKILLBUFFATTRIBUTELISTCOMPONENT_H_ */
