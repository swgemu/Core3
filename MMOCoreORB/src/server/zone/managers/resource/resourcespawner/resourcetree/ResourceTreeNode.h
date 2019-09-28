/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file ResourceTreeNode.h
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#pragma once

#include "ResourceTreeEntry.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

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

	String getName() const;
	String getStfName() const;

	void setParentNode(ResourceTreeNode* parent);
	ResourceTreeNode* getParentNode();
	const ResourceTreeNode* getParentNode() const;

	void add(ResourceTreeEntry* entry);

	const ResourceTreeEntry* getEntry(const String& type, const Vector<String>& excludes = 0, const String& zoneName = "") const;

	const ResourceTreeEntry* find(const String& type, const ResourceTreeEntry* entry = nullptr) const;
	ResourceTreeEntry* find(const String& type, ResourceTreeEntry* entry = nullptr);
	const ResourceTreeNode* findNode(const String& type, const ResourceTreeNode* node = nullptr) const;
	ResourceTreeNode* findNode(const String& type, ResourceTreeNode* node = nullptr);

	const ResourceTreeEntry* getPlanetSpecificEntry(const String& planet) const;

	void addToSuiListBox(SuiListBox* suil) const;

	//void updateEntries();

	void toString() const;

private:

	void getEntryPool(Vector<ResourceTreeEntry*>& candidates,
			const Vector<String> excludes) const;

};

