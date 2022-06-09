
#ifndef JEDIROBEATTIBUTELISTCOMPONENT_H_
#define JEDIROBEATTIBUTELISTCOMPONENT_H_

#include "server/zone/objects/tangible/wearables/RobeObject.h"
#include "server/zone/objects/scene/components/AttributeListComponent.h"

class JediRobeAttributeListComponent: public AttributeListComponent {
public:

	/**
	 * Fills the Attributes
	 * @pre { this object is locked }
	 * @post { this object is locked, menuResponse is complete}
	 * @param menuResponse ObjectMenuResponse that will be sent to the client
	 */
	void fillAttributeList(AttributeListMessage* alm, CreatureObject* creature, SceneObject* object) const {

		ManagedReference<RobeObject*> robe = cast<RobeObject*> (object);
		if (robe == nullptr) {
			return;
		}

		int maxCondition = robe->getMaxCondition();

		if (maxCondition > 0) {
			StringBuffer cond;
			cond << maxCondition << "/" << maxCondition;

			auto config = ConfigManager::instance();

			if (robe->isForceNoTrade()) {
				cond << config->getForceNoTradeMessage();
			}

			alm->insertAttribute("condition", cond);
		}

		int volume = robe->getVolume();

		if (volume > 0) {
			alm->insertAttribute("volume", volume);
		}

		String rankRequired = robe->getSkillRequired();

		if (!rankRequired.isEmpty() && rankRequired != "force_title_jedi_rank_02") {
			alm->insertAttribute("jedi_rank_required", "@skl_n:" + rankRequired);
		}

		const auto skills = robe->getTemplateSkillMods();

		if (skills->contains("jedi_force_power_regen")) {
			int mod = skills->get("jedi_force_power_regen");
			alm->insertAttribute("jedi_robe_regen", "+" + String::valueOf(mod));
		}

		if (skills->contains("jedi_force_power_max")) {
			int mod = skills->get("jedi_force_power_max");
			alm->insertAttribute("jedi_robe_power", "+" + String::valueOf(mod));
		}
	}
};

#endif /* JEDIROBEATTIBUTELISTCOMPONENT_H_ */
