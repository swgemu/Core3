#include "server/zone/objects/tangible/misc/ContractCrate.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/crafting/schematicmap/SchematicMap.h"
#include "templates/manager/TemplateManager.h"
#include "templates/SharedTangibleObjectTemplate.h"
#include "templates/tangible/SchematicFragmentTemplate.h"
#include "server/zone/objects/tangible/misc/SchematicFragment.h"

void SchematicFragmentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	SchematicFragmentTemplate* fragmentData = dynamic_cast<SchematicFragmentTemplate*>(templateData);

	if (fragmentData == nullptr) {
		info("fragmentData is null", true);
		return;
}

	targetSchematic = fragmentData->getTargetSchematic();

	totalFragments = fragmentData->getTotalFragments();

	fragmentBitmask = fragmentData->getfragmentBitmask();
}
