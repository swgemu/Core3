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

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!sui->isColorPicker() || cancelPressed)
			return;

		if (!creature->isPlayerCreature())
			return;

		SuiColorBox* cBox = cast<SuiColorBox*>(sui);

		int index = Integer::valueOf(args->get(0).toString());

		String palette = cBox->getColorPalette();

		ManagedReference<SceneObject*> armorRehue = cBox->getUsingObject().get();

		if (armorRehue == NULL)
			return;

		ManagedReference<TangibleObject*> armorRehueTano = armorRehue->asTangibleObject();

		if (armorRehueTano != NULL) {
			Locker locker(armorRehueTano, creature);

			armorRehueTano->setCustomizationVariable(palette, index, true);
		}
	}
};

#endif /* COLORARMORSUICALLBACK_H_ */
