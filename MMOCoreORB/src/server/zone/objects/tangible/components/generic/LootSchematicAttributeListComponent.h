/*
 * LootSchematicAttributeListComponent.h
 *
 *  Created on: 1/29/2012
 *      Author: kyle
 */

#ifndef LOOTSCHEMATICATTIBUTELISTCOMPONENT_H_
#define LOOTSCHEMATICATTIBUTELISTCOMPONENT_H_

#include "templates/tangible/LootSchematicTemplate.h"
#include "server/zone/managers/stringid/StringIdManager.h"

class LootSchematicAttributeListComponent: public AttributeListComponent {
public:

	/**
	 * Fills the Attributes
	 * @pre { this object is locked }
	 * @post { this object is locked, menuResponse is complete}
	 * @param menuResponse ObjectMenuResponse that will be sent to the client
	 */
	void fillAttributeList(AttributeListMessage* alm, CreatureObject* creature, SceneObject* object) const {

		LootSchematicTemplate* schematicData = cast<LootSchematicTemplate*> (object->getObjectTemplate());
		if (schematicData == NULL) {
			return;
		}

		String skillNeeded = "@skl_n:" + schematicData->getRequiredSkill();
		StringIdManager* stringIdManager = StringIdManager::instance();

		UnicodeString skill = stringIdManager->getStringId(skillNeeded.hashCode());

		if(!skill.isEmpty())
			alm->insertAttribute("skill_required", skill);
	}

};

#endif /* ATTIBUTELISTCOMPONENT_H_ */
