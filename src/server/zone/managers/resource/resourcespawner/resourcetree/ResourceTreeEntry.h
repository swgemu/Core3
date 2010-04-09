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

class ResourceTreeEntry {

	String name;

	String class1;
	String class2;
	String class3;
	String class4;
	String class5;
	String class6;
	String class7;

	int maxtype;
	int mintype;
	int minpool;
	int maxpool;

	bool recycled;

	String att1;
	int att1min;
	int att1max;

	String att2;
	int att2min;
	int att2max;

	String att3;
	int att3min;
	int att3max;

	String att4;
	int att4min;
	int att4max;

	String att5;
	int att5min;
	int att5max;

	String att6;
	int att6min;
	int att6max;

	String att7;
	int att7min;
	int att7max;

	String att8;
	int att8min;
	int att8max;

	String att9;
	int att9min;
	int att9max;

	String att10;
	int att10min;
	int att10max;

	String att11;
	int att11min;
	int att11max;

	String resourceContainerType;
	uint32 resourceContainerTypeCRC;
	String randomNameClass;
	float weight;


public:
	ResourceTreeEntry(const String& inType) {
		name = inType;

		class1 = "";
		class2 = "";
		class3 = "";
		class4 = "";
		class5 = "";
		class6 = "";
		class7 = "";

		maxtype = 0;
		mintype = 0;
		minpool = 0;
		maxpool = 0;

		att1 = "";
		att1min = 0;
		att1max = 1000;

		att2 = "";
		att2min = 0;
		att2max = 1000;

		att3 = "";
		att3min = 0;
		att3max = 1000;

		att4 = "";
		att4min = 0;
		att4max = 1000;

		att5 = "";
		att5min = 0;
		att5max = 1000;

		att6 = "";
		att6min = 0;
		att6max = 1000;

		att7 = "";
		att7min = 0;
		att7max = 1000;

		att8 = "";
		att8min = 0;
		att8max = 1000;

		att9 = "";
		att9min = 0;
		att9max = 1000;

		att10 = "";
		att10min = 0;
		att10max = 1000;

		att11 = "";
		att11min = 0;
		att11max = 1000;

		resourceContainerType = "";
		randomNameClass = "";

	}

	~ResourceTreeEntry() {

	}

    String getAtt1() const
    {
        return att1;
    }

    String getAtt10() const
    {
        return att10;
    }

    int getAtt10max() const
    {
        return att10max;
    }

    int getAtt10min() const
    {
        return att10min;
    }

    String getAtt11() const
    {
        return att11;
    }

    int getAtt11max() const
    {
        return att11max;
    }

    int getAtt11min() const
    {
        return att11min;
    }

    int getAtt1max() const
    {
        return att1max;
    }

    int getAtt1min() const
    {
        return att1min;
    }

    String getAtt2() const
    {
        return att2;
    }

    int getAtt2max() const
    {
        return att2max;
    }

    int getAtt2min() const
    {
        return att2min;
    }

    String getAtt3() const
    {
        return att3;
    }

    int getAtt3max() const
    {
        return att3max;
    }

    int getAtt3min() const
    {
        return att3min;
    }

    String getAtt4() const
    {
        return att4;
    }

    int getAtt4max() const
    {
        return att4max;
    }

    int getAtt4min() const
    {
        return att4min;
    }

    String getAtt5() const
    {
        return att5;
    }

    int getAtt5max() const
    {
        return att5max;
    }

    int getAtt5min() const
    {
        return att5min;
    }

    String getAtt6() const
    {
        return att6;
    }

    int getAtt6max() const
    {
        return att6max;
    }

    int getAtt6min() const
    {
        return att6min;
    }

    String getAtt7() const
    {
        return att7;
    }

    int getAtt7max() const
    {
        return att7max;
    }

    int getAtt7min() const
    {
        return att7min;
    }

    String getAtt8() const
    {
        return att8;
    }

    int getAtt8max() const
    {
        return att8max;
    }

    int getAtt8min() const
    {
        return att8min;
    }

    String getAtt9() const
    {
        return att9;
    }

    int getAtt9max() const
    {
        return att9max;
    }

    int getAtt9min() const
    {
        return att9min;
    }

    String getClass1() const
    {
        return class1;
    }

    String getClass2() const
    {
        return class2;
    }

    String getClass3() const
    {
        return class3;
    }

    String getClass4() const
    {
        return class4;
    }

    String getClass5() const
    {
        return class5;
    }

    String getClass6() const
    {
        return class6;
    }

    String getClass7() const
    {
        return class7;
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

    void setAtt1(String att1)
    {
        this->att1 = att1;
    }

    void setAtt10(String att10)
    {
        this->att10 = att10;
    }

    void setAtt10max(int att10max)
    {
        this->att10max = att10max;
    }

    void setAtt10min(int att10min)
    {
        this->att10min = att10min;
    }

    void setAtt11(String att11)
    {
        this->att11 = att11;
    }

    void setAtt11max(int att11max)
    {
        this->att11max = att11max;
    }

    void setAtt11min(int att11min)
    {
        this->att11min = att11min;
    }

    void setAtt1max(int att1max)
    {
        this->att1max = att1max;
    }

    void setAtt1min(int att1min)
    {
        this->att1min = att1min;
    }

    void setAtt2(String att2)
    {
        this->att2 = att2;
    }

    void setAtt2max(int att2max)
    {
        this->att2max = att2max;
    }

    void setAtt2min(int att2min)
    {
        this->att2min = att2min;
    }

    void setAtt3(String att3)
    {
        this->att3 = att3;
    }

    void setAtt3max(int att3max)
    {
        this->att3max = att3max;
    }

    void setAtt3min(int att3min)
    {
        this->att3min = att3min;
    }

    void setAtt4(String att4)
    {
        this->att4 = att4;
    }

    void setAtt4max(int att4max)
    {
        this->att4max = att4max;
    }

    void setAtt4min(int att4min)
    {
        this->att4min = att4min;
    }

    void setAtt5(String att5)
    {
        this->att5 = att5;
    }

    void setAtt5max(int att5max)
    {
        this->att5max = att5max;
    }

    void setAtt5min(int att5min)
    {
        this->att5min = att5min;
    }

    void setAtt6(String att6)
    {
        this->att6 = att6;
    }

    void setAtt6max(int att6max)
    {
        this->att6max = att6max;
    }

    void setAtt6min(int att6min)
    {
        this->att6min = att6min;
    }

    void setAtt7(String att7)
    {
        this->att7 = att7;
    }

    void setAtt7max(int att7max)
    {
        this->att7max = att7max;
    }

    void setAtt7min(int att7min)
    {
        this->att7min = att7min;
    }

    void setAtt8(String att8)
    {
        this->att8 = att8;
    }

    void setAtt8max(int att8max)
    {
        this->att8max = att8max;
    }

    void setAtt8min(int att8min)
    {
        this->att8min = att8min;
    }

    void setAtt9(String att9)
    {
        this->att9 = att9;
    }

    void setAtt9max(int att9max)
    {
        this->att9max = att9max;
    }

    void setAtt9min(int att9min)
    {
        this->att9min = att9min;
    }

    void setClass1(String class1)
    {
        this->class1 = class1;
    }

    void setClass2(String class2)
    {
        this->class2 = class2;
    }

    void setClass3(String class3)
    {
        this->class3 = class3;
    }

    void setClass4(String class4)
    {
        this->class4 = class4;
    }

    void setClass5(String class5)
    {
        this->class5 = class5;
    }

    void setClass6(String class6)
    {
        this->class6 = class6;
    }

    void setClass7(String class7)
    {
        this->class7 = class7;
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
		System::out << "Class1 = " << class1 << endl;
		System::out << "Class2 = " << class2 << endl;
		System::out << "Class3 = " << class3 << endl;
		System::out << "Class4 = " << class4 << endl;
		System::out << "Class5 = " << class5 << endl;
		System::out << "Class6 = " << class6 << endl;
		System::out << "Class7 = " << class7 << endl;

		System::out << "Max Types = " << maxtype << endl;
		System::out << "Min Types = " << mintype << endl;
		System::out << "Min Pools = " << minpool << endl;
		System::out << "Max Pools = " << maxpool << endl;

		if(att1 != "")
			System::out << att1 << ": " << att1min << " - " << att1max<< endl;
		if(att2 != "")
			System::out << att2 << ": " << att2min << " - " << att2max<< endl;
		if(att3 != "")
			System::out << att3 << ": " << att3min << " - " << att3max<< endl;
		if(att4 != "")
			System::out << att4 << ": " << att4min << " - " << att4max<< endl;
		if(att5 != "")
			System::out << att5 << ": " << att5min << " - " << att5max<< endl;
		if(att6 != "")
			System::out << att6 << ": " << att6min << " - " << att6max<< endl;
		if(att7 != "")
			System::out << att7 << ": " << att7min << " - " << att7max<< endl;
		if(att8 != "")
			System::out << att8 << ": " << att8min << " - " << att8max<< endl;
		if(att9 != "")
			System::out << att9 << ": " << att9min << " - " << att9max<< endl;
		if(att10 != "")
			System::out << att10 << ": " << att10min << " - " << att10max<< endl;
		if(att11 != "")
			System::out << att11 << ": " << att11min << " - " << att11max<< endl;


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
