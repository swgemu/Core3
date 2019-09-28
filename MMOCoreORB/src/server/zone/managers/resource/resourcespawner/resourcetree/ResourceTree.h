/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file ResourceTree.h
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#pragma once

#include "ResourceTreeNode.h"
#include "ResourceTreeEntry.h"

/**
 * The ResourceTree class is a representation of the
 * resource_tree table in the datatable
 */

class ResourceSpawner;

class ResourceTree : public Logger {
private:

	/// The tree's base node
	ResourceTreeNode* baseNode;

	/// Resource Spawner object
	ResourceSpawner* spawner;

public:
	/**
	 * Constructor
	 */
	ResourceTree(ResourceSpawner* spawn);

	/**
	 * Destructor
	 */
	~ResourceTree();

	/**
	 * Locates 'type' in Tree
	 * \param type Resource Type
	 * \param Excludes Vector of items that can't be chosen
	 * \param zoneid If the resource is tied to a certain zone
	 */
	const ResourceTreeEntry* getEntry(const String& type,
			const Vector<String>& excludes = 0,  const String& zoneName = "") const;

	ResourceTreeNode* getBaseNode() {
		return baseNode;
	}

	const ResourceTreeNode* getBaseNode() const {
		return baseNode;
	}

	/**
	 * Prints the tree
	 */
	void toString() const;

private:
	/*
	 * Loads tree from database
	 */
	bool buildTreeFromClient();

	/*
	 * Sets Zone restriction
	 */
	void setZoneRestriction(ResourceTreeEntry* entry);

	/*
	 * Sets if resource is from JTL
	 */
	void setJtl(ResourceTreeEntry* entry);

	/*
	 * Sets the survey tool type
	 */
	void setSurveyToolType(ResourceTreeEntry* entry);

	/*
	 * Sets the recycle tool type and sub type
	 */
	void setRecycleToolType(ResourceTreeEntry* entry);

};

