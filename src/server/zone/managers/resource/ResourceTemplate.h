/*
Copyright (C) 2007 <SWGEmu>

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

#ifndef RESOURCETEMPLATE_H_
#define RESOURCETEMPLATE_H_

#include "engine/engine.h"

#include "SpawnLocation.h"

class ResourceTemplate {
	uint64 rid;

	String resname;
	String restype;
	String class1;
	String class2;
	String class3;
	String class4;
	String class5;
	String class6;
	String class7;
	String container;
	String att1;
	String att2;
	String att3;
	String att4;
	String att5;
	String att6;
	String att7;
	String att8;
	String att9;
	String att10;
	String att11;

	int att1stat;
	int att2stat;
	int att3stat;
	int att4stat;
	int att5stat;
	int att6stat;
	int att7stat;
	int att8stat;
	int att9stat;
	int att10stat;
	int att11stat;
	int maxtype;
	int mintype;

	int minpool;
	int maxpool;
	int objectSubType;

	uint32 containerCRC;

	Vector<SpawnLocation*> * spawnLocations;

public:
	ResourceTemplate(const String& inType) {
		resname = "";
		restype = "";
		class1 = "";
		class2 = "";
		class3 = "";
		class4 = "";
		class5 = "";
		class6 = "";
		class7 = "";
		container = "";
		att1 = "";
		att2 = "";
		att3 = "";
		att4 = "";
		att5 = "";
		att6 = "";
		att7 = "";
		att8 = "";
		att9 = "";
		att10 = "";
		att11 = "";

		att1stat;
		att2stat;
		att3stat;
		att4stat;
		att5stat;
		att6stat;
		att7stat;
		att8stat;
		att9stat;
		att10stat;
		att11stat;
		maxtype;
		mintype;

		minpool;
		maxpool;
		objectSubType;

		restype = inType;
		spawnLocations = new Vector<SpawnLocation*>();
	}

	~ResourceTemplate() {
		if (spawnLocations != NULL) {
			for (int i = 0; i < spawnLocations->size(); ++i)
				delete spawnLocations->get(i);

			delete spawnLocations;

			spawnLocations = NULL;
		}
	}

	bool compare(ResourceTemplate* inResource) {

		StringBuffer error;

		if (resname != inResource->resname)
			error << "resname: " << resname << " != " << inResource->resname
					<< "\n";

		if (restype != inResource->restype)
			error << "restype: " << restype << " != " << inResource->restype
					<< "\n";

		if (class1 != inResource->class1)
			error << "class1: " << class1 << " != " << inResource->class1
					<< "\n";

		if (class2 != inResource->class2)
			error << "class2: " << class2 << " != " << inResource->class2
					<< "\n";

		if (class3 != inResource->class3)
			error << "class3: " << class3 << " != " << inResource->class3
					<< "\n";

		if (class4 != inResource->class4)
			error << "class4: " << class4 << " != " << inResource->class4
					<< "\n";

		if (class5 != inResource->class5)
			error << "class5: " << class5 << " != " << inResource->class5
					<< "\n";

		if (class6 != inResource->class6)
			error << "class6: " << class6 << " != " << inResource->class6
					<< "\n";

		if (class7 != inResource->class7)
			error << "class7: " << class7 << " != " << inResource->class7
					<< "\n";

		if (container != inResource->container)
			error << "container: " << container << " != "
					<< inResource->container << "\n";

		if ((att1 != inResource->att1) && !att1.isEmpty())
			error << "att1: " << att1 << " != " << inResource->att1 << "\n";

		if ((att2 != inResource->att2) && !att2.isEmpty())
			error << "att2: " << att2 << " != " << inResource->att2 << "\n";

		if ((att3 != inResource->att3) && !att3.isEmpty())
			error << "att3: " << att3 << " != " << inResource->att3 << "\n";

		if ((att4 != inResource->att4) && !att4.isEmpty())
			error << "att4: " << att4 << " != " << inResource->att4 << "\n";

		if ((att5 != inResource->att5) && !att5.isEmpty())
			error << "att5: " << att5 << " != " << inResource->att5 << "\n";

		if ((att6 != inResource->att6) && !att6.isEmpty())
			error << "att6: " << att6 << " != " << inResource->att6 << "\n";

		if ((att7 != inResource->att7) && !att7.isEmpty())
			error << "att7: " << att7 << " != " << inResource->att7 << "\n";

		if ((att8 != inResource->att8) && !att8.isEmpty())
			error << "att8: " << att8 << " != " << inResource->att8 << "\n";

		if ((att9 != inResource->att9) && !att9.isEmpty())
			error << "att9: " << att9 << " != " << inResource->att9 << "\n";

		if ((att10 != inResource->att10) && !att10.isEmpty())
			error << "att10: " << att10 << " != " << inResource->att10 << "\n";

		if ((att11 != inResource->att11) && !att11.isEmpty())
			error << "att11: " << att11 << " != " << inResource->att11 << "\n";

		if (((att1stat != inResource->att1stat) && att1stat != 0))
			error << "att1stat: " << att1stat << " != " << inResource->att1stat
					<< "\n";

		if (((att2stat != inResource->att2stat) && att2stat != 0))
			error << "att2stat: " << att2stat << " != " << inResource->att2stat
					<< "\n";

		if (((att3stat != inResource->att3stat) && att3stat != 0))
			error << "att3stat: " << att3stat << " != " << inResource->att3stat
					<< "\n";

		if (((att4stat != inResource->att4stat) && att4stat != 0))
			error << "att4stat: " << att4stat << " != " << inResource->att4stat
					<< "\n";

		if (((att5stat != inResource->att5stat) && att5stat != 0))
			error << "att5stat: " << att5stat << " != " << inResource->att5stat
					<< "\n";

		if (((att6stat != inResource->att6stat) && att6stat != 0))
			error << "att6stat: " << att6stat << " != " << inResource->att6stat
					<< "\n";

		if (((att7stat != inResource->att7stat) && att7stat != 0))
			error << "att7stat: " << att7stat << " != " << inResource->att7stat
					<< "\n";

		if (((att8stat != inResource->att8stat) && att7stat != 0))
			error << "att7stat: " << att7stat << " != " << inResource->att7stat
					<< "\n";

		if (((att9stat != inResource->att9stat) && att9stat != 0))
			error << "att9stat: " << att9stat << " != " << inResource->att9stat
					<< "\n";

		if (((att10stat != inResource->att10stat) && att10stat != 0))
			error << "att10stat: " << att10stat << " != "
					<< inResource->att10stat << "\n";

		if (((att11stat != inResource->att11stat) && att11stat != 0))
			error << "att11stat: " << att11stat << " != "
					<< inResource->att11stat << "\n";

		if (objectSubType != inResource->objectSubType)
			error << "objectSubType: " << hex << objectSubType << " != "
					<< inResource->objectSubType << "\n";

		if (containerCRC != inResource->containerCRC)
			error << "containerCRC: " << containerCRC << " != " << inResource->containerCRC << dec << "\n";

		if (error.toString() == "") {
			return true;
		} else {
			System::out << error.toString();
			return false;
		}

	}

	// Spawn Stuff
	inline SpawnLocation* getSpawn(int i) {
		return spawnLocations->get(i);
	}

	inline int getSpawnSize() {
		return spawnLocations->size();
	}

	inline void addSpawn(SpawnLocation* sl) {
		spawnLocations->add(sl);
	}

	inline SpawnLocation* removeSpawn(int sid) {
		for (int i = spawnLocations->size() - 1; i >= 0; i--) {
			SpawnLocation* sl = spawnLocations->get(i);
			if (sl->getID() == sid) {
				spawnLocations->remove(i);
				return sl;
			}
		}
		return NULL;
	}

	// setters
	inline void setName(const String& inString) {
		resname = inString;
	}

	inline void setClass1(const String& inString) {
		class1 = inString;
	}

	inline void setClass2(const String& inString) {
		class2 = inString;
	}

	inline void setClass3(const String& inString) {
		class3 = inString;
	}

	inline void setClass4(const String& inString) {
		class4 = inString;
	}

	inline void setClass5(const String& inString) {
		class5 = inString;
	}

	inline void setClass6(const String& inString) {
		class6 = inString;
	}

	inline void setClass7(const String& inString) {
		class7 = inString;
	}

	inline void setAtt1(const String& inString) {
		att1 = inString;
	}

	inline void setAtt2(const String& inString) {
		att2 = inString;
	}

	inline void setAtt3(const String& inString) {
		att3 = inString;
	}

	inline void setAtt4(const String& inString) {
		att4 = inString;
	}

	inline void setAtt5(const String& inString) {
		att5 = inString;
	}

	inline void setAtt6(const String& inString) {
		att6 = inString;
	}

	inline void setAtt7(const String& inString) {
		att7 = inString;
	}

	inline void setAtt8(const String& inString) {
		att8 = inString;
	}

	inline void setAtt9(const String& inString) {
		att9 = inString;
	}

	inline void setAtt10(const String& inString) {
		att10 = inString;
	}

	inline void setAtt11(const String& inString) {
		att11 = inString;
	}

	inline void setAtt1Stat(int inInt) {
		att1stat = inInt;
	}

	inline void setAtt2Stat(int inInt) {
		att2stat = inInt;
	}

	inline void setAtt3Stat(int inInt) {
		att3stat = inInt;
	}

	inline void setAtt4Stat(int inInt) {
		att4stat = inInt;
	}

	inline void setAtt5Stat(int inInt) {
		att5stat = inInt;
	}

	inline void setAtt6Stat(int inInt) {
		att6stat = inInt;
	}

	inline void setAtt7Stat(int inInt) {
		att7stat = inInt;
	}

	inline void setAtt8Stat(int inInt) {
		att8stat = inInt;
	}

	inline void setAtt9Stat(int inInt) {
		att9stat = inInt;
	}

	inline void setAtt10Stat(int inInt) {
		att10stat = inInt;
	}

	inline void setAtt11Stat(int inInt) {
		att11stat = inInt;
	}

	inline void setMaxType(int inInt) {
		maxtype = inInt;
	}

	inline void setMinType(int inInt) {
		mintype = inInt;
	}

	inline void setMaxPool(int inInt) {
		maxpool = inInt;
	}

	inline void setMinPool(int inInt) {
		minpool = inInt;
	}

	inline void setContainer(const String& inString) {
		container  = inString;
	}

	inline void setContainerCRC(uint32 inCRC) {
		containerCRC = inCRC;
	}

	inline void setResourceID(uint64 inID) {
		rid = inID;
	}

	inline void setObjectSubType(int subType) {
		objectSubType = subType;
	}

	// getters
	inline String& getName() {
		return resname;
	}

	inline String& getType() {
		return restype;
	}

	inline String& getClass1() {
		return class1;
	}

	inline String& getClass2() {
		return class2;
	}

	inline String& getClass3() {
		return class3;
	}

	inline String& getClass4() {
		return class4;
	}

	inline String& getClass5() {
		return class5;
	}

	inline String& getClass6() {
		return class6;
	}

	inline String& getClass7() {
		return class7;
	}

	inline String& getAtt1() {
		return att1;
	}

	inline String& getAtt2() {
		return att2;
	}

	inline String& getAtt3() {
		return att3;
	}

	inline String& getAtt4() {
		return att4;
	}

	inline String& getAtt5() {
		return att5;
	}

	inline String& getAtt6() {
		return att6;
	}

	inline String& getAtt7() {
		return att7;
	}

	inline String& getAtt8() {
		return att8;
	}

	inline String& getAtt9() {
		return att9;
	}

	inline String& getAtt10() {
		return att10;
	}

	inline String& getAtt11() {
		return att11;
	}

	inline int getAtt1Stat() {
		return att1stat;
	}

	inline int getAtt2Stat() {
		return att2stat;
	}

	inline int getAtt3Stat() {
		return att3stat;
	}

	inline int getAtt4Stat() {
		return att4stat;
	}

	inline int getAtt5Stat() {
		return att5stat;
	}

	inline int getAtt6Stat() {
		return att6stat;
	}

	inline int getAtt7Stat() {
		return att7stat;
	}

	inline int getAtt8Stat() {
		return att8stat;
	}

	inline int getAtt9Stat() {
		return att9stat;
	}

	inline int getAtt10Stat() {
		return att10stat;
	}

	inline int getAtt11Stat() {
		return att11stat;
	}

	inline int getMaxType() {
		return maxtype;
	}

	inline int getMinType() {
		return mintype;
	}

	inline int getMaxPool() {
		return maxpool;
	}

	inline int getMinPool() {
		return minpool;
	}

	inline String& getContainer() {
		return container;
	}

	inline uint32 getContainerCRC() {
		return containerCRC;
	}

	inline uint64 getResourceID() {
		return rid;
	}

	inline int getObjectSubType() {
		return objectSubType;
	}

	void toString(){

		System::out << "************ Resource Template ********************\n";
		System::out << "Resource ID = " << rid << endl;

		System::out << "Resource ID = " << resname << endl;
		System::out << "Resource Type = " << restype << endl;
		System::out << "Class1 = " << class1 << endl;
		System::out << "Class2 = " << class2 << endl;
		System::out << "Class3 = " << class3 << endl;
		System::out << "Class4 = " << class4 << endl;
		System::out << "Class5 = " << class5 << endl;
		System::out << "Class6 = " << class6 << endl;
		System::out << "Class7 = " << class7 << endl;
		System::out << "Container = " << container << endl;
		System::out << att1 << " = " << att1stat << endl;
		System::out << att2 << " = " << att2stat << endl;
		System::out << att3 << " = " << att3stat << endl;
		System::out << att4 << " = " << att4stat << endl;
		System::out << att5 << " = " << att5stat << endl;
		System::out << att6 << " = " << att6stat << endl;
		System::out << att7 << " = " << att7stat << endl;
		System::out << att8 << " = " << att8stat << endl;
		System::out << att9 << " = " << att9stat << endl;
		System::out << att10 << " = " << att10stat << endl;
		System::out << att11 << " = " << att11stat << endl;

		System::out << "Subtype = " << objectSubType  << endl;
		System::out << "containerCRC = " << containerCRC  << endl;

	}

};

#endif /*RESOURCETEMPLATE_H_*/
