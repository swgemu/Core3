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

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {

		SuiColorBox* cBox = cast<SuiColorBox*>( sui);

		if(!creature->isPlayerCreature())
			return;

		if(!cancelPressed) {

			int index = Integer::valueOf(args->get(0).toString());

			String palette = cBox->getColorPalette();

			ManagedReference<SceneObject*> goggles = cBox->getUsingObject();

			ManagedReference<TangibleObject*> gogglesTano = cast<TangibleObject*>(goggles.get());

			if (gogglesTano != NULL) {
				Locker locker(gogglesTano, creature);

				gogglesTano->setCustomizationVariable(palette, index, true);
			}


		}
	}
};

#endif /* AREATRACKSUICALLBACK_H_ */
