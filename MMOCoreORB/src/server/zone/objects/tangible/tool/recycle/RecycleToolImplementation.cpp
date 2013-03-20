

#include "engine/engine.h"
#include "RecycleTool.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/tangible/Container.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/templates/tangible/tool/RecycleToolTemplate.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

void RecycleToolImplementation::initializeTransientMembers() {

	ContainerImplementation::initializeTransientMembers();

	setLoggingName("RecycleTool");
}

void RecycleToolImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ContainerImplementation::loadTemplateData(templateData);

	RecycleToolTemplate* recycleToolData = dynamic_cast<RecycleToolTemplate*>(templateData);

	if (recycleToolData == NULL) {
		throw Exception("invalid template for RecycleTool");
	}

	toolType = recycleToolData->getToolType();

	switch (toolType) {
	case CHEMICAL:
		getChemical(&resourceTypes);
		break;
	case CREATURE:
		getCreature(&resourceTypes);
		break;
	case FLORA:
		getFlora(&resourceTypes);
		break;
	case METAL:
		getMetal(&resourceTypes);
		break;
	case ORE:
		getOre(&resourceTypes);
		break;
	}
}

void RecycleToolImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	ContainerImplementation::fillObjectMenuResponse(menuResponse, player);

	menuResponse->addRadialMenuItem(245, 3, "@recycler_messages:choose_type");

	String stub = "@recycler_messages:";

	switch (toolType) {
	case CHEMICAL:
		menuResponse->addRadialMenuItemToRadialID(245,246, 3, stub + resourceTypes.get(0));
		menuResponse->addRadialMenuItemToRadialID(245,247, 3, stub + resourceTypes.get(1));
		menuResponse->addRadialMenuItemToRadialID(245,248, 3, stub + resourceTypes.get(2));
		menuResponse->addRadialMenuItemToRadialID(245,249, 3, stub + resourceTypes.get(3));
		break;
	case CREATURE:
		menuResponse->addRadialMenuItemToRadialID(245,246, 3, stub + resourceTypes.get(0));
		menuResponse->addRadialMenuItemToRadialID(245,247, 3, stub + resourceTypes.get(1));
		menuResponse->addRadialMenuItemToRadialID(245,248, 3, stub + resourceTypes.get(2));
		menuResponse->addRadialMenuItemToRadialID(245,249, 3, stub + resourceTypes.get(3));
		menuResponse->addRadialMenuItemToRadialID(245,250, 3, stub + resourceTypes.get(4));
		menuResponse->addRadialMenuItemToRadialID(245,251, 3, stub + resourceTypes.get(5));
		break;
	case FLORA:
		menuResponse->addRadialMenuItemToRadialID(245,246, 3, stub + resourceTypes.get(0));
		menuResponse->addRadialMenuItemToRadialID(245,247, 3, stub + resourceTypes.get(1));
		menuResponse->addRadialMenuItemToRadialID(245,248, 3, stub + resourceTypes.get(2));
		menuResponse->addRadialMenuItemToRadialID(245,249, 3, stub + resourceTypes.get(3));
		break;
	case METAL:
		menuResponse->addRadialMenuItemToRadialID(245,246, 3, stub + resourceTypes.get(0));
		menuResponse->addRadialMenuItemToRadialID(245,247, 3, stub + resourceTypes.get(1));
		break;
	case ORE:
		menuResponse->addRadialMenuItemToRadialID(245,246, 3, stub + resourceTypes.get(0));
		menuResponse->addRadialMenuItemToRadialID(245,247, 3, stub + resourceTypes.get(1));
		menuResponse->addRadialMenuItemToRadialID(245,248, 3, stub + resourceTypes.get(2));
		break;
	}
}

int RecycleToolImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	PlayerObject* playerObject = player->getPlayerObject();

	if(isASubChildOf(player)) {

		switch (selectedID) {
		case 245:
			break;
		case 246:
			setSelectedResource(toolType + 1);
			setSelectedTypeName(resourceTypes.get(0));
			break;
		case 247:
			setSelectedResource(toolType + 2);
			setSelectedTypeName(resourceTypes.get(1));
			break;
		case 248:
			setSelectedResource(toolType + 3);
			setSelectedTypeName(resourceTypes.get(2));
			break;
		case 249:
			setSelectedResource(toolType + 4);
			setSelectedTypeName(resourceTypes.get(3));
			break;
		case 250:
			setSelectedResource(toolType + 5);
			setSelectedTypeName(resourceTypes.get(4));
			break;
		case 251:
			setSelectedResource(toolType + 6);
			setSelectedTypeName(resourceTypes.get(5));
			break;
		}
	}

	return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);
}

void RecycleToolImplementation::getChemical(Vector <String>* chemical) {
	chemical->setElementAt(0, "water");
	chemical->setElementAt(1, "chemical");
	chemical->setElementAt(2, "fuel_petrochem_solid");
	chemical->setElementAt(3, "radioactive");
}

void RecycleToolImplementation::getCreature(Vector <String>* creature) {
	creature->setElementAt(0, "hide");
	creature->setElementAt(1, "meat");
	creature->setElementAt(2, "bone");
	creature->setElementAt(3, "horn");
	creature->setElementAt(4, "seafood");
	creature->setElementAt(5, "milk");
}

void RecycleToolImplementation::getFlora(Vector <String>* flora) {
	flora->setElementAt(0, "cereal");
	flora->setElementAt(1, "fruit");
	flora->setElementAt(2, "vegetable");
	flora->setElementAt(3, "wood");
}

void RecycleToolImplementation::getMetal(Vector <String>* metal) {
	metal->setElementAt(0, "ferrous");
	metal->setElementAt(1, "nonferrous");
}

void RecycleToolImplementation::getOre(Vector <String>* ore) {
	ore->setElementAt(0, "igneous");
	ore->setElementAt(1, "sedimentary");
	ore->setElementAt(2, "gemstone");
}
