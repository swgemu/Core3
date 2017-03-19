/*
 * ColorGogglesSuiCallback.h
 *
 *  Created on: Feb 5, 2012
 *      Author: Kyle
 */

#ifndef COLORGOGGLESSUICALLBACK_H_
#define COLORGOGGLESSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"


class ColorGogglesSuiCallback : public SuiCallback {
	String nodeName;

public:
	ColorGogglesSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
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

		ManagedReference<SceneObject*> goggles = cBox->getUsingObject().get();

		if (goggles == NULL)
			return;

		ManagedReference<TangibleObject*> gogglesTano = goggles->asTangibleObject();

		if (gogglesTano != NULL) {
			Locker locker(gogglesTano, creature);

			gogglesTano->setCustomizationVariable(palette, index, true);
		}
	}
};

#endif /* AREATRACKSUICALLBACK_H_ */
