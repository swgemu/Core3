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

#include "ResourceTreeNode.h"

ResourceTreeNode::ResourceTreeNode(const String& t, const String& n, const int d) {

	stfType = t;
	nodeClass = n;
	depth = d;
}
ResourceTreeNode::~ResourceTreeNode() {
	while (nodes.size() > 0)
		delete nodes.remove(0);

	while (entries.size() > 0)
		delete entries.remove(0);
}

void ResourceTreeNode::addEntry(ResourceTreeEntry* entry) {


	 //Find out which child node this entry belongs to, and
	 //if it doesn't exist, create it
	for(int ii = 0; ii < nodes.size(); ++ii) {

		ResourceTreeNode* node = nodes.get(ii);
		if(node->getNodeClass() == entry->getClass(depth)) {
			node->addEntry(entry);
			return;
		}
	}

	//The entry doesn't belong to an existing child node, now we
	//determine if it belong on this node, or on a new child node.
	if(entry->getClassCount() > depth + 1) {
		ResourceTreeNode* newnode = new ResourceTreeNode(entry->getType(), entry->getClass(depth), depth + 1);
		nodes.add(newnode);
		newnode->addEntry(entry);
	} else {
		entry->setMyNode(this);
		entries.add(entry);
	}
}

ResourceTreeEntry* ResourceTreeNode::getEntry(ResourceTreeEntry* entry,
		const String& type, const bool random) {

	if (entry != NULL)
		return entry;

	for(int i = 0; i < entries.size(); ++i) {
		ResourceTreeEntry* ent = entries.get(i);
		if(ent->getType() == type && !random)
			return ent;
		else if(ent->getType() == type && random)
			return getRandomEntry(type);
	}

	for(int i = 0; i < nodes.size(); ++i) {
		ResourceTreeNode* node = nodes.get(i);
		entry = node->getEntry(entry, type, random);
	}

	return entry;
}

ResourceTreeEntry* ResourceTreeNode::getRandomEntry(const String& type) {
	Vector<ResourceTreeEntry*> candidates;

	for(int i = 0; i < nodes.size(); ++i) {
		ResourceTreeNode* node = nodes.get(i);
		if(node->getType() == type) {
			node->getEntryPool(candidates);
			break;
		}
	}
}

void ResourceTreeNode::getEntryPool(Vector<ResourceTreeEntry*>& candidates) {
	for(int i = 0; i < entries.size(); ++i) {
		ResourceTreeEntry* ent = entries.get(i);
		candidates.add(ent);
		System::out << "Added " << ent->getType() << endl;
	}

	for(int i = 0; i < nodes.size(); ++i) {
		ResourceTreeNode* node = nodes.get(i);
		node->getEntryPool(candidates);
	}
}

void ResourceTreeNode::toString() {
	System::out << "--- Node " << depth << " : " << nodeClass << "---" << endl;

	System::out << "NODES" << endl;
	for(int i = 0; i < nodes.size(); ++i)
		System::out << nodes.get(i)->getNodeClass() << endl;

	System::out << "ENTRIES" << endl;
	for(int i = 0; i < entries.size(); ++i)
		System::out << entries.get(i)->getType() << endl;

	for(int i = 0; i < nodes.size(); ++i)
		nodes.get(i)->toString();
}
