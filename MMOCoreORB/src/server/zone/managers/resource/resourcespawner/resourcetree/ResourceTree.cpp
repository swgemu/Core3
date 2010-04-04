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

#include "../../../../../db/ServerDatabase.h"
#include "ResourceTree.h"
#include "ResourceTreeEntry.h"

ResourceTree::ResourceTree() {

	if(!buildTreeFromDatabase()) {

	}
}

ResourceTree::~ResourceTree() {

	delete baseNode;

}

bool ResourceTree::buildTreeFromDatabase() {

	baseNode = new ResourceTreeNode("resource");

	String query = "SELECT resource_tree.`Index`,resource_tree.stfname, resource_tree.class1, "
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
			"resource_tree.resourcecontainer, resource_tree.randomname, resource_tree.weight FROM resource_tree";

	try {
		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		if (res->size() != 0) {
			while (res->next()) {

				String type = res->getString(1);
				ResourceTreeEntry* entry = new ResourceTreeEntry(type);

				entry->setClass1(res->getString(2));
				entry->setClass2(res->getString(3));
				entry->setClass3(res->getString(4));
				entry->setClass4(res->getString(5));
				entry->setClass5(res->getString(6));
				entry->setClass6(res->getString(7));
				entry->setClass7(res->getString(8));

				entry->setMaxtype(res->getInt(9));
				entry->setMintype(res->getInt(10));
				entry->setMinpool(res->getInt(11));
				entry->setMaxpool(res->getInt(12));

				entry->setRecycled(res->getBoolean(13));

				entry->setAtt1(res->getString(14));
				entry->setAtt2(res->getString(15));
				entry->setAtt3(res->getString(16));
				entry->setAtt4(res->getString(17));
				entry->setAtt5(res->getString(18));
				entry->setAtt6(res->getString(19));
				entry->setAtt7(res->getString(20));
				entry->setAtt8(res->getString(21));
				entry->setAtt9(res->getString(22));
				entry->setAtt10(res->getString(23));
				entry->setAtt11(res->getString(24));

				entry->setAtt1min(res->getInt(25));
				entry->setAtt1max(res->getInt(26));
				entry->setAtt2min(res->getInt(27));
				entry->setAtt2max(res->getInt(28));
				entry->setAtt3min(res->getInt(29));
				entry->setAtt3max(res->getInt(30));
				entry->setAtt4min(res->getInt(31));
				entry->setAtt4max(res->getInt(32));
				entry->setAtt5min(res->getInt(33));
				entry->setAtt5max(res->getInt(34));
				entry->setAtt6min(res->getInt(35));
				entry->setAtt6max(res->getInt(36));
				entry->setAtt7min(res->getInt(37));
				entry->setAtt7max(res->getInt(38));
				entry->setAtt8min(res->getInt(39));
				entry->setAtt8max(res->getInt(40));
				entry->setAtt9min(res->getInt(41));
				entry->setAtt9max(res->getInt(42));
				entry->setAtt10min(res->getInt(43));
				entry->setAtt10max(res->getInt(44));
				entry->setAtt11min(res->getInt(45));
				entry->setAtt11max(res->getInt(46));

				entry->setResourceContainerType(res->getString(47));
				//entry->setResourceContainerTypeCRC(res->getUnsignedInt(47));

				entry->setRandomNameClass(res->getString(48));
				//entry->setWeight(res->getFloat(49));

				entry->toString();

				//baseNode->addEntry(entry);

				//server->addObject(tempSpawn);
			}
		}
		delete res;
	} catch (DatabaseException& e) {
		System::out << "Database error in buildTreeFromDatabase\n";
		System::out << e.getMessage() << endl;
	} catch (...) {
		System::out << "unreported exception caught in ResourceTree::buildTreeFromDatabase()\n";
	}
	return true;
}
