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

/**
 * \file ResourceTree.cpp
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#include "ResourceTree.h"
#include "ResourceTreeEntry.h"
#include "ResourceAttribute.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "../ResourceSpawner.h"
#include "server/zone/objects/tangible/tool/SurveyTool.h"

ResourceTree::ResourceTree(ResourceSpawner* spawn) : Logger() {

	spawner = spawn;
	buildTreeFromClient();
}

ResourceTree::~ResourceTree() {

	delete baseNode;
}

bool ResourceTree::buildTreeFromClient() {
	TemplateManager* templateManager = TemplateManager::instance();

	IffStream* iffStream = templateManager->openIffFile("datatables/resource/resource_tree.iff");

	if (iffStream == NULL) {
		info("The Resource Tree could not be found.", true);
		return false;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	Vector<String> currentClasses;
	Vector<String> currentStfClasses;

	baseNode = new ResourceTreeNode("resource", "Resources", 0);

	String stringvalue, randomname, resourcecontainer;
	int intvalue;
	bool boolValue;

	for (int i = 1; i < dtiff.getTotalRows(); ++i) {

		DataTableRow* row = dtiff.getRow(i);

		row->getValue(1, stringvalue);

		ResourceTreeEntry* entry = new ResourceTreeEntry(stringvalue);

		for (int j = 3; j <= 9; ++j) {
			String resourceclass;
			row->getValue(j, resourceclass);

			if (resourceclass.isEmpty())
				continue;

			while (currentStfClasses.size() > j - 3) {
				currentStfClasses.removeElementAt(j - 3);
				currentClasses.removeElementAt(j - 3);
			}

			currentStfClasses.add(stringvalue);
			currentClasses.add(resourceclass);
		}

		for (int j = 0; j < currentStfClasses.size(); ++j) {
			entry->addClass(currentClasses.get(j));
			entry->addStfClass(currentStfClasses.get(j));
		}

		row->getValue(10, intvalue);
		entry->setMaxtype(intvalue);

		row->getValue(11, intvalue);
		entry->setMintype(intvalue);

		row->getValue(12, intvalue);
		entry->setMinpool(intvalue);

		row->getValue(13, intvalue);
		entry->setMaxpool(intvalue);

		row->getValue(14, boolValue);
		entry->setRecycled(boolValue);

		for (int j = 16; j <= 26; ++j) {
			row->getValue(j, stringvalue);
			if (stringvalue == "")
				break;

			int min;
			row->getCell(j + 11 + (j - 16))->getValue(min);

			int max;
			row->getCell(j + 12 + (j - 16))->getValue(max);

			entry->addAttribute(new ResourceAttribute(stringvalue, min, max));
		}

		row->getCell(49)->getValue(stringvalue);
		if(stringvalue != "")
			resourcecontainer = stringvalue;
		entry->setResourceContainerType(resourcecontainer);

		row->getCell(50)->getValue(stringvalue);
		if(stringvalue != "")
				randomname = stringvalue;
		entry->setRandomNameClass(randomname);

		setZoneRestriction(entry);
		setJtl(entry);
		setSurveyToolType(entry);

		/// Add entry to the tree
		baseNode->add(entry);
	}
	/// Update the Stf Entries now that the tree is built
	//baseNode->updateEntries();

	return true;
}

ResourceTreeEntry* ResourceTree::getEntry(const String& type, const Vector<String>& excludes, const String& zoneName) {
	return baseNode->getEntry(type, excludes, zoneName);
}

void ResourceTree::setZoneRestriction(ResourceTreeEntry* entry) {
	String name = entry->getType();

	Vector<String>& activeZones = spawner->getActiveResourceZones();

	for(int i = 0; i < activeZones.size(); ++i) {
		String zonename = activeZones.get(i);

		if(name.indexOf(zonename) != -1) {
			entry->setZoneRestriction(zonename);
			return;
		}
	}
}

void ResourceTree::setJtl(ResourceTreeEntry* entry) {
	String name = entry->getType();

	Vector<String>& jtlResources = spawner->getJtlResources();

	for(int i = 0; i < jtlResources.size(); ++i) {
		String jtlresource = jtlResources.get(i);

		if(name == jtlresource) {
			entry->setJTL(true);
			return;
		}
	}
}

void ResourceTree::setSurveyToolType(ResourceTreeEntry* entry) {

	if(entry->isType("energy")) {

		String type = entry->getType();
		if(type.indexOf("geothermal") != -1)
			entry->setSurveyToolType(SurveyTool::GEOTHERMAL);
		else if(type.indexOf("solar") != -1)
			entry->setSurveyToolType(SurveyTool::SOLAR);
		else if(type.indexOf("unlimited_wind") != -1)
			entry->setSurveyToolType(SurveyTool::WIND);
		else
			entry->setSurveyToolType(SurveyTool::NOTYPE);

	} else if(entry->isType("chemical"))
		entry->setSurveyToolType(SurveyTool::CHEMICAL);

	else if(entry->isType("flora_resource"))
		entry->setSurveyToolType(SurveyTool::FLORA);

	else if(entry->isType("gas"))
		entry->setSurveyToolType(SurveyTool::GAS);

	else if(entry->isType("mineral")) {

		if(entry->isType("radioactive"))
			entry->setSurveyToolType(SurveyTool::FUSION);
		else
			entry->setSurveyToolType(SurveyTool::MINERAL);
	}

	else if(entry->isType("water"))
		entry->setSurveyToolType(SurveyTool::WATER);

	else
		entry->setSurveyToolType(SurveyTool::NOTYPE);
}

void ResourceTree::toString() {
	baseNode->toString();
}
