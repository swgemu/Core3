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

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {

		SuiColorBox* cBox = cast<SuiColorBox*>( sui);

		if(!creature->isPlayerCreature())
			return;

		if(!cancelPressed) {

			int index = Integer::valueOf(args->get(0).toString());

			String palette = cBox->getColorPalette();

			ManagedReference<SceneObject*> target = cBox->getUsingObject();

			ManagedReference<TangibleObject*> targetTano = cast<TangibleObject*>(target.get());

			if (targetTano != NULL) {
				Locker clocker(targetTano, creature);

				targetTano->setCustomizationVariable(palette, index, true);
			}

			if(customizationKit != NULL){
				Locker clocker(customizationKit, creature);
				customizationKit->decreaseUseCount();
			}
		}
	}
};

#endif /* COLORWITHKITSUICALLBACK_H */
