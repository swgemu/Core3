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

#include "../../../../../db/ServerDatabase.h"
#include "ResourceTree.h"
#include "ResourceTreeEntry.h"
#include "ResourceAttribute.h"
#include "server/zone/managers/templates/TemplateManager.h"

ResourceTree::ResourceTree() {

	buildTreeFromDatabase();
}

ResourceTree::~ResourceTree() {

	delete baseNode;
}

bool ResourceTree::buildTreeFromDatabase() {

	baseNode = new ResourceTreeNode("resource", "Resource", 0);

	String query = "SELECT resource_tree.index,resource_tree.stfname, resource_tree.class1, "
			"resource_tree.class2, resource_tree.class3, resource_tree.class4, resource_tree.class5, "
			"resource_tree.class6, resource_tree.class7, resource_tree.maxtype, resource_tree.mintype, "
			"resource_tree.minpool, resource_tree.maxpool, resource_tree.recycled, resource_tree.attrib1, "
			"resource_tree.attrib2, resource_tree.attrib3, resource_tree.attrib4, resource_tree.attrib5, "
			"resource_tree.attrib6, resource_tree.attrib7, resource_tree.attrib8, resource_tree.attrib9, "
			"resource_tree.attrib10, resource_tree.attrib11, resource_tree.attrib1min, resource_tree.attrib1max, "
			"resource_tree.attrib2min, resource_tree.attrib2max, resource_tree.attrib3min, resource_tree.attrib3max, "
			"resource_tree.attrib4min, resource_tree.attrib4max, resource_tree.attrib5min, resource_tree.attrib5max, "
			"resource_tree.attrib6min, resource_tree.attrib6max, resource_tree.attrib7min, resource_tree.attrib7max, "
			"resource_tree.attrib8min, resource_tree.attrib8max, resource_tree.attrib9min, resource_tree.attrib9max, "
			"resource_tree.attrib10min, resource_tree.attrib10max, resource_tree.attrib11min, resource_tree.attrib11max, "
			"resource_tree.resourcecontainer, resource_tree.randomname, resource_tree.zoneRestriction, resource_tree.jtl, "
			"resource_tree.toolType, resource_tree.resourcecontainer FROM resource_tree ORDER BY resource_tree.index ASC";

	try {
		Reference<ResultSet*> res = ServerDatabase::instance()->executeQuery(query);

		if (res->size() != 0) {
			while (res->next()) {

				/// Build the ResourceTreeEntry

				String type = res->getString(1);
				ResourceTreeEntry* entry = new ResourceTreeEntry(type);

				for(int i = 2; i <= 8; ++i) {
					String newclass = res->getString(i);
					if(newclass != "")
						entry->addClass(newclass);
				}

				entry->setMaxtype(res->getInt(9));
				entry->setMintype(res->getInt(10));
				entry->setMinpool(res->getInt(11));
				entry->setMaxpool(res->getInt(12));

				entry->setRecycled(res->getBoolean(13));

				for(int i = 14; i <= 24; ++i) {
					String attribname = res->getString(i);
					if (attribname != "") {
						int min = res->getInt(i + 11 + (i - 14));
						int max = res->getInt(i + 12 + (i - 14));

						entry->addAttribute(new ResourceAttribute(attribname, min, max));
					}
				}

				entry->setResourceContainerType(res->getString(47));
				entry->setRandomNameClass(res->getString(48));
				entry->setZoneRestriction(res->getInt(49));
				entry->setJTL(res->getInt(50));
				entry->setSurveyToolType(res->getInt(51));
				String containerFile = res->getString(52);

				uint32 hashCode = containerFile.hashCode();
				entry->setContainerCRC(hashCode);

				try {
					if (hashCode != 0)
						TemplateManager::instance()->getTemplateFile(hashCode);
				} catch (Exception& e) {
					System::out << e.getMessage() << " for file " << containerFile << endl;
				}

				/// Add entry to the tree
				baseNode->add(entry);
			}
			/// Update the Stf Entries now that the tree is built
			baseNode->updateEntries();
		}
	} catch (DatabaseException& e) {
		System::out << "Database error in buildTreeFromDatabase\n";
		System::out << e.getMessage() << endl;

		return false;
	}

	return true;
}

ResourceTreeEntry* ResourceTree::getEntry(const String& type, Vector<String> excludes, int zoneid) {
	return baseNode->getEntry(type, excludes, zoneid);
}

void ResourceTree::toString() {
	baseNode->toString();
}
