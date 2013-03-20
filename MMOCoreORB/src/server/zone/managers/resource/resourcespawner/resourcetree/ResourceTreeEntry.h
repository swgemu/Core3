/*
Copyright (C) 2010 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
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
 * \file ResourceTreeEntry.h
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#ifndef RESOURCETREEENTRY_H_
#define RESOURCETREEENTRY_H_

#include "engine/engine.h"
#include "ResourceAttribute.h"
#include "ResourceTreeNode.h"

/**
 * The ResourceTreeEntry class represents an
 * entry on the ResourceTree node tree
 */
class ResourceTreeNode;

class ResourceTreeEntry {
private:

	/// Node that this entry is on
	ResourceTreeNode* myNode;

	/// Stf type
	String type;

	/// List of Class names in plain english Format
	Vector<String> classList;

	/// List of Class names in swg stfname
	Vector<String> stfClassList;

	/// List of Attributes
	VectorMap<String, ResourceAttribute* > attributeMap;

	/// Maximum of this type that can spawn
	int maxtype;
	/// Minimum of this type that can spawn
	int mintype;

	/// Minimum number of resource pools this spawns in
	int minpool;

	/// Maximum number of resource pools this spawns in
	int maxpool;

	/// If type is a recycled type
	bool recycled;

	/// Notates if this entry has children
	bool children;

	/// Notates id this resource is restricted to a zone
	String zoneRestriction;

	/// Lets us know if this resource was a JTL resource
	bool jtl;

	/// The script that explains the resource container type
	String resourceContainerType;

	/// Unused, but in the resource tree
	String randomNameClass;

	/// The type of survey tool that can survey this
	int surveyToolType;

	/// The recyler setting that can recycle this
	int recycleToolType;

	/// CRC of resourceContainerType
	uint32 containerCRC;

public:
	/**
	 * Constructor
	 * \param inType The type of resource this in in stfname
	 */
	ResourceTreeEntry(const String& inType) {
		type = inType;

		recycled = false;
		children = false;
		jtl = false;

		maxtype = 0;
		mintype = 0;
		minpool = 0;
		maxpool = 0;

		resourceContainerType = "";
		randomNameClass = "";

		zoneRestriction = "";

		surveyToolType = -1;

		recycleToolType = -1;

		containerCRC = 0;

		attributeMap.setNullValue(NULL);
	}

	/**
	 * Deconstructor
	 */
	~ResourceTreeEntry() {
		classList.removeAll();
		stfClassList.removeAll();
		for(int i = 0; i < attributeMap.size(); ++i)
			delete attributeMap.get(i);
	}

	/**
	 * Sets the node this entry is on
	 * \param node Tree Node
	 */
	void setMyNode(ResourceTreeNode* node) {
		myNode = node;
	}

	/**
	 * Gets the node this entry is on
	 * \return Node this entry is on
	 */
	ResourceTreeNode* getMyNode() {
		return myNode;
	}

	/**
	 * Adds class to classList
	 * \param newclass New class string to add
	 */
	void addClass(const String newclass) {
		classList.add(newclass);
	}

	/**
	 * Adds stfClass to stfClassList
	 * \param newclass New class string to add
	 */
	void addStfClass(const String newclass) {

		stfClassList.add(newclass);
	}

	/**
	 * Gets class based in Vector index
	 * \param index index
	 * \return Class at index
	 */
	String getClass(const int index) {
		if(index <= classList.size())
			return classList.get(index);
		else
			return "";
	}

	/**
	 * Gets stfClass based on vector index
	 * \param index index
	 * \return StfClass at index
	 */
	String getStfClass(const int index) {
		if(index <= stfClassList.size())
			return stfClassList.get(index);
		else
			return "";
	}

	/**
	 * Gets size on classList
	 * \return classList size
	 */
	int getClassCount() {
		return classList.size();
	}

	/**
	 * Gets size of stfClassList
	 * \return stfClassList size
	 */
	int getStfClassCount() {
		return stfClassList.size();
	}

	/**
	 * Gets the Final Class name
	 * \return Final name of entry
	 */
	String getFinalClass() {
		if(classList.size() > 0)
			return classList.get(classList.size() - 1);
		else
			return "";
	}

	/**
	 * Denotes if entry is organic
	 * \return Is value organic
	 */
	bool isOrganic() {
		if(classList.size() > 0)
			return classList.get(0) == "Organic";
		else
			return false;
	}

	/**
	 * Adds an attribute to this entry
	 * \param attrib ResourceAttribute to add
	 */
	void addAttribute(ResourceAttribute* attrib) {
		attributeMap.put(attrib->getName(), attrib);
	}

	/**
	 * Gets attribute
	 * \param index index of attribute
	 * \return ResourceAttibute at index
	 */
	ResourceAttribute* getAttribute(const String& attrib) {
		return attributeMap.get(attrib);
	}

	/**
	 * Gets attribute
	 * \param index index of attribute
	 * \return ResourceAttibute at index
	 */
	ResourceAttribute* getAttribute(const int index) {
		return attributeMap.get(index);
	}

	/**
	 * Gets number of attributes
	 * \return Number of attributes
	 */
	int getAttributeCount() {
		return attributeMap.size();
	}

	/**
	 * Gets maxpool
	 * \return maxpool
	 */
    int getMaxpool() const
    {
        return maxpool;
    }

	/**
	 * Gets maxtype
	 * \return maxtype
	 */
    int getMaxtype() const
    {
        return maxtype;
    }

	/**
	 * Gets minpool
	 * \return minpool
	 */
    int getMinpool() const
    {
        return minpool;
    }

	/**
	 * Gets mintype
	 * \return mintype
	 */
    int getMintype() const
    {
        return mintype;
    }

	/**
	 * Gets type
	 * \return type
	 */
    String getType() const
    {
        return type;
    }

	/**
	 * Gets randomNameClass
	 * \return randomNameClass
	 */
    String getRandomNameClass() const
    {
        return randomNameClass;
    }

	/**
	 * Gets zoneRestriction
	 * \return zoneRestriction
	 */
    String& getZoneRestriction() {
    	return zoneRestriction;
    }

	/**
	 * Gets recycled
	 * \return recycled
	 */
    bool isRecycled() const
    {
        return recycled == true;
    }

	/**
	 * Gets resourceContainerType
	 * \return resourceContainerType
	 */
    String getResourceContainerType() const
    {
        return resourceContainerType;
    }

    /**
     * sets maxpool
     * \param maxpool
     */
    void setMaxpool(int maxpool)
    {
        this->maxpool = maxpool;
    }

    /**
     * sets maxtype
     * \param maxtype
     */
    void setMaxtype(int maxtype)
    {
        this->maxtype = maxtype;
    }

    /**
     * sets minpool
     * \param minpool
     */
    void setMinpool(int minpool)
    {
        this->minpool = minpool;
    }

    /**
     * sets mintype
     * \param mintype
     */
    void setMintype(int mintype)
    {
        this->mintype = mintype;
    }

    /**
     * sets type
     * \param type
     */
    void setType(String name)
    {
        this->type = name;
    }

    /**
      * sets randomNameClass
      * \param randomNameClass
      */
    void setRandomNameClass(String randomNameClass)
    {
        this->randomNameClass = randomNameClass;
    }

    /**
      * sets recycled
      * \param recycled
      */
    void setRecycled(bool recycled)
    {
        this->recycled = recycled;
    }

    /**
      * sets resourceContainerType
      * \param resourceContainerType
      */
    void setResourceContainerType(String resourceContainerType)
    {
        this->resourceContainerType = resourceContainerType;
        containerCRC = resourceContainerType.hashCode();
    }

    /**
      * Does entry have children
      * \return children
      */
    bool hasChildren() {
    	return children;
    }

    /**
      * sets children
      * \param child
      */
    void setChildren(bool child) {
    	children = child;
    }

    /**
      * sets zoneRestriction
      * \param zone
      */
    void setZoneRestriction(String zone) {
    	zoneRestriction = zone;
    }

    /**
      * Lets us know if it is zonerestricted type
      * \return isZoneRestricted
      */
    bool isZoneRestricted() {
    	return zoneRestriction != "";
    }

    /**
      * sets jtl
      * \param j
      */
    void setJTL(bool j) {
    	jtl = j;
    }

    /**
      * Is JTL?
      * \return is Jtl resource
      */
    bool isJTL() {
    	return jtl;
    }

    /**
     * Sets surveyToolType
     * \param type
     */
    void setSurveyToolType(int type) {
    	surveyToolType = type;
    }

    /**
     * Gets surveyToolType
     * \return surveyToolType
     */
    int getSurveyToolType() {
    	return surveyToolType;
    }

    /**
     * Sets recycleToolType
     * \param type
     */
    void setRecycleToolType(int type) {
    	recycleToolType = type;
    }

    /**
     * Gets recycleToolType
     * \return recycleToolType
     */
    int getRecycleToolType() {
    	return recycleToolType;
    }

    /**
      * Gets containerCRC
      * \return containerCRC
      */
    uint32 getContainerCRC() {
    	return containerCRC;
    }

    /**
     * Tells us is Entry if of type
     * \param type
     */
	bool isType(String type) {
		for (int i = 0; i < stfClassList.size(); ++i) {

			if (stfClassList.get(i) == type)
				return true;
		}
		for (int i = 0; i < classList.size(); ++i) {

			if (classList.get(i) == type)
				return true;
		}
		return false;
	}

	/**
	 * Outputs visual representation of class
	 */
	void toString(){

		System::out << "************ Resource Tree Entry ********************\n";
		System::out << "Type = " << type << endl;
		for(int i = 0; i < classList.size(); ++i)
			System::out << "Class" << i << " = " << classList.get(i) << endl;

		for(int i = 0; i < stfClassList.size(); ++i)
			System::out << "STFClass" << i << " = " << stfClassList.get(i) << endl;


		System::out << "Max Types = " << maxtype << endl;
		System::out << "Min Types = " << mintype << endl;
		System::out << "Min Pools = " << minpool << endl;
		System::out << "Max Pools = " << maxpool << endl;

		for(int i = 0; i < attributeMap.size(); ++i)
			System::out << attributeMap.get(i)->getName() << ": "
			<< attributeMap.get(i)->getMinimum()  << " - "
			<< attributeMap.get(i)->getMaximum() << endl;

		System::out << "Recycled = " << recycled  << endl;
		System::out << "Resource Container Type = " << resourceContainerType  << endl;
		System::out << "Random Name Class = " << randomNameClass  << endl;
		System::out << "Zone Restriction = " << zoneRestriction  << endl;
		System::out << "Survey Tool Type = " << surveyToolType  << endl;
	}
};

#endif /*RESOURCETREEENTRY_H_*/
