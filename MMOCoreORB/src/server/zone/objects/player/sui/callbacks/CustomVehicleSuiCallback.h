/*
 * CustomVehicleSuiCallback.h
 *
 *  Created on: May 5, 2013
 *      Author: Trick77
 */

#ifndef CUSTOMVEHICLESUICALLBACK_H_
#define CUSTOMVEHICLESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/colorbox/SuiColorBox.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/ColorArmorSuiCallback.h"



class CustomVehicleSuiCallback : public SuiCallback {
int numPalette;

public:
	CustomVehicleSuiCallback(ZoneServer* serv,int palette) : SuiCallback(serv), numPalette(palette) {
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

		ManagedReference<TangibleObject*> target = cast<TangibleObject*>(obj.get());

		if(!cancelPressed) {

			int index = Integer::valueOf(args->get(0).toString());

			if(index < 0 || index > 3)
				return;

			if(server != NULL) {
				//ManagedReference<TangibleObject*> target = dynamic_cast<TangibleObject*>(server->getObject(targetID, true));

				if (target == NULL || !target->isVehicleObject()) {
					creature->sendSystemMessage("You can only use this tool to customize vehicle");
					return;
				}

				if (numPalette == 4){//av21 has a strange first white color that cannot be changed
					++index;
				}
				if (numPalette == 3){//swoop has a palette0 as extra finiture instead of being frame
					++index;
					if (index == 3) index = 0;//extra finiture
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
							cbox->setCallback(new ColorArmorSuiCallback(server));
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

#endif /* CUSTOMVEHICLESUICALLBACK_H_ */
