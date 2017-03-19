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


class ColorWithKitSuiCallback : public SuiCallback {
	TangibleObject* customizationKit;

public:
	ColorWithKitSuiCallback(ZoneServer* serv, TangibleObject* kitTano ):
		SuiCallback(serv), customizationKit( kitTano ) {
	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		SuiColorBox* cBox = cast<SuiColorBox*>( sui);

		if (cBox == NULL)
			return;

		if(!creature->isPlayerCreature())
			return;

		if(!cancelPressed) {

			int index = Integer::valueOf(args->get(0).toString());

			String palette = cBox->getColorPalette();

			ManagedReference<TangibleObject*> target = cBox->getUsingObject().get().castTo<TangibleObject*>();

			if (target == NULL)
				return;

			Locker clocker(target, creature);

			target->setCustomizationVariable(palette, index, true);

			clocker.release();

			if (customizationKit != NULL) {
				Locker clocker2(customizationKit, creature);
				customizationKit->decreaseUseCount();
			}
		}
	}
};

#endif /* COLORWITHKITSUICALLBACK_H */
