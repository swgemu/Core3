
#ifndef ROBEOBJECTATTIBUTELISTCOMPONENT_H_
#define ROBEOBJECTATTIBUTELISTCOMPONENT_H_

#include "server/zone/objects/tangible/wearables/RobeObject.h"
#include "server/zone/objects/scene/components/AttributeListComponent.h"
#include "server/zone/objects/tangible/TangibleObject.h"

class RobeObjectAttributeListComponent: public AttributeListComponent {
public:

	/**
	 * Fills the Attributes
	 * @pre { this object is locked }
	 * @post { this object is locked, menuResponse is complete}
	 * @param menuResponse ObjectMenuResponse that will be sent to the client
	 */
	void fillAttributeList(AttributeListMessage* alm, CreatureObject* creature, SceneObject* object) {

		ManagedReference<RobeObject*> schematicData = cast<RobeObject*> (object);
		if (schematicData == NULL) {
			return;
		}

		String rankRequired = schematicData->getSkillRequired();

		if (!rankRequired.isEmpty()){

		alm->insertAttribute("jedi_robe_power", "+250");

		alm->insertAttribute("jedi_robe_regen", "+10");
		}

		if(!rankRequired.isEmpty() && rankRequired != "force_title_jedi_rank_02")
			alm->insertAttribute("jedi_rank_required", "@skl_n:" + rankRequired);
	}

};

#endif /* ATTIBUTELISTCOMPONENT_H_ */
