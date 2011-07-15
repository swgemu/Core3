/*
 * SharedObjectTemplate.h
 *
 *  Created on: 30/04/2010
 *      Author: victor
 */

#ifndef SHAREDOBJECTTEMPLATE_H_
#define SHAREDOBJECTTEMPLATE_H_

#include "engine/engine.h"

#include "LuaTemplate.h"
#include "IffTemplate.h"
#include "ChildObject.h"
#include "server/zone/managers/templates/PlanetMapCategory.h"
#include "server/zone/templates/slots/SlotDescriptor.h"
#include "server/zone/templates/slots/ArrangementDescriptor.h"

#include "params/primitives/IntegerParam.h"
#include "params/StringIdParam.h"
#include "params/primitives/StringParam.h"
#include "params/primitives/BoolParam.h"
#include "params/primitives/FloatParam.h"

class PortalLayout;
class AppearanceTemplate;
class SlotDescriptor;
class ArrangementDescriptor;

namespace server {
 namespace zone {
  namespace templates {


class SharedObjectTemplate : public LuaTemplate, public IffTemplate {
protected:
	StringIdParam objectName;
	StringIdParam detailedDescription;
	StringIdParam lookAtText;

	BoolParam snapToTerrain;
	IntegerParam containerType;
	IntegerParam containerVolumeLimit;

	StringParam tintPallete;
	/*Vector<String>* slotDescriptors;
	Vector<String>* arrangementDescriptors;*/
	Reference<ArrangementDescriptor*> arrangementDescriptors;
	Reference<SlotDescriptor*> slotDescriptors;
	StringParam appearanceFilename;
	StringParam portalLayoutFilename;
	int totalCellNumber;
	StringParam clientDataFile;

	IntegerParam collisionMaterialFlags;
	IntegerParam collisionMaterialPassFlags;
	FloatParam scale;
	IntegerParam collisionMaterialBlockFlags;
	IntegerParam collisionActionFlags;
	IntegerParam collisionActionPassFlags;
	IntegerParam collisionActionBlockFlags;
	IntegerParam gameObjectType;
	int clientGameObjectType;
	BoolParam sendToClient;
	FloatParam scaleThresholdBeforeExtentTest;
	FloatParam clearFloraRadius;
	IntegerParam surfaceType;
	FloatParam noBuildRadius;
	BoolParam onlyVisibleInTools;
	FloatParam locationReservationRadius;
	uint32 clientObjectCRC;

	Reference<PlanetMapCategory*> planetMapCategory;
	Reference<PlanetMapCategory*> planetMapSubCategory;

	String fullTemplateString;

	int templateType;

	Vector<ChildObject> childObjects;

	PortalLayout* portalLayout;
	AppearanceTemplate* appearanceTemplate;
	bool loadedPortalLayout, loadedAppearanceTemplate;
	String containerComponent, zoneComponent, objectMenuComponent;

	SortedVector<String> loadedDerivedFiles;

public:
	const static int SHOT = 'SHOT';
	const static int STOT = 'STOT';
	const static int SBMK = 'SBMK';
	const static int SBOT = 'SBOT';
	const static int STAT = 'STAT';
	const static int SIOT = 'SIOT';
	const static int CCLT = 'CCLT';
	const static int SCOU = 'SCOU';
	const static int SDSC = 'SDSC';
	const static int SFOT = 'SFOT';
	const static int SGRP = 'SGRP';
	const static int SITN = 'SITN';
	const static int SGLD = 'SGLD';
	const static int SJED = 'SJED';
	const static int SMSC = 'SMSC';
	const static int SMSO = 'SMSO';
	const static int SMSD = 'SMSD';
	const static int SMLE = 'SMLE';
	const static int SPLY = 'SPLY';
	const static int RCCT = 'RCCT';
	const static int SSHP = 'SSHP';
	const static int SUNI = 'SUNI';
	const static int SWAY = 'SWAY';
	const static int STOK = 'STOK';
	const static int SWOT = 'SWOT';
	const static int SCNC = 'SCNC';
	const static int SCOT = 'SCOT';
	const static int CHARACTERBUILDERTERMINAL = 0x4000001;
	const static int SURVEYTOOL = 0x4000002;
	const static int RESOURCESPAWN = 0x4000003;
	const static int RESOURCECONTAINER = 0x4000004;
	const static int ARMOROBJECT = 0x4000005;
	const static int DEED = 0x4000006;
	const static int CRAFTINGTOOL = 0x4000007;
	const static int CRAFTINGSTATION = 0x4000008;
	const static int MISSIONTERMINAL = 0x4000009;
	const static int CLONINGBUILDING = 0x400000A;
	const static int DRAFTSCHEMATIC = 0x400000B;
	const static int NPCCREATURE = 0x400000C;
	const static int LAIRTEMPLATE = 0x400000D;
	const static int FACTORY = 0x400000E;
	const static int STIMPACK = 0x400000F;
	const static int RANGEDSTIMPACK = 0x4000010;
	const static int ENHANCEPACK = 0x4000011;
	const static int CUREPACK = 0x4000012;
	const static int DOTPACK = 0x4000013;
	const static int WOUNDPACK = 0x4000014;
	const static int STATEPACK = 0x4000015;
	const static int CONSUMABLE = 0x4000016;
	const static int ELEVATORTERMINAL = 0x4000017;
	const static int GAMBLINGTERMINAL = 0x4000018;
	const static int LOOTKIT = 0x4000019;
	const static int INSTRUMENT = 0x400001A;
	const static int FIREWORK = 0x400001B;
	const static int VEHICLEDEED = 0x400001C;
	const static int CAMPKIT = 0x400001D;
	const static int PLAYERCREATURE = 0x400001E;
	const static int SLICINGTOOL = 0x400001F;
	const static int CONTAINER = 0x4000020;
	const static int VENDORCREATURE = 0x4000021;

public:
	SharedObjectTemplate();

	virtual ~SharedObjectTemplate() {

	}

	void readObject(LuaObject* templateData);
	void readObject(IffStream* iffStream);

	void parseVariableData(const String& varName, Chunk* data);
	void parseVariableData(const String& varName, LuaObject* templateData);

	void loadDerv(IffStream* iffStream);
	void parseFileData(IffStream* iffStream);

	bool isDerivedFrom(String& iffPath, bool includeSelf = true);

    inline String getAppearanceFilename() const {
		return appearanceFilename;
	}

    inline float getClearFloraRadius() const {
		return clearFloraRadius;
	}

    inline String getClientDataFile() const {
		return clientDataFile;
	}

    inline int getCollisionActionBlockFlags() const {
		return collisionActionBlockFlags;
	}

    inline int getCollisionActionFlags() const {
		return collisionActionFlags;
	}

    inline int getCollisionActionPassFlags() const {
		return collisionActionPassFlags;
	}

    inline int getCollisionMaterialBlockFlags() const {
		return collisionMaterialBlockFlags;
	}

    inline int getCollisionMaterialFlags() const {
		return collisionMaterialFlags;
	}

    inline int getCollisionMaterialPassFlags() const {
		return collisionMaterialPassFlags;
	}

    inline int getContainerType() const {
		return containerType;
	}

    inline int getContainerVolumeLimit() const {
		return containerVolumeLimit;
	}

    inline String getDetailedDescription() {
		return detailedDescription.getFullString();
	}

    inline int getGameObjectType() const {
		return gameObjectType;
	}

    inline int getClientGameObjectType() const {
    	return clientGameObjectType;
    }

    inline float getLocationReservationRadius() const {
		return locationReservationRadius;
	}

    inline String getLookAtText() const {
		return lookAtText.getFullString();
	}

    inline float getNoBuildRadius() const {
		return noBuildRadius;
	}

    inline String getObjectName() const {
		return objectName.getFullString();
	}

    inline bool getOnlyVisibleInTools() const {
		return onlyVisibleInTools;
	}

    inline String getPortalLayoutFilename() const {
		return portalLayoutFilename;
	}

    PortalLayout* getPortalLayout();
    AppearanceTemplate* getAppearanceTemplate();

    inline Vector<String>* getArrangementDescriptors() {
    	if (arrangementDescriptors == NULL)
    		return NULL;
    	else
    		return arrangementDescriptors->getArrangementSlots();
	}

    /*inline Vector<float>* getScale() {
		return &scale;
	}*/

	inline float getMinScale() {
		return scale.getMin();
	}

	inline float getMaxScale() {
		return scale.getMax();
	}

    inline float getScaleThresholdBeforeExtentTest() const {
		return scaleThresholdBeforeExtentTest;
	}

    inline bool getSendToClient() const {
		return sendToClient;
	}

    inline Vector<String>* getSlotDescriptors() {
    	if (slotDescriptors == NULL)
    		return NULL;
    	else
    		return slotDescriptors->getSlots();
	}

    inline bool getSnapToTerrain() const {
		return snapToTerrain;
	}

    inline int getSurfaceType() const {
		return surfaceType;
	}

    inline String getTintPallete() const {
		return tintPallete;
	}

    inline int getTotalCellNumber() const {
		return totalCellNumber;
	}

    inline uint32 getClientObjectCRC() const {
		return clientObjectCRC;
	}

    inline uint32 getServerObjectCRC() {
    	return fullTemplateString.hashCode();
    }

    inline String getFullTemplateString() {
		return fullTemplateString;
	}

    inline String getContainerComponent() {
    	return containerComponent;
    }

    inline String getZoneComponent() {
    	return zoneComponent;
    }

    inline String getObjectMenuComponent() {
    	return objectMenuComponent;
    }

	inline PlanetMapCategory* getPlanetMapCategory() const {
		return planetMapCategory;
	}

	inline PlanetMapCategory* getPlanetMapSubCategory() const {
		return planetMapSubCategory;
	}

	inline int getChildObjectsSize() {
		return childObjects.size();
	}

	inline ChildObject* getChildObject(int idx) {
		return &childObjects.get(idx);
	}

public:
	void setAppearanceFilename(String appearanceFilename) {
		this->appearanceFilename = appearanceFilename;
	}

	void setClearFloraRadius(float clearFloraRadius) {
		this->clearFloraRadius = clearFloraRadius;
	}

	void setClientDataFile(String clientDataFile) {
		this->clientDataFile = clientDataFile;
	}

	void setCollisionActionBlockFlags(int collisionActionBlockFlags) {
		this->collisionActionBlockFlags = collisionActionBlockFlags;
	}

	void setCollisionActionFlags(int collisionActionFlags) {
		this->collisionActionFlags = collisionActionFlags;
	}

	void setCollisionActionPassFlags(int collisionActionPassFlags) {
		this->collisionActionPassFlags = collisionActionPassFlags;
	}

	void setCollisionMaterialBlockFlags(int collisionMaterialBlockFlags) {
		this->collisionMaterialBlockFlags = collisionMaterialBlockFlags;
	}

	void setCollisionMaterialFlags(int collisionMaterialFlags) {
		this->collisionMaterialFlags = collisionMaterialFlags;
	}

	void setCollisionMaterialPassFlags(int collisionMaterialPassFlags) {
		this->collisionMaterialPassFlags = collisionMaterialPassFlags;
	}

	void setContainerType(int containerType) {
		this->containerType = containerType;
	}

	void setContainerVolumeLimit(int containerVolumeLimit) {
		this->containerVolumeLimit = containerVolumeLimit;
	}

	void setDetailedDescription(String detailedDescription) {
		this->detailedDescription = detailedDescription;
	}

	void setGameObjectType(int gameObjectType) {
		this->gameObjectType = gameObjectType;
	}

	void setLocationReservationRadius(float locationReservationRadius) {
		this->locationReservationRadius = locationReservationRadius;
	}

	void setLookAtText(String lookAtText) {
		this->lookAtText = lookAtText;
	}

	void setNoBuildRadius(float noBuildRadius) {
		this->noBuildRadius = noBuildRadius;
	}

	void setObjectName(String objectName) {
		this->objectName = objectName;
	}

	void setOnlyVisibleInTools(bool onlyVisibleInTools) {
		this->onlyVisibleInTools = onlyVisibleInTools;
	}

	void setPortalLayoutFilename(String portalLayoutFilename) {
		this->portalLayoutFilename = portalLayoutFilename;
	}

	/*void setRrangementDescriptors(Vector<String> rrangementDescriptors) {
		this->arrangementDescriptors = rrangementDescriptors;
	}*/

	void setScale(float scale) {
		this->scale = scale;
	}

	void setScaleThresholdBeforeExtentTest(float scaleThresholdBeforeExtentTest) {
		this->scaleThresholdBeforeExtentTest = scaleThresholdBeforeExtentTest;
	}

	void setSendToClient(bool sendToClient) {
		this->sendToClient = sendToClient;
	}

	/*void setSlotDescriptors(Vector<String> slotDescriptors) {
		this->slotDescriptors = slotDescriptors;
	}*/

	void setSnapToTerrain(bool snapToTerrain) {
		this->snapToTerrain = snapToTerrain;
	}

	void setSurfaceType(int surfaceType) {
		this->surfaceType = surfaceType;
	}

	void setTintPallete(String tintPallete) {
		this->tintPallete = tintPallete;
	}

	void setTotalCellNumber(int totalCellNumber) {
		this->totalCellNumber = totalCellNumber;
	}

	void setFullTemplateString(const String& str) {
		fullTemplateString = str;
	}

public:
	virtual bool isArmorObjectTemplate() {
		return false;
	}

	virtual bool isSharedBuildingObjectTemplate() {
		return false;
	}

	virtual bool isSharedInstallationObjectTemplate() {
		return false;
	}

	virtual bool isMissionTerminalTemplate() {
		return false;
	}

	virtual bool isGamblingTerminalTemplate() {
		return false;
	}

	virtual bool isFireworkObjectTemplate() {
		return false;
	}

	virtual bool isCloningBuildingObjectTemplate() {
		return false;
	}

	virtual bool isNonPlayerCreatureObjectTemplate() {
		return false;
	}

	virtual bool isStimPackTemplate() {
		return false;
	}

	virtual bool isStatePackTemplate() {
		return false;
	}

	virtual bool isRangedStimPackTemplate() {
		return false;
	}

	virtual bool isEnhancePackTemplate() {
		return false;
	}

	virtual bool isCurePackTemplate() {
		return false;
	}

	virtual bool isDotPackTemplate() {
		return false;
	}

	virtual bool isWoundPackTemplate() {
		return false;
	}

	virtual bool isLairObjectTemplate() {
		return false;
	}

	virtual bool isElevatorTerminalTemplate() {
		return false;
	}

	virtual bool isInstrumentObjectTemplate() {
		return false;
	}

	virtual bool isCampKitTemplate() {
		return false;
	}

	virtual bool isVendorCreatureTemplate() {
		return false;
	}

};


  }
 }
}

using namespace server::zone::templates;

#endif /* SHAREDOBJECTTEMPLATE_H_ */
