
#ifndef HERORINGATTIBUTELISTCOMPONENT_H_
#define HERORINGATTIBUTELISTCOMPONENT_H_

#include "server/zone/objects/scene/components/AttributeListComponent.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/tangible/components/HeroRingDataComponent.h"

class HeroRingAttributeListComponent: public AttributeListComponent {
public:

	/**
	 * Fills the Attributes
	 * @pre { this object is locked }
	 * @post { this object is locked, menuResponse is complete}
	 * @param menuResponse ObjectMenuResponse that will be sent to the client
	 */
	void fillAttributeList(AttributeListMessage* alm, CreatureObject* creature, SceneObject* object) {

		ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(object);

		HeroRingDataComponent* data = cast<HeroRingDataComponent*>(tano->getDataObjectComponent()->get());

		if (data == NULL || !data->isHeroRingData())
			return;

		int charges = data->getCharges();

		alm->insertAttribute("effect", "@quest/hero_of_tatooine/system_messages:restore");
		alm->insertAttribute("charges", charges);

		if (!creature->checkCooldownRecovery("mark_of_hero")) {
			Time* timeRemaining = creature->getCooldownTime("mark_of_hero");
			alm->insertAttribute("time_remaining", getCooldownString(timeRemaining->miliDifference() * -1));
		}
	}

	String getCooldownString(uint32 delta) {

		int seconds = delta / 1000;

		int hours = seconds / 3600;
		seconds -= hours * 3600;

		int minutes = seconds / 60;
		seconds -= minutes * 60;

		StringBuffer buffer;

		if (hours > 0)
			buffer << hours << "h ";

		if (minutes > 0)
			buffer << minutes << "m ";

		if (seconds > 0)
			buffer << seconds << "s";

		return buffer.toString();
	}

};

#endif /* HERORINGATTIBUTELISTCOMPONENT_H_ */
