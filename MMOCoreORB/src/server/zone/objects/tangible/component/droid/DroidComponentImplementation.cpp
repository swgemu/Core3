/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "server/zone/objects/tangible/components/droid/BaseDroidModuleComponent.h"

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
