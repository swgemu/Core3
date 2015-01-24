/*
 * CustomDroidSuiCallback.h
 *
 *  Created on: 11/29/2013
 *      Author: Klivian
 */

#ifndef CUSTOMDROIDSUICALLBACK_H_
#define CUSTOMDROIDSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/colorbox/SuiColorBox.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/ColorWithKitSuiCallback.h"



class CustomDroidSuiCallback : public SuiCallback {
	int numPalette;
	TangibleObject* customizationKit;

public:
	CustomDroidSuiCallback( ZoneServer* serv, int palette, TangibleObject* kitTano ) :
		SuiCallback(serv), numPalette(palette), customizationKit(kitTano) {
	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!sui->isListBox() || cancelPressed)
			return;

		SuiListBox* listBox = cast<SuiListBox*>( sui);

		if(!creature->isPlayerCreature())
			return;
		ManagedReference<SceneObject*> obj = sui->getUsingObject();

		if(obj == NULL)
			return;

		if( customizationKit == NULL )
			return;

		ManagedReference<TangibleObject*> target = cast<TangibleObject*>(obj.get());

		if(!cancelPressed) {

			int index = Integer::valueOf(args->get(0).toString());

			if(index < 0 || index > 3)
				return;

			if(server != NULL) {

				if (target == NULL || !target->isDroidObject()) {
					creature->sendSystemMessage("You can only use this tool to customize droids");
					return;
				}

				String appearanceFilename = target->getObjectTemplate()->getAppearanceFilename();
				VectorMap<String, Reference<CustomizationVariable*> > variables;
				AssetCustomizationManagerTemplate::instance()->getCustomizationVariables(appearanceFilename.hashCode(), variables, false);
				int count = 0;
				for(int i = 0; i< variables.size(); ++i){
					String varkey = variables.elementAt(i).getKey();
					if (varkey.contains("color")){
						if (count == index){
							ManagedReference<SuiColorBox*> cbox = new SuiColorBox(creature, SuiWindowType::COLOR_ARMOR);
							cbox->setCallback(new ColorWithKitSuiCallback(server, customizationKit));
							cbox->setColorPalette(variables.elementAt(i).getKey());
							cbox->setUsingObject(target);

							ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
							ghost->addSuiBox(cbox);
							creature->sendMessage(cbox->generateMessage());

						}
						++count;
					}
				}
			}
		}
	}
};

#endif /* CUSTOMDROIDSUICALLBACK_H_ */
