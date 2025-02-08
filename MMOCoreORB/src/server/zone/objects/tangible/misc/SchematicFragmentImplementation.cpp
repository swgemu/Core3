#include "server/zone/objects/tangible/misc/SchematicFragment.h"
#include "templates/tangible/SchematicFragmentTemplate.h"

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
