/*
 * SurveyToolApproveRadioactiveSuiCallback.h
 *
 *  Created on: may 22, 2012
 *      Author: kyle
 */

#ifndef INSERTSCHEMATICSUICALLBACK_H_
#define INSERTSCHEMATICSUICALLBACK_H_


#include "server/zone/objects/installation/factory/FactoryObject.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"

class InsertSchematicSuiCallback : public SuiCallback {
public:
	InsertSchematicSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if(suiBox->getWindowType() == SuiWindowType::FACTORY_SCHEMATIC2BUTTON)
			handleInsertFactorySchem2(player, suiBox, eventIndex, args);

		if(suiBox->getWindowType() == SuiWindowType::FACTORY_SCHEMATIC3BUTTON)
			handleInsertFactorySchem3(player, suiBox, eventIndex, args);
	}

	void handleInsertFactorySchem2(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox() || eventIndex == 1)
			return;

		if (args->size() < 1)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		SuiListBox* listBox = cast<SuiListBox*>( suiBox);

		ManagedReference<SceneObject*> object = suiBox->getUsingObject().get();

		if (object == NULL || !object->isFactory())
			return;

		FactoryObject* factory = cast<FactoryObject*>( object.get());

		Locker locker(player);
		Locker clocker(factory, player);

		ManagedReference<ManufactureSchematic*> schematic = server->getObject(listBox->getMenuObjectID(index)).castTo<ManufactureSchematic*>();
		factory->handleInsertFactorySchem(player, schematic);
	}

	void handleInsertFactorySchem3(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox() || eventIndex == 1)
			return;

		if (args->size() < 2)
			return;

		bool otherPressed = Bool::valueOf(args->get(0).toString());
		int index = Integer::valueOf(args->get(1).toString());

		SuiListBox* listBox = cast<SuiListBox*>( suiBox);

		ManagedReference<SceneObject*> object = suiBox->getUsingObject().get();

		if (object == NULL || !object->isFactory())
			return;

		FactoryObject* factory = cast<FactoryObject*>( object.get());

		Locker locker(player);
		Locker clocker(factory, player);

		factory->handleRemoveFactorySchem(player);

		if (!otherPressed) {
			ManagedReference<ManufactureSchematic*> schematic = server->getObject(listBox->getMenuObjectID(index)).castTo<ManufactureSchematic*>();
			factory->handleInsertFactorySchem(player, schematic);
		}
	}
};

#endif /* INSERTSCHEMATICSUICALLBACK_H_ */
