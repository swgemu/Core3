

#include "engine/engine.h"
#include "server/zone/objects/tangible/tool/recycle/RecycleTool.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "templates/tangible/tool/RecycleToolTemplate.h"
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

}

void RecycleToolImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	ContainerImplementation::fillObjectMenuResponse(menuResponse, player);

	menuResponse->addRadialMenuItem(245, 3, "@recycler_messages:choose_type");

	String stub = "@recycler_messages:";

	SharedObjectTemplate* templateData = TemplateManager::instance()->getTemplate(_this.getReferenceUnsafeStaticCast()->getServerObjectCRC());

	if (templateData == NULL) {
		error("No template data for: " + String::valueOf(_this.getReferenceUnsafeStaticCast()->getServerObjectCRC()));
		return;
	}

	RecycleToolTemplate* recycleToolData = dynamic_cast<RecycleToolTemplate*>(templateData);

	if (recycleToolData == NULL) {
		error("No RecycleToolTemplate for: " + String::valueOf(_this.getReferenceUnsafeStaticCast()->getServerObjectCRC()));
		return;
	}

	Vector<String> resourceTypes = recycleToolData->getResourceTypes();

	for (int i = 0; i < resourceTypes.size(); i++) {
		menuResponse->addRadialMenuItemToRadialID(245, 246 + i, 3, stub + resourceTypes.get(i));
	}
}

int RecycleToolImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (isASubChildOf(player)) {
		SharedObjectTemplate* templateData = TemplateManager::instance()->getTemplate(_this.getReferenceUnsafeStaticCast()->getServerObjectCRC());

		if (templateData == NULL || !templateData->isRecycleToolTemplate())
			return 1;

		RecycleToolTemplate* recycleToolData = dynamic_cast<RecycleToolTemplate*>(templateData);

		Vector<String> resourceTypes = recycleToolData->getResourceTypes();

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

		return 0;
	}

	return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);
}
