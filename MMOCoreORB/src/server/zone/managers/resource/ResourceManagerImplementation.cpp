/*
Copyright (C) 2010 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 3 of the License,
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

#include "engine/engine.h"

#include "ResourceManager.h"

void ResourceManagerImplementation::initialize() {
	Lua::init();

	info("building resource tree");
	resourceSpawner = new ResourceSpawner(zoneServer, processor, objectManager);

	info("loading configuration");
	if(!loadConfigData()) {

		loadDefaultConfig();

		info("***** ERROR in configuration, using default values");
	}

	info("starting resource spawner");
	startResourceSpawner();
	info("resource manager initialized");

}

bool ResourceManagerImplementation::loadConfigFile() {
	return runFile("scripts/resources/config.lua");
}

bool ResourceManagerImplementation::loadConfigData() {
	if (!loadConfigFile())
		return false;

	String zonesString = getGlobalString("activeZones");

	StringTokenizer zonesTokens(zonesString);
	zonesTokens.setDelimeter(",");

	while(zonesTokens.hasMoreTokens()) {
		int token = zonesTokens.getIntToken();
		resourceSpawner->addPlanet(token);
	}

	int averageShiftTime = getGlobalInt("averageShiftTime");
	int aveduration = getGlobalInt("aveduration");
	float spawnThrottling = float(getGlobalInt("spawnThrottling")) / 100.0f;
	int lowerGateOverride = getGlobalInt("lowerGateOverride");
	int maxSpawnQuantity = getGlobalInt("maxSpawnQuantity");

	resourceSpawner->setSpawningParameters(averageShiftTime, aveduration,
			spawnThrottling, lowerGateOverride, maxSpawnQuantity);

	String minpoolinc = getGlobalString("minimumpoolincludes");
	String minpoolexc = getGlobalString("minimumpoolexcludes");
	resourceSpawner->initializeMinimumPool(minpoolinc, minpoolexc);

	String randpoolinc = getGlobalString("randompoolincludes");
	String randpoolexc = getGlobalString("randompoolexcludes");
	int randpoolsize = getGlobalInt("randompoolsize");
	resourceSpawner->initializeRandomPool(randpoolinc, randpoolexc, randpoolsize);

	String fixedpoolinc = getGlobalString("fixedpoolincludes");
	String fixedpoolexc = getGlobalString("fixedpoolexcludes");
	resourceSpawner->initializeFixedPool(fixedpoolinc, fixedpoolexc);

	String natpoolinc = getGlobalString("nativepoolincludes");
	String natpoolexc = getGlobalString("nativepoolexcludes");
	resourceSpawner->initializeNativePool(natpoolinc, natpoolexc);

	return true;
}

void ResourceManagerImplementation::loadDefaultConfig() {
	for(int i = 0;i < 10; ++i) {
		resourceSpawner->addPlanet(i);
	}

	resourceSpawner->setSpawningParameters(7200000, 86400, 90, 1000, 0);
}

void ResourceManagerImplementation::stop() {


}

void ResourceManagerImplementation::startResourceSpawner() {
	resourceSpawner->start();
}
