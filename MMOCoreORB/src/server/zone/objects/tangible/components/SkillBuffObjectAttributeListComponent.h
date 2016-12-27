/*
 * SkillBuffObjectAttributeListComponent.h
 *
 *  Created on: 9/21/2013
 *      Author: Klivian
 */

#ifndef SKILLBUFFATTRIBUTELISTCOMPONENT_H_
#define SKILLBUFFATTRIBUTELISTCOMPONENT_H_

#include "templates/tangible/SkillBuffTemplate.h"
#include "server/zone/objects/scene/components/AttributeListComponent.h"

class SkillBuffObjectAttributeListComponent: public AttributeListComponent {
public:

	/**
	 * Fills the Attributes
	 * @pre { this object is locked }
	 * @post { this object is locked, menuResponse is complete}
	 * @param menuResponse ObjectMenuResponse that will be sent to the client
	 */
	void fillAttributeList(AttributeListMessage* alm, CreatureObject* creature, SceneObject* object) const {

		ManagedReference<SkillBuffTemplate*> skillBuff = cast<SkillBuffTemplate*>(object->getObjectTemplate());
		if (skillBuff == NULL) {
			error("No SkillBuffTemplate for: " + String::valueOf(object->getServerObjectCRC()));
			return;
		}

		if(!object->isTangibleObject())
			return;

		// Already handled in tano.
		AttributeListComponent::fillAttributeList(alm, creature, object);

		/*ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(object);
		if(tano->getUseCount() > 1)
			alm->insertAttribute("quantity", tano->getUseCount());*/

		VectorMap<String,float>* modifiers = skillBuff->getModifiers();

		for (int i = 0; i < modifiers->size(); ++i) {
			VectorMapEntry<String, float>* entry = &modifiers->elementAt(i);
			alm->insertAttribute("cat_skill_mod_bonus.@stat_n:" + entry->getKey(), (int)entry->getValue() );
		}

		StringBuffer durationstring;
		int minutes = (int) floor(skillBuff->getDuration() / 60.0f);
		int seconds = skillBuff->getDuration() % 60;

		if (minutes > 0){
			durationstring << minutes << "m ";
		}

		durationstring << seconds << "s";

		alm->insertAttribute("duration", durationstring.toString());
	}

};

#endif /* SKILLBUFFATTRIBUTELISTCOMPONENT_H_ */
