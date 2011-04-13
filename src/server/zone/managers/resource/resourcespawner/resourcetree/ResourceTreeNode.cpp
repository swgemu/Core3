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
 * \file ResourceTreeNode.cpp
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#include "ResourceTreeNode.h"

ResourceTreeNode::ResourceTreeNode(const String& t, const String& n, const int d) {

	stfName = t;
	name = n;
	depth = d;

	parentNode = NULL;
}

ResourceTreeNode::~ResourceTreeNode() {
	while (nodes.size() > 0)
		delete nodes.remove(0);

	while (entries.size() > 0)
		delete entries.remove(0);

	parentNode = NULL;
}

String ResourceTreeNode::getName() {
	return name;
}

String ResourceTreeNode::getStfName() {
	return stfName;
}

void ResourceTreeNode::setParentNode(ResourceTreeNode* parent) {
	parentNode = parent;
}

ResourceTreeNode* ResourceTreeNode::getParentNode() {
	return parentNode;
}

void ResourceTreeNode::add(ResourceTreeEntry* entry) {


	 //Find out which child node this entry belongs to, and
	 //if it doesn't exist, create it
	for(int ii = 0; ii < nodes.size(); ++ii) {

		ResourceTreeNode* node = nodes.get(ii);
		if(node->getName() == entry->getClass(depth)) {
			node->add(entry);
			return;
		}
	}

	//The entry doesn't belong to an existing child node, now we
	//determine if it belong on this node, or on a new child node.
	if(entry->getClassCount() > depth + 1) {

		String stfType = "";

		for(int i = 0; i < entries.size(); ++i) {
			ResourceTreeEntry* ent = entries.get(i);
			if(ent->getFinalClass() == entry->getClass(depth)) {
				stfType = ent->getType();
				ent->setChildren(true);
				break;
			}
		}

		ResourceTreeNode* newnode = new ResourceTreeNode(stfType, entry->getClass(depth), depth + 1);
		nodes.add(newnode);
		newnode->add(entry);
		newnode->setParentNode(this);

	} else {

		entry->setMyNode(this);
		entries.add(entry);
	}
}

ResourceTreeEntry* ResourceTreeNode::find(ResourceTreeEntry* entry, const String& type) {
	if (entry != NULL)
		return entry;

	for(int i = 0; i < entries.size(); ++i) {
		ResourceTreeEntry* ent = entries.get(i);

		if(ent->getType() == type || ent->getFinalClass() == type) {
			return ent;
		}
	}

	for(int i = 0; i < nodes.size(); ++i) {
		ResourceTreeNode* node = nodes.get(i);
		entry = node->find(entry, type);
	}
	return entry;
}

ResourceTreeNode* ResourceTreeNode::find(ResourceTreeNode* node, const String& type) {
	if (node != NULL)
		return node;

	for(int i = 0; i < nodes.size(); ++i) {
		ResourceTreeNode* n = nodes.get(i);
		if(n->getStfName() == type || n->getName() == type)
			return n;
		else
			node = n->find(node, type);
	}
	return node;
}

ResourceTreeEntry* ResourceTreeNode::getEntry(const String& type,
		Vector<String> excludes, int zoneid) {

	ResourceTreeEntry* entry = NULL;
	entry = find(entry, type);

	if(entry == NULL)
		return NULL;

	// If the entry has no childen, it means
	// that a specific resource was requested
	if(!entry->hasChildren())
		return entry;

	ResourceTreeNode* node = NULL;
	node = entry->getMyNode()->find(node, type);

	if(node == NULL)
		return NULL;

	if (zoneid != -1) {

		String planet = Planet::getPlanetName(zoneid);

		return node->getPlanetSpecificEntry(planet);

	} else {

		Vector<ResourceTreeEntry*> candidates;

		node->getEntryPool(candidates, excludes);

		if(candidates.size() == 0)
			return NULL;

		int random = System::random(candidates.size() - 1);

		return candidates.get(random);
	}
}

ResourceTreeEntry* ResourceTreeNode::getPlanetSpecificEntry(const String& planet) {
	for(int i = 0; i < entries.size(); ++i) {
		ResourceTreeEntry* ent = entries.get(i);
		if(ent->getType().indexOf(planet) != -1) {
			return ent;
		}
	}
	return NULL;
}

void ResourceTreeNode::getEntryPool(Vector<ResourceTreeEntry*>& candidates,
		const Vector<String> excludes) {
	for(int i = 0; i < entries.size(); ++i) {

		ResourceTreeEntry* ent = entries.get(i);
		bool valid = true;

		if(!ent->isRecycled() && !ent->hasChildren()) {

			for(int ii = 0; ii < excludes.size(); ++ii) {
				if(ent->isType(excludes.get(ii))) {
					valid = false;
					break;
				}
			}

			if(valid)
				candidates.add(ent);
		}
	}

	for(int i = 0; i < nodes.size(); ++i) {
		ResourceTreeNode* node = nodes.get(i);
		node->getEntryPool(candidates, excludes);
	}
}

void ResourceTreeNode::updateEntries() {
	for(int i = 0; i < entries.size(); ++i) {
		ResourceTreeEntry* ent = entries.get(i);
		ResourceTreeNode* node = ent->getMyNode();
		ent->addStfClass(ent->getType());
		while(node->getParentNode() != NULL) {
			ent->addStfClass(node->getStfName());
			node = node->getParentNode();
		}
	}

	for(int i = 0; i < nodes.size(); ++i) {
		ResourceTreeNode* node = nodes.get(i);
		node->updateEntries();
	}
}

void ResourceTreeNode::addToSuiListBox(SuiListBox* suil) {
	for(int i = 0; i < nodes.size(); ++i) {
		ResourceTreeNode* node = nodes.get(i);
		suil->addMenuItem(node->getName(), 0);
	}

	for(int i = 0; i < entries.size(); ++i) {
		ResourceTreeEntry* ent = entries.get(i);
		if(!ent->hasChildren() && !ent->isRecycled())
			suil->addMenuItem(ent->getFinalClass());
	}
}

void ResourceTreeNode::toString() {
	System::out << "--- Node " << depth << " : " << name << "---" << stfName << endl;

	System::out << "NODES" << endl;
	for(int i = 0; i < nodes.size(); ++i)
		System::out << nodes.get(i)->getName() << " " <<
				nodes.get(i)->getStfName() << endl;

	System::out << "ENTRIES" << endl;
	for(int i = 0; i < entries.size(); ++i)
		//System::out << entries.get(i)->getType() << " Has Children = " << entries.get(i)->hasChildren() << endl;
		entries.get(i)->toString();

	for(int i = 0; i < nodes.size(); ++i)
		nodes.get(i)->toString();
}
