/*
 * ForceShrineMenuComponent.h
 *
 *  Created on: 01/23/2012
 *      Author: xyborn
 */

#ifndef FORCESHRINEMENUCOMPONENT_H_
#define FORCESHRINEMENUCOMPONENT_H_

#include "TangibleObjectMenuComponent.h"

namespace server {
namespace zone {
namespace objects {
namespace scene {
	class SceneObject;
}
}
}
}

using namespace server::zone::objects::scene;

namespace server {
namespace zone {
namespace objects {
namespace creature {
	class CreatureObject;
}
}
}
}

using namespace server::zone::objects::creature;

class ForceShrineMenuComponent : public TangibleObjectMenuComponent {
public:
	enum {
		PADAWAN_TRIAL_ARCHITECT,
		PADAWAN_TRIAL_ARTIST,
		PADAWAN_TRIAL_BADCAT,
		PADAWAN_TRIAL_CHEF,
		PADAWAN_TRIAL_OLD_MUSICIAN,
		PADAWAN_TRIAL_PANNAQA,
		PADAWAN_TRIAL_PEOPLES_SOLDIER,
		PADAWAN_TRIAL_SOB_STORY,
		PADAWAN_TRIAL_SPICE_MOM,
		PADAWAN_TRIAL_SURVEYOR,
		PADAWAN_TRIAL_POLITICIAN,
		PADAWAN_TRIAL_THE_RING,
		PADAWAN_TRIAL_BAZ_NITCH,
		PADAWAN_TRIAL_SLUDGE_PANTHER,
		PADAWAN_TRIAL_FALUMPASET,
		PADAWAN_TRIAL_CRAFT_LIGHTSABER
	};

	const static int PADAWAN_TRIALS_TOTAL = 16;

	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID);

	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player);

};


#endif /* FORCESHRINEMENUCOMPONENT_H_ */
