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

#ifndef CAMPSITEIMPLEMENTATION_H_
#define CAMPSITEIMPLEMENTATION_H_

#include "engine/engine.h"

#include "../VisitorList.h"
#include "../../terminal/camp/CampTerminal.h"
#include "../events/CampDespawnEvent.h"
#include "../events/CampAbandonEvent.h"
class Zone;
class Player;
class DeedObject;
class InstallationSyncUIEvent;


class CampSiteImplementation : public CampSiteServant {
protected:
	float currentXP;
	uint8 campType;
	uint8 aggroMod;

	ActiveAreaTrigger* campArea;
	float areaRange;

	Vector<ManagedReference<SceneObject> > campObjects;
	VisitorList* visitor;
	bool abandoned;

	CampDespawnEvent* despawnEvent;
	CampAbandonEvent* abandonEvent;

	String defaultName;
	UnicodeString name;

	uint8 maxXP;
	uint8 campModifier;
	uint32 duration;

	Player* campOwner;

public:

	CampSiteImplementation(Player* player, uint64 oid, CampKit* campKit);
	~CampSiteImplementation();

	virtual void init() {

	}

	// Attribute Setters
	int getXP() {
		return maxXP;
	}

	Player* getOwner() {
		return campOwner;
	}

	int getDuration() {
		return duration;
	}

	int getCampModifier() {
		return campModifier;
	}

	int getAggroMod() {
		return aggroMod;
	}

	UnicodeString& getName() {
		return name;
	}
	String& getDefaultName() {
		return defaultName;
	}

	void setXP(const int xp) {
		maxXP = xp;
	}

	void setOwner(Player* player) {
		campOwner = player;
	}

	void setDuration(int dur) {
		duration = dur;
	}

	void setCampModifier(int mod) {
		campModifier = mod;
	}

	void setAggroMod(int mod) {
		aggroMod = mod;
	}

	// Object Handlers
	void sendTo(Player* player, bool doClose = true);


	// Object Attribute
	void generateAttributes(SceneObject* obj);

	virtual void parseItemAttributes();
	virtual void addAttributes(AttributeListMessage* alm);
	void addHeaderAttributes(AttributeListMessage* alm);
	void addFooterAttributes(AttributeListMessage* alm);

	inline void setObjectSubType(const int type) {
	}

	inline int getObjectSubType() {
		return TangibleObjectImplementation::MISC;
	}

	void calculateXP();
	void addXP(uint64 playerID);

	void createCampArea();
	virtual void spawnCampItems() {

	}
	void addCampObject(uint64 oid, uint32 ocrc, float x, float z, float y, float oX, float oZ,float oY, float oW);
	void addCampObject(uint64 oid, uint32 ocrc, const UnicodeString& n, float x, float z, float y, float oX, float oZ,float oY, float oW);

	void addCampObject(SceneObject* obj) {
		obj->insertToZone(campOwner->getZone());
		campObjects.add(obj);
	}

	void removeCampArea();
	void disbandCamp();
	void abandonCamp();
	void abortAbandonPhase();

	SceneObject* getCampObject(int num) {
		return campObjects.get(num);
	}

	bool isAbandoned() {
		return abandoned;
	}

	void enterNotification(Player* player);
	void exitNotificaton(Player* player);

};

#endif
