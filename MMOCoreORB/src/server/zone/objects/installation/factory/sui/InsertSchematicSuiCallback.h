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

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {

		if(suiBox->getWindowType() == SuiWindowType::FACTORY_SCHEMATIC2BUTTON)
			handleInsertFactorySchem2(player, suiBox, cancelPressed, args);

		if(suiBox->getWindowType() == SuiWindowType::FACTORY_SCHEMATIC3BUTTON)
			handleInsertFactorySchem3(player, suiBox, cancelPressed, args);
	}

	void handleInsertFactorySchem2(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox() || cancel != 0)
			return;

		if (args->size() < 1)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		SuiListBox* listBox = cast<SuiListBox*>( suiBox);

		ManagedReference<SceneObject*> object = suiBox->getUsingObject();

		if (object == NULL || !object->isFactory())
			return;

		FactoryObject* factory = cast<FactoryObject*>( object.get());

		Locker locker(player);
		Locker clocker(factory, player);

		ManagedReference<ManufactureSchematic*> schematic = cast<ManufactureSchematic*>(server->getObject(listBox->getMenuObjectID(index)));
		factory->handleInsertFactorySchem(player, schematic);
	}

	void handleInsertFactorySchem3(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox() || cancel != 0)
			return;

		if (args->size() < 2)
			return;

		bool otherPressed = Bool::valueOf(args->get(0).toString());
		int index = Integer::valueOf(args->get(1).toString());

		SuiListBox* listBox = cast<SuiListBox*>( suiBox);

		ManagedReference<SceneObject*> object = suiBox->getUsingObject();

		if (object == NULL || !object->isFactory())
			return;

		FactoryObject* factory = cast<FactoryObject*>( object.get());

		Locker locker(player);
		Locker clocker(factory, player);

		factory->handleRemoveFactorySchem(player);

		if (!otherPressed) {
			ManagedReference<ManufactureSchematic*> schematic = cast<ManufactureSchematic*>(server->getObject(listBox->getMenuObjectID(index)));
			factory->handleInsertFactorySchem(player, schematic);
		}
	}
};

#endif /* INSERTSCHEMATICSUICALLBACK_H_ */
