/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file ResourceTreeNode.h
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#ifndef RESOURCETREENODE_H_
#define RESOURCETREENODE_H_

#include <stddef.h>
#include <algorithm>

#include "ResourceTreeEntry.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "system/lang/String.h"
#include "system/util/Vector.h"

class ResourceTreeEntry;
namespace server {
namespace zone {
namespace objects {
namespace player {
namespace sui {
namespace listbox {
class SuiListBox;
}  // namespace listbox
}  // namespace sui
}  // namespace player
}  // namespace objects
}  // namespace zone
}  // namespace server

class ResourceTreeNode {
private:
	String name;
	String stfName;
	int maxtype, mintype, maxpool, minpool;

	int depth;
	Vector<ResourceTreeEntry* > entries;
	Vector<ResourceTreeNode* > nodes;

	ResourceTreeNode* parentNode;

public:
	ResourceTreeNode(const String& t, const String& n, const int d);
	~ResourceTreeNode();

	String getName();
	String getStfName();

	void setParentNode(ResourceTreeNode* parent);
	ResourceTreeNode* getParentNode();

	void add(ResourceTreeEntry* entry);

	ResourceTreeEntry* getEntry(const String& type, const Vector<String>& excludes = 0, const String& zoneName = "");

	ResourceTreeEntry* find(const String& type, ResourceTreeEntry* entry = NULL);
	ResourceTreeNode* findNode(const String& type, ResourceTreeNode* node = NULL);

	ResourceTreeEntry* getPlanetSpecificEntry(const String& planet);

	void addToSuiListBox(SuiListBox* suil);

	//void updateEntries();

	void toString();

private:

	void getEntryPool(Vector<ResourceTreeEntry*>& candidates,
			const Vector<String> excludes);

};

#endif /* RESOURCETREENODE_H_ */
