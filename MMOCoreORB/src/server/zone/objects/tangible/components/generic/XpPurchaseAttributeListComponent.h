#ifndef XPPURCHASEATTIBUTELISTCOMPONENT_H_
#define XPPURCHASEATTIBUTELISTCOMPONENT_H_

#include "templates/tangible/XpPurchaseTemplate.h"
#include "server/zone/managers/stringid/StringIdManager.h"

class XpPurchaseAttributeListComponent: public AttributeListComponent {
public:

	/**
	 * Fills the Attributes
	 * @pre { this object is locked }
	 * @post { this object is locked, menuResponse is complete}
	 * @param menuResponse ObjectMenuResponse that will be sent to the client
	 */
	void fillAttributeList(AttributeListMessage* alm, CreatureObject* creature, SceneObject* object) const {

		XpPurchaseTemplate* templateData = cast<XpPurchaseTemplate*> (object->getObjectTemplate());
		if (templateData == NULL) {
			return;
		}

		StringIdManager* stringIdManager = StringIdManager::instance();

		int xpAmount = templateData->getXpAmount();

		if (xpAmount > 0) {
			String xpTypeNeeded = "@exp_n:" + templateData->getXpType();
			UnicodeString xpType = String::valueOf(xpAmount) + " " + stringIdManager->getStringId(xpTypeNeeded.hashCode());
			alm->insertAttribute("experience_required", xpType);
		}

		String skillNeeded = templateData->getRequiredSkill();

		if (skillNeeded != "") {
			skillNeeded = "@skl_n:" + skillNeeded;
			UnicodeString skill = stringIdManager->getStringId(skillNeeded.hashCode());
			alm->insertAttribute("skill_required", skillNeeded);
		}

	}

};

#endif /* XPPURCHASEATTIBUTELISTCOMPONENT_H_ */
