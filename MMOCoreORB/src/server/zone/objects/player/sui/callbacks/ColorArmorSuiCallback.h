/*
 * ColorArmorSuiCallback.h
 *
 *  Created on: 2/4/2013
 *      Author: bluree
 *		Credits: TA & Valk
 */

#ifndef COLORARMORSUICALLBACK_H_
#define COLORARMORSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"


class ColorArmorSuiCallback : public SuiCallback {
public:
	ColorArmorSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {

		SuiColorBox* cBox = cast<SuiColorBox*>( sui);

		if(!creature->isPlayerCreature())
			return;

		if(!cancelPressed) {

			int index = Integer::valueOf(args->get(0).toString());

			String palette = cBox->getColorPalette();

			ManagedReference<SceneObject*> armorRehue = cBox->getUsingObject();

			ManagedReference<TangibleObject*> armorRehueTano = cast<TangibleObject*>(armorRehue.get());

			if (armorRehueTano != NULL) {
				Locker locker(armorRehueTano, creature);

				armorRehueTano->setCustomizationVariable(palette, index, true);
			}

		}
	}
};

#endif /* COLORARMORSUICALLBACK_H_ */
