
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/managers/creature/ValidMountScaleRange.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/templates/datatables/DataTableIff.h"
#include "server/zone/templates/datatables/DataTableRow.h"
#include "server/zone/templates/params/primitives/StringParam.h"


void PetManagerImplementation::loadValidMountScaleRanges() {
	IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/mount/valid_scale_range.iff");

	if (iffStream == NULL) {
		error("Could not load valid mount scales.");
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	delete iffStream;

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);

		Reference<ValidMountScaleRange*> validMountScale = new ValidMountScaleRange();
		validMountScale->parseDataTableRow(row);

		validMountScaleRanges.add(validMountScale);
	}

	info("Loaded " + String::valueOf(validMountScaleRanges.size()) + " mount scale ranges.", true);
}

short PetManagerImplementation::isValidMountScale(const String& appearanceFilename, int saddleCapacity, float scale) {
	for (int i = 0; i < validMountScaleRanges.size(); i++) {
		ValidMountScaleRange* range = validMountScaleRanges.get(i);

		if (range == NULL)
			continue;

		if (appearanceFilename == range->getAppearanceFilename() && saddleCapacity == range->getSaddleCapacity()) {

			if (scale < range->getValidScaleMin())
				return TOOSMALL;
			else if (scale > range->getValidScaleMax())
				return TOOLARGE;
			else
				return CANBEMOUNTTRAINED;
		}
	}

	return INVALIDCREATURE;
}

short PetManagerImplementation::checkMountEligibility(PetControlDevice* petControlDevice) {
	if (petControlDevice->isTrainedAsMount())
		return PetManager::INVALIDCREATURE;

	ManagedReference<TangibleObject*> controlledObject = petControlDevice->getControlledObject();
	if (controlledObject == NULL || !controlledObject->isAiAgent())
		return PetManager::INVALIDCREATURE;

	ManagedReference<AiAgent*> pet = cast<AiAgent*>(controlledObject.get());
	if( pet == NULL )
		return PetManager::INVALIDCREATURE;

	//Check if the pet's species is able to be trained as a mount
	if (!pet->hasSlotDescriptor("rider"))
		return PetManager::INVALIDCREATURE;

	SharedObjectTemplate* objectTemplate = petControlDevice->getObjectTemplate();
	if (objectTemplate == NULL)
		return PetManager::INVALIDCREATURE;

	short result = isValidMountScale(objectTemplate->getAppearanceFilename(), 1, pet->getHeight());

	return result;
}
