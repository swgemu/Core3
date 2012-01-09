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

#include "CityRegion.h"

#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/scene/ObserverEventType.h"

void CityRegionImplementation::addActiveArea(Zone* zone, float x, float y, float radius) {
	ManagedReference<ActiveArea*> area = cast<ActiveArea*>( ObjectManager::instance()->createObject(String("object/active_area.iff").hashCode(), 0, ""));
	area->registerObserver(ObserverEventType::ENTEREDAREA, _this);
	area->registerObserver(ObserverEventType::EXITEDAREA, _this);
	area->initializePosition(x, 0, y);
	area->setRadius(radius);
	area->setClientObject(true);
	area->setNoBuildArea(true);

	if (activeAreas.size() == 0) { //If this is the first active area, set it's planet map category to city.
		area->setPlanetMapCategory(TemplateManager::instance()->getPlanetMapCategoryByName("city"));
		area->getObjectName()->setStringId(regionName);
	}

	//area->insertToZone(zone);
	zone->transferObject(area, -1, true);

	activeAreas.put(area);
}

void CityRegionImplementation::notifyEnter(SceneObject* object) {
	if (!object->isVendor()) //main region only tracks down vendors for now
		return;

	object->setCityRegion(_this);

	if (object->isVendor()) {
		Locker locker(_this);

		regionObjects.put(object->getObjectID(), object);
	}
}

void CityRegionImplementation::notifyExit(SceneObject* object) {
	if (!object->isVendor()) //main region only tracks down vendors for now
		return;

	object->setCityRegion(NULL);

	if (object->isVendor()) {
		Locker locker(_this);

		regionObjects.drop(object->getObjectID());
	}
}

Vector<ManagedReference<SceneObject* > >* CityRegionImplementation::getVendorsInCity() {
	Locker locker(_this);

	Vector<ManagedReference<SceneObject* > >* vendors = new Vector<ManagedReference<SceneObject*> >();

	for (int i = 0; i < regionObjects.size(); ++i) {
		SceneObject* object = regionObjects.get(i);

		if (object->isVendor())
			vendors->add(object);
	}

	return vendors;
}

SortedVector<ManagedReference<SceneObject*> > CityRegionImplementation::getRegionObjectsByPlanetMapCategory(const String& catname) {
	Locker locker(_this);

	SortedVector<ManagedReference<SceneObject*> > objects;

	for (int i = 0; i < regionObjects.size(); ++i) {
		ManagedReference<SceneObject*> object = regionObjects.get(i);

		if (object->getPlanetMapCategory() != NULL && object->getPlanetMapCategory()->getName() == catname)
			objects.put(object);
	}

	return objects;
}
