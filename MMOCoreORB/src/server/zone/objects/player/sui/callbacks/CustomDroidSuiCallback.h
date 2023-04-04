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
#include "server/zone/objects/player/sui/callbacks/ColorWithKitSuiCallback.h"

class CustomDroidSuiCallback : public SuiCallback, public Logger {
	int numPalette;
	TangibleObject* customizationKit;

public:
	CustomDroidSuiCallback(ZoneServer* serv, int palette, TangibleObject* kitTano) :
		SuiCallback(serv), numPalette(palette), customizationKit(kitTano) {

		setLoggingName("CustomDroidSuiCallback");
	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!sui->isListBox() || cancelPressed)
			return;

		SuiListBox* listBox = cast<SuiListBox*>( sui);

		if (!creature->isPlayerCreature())
			return;

		ManagedReference<SceneObject*> obj = sui->getUsingObject().get();

		if (obj == nullptr)
			return;

		if (customizationKit == nullptr )
			return;

		ManagedReference<TangibleObject*> target = cast<TangibleObject*>(obj.get());

		if (!cancelPressed) {
			int index = Integer::valueOf(args->get(0).toString());

			if (index < 0 || index > 3)
				return;

			if (server != nullptr) {
				if (target == nullptr || !target->isDroidObject()) {
					creature->sendSystemMessage("@tool/customizer:droid_pet_only"); // You may only use this tool to customize droid pets.
					return;
				}

				String appearanceFilename = target->getObjectTemplate()->getAppearanceFilename();
				VectorMap<String, Reference<CustomizationVariable*> > variables;
				AssetCustomizationManagerTemplate::instance()->getCustomizationVariables(appearanceFilename.hashCode(), variables, false);

				int count = 0;

				for (int i = 0; i < variables.size(); ++i) {
					String varKey = variables.elementAt(i).getKey();

					if (varKey != "/private/index_color_0" && varKey.contains("color")) {
						if (count == index) {
							ManagedReference<SuiColorBox*> cbox = new SuiColorBox(creature, SuiWindowType::CUSTOMIZE_KIT);

							cbox->setCallback(new ColorWithKitSuiCallback(server, customizationKit));
							cbox->setColorPalette(varKey);
							cbox->setUsingObject(target);

							int skillMod = creature->getSkillMod("droid_customization");

							if (skillMod < 32)
								skillMod = 32;
							else if (skillMod > 64)
								skillMod = 64;

							cbox->setSkillMod(skillMod);

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
