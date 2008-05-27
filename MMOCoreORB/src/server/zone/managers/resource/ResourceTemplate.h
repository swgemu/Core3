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
	
	string resname, restype, class1, class2, class3, class4, class5, class6,
			class7, container, att1, att2, att3, att4, att5, att6, att7, att8,
			att9, att10, att11;
	
	int att1stat, att2stat, att3stat, att4stat, att5stat, att6stat, att7stat,
			att8stat, att9stat, att10stat, att11stat, maxtype, mintype,
			minpool, maxpool, objectSubType;
	
	uint32 containerCRC;
	
	Vector<SpawnLocation*> * spawnLocations;

public:
	ResourceTemplate(const string& inType) {
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
		for(int i = spawnLocations->size() - 1; i >= 0; i--) {
			SpawnLocation* sl = spawnLocations->get(i);
			if (sl->getID() == sid) {
				spawnLocations->remove(i);
				return sl;
			}
		}
		return NULL;
	}

	// setters
	inline void setName(const string& instring) {
		resname = instring;
	}
	
	inline void setClass1(const string& inString) {
		class1 = inString;
	}
	
	inline void setClass2(const string& inString) {
		class2 = inString;
	}
	
	inline void setClass3(const string& inString) {
		class3 = inString;
	}
	
	inline void setClass4(const string& inString) {
		class4 = inString;
	}
	
	inline void setClass5(const string& inString) {
		class5 = inString;
	}
	
	inline void setClass6(const string& inString) {
		class6 = inString;
	}
	
	inline void setClass7(const string& inString) {
		class7 = inString;
	}
	
	inline void setAtt1(const string& inString) {
		att1 = inString;
	}
	
	inline void setAtt2(const string& inString) {
		att2 = inString;
	}
	
	inline void setAtt3(const string& inString) {
		att3 = inString;
	}
	
	inline void setAtt4(const string& inString) {
		att4 = inString;
	}
	
	inline void setAtt5(const string& inString) {
		att5 = inString;
	}
	
	inline void setAtt6(const string& inString) {
		att6 = inString;
	}
	
	inline void setAtt7(const string& inString) {
		att7 = inString;
	}
	
	inline void setAtt8(const string& inString) {
		att8 = inString;
	}
	
	inline void setAtt9(const string& inString) {
		att9 = inString;
	}
	
	inline void setAtt10(const string& inString) {
		att10 = inString;
	}
	
	inline void setAtt11(const string& inString) {
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
	
	inline void setContainer(const string& inString) {
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
	inline string& getName() {
		return resname;
	}
	
	inline string& getType() {
		return restype;
	}
	
	inline string& getClass1() {
		return class1;
	}
	
	inline string& getClass2() {
		return class2;
	}
	
	inline string& getClass3() {
		return class3;
	}
	
	inline string& getClass4() {
		return class4;
	}
	
	inline string& getClass5() {
		return class5;
	}
	
	inline string& getClass6() {
		return class6;
	}
	
	inline string& getClass7() {
		return class7;
	}
	
	inline string& getAtt1() {
		return att1;
	}
	
	inline string& getAtt2() {
		return att2;
	}
	
	inline string& getAtt3() {
		return att3;
	}
	
	inline string& getAtt4() {
		return att4;
	}
	
	inline string& getAtt5() {
		return att5;
	}
	
	inline string& getAtt6() {
		return att6;
	}
	
	inline string& getAtt7() {
		return att7;
	}
	
	inline string& getAtt8() {
		return att8;
	}
	
	inline string& getAtt9() {
		return att9;
	}
	
	inline string& getAtt10() {
		return att10;
	}
	
	inline string& getAtt11() {
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
	
	inline string& getContainer() {
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

};

#endif /*RESOURCETEMPLATE_H_*/
