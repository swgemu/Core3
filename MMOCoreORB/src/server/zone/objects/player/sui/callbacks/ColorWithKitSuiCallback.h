/*
 * ColorWithKitSuiCallback.h
 *
 *  Created on: 1/20/215
 *      Author: Nick Rafalski
 *		Credits: TA & Valk
 */

#ifndef COLORWITHKITSUICALLBACK_H
#define COLORWITHKITSUICALLBACK_H

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/objects/creature/VehicleObject.h"


class ColorWithKitSuiCallback : public SuiCallback {
	TangibleObject* customizationKit;

public:
	ColorWithKitSuiCallback(ZoneServer* serv, TangibleObject* kitTano ):
		SuiCallback(serv), customizationKit( kitTano ) {
	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		SuiColorBox* cBox = cast<SuiColorBox*>( sui);

		if (cBox == nullptr)
			return;

		if(!creature->isPlayerCreature())
			return;

		if(!cancelPressed) {

			int index = Integer::valueOf(args->get(0).toString());

			String palette = cBox->getColorPalette();

			ManagedReference<TangibleObject*> target = cBox->getUsingObject().get().castTo<TangibleObject*>();

			if (target == nullptr)
				return;

			Locker clocker(target, creature);

			target->setCustomizationVariable(palette, index, true);

			if (target->isDroidObject()) {
				DroidObject* droid = cast<DroidObject*>(target.get());
				if (droid != nullptr)
					droid->refreshPaint();
			} else if (target->isVehicleObject()) {
				VehicleObject* painted = cast<VehicleObject*>(target.get());
				if (painted != nullptr)
					painted->refreshPaint();
			}

			clocker.release();

			if (customizationKit != nullptr) {
				Locker clocker2(customizationKit, creature);
				customizationKit->decreaseUseCount();
			}
		}
	}
};

#endif /* COLORWITHKITSUICALLBACK_H */
