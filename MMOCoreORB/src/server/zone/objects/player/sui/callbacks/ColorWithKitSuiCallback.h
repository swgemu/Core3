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
	void (*onUseHook) (ManagedReference<TangibleObject*>);
public:
	ColorWithKitSuiCallback(ZoneServer* serv, TangibleObject* kitTano ):
		SuiCallback(serv), customizationKit( kitTano ), onUseHook(nullptr) {
	}

	ColorWithKitSuiCallback(ZoneServer* serv, TangibleObject* kitTano, void (*onUseHook) (ManagedReference<TangibleObject*>)):
		SuiCallback(serv), customizationKit( kitTano ), onUseHook(onUseHook) {
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

			// done with main work - now we are running the onUseHook
			if (onUseHook != nullptr)
				onUseHook(target);

			clocker.release();

			if (customizationKit != nullptr) {
				Locker clocker2(customizationKit, creature);
				customizationKit->decreaseUseCount();
			}
		}
	}
};

#endif /* COLORWITHKITSUICALLBACK_H */
