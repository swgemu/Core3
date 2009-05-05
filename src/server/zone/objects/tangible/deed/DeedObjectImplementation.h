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

#ifndef DEEDOBJECTIMPLEMENTATION_H_
#define DEEDOBJECTIMPLEMENTATION_H_

#include "DeedObject.h"

class DeedObjectImplementation : public DeedObjectServant {
protected:
	String targetStfFile;
	String targetStfName;
	String targetObjectFile;
	UnicodeString targetCustomName;

	uint32 targetObjectType;
	uint32 targetObjectSubType;

	void init();

public:
	DeedObjectImplementation(uint64 objid, uint32 objcrc, const UnicodeString& customname, const String& stfname);
	DeedObjectImplementation(CreatureObject* creature, uint32 objcrc, const UnicodeString& customname, const String& stfname);
	DeedObjectImplementation(uint64 objid);

	~DeedObjectImplementation();

	int useObject(Player * player);

	virtual SceneObject* generateObject(Player* player);

	void generateAttributes(SceneObject* obj);

	virtual void parseItemAttributes();
	virtual void addAttributes(AttributeListMessage* alm);
	void addHeaderAttributes(AttributeListMessage* alm);

	//Setters
	inline void setTargetStfFile(const String& stffile) {
		targetStfFile = stffile;
		String attr("targetStfFile");
		itemAttributes->setStringAttribute(attr, targetStfFile);
	}

	inline void setTargetStfName(const String& stfname) {
		targetStfName = stfname;
		String attr("targetStfName");
		itemAttributes->setStringAttribute(attr, targetStfName);
	}

	inline void setTargetObjectFile(const String& objfile) {
		targetObjectFile = objfile;
		String attr("targetObjectFile");
		itemAttributes->setStringAttribute(attr, targetObjectFile);
	}

	inline void setTargetCustomName(const UnicodeString& customname) {
		targetCustomName = customname;
		String attr("targetCustomName");
		String strname = targetCustomName.toString();
		itemAttributes->setStringAttribute(attr, strname);
	}

	inline void setTargetObjectType(uint32 type) {
		targetObjectType = type;
		String attr("targetObjectType");
		itemAttributes->setIntAttribute(attr, targetObjectType);
	}

	inline void setTargetObjectSubType(uint32 subtype) {
		targetObjectSubType = subtype;
		String attr("targetObjectSubType");
		itemAttributes->setIntAttribute(attr, targetObjectSubType);
	}

	//Getters
	inline String& getTargetStfFile() {
		return targetStfFile;
	}

	inline String& getTargetStfName() {
		return targetStfName;
	}

	inline String& getTargetObjectFile() {
		return targetObjectFile;
	}

	inline UnicodeString& getTargetCustomName() {
		return targetCustomName;
	}

	inline uint32 getTargetObjectCRC() {
		return targetObjectFile.hashCode();
	}

	inline uint32 getTargetObjectType() {
		return targetObjectType;
	}

	inline uint32 getTargetObjectSubType() {
		return targetObjectSubType;
	}

	inline bool isInstallationDeed() {
		return (objectSubType == TangibleObjectImplementation::INSTALLATIONDEED);
	}

	inline bool isBuildingDeed() {
		return (objectSubType == TangibleObjectImplementation::BUILDINGDEED);
	}

	inline bool isPetDeed() {
		return (objectSubType == TangibleObjectImplementation::PETDEED);
	}

	inline bool isDroidDeed() {
		return (objectSubType == TangibleObjectImplementation::DROIDDEED);
	}

	inline bool isVehicleDeed() {
		return (objectSubType == TangibleObjectImplementation::VEHICLEDEED);
	}

	inline bool isResourceDeed() {
		return (objectSubType == TangibleObjectImplementation::RESOURCEDEED);
	}


	//Virtual getters which get overridden in dervied classes.
	inline virtual uint8 getLotSize() {
		return 0;
	}

	inline virtual uint32 getTargetConstructionObjectCRC() {
		return 0;
	}
};

#endif /*DEEDOBJECTIMPLEMENTATION_H_*/
