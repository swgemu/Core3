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

#ifndef RESOURCETREEENTRY_H_
#define RESOURCETREEENTRY_H_

#include "engine/engine.h"
#include "ResourceAttribute.h"

class ResourceTreeEntry {

	String name;

	Vector<String> classList;
	Vector<ResourceAttribute* > attributeList;

	int maxtype;
	int mintype;
	int minpool;
	int maxpool;

	bool recycled;

	String resourceContainerType;
	uint32 resourceContainerTypeCRC;
	String randomNameClass;
	float weight;

public:
	ResourceTreeEntry(const String& inType) {
		name = inType;

		classList.removeAll();
		attributeList.removeAll();

		maxtype = 0;
		mintype = 0;
		minpool = 0;
		maxpool = 0;

		resourceContainerType = "";
		randomNameClass = "";

	}

	~ResourceTreeEntry() {
		classList.removeAll();
		for(int i = 0; i < attributeList.size(); ++i)
			delete attributeList.get(i);
	}

	void addClass(const String newclass) {
		classList.add(newclass);
	}

	String getClass(const int classNum) {
		if(classNum <= classList.size())
			return classList.get(classNum);
		else
			return "";
	}

	int getClassCount() {
		return classList.size();
	}

	String getFinalClass() {
		return classList.get(classList.size());
	}

	void addAttribute(ResourceAttribute* attrib) {
		attributeList.add(attrib);
	}

	ResourceAttribute* getAttribute(const int attribute) {
		if(attribute <= attributeList.size())
			return attributeList.get(attribute);
		else
			return NULL;
	}

    int getMaxpool() const
    {
        return maxpool;
    }

    int getMaxtype() const
    {
        return maxtype;
    }

    int getMinpool() const
    {
        return minpool;
    }

    int getMintype() const
    {
        return mintype;
    }

    String getName() const
    {
        return name;
    }

    String getRandomNameClass() const
    {
        return randomNameClass;
    }

    bool getRecycled() const
    {
        return recycled;
    }

    String getResourceContainerType() const
    {
        return resourceContainerType;
    }

    void setMaxpool(int maxpool)
    {
        this->maxpool = maxpool;
    }

    void setMaxtype(int maxtype)
    {
        this->maxtype = maxtype;
    }

    void setMinpool(int minpool)
    {
        this->minpool = minpool;
    }

    void setMintype(int mintype)
    {
        this->mintype = mintype;
    }

    void setName(String name)
    {
        this->name = name;
    }

    void setRandomNameClass(String randomNameClass)
    {
        this->randomNameClass = randomNameClass;
    }

    void setRecycled(bool recycled)
    {
        this->recycled = recycled;
    }

    void setResourceContainerType(String resourceContainerType)
    {
        this->resourceContainerType = resourceContainerType;
    }


	void toString(){

		System::out << "************ Resource Tree Entry ********************\n";
		System::out << "ENUM = " << name << endl;
		for(int i = 0; i < classList.size(); ++i)
			System::out << "Class" << i << " = " << classList.get(i) << endl;


		System::out << "Max Types = " << maxtype << endl;
		System::out << "Min Types = " << mintype << endl;
		System::out << "Min Pools = " << minpool << endl;
		System::out << "Max Pools = " << maxpool << endl;

		for(int i = 0; i < attributeList.size(); ++i)
			System::out << attributeList.get(i)->getName() << ": "
			<< attributeList.get(i)->getMinimum()  << " - "
			<< attributeList.get(i)->getMaximum() << endl;

		System::out << "Recycled = " << recycled  << endl;
		System::out << "Resource Container Type = " << resourceContainerType  << endl;
		System::out << "Random Name Class = " << randomNameClass  << endl;
	}
    uint32 getResourceContainerTypeCRC() const
    {
        return resourceContainerTypeCRC;
    }

    void setResourceContainerTypeCRC(uint32 resourceContainerTypeCRC)
    {
        this->resourceContainerTypeCRC = resourceContainerTypeCRC;
    }

    float getWeight() const
    {
        return weight;
    }

    void setWeight(float weight)
    {
        this->weight = weight;
    }

};

#endif /*RESOURCETREEENTRY_H_*/
