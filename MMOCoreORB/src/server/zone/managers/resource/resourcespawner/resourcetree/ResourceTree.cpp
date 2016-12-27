/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file ResourceTree.cpp
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#include "ResourceTree.h"
#include "ResourceTreeEntry.h"
#include "ResourceAttribute.h"
#include "templates/manager/TemplateManager.h"
#include "server/zone/managers/resource/resourcespawner/ResourceSpawner.h"
#include "server/zone/objects/tangible/tool/SurveyTool.h"
#include "server/zone/objects/tangible/tool/recycle/RecycleTool.h"

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

	delete iffStream;

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
		setRecycleToolType(entry);

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

		if(name.indexOf("_" + zonename) != -1) {
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

	else if(entry->isType("flora_resources"))
		entry->setSurveyToolType(SurveyTool::FLORA);

	else if(entry->isType("gas"))
		entry->setSurveyToolType(SurveyTool::GAS);

	else if(entry->isType("mineral")) {
		entry->setSurveyToolType(SurveyTool::MINERAL);
	}

	else if(entry->isType("water"))
		entry->setSurveyToolType(SurveyTool::WATER);

	else
		entry->setSurveyToolType(SurveyTool::NOTYPE);
}

void ResourceTree::setRecycleToolType(ResourceTreeEntry* entry) {

	if(entry->isType("chemical")) {
		entry->setRecycleToolType(RecycleTool::CHEMICALS);
	} else if(entry->isType("water")) {
		entry->setRecycleToolType(RecycleTool::WATER);
	} else if(entry->isType("radioactive")) {
		entry->setRecycleToolType(RecycleTool::RADIOACTIVE);
	} else if(entry->isType("fuel_petrochem_solid")) {
		entry->setRecycleToolType(RecycleTool::SOLIDFUEL);
	}

	else if(entry->isType("hide")) {
		entry->setRecycleToolType(RecycleTool::HIDE);
	} else if(entry->isType("meat")) {
		entry->setRecycleToolType(RecycleTool::MEAT);
	} else if(entry->isType("bone")) {
		entry->setRecycleToolType(RecycleTool::BONE);
	} else if(entry->isType("horn")) {
		entry->setRecycleToolType(RecycleTool::HORN);
	} else if(entry->isType("seafood")) {
		entry->setRecycleToolType(RecycleTool::SEAFOOD);
	} else if(entry->isType("milk")) {
		entry->setRecycleToolType(RecycleTool::MILK);
	}

	else if(entry->isType("cereal")) {
		entry->setRecycleToolType(RecycleTool::CEREAL);
	} else if(entry->isType("fruit")) {
		entry->setRecycleToolType(RecycleTool::FRUIT);
	} else if(entry->isType("vegetable")) {
		entry->setRecycleToolType(RecycleTool::VEGETABLE);
	} else if(entry->isType("wood")) {
		entry->setRecycleToolType(RecycleTool::WOOD);
	}

	else if(entry->isType("metal_ferrous")) {
		entry->setRecycleToolType(RecycleTool::FERROUS);
	} else if(entry->isType("metal_nonferrous")) {
		entry->setRecycleToolType(RecycleTool::NONFERROUS);
	}

	else if(entry->isType("ore_igneous")) {
		entry->setRecycleToolType(RecycleTool::IGNEOUS);
	} else if(entry->isType("ore_sedimentary")) {
		entry->setRecycleToolType(RecycleTool::SEDIMENTARY);
	} else if (entry->isType("gemstone")) {
		entry->setRecycleToolType(RecycleTool::GEMSTONE);
	}

	else {
		entry->setRecycleToolType(RecycleTool::NOTYPE);
	}

}

void ResourceTree::toString() {
	baseNode->toString();
}
