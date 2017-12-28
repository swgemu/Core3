/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include <stddef.h>
#include <algorithm>

#include "engine/core/ManagedReference.h"
#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/scene/components/DataObjectComponent.h"
#include "server/zone/objects/scene/components/DataObjectComponentReference.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/tangible/component/Component.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/objects/tangible/components/droid/BaseDroidModuleComponent.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "system/lang/String.h"
#include "system/lang/ref/Reference.h"
#include "system/platform.h"
#include "templates/SharedObjectTemplate.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
}  // namespace creature
}  // namespace objects
}  // namespace zone
}  // namespace server

void DroidComponentImplementation::initializeTransientMembers() {
	ComponentImplementation::initializeTransientMembers();
}

void DroidComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ComponentImplementation::updateCraftingValues(values, firstUpdate);

	quality = values->getCurrentValue("mechanism_quality");
	durability = values->getCurrentValue("decayrate");
	if (values->hasProperty("droid_count")) {
		setUseCount(values->getCurrentValue("droid_count"));
		surveyDroid = true;
	}

	DataObjectComponentReference* data = getDataObjectComponent();
	if(data != NULL && data->get() != NULL && data->get()->isDroidModuleData() ){
		BaseDroidModuleComponent* module = cast<BaseDroidModuleComponent*>(data->get());
		if( module != NULL ){
			module->updateCraftingValues( values, firstUpdate );
		}
	}
}
void DroidComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {

	// need to update this for non survey droids
	if (surveyDroid) {
		TangibleObjectImplementation::fillAttributeList(alm, object);
		alm->insertAttribute("decayrate",(int)durability);
		alm->insertAttribute("mechanism_quality",(int)quality);
	} else {
		ComponentImplementation::fillAttributeList(alm,object);
		// if this is a cluster module, add the cluter items
		if (isSocketCluster()) {
			ManagedReference<SceneObject*> craftingComponents = getSlottedObject("crafted_components");
			if(craftingComponents != NULL) {
				SceneObject* satchel = craftingComponents->getContainerObject(0);
				// remove all items form satchel and add int he new items
				for (int i = 0; i < satchel->getContainerObjectsSize(); ++i) {
					ManagedReference<SceneObject*> sceno = satchel->getContainerObject(i);
					// if its a droid componet and a data module add it.
					ManagedReference<DroidComponent*> sub = cast<DroidComponent*>( sceno.get());
					if (sub != NULL) {
						DataObjectComponentReference* data = sub->getDataObjectComponent();
						BaseDroidModuleComponent* module = NULL;
						if(data != NULL && data->get() != NULL && data->get()->isDroidModuleData() ){
							module = cast<BaseDroidModuleComponent*>(data->get());
						}
						if (module == NULL) {
							continue;
						}
						module->fillAttributeList(alm,object);
					}
				}
			}
		}
	}
}
bool DroidComponentImplementation::isSocketCluster() {
	String objTemplate = getObjectTemplate()->getFullTemplateString();
	return objTemplate.contains("socket_bank");
}
