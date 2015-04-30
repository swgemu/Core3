/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GENERATECRAFTEDITEMCOMMAND_H_
#define GENERATECRAFTEDITEMCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "server/zone/objects/draftschematic/DraftSchematic.h"
#include "server/zone/objects/factorycrate/FactoryCrate.h"
#include "server/zone/managers/crafting/CraftingManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"

class GenerateCraftedItemCommand : public QueueCommand {
public:

	GenerateCraftedItemCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if(!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(creature);

		ManagedReference<CraftingManager*> craftingManager = player->getZoneServer()->getCraftingManager();
		if(craftingManager == NULL) {
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

		if(inventory == NULL) {
			creature->sendSystemMessage("Error locating target inventory");
			return GENERALERROR;
		}

		try {

			StringTokenizer tokenizer(arguments.toString());

			if(!tokenizer.hasMoreTokens()) {
				creature->sendSystemMessage("Usage: /GenerateCraftedItem SERVERSCRIPTPATH [Quantity] [Quality] [Template Number]");
				return GENERALERROR;
			}

			String file;
			tokenizer.getStringToken(file);
			if (file.indexOf("draft_schematic") == -1)
				file = "object/draft_schematic/" + file;

			if (file.indexOf(".iff") == -1)
				file = file + ".iff";

			ManagedReference<DraftSchematic* > draftSchematic =
					creature->getZoneServer()->createObject(file.hashCode(), 0).castTo<DraftSchematic*>();

			if(draftSchematic == NULL || !draftSchematic->isValidDraftSchematic()) {
				creature->sendSystemMessage("File entered not valid, please be sure to use the draft schematics server script path not client path");
				return GENERALERROR;
			}

			ManagedReference<ManufactureSchematic* > manuSchematic = ( draftSchematic->createManufactureSchematic()).castTo<ManufactureSchematic*>();

			if(manuSchematic == NULL) {
				creature->sendSystemMessage("Error creating ManufactureSchematic from DraftSchematic");
				return GENERALERROR;
			}

			manuSchematic->createChildObjects();

			int quantity = 1;

			if(tokenizer.hasMoreTokens())
				quantity = tokenizer.getIntToken();

			if(quantity == 0)
				quantity = 1;

			int quality = 0;
			if (tokenizer.hasMoreTokens())
				quality = tokenizer.getIntToken();

			quality = MAX(0, quality);

			unsigned int targetTemplate = draftSchematic->getTanoCRC();

			if (draftSchematic->getTemplateListSize() > 0) {
				if (tokenizer.hasMoreTokens()) {
					int index = tokenizer.getIntToken();

					if (index >= draftSchematic->getTemplateListSize() || index < 0) {
						creature->sendSystemMessage("Invalid template requested.");
						return GENERALERROR;
					}

					String requestedTemplate = draftSchematic->getTemplate(index);

					String templateName = requestedTemplate.subString(0, requestedTemplate.lastIndexOf('/') + 1) + requestedTemplate.subString(requestedTemplate.lastIndexOf('/') + 8);

					targetTemplate = templateName.hashCode();
				}
			}

			ManagedReference<TangibleObject *> prototype =  (
					creature->getZoneServer()->createObject(targetTemplate, 2)).castTo<TangibleObject*>();

			if(prototype == NULL) {
				creature->sendSystemMessage("Unable to create target item, is it implemented yet?");
				return GENERALERROR;
			}

			Locker locker(prototype);
			Locker mlock(manuSchematic, prototype);
			craftingManager->setInitialCraftingValues(prototype,manuSchematic,CraftingManager::GREATSUCCESS);
			Reference<CraftingValues*> craftingValues = manuSchematic->getCraftingValues();
			int nRows = craftingValues->getVisibleExperimentalPropertyTitleSize();
			prototype->updateCraftingValues(craftingValues, true);

			if (quality > 0) {
				for (int i = 0; i < nRows; i++) {
					String title = craftingValues->getVisibleExperimentalPropertyTitle(i);
					for (int j = 0; j < craftingValues->getExperimentalPropertySubtitleSize(); ++j) {
						String subtitlesTitle = craftingValues->getExperimentalPropertySubtitlesTitle(j);
						if (subtitlesTitle == title) {
							String subtitle = craftingValues->getExperimentalPropertySubtitle(j);

							float maxValue = craftingValues->getMaxValue(subtitle);
							float minValue = craftingValues->getMinValue(subtitle);

							//float newValue = fabs(maxValue-minValue)*((float)quality/100.f) + MAX(minValue, maxValue);
							//craftingValues->setCurrentValue(subtitle, newValue);

							craftingValues->setCurrentPercentage(subtitle, (float)quality/100.f, 5.f);
						}
					}
				}

				craftingValues->recalculateValues(true);
				prototype->updateCraftingValues(craftingValues, true);
			}

			prototype->createChildObjects();

			// Set Crafter name and generate serial number
			String name = "Generated with GenerateC Command";
			prototype->setCraftersName(name);

			StringBuffer customName;
			customName << prototype->getDisplayedName() <<  " (System Generated)";
			prototype->setCustomObjectName(customName.toString(), false);

			String serial = craftingManager->generateSerial();
			prototype->setSerialNumber(serial);

			prototype->updateToDatabase();

			if(quantity > 1) {

				ManagedReference<FactoryCrate* > crate = prototype->createFactoryCrate(true);
				if (crate == NULL) {
					prototype->destroyObjectFromDatabase(true);
					return GENERALERROR;
				}

				crate->setUseCount(quantity);

				if (!inventory->transferObject(crate, -1, true)) {
					crate->destroyObjectFromDatabase(true);
					return GENERALERROR;
				}
				crate->sendTo(creature, true);

			} else {
				if (!inventory->transferObject(prototype, -1, true)) {
					prototype->destroyObjectFromDatabase(true);
					return GENERALERROR;
				}
				prototype->sendTo(creature, true);
			}

		} catch (Exception& e) {
			creature->sendSystemMessage("Error in data input, try again");
			return GENERALERROR;
		}

		return SUCCESS;
	}
};

#endif //GENERATECRAFTEDITEMCOMMAND_H_
