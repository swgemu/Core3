#ifndef SCENEOBJECT_H_
#define SCENEOBJECT_H_

#include "engine/engine.h"
#include "variables/StringId.h"

class ZoneClient;
class Zone;

class SceneObject : public Coordinate, public Mutex, public Logger {
protected:
	uint64 objectID;
	uint32 objectCRC;

	uint32 movementCounter;

	SceneObject* parent;
	VectorMap<String, Reference<SceneObject*> > slottedObjects;
	VectorMap<uint64, Reference<SceneObject*> > containerObjects;
	Vector<String> arrangementDescriptors;
	Vector<String> slotDescriptors;
	StringId objectName;
	StringId detailedDescription;

	Quaternion direction;
	int containerType;
	int containerVolumeLimit;
	int gameObjectType;
	int containmentType;

	ZoneClient* client;
	Zone* zone;

public:
	SceneObject(LuaObject* templateData);
	~SceneObject();

	const static int CELLOBJECT = 11;
	const static int PLAYEROBJECT = 12;
	const static int ARMOR = 0x100;
	const static int BODYARMOR = 0x101;
	const static int HEADARMOR = 0x102;
	const static int MISCARMOR = 0x103;
	const static int LEGARMOR = 0x104;
	const static int ARMARMOR = 0x105;
	const static int HANDARMOR = 0x106;
	const static int FOOTARMOR = 0x107;
	const static int SHIELDGENERATOR = 0x108;

	const static int BUILDING = 0x200;
	const static int MUNICIPALBUILDING = 0x201;
	const static int FACTIONPERKBUILDING = 0x203;

	const static int CREATURE = 0x400;
	const static int NPCCREATURE = 0x401;
	const static int DROIDCREATURE = 0x402;
	const static int PROBOTCREATURE = 0x403;
	const static int PLAYERCREATURE = 0x409;

	const static int INTANGIBLE = 0x800;
	const static int DRAFTSCHEMATIC = 0x801;
	const static int MANUFACTURINGSCHEMATIC = 0x802;
	const static int MISSIONOBJECT = 0x803;
	const static int TOKEN = 0x804;
	const static int WAYPOINT = 0x805;
	const static int DATA2 = 0x806;
	const static int PETCONTROLDEVICE = 0x807;
	const static int VEHICLECONTROLDEVICE = 0x808;
	const static int SHIPCONTROLDEVICE = 0x80A;
	const static int DROIDCONTROLDEVICE = 0x80B;

	const static int INSTALLATION = 0x1000;
	const static int FACTORY = 0x1001;
	const static int GENERATOR = 0x1002;
	const static int HARVESTER = 0x1003;
	const static int TURRET = 0x1004;
	const static int MINEFIELD = 0x1005;

	const static int TANGIBLE = 0x2000;
	const static int AMMUNITION = 0x2001;
	const static int CHEMICAL = 0x2002;
	const static int CONTAINER = 0x2005;
	const static int CRAFTINGSTATION = 0x2006;
	const static int ELECTRONICS = 0x2008;
	const static int FLORA = 0x2009;
	const static int FOOD = 0x200A;
	const static int FURNITURE = 0x200B;
	const static int INSTRUMENT = 0x200C;
	const static int PHARMACEUTICAL = 0x200D;
	const static int SIGN = 0x200F;
	const static int COUNTER = 0x2010;
	const static int FACTORYCRATE = 0x2011;
	const static int TRAVELTICKET = 0x2012;
	const static int GENERICITEM = 0x2013;
	const static int TRAP = 0x2014;
	const static int WEARABLECONTAINER = 0x2015;
	const static int FISHINGPOLE = 0x2016;
	const static int FISHINGBAIT = 0x2017;
	const static int DRINK = 0x2018;
	const static int FIREWORK = 0x2019;
	const static int ITEM = 0x201A;
	const static int PETMEDECINE = 0x201B;
	const static int FIREWORKSHOW = 0x201C;
	const static int CLOTHINGATTACHMENT = 0x201D;
	const static int LIVESAMPLE = 0x201E;
	const static int ARMORATTACHMENT = 0x201F;
	const static int COMMUNITYCRAFTINGPROJECT = 0x2020;
	const static int CRYSTAL = 0x2021;
	const static int DROIDPROGRAMMINGCHIP = 0x2022;
	const static int ASTEROID = 0x2023;
	const static int PILOTCHAIR = 0x2024;
	const static int OPERATIONSCHAIR = 0x2025;
	const static int TURRETACCESSLADDER = 0x2026;
	const static int CONTAINER2 = 0x2027;
	const static int CAMOKIT = 0x2028;

	const static int TERMINAL = 0x4000;
	const static int BANK = 0x4001;
	const static int BAZAAR = 0x4002;
	const static int CLONING = 0x4003;
	const static int INSURANCE = 0x4004;
	const static int MISSIONTERMINAL = 0x4006;
	const static int PLAYERTERMINALSTRUCTURE = 0x4008;
	const static int SHIPPINGTERMINAL = 0x4009;
	const static int SPACETERMINAL = 0x400B;
	const static int INTERACTIVETERMINAL = 0x400C;
	const static int NEWBIETUTORIALTERMINAL = 0x400F;

	const static int TOOL = 0x8000;
	const static int CRAFTINGTOOL = 0x8001;
	const static int SURVEYTOOL = 0x8002;
	const static int REPAIRTOOL = 0x8003;
	const static int CAMPKIT = 0x8004;
	const static int SHIPCOMPONENTREPAIRITEM = 0x8005;

	const static int VEHICLE = 0x10000;
	const static int HOVERVEHICLE = 0x10001;

	const static int WEAPON = 0x20000;
	const static int MELEEWEAPON = 0x20001;
	const static int RANGEDWEAPON = 0x20002;
	const static int THROWNWEAPON = 0x20003;
	const static int HEAVYWEAPON = 0x20004;
	const static int MINE = 0x20005;
	const static int SPECIALHEAVYWEAPON = 0x20006;
	const static int ONEHANDMELEEWEAPON = 0x20007;
	const static int TWOHANDMELEEWEAPON = 0x20008;
	const static int POLEARM = 0x20009;
	const static int PISTOL = 0x2000A;
	const static int CARBINE = 0x2000B;
	const static int RIFLE = 0x2000C;
	const static int GRENADE = 0x2000E;

	const static int COMPONENT = 0x40000;
	const static int ARMORCOMPONENT = 0x40001;
	const static int CHEMISTRYCOMPONENT = 0x40002;
	const static int CLOTHINGCOMPONENT = 0x40003;
	const static int COMMUNITYCRAFTINGCOMPONENT = 0x40004;
	const static int DROIDCOMPONENT = 0x40005;
	const static int ELECTRONICSCOMPONENT = 0x40006;
	const static int GENETICCOMPONENT = 0x40007;
	const static int LIGHTSABERCRYSTAL = 0x40008;
	const static int MELEEWEAPONCOMPONENT = 0x40009;
	const static int MUNITIONCOMPONENT = 0x4000A;
	const static int RANGEDWEAPONCOMPONENT = 0x4000B;
	const static int STRUVTURECOMPONENT = 0x4000C;
	const static int TISSUECOMPONENT = 0x4000D;

	const static int WEAPONPOWERUP = 0x80000;
	const static int MELEEWEAPONPOWERUP = 0x80001;
	const static int RANGEDWEAPONPOWERUP = 0x80002;
	const static int THROWNWEAPONPOWERUP = 0x80003;
	const static int HEAVYWEAPONPOWERUP = 0x80004;
	const static int MINEPOWERUP = 0x80005;
	const static int SPECIALHEAVYWEAPONPOWERUP = 0x80006;

	const static int WEARABLE = 0x200000;
	const static int RING = 0x200001;
	const static int BRACELET = 0x200002;
	const static int NECKLACE = 0x200003;
	const static int EARRING = 0x200004;

	const static int RESOURCECONTAINER = 0x400000;
	const static int ENERGYGAS = 0x400001;
	const static int ENERGYLIQUID = 0x400002;
	const static int ENERGYRADIOACTIVE = 0x400003;
	const static int ENERGYSOLID = 0x400004;
	const static int INORGANICCHEMICAL = 0x400005;
	const static int INORGANICGAS = 0x400006;
	const static int INORGANICMINERAL = 0x400007;
	const static int WATER = 0x400008;
	const static int ORGANICFOOD = 0x400009;
	const static int ORGANICHIDE = 0x40000A;
	const static int ORGANICSTRUCTURAL = 0x40000B;
	const static int QUESTREOURCE = 0x40000C;

	const static int DEED = 0x800000;
	const static int BUILDINGDEED = 0x800001;
	const static int INSTALLATIONDEED = 0x800002;
	const static int PETDEED = 0x800003;
	const static int DROIDDEED = 0x800004;
	const static int VEHICLEDEED = 0x800005;
	const static int RESOURCEDEED = 0x800006;

	const static int CLOTHING = 0x1000000;
	const static int BANDOLIER = 0x1000001;
	const static int BELT = 0x1000002;
	const static int BODYSUIT = 0x1000003;
	const static int CAPE = 0x1000004;
	const static int CLOAK = 0x1000005;
	const static int FOOTWEAR = 0x1000006;
	const static int DRESS = 0x1000007;
	const static int HANDWEAR = 0x1000008;
	const static int EYEWEAR = 0x1000009;
	const static int HEADWEAR = 0x100000A;
	const static int JACKET = 0x100000B;
	const static int PANTS = 0x100000C;
	const static int ROBE = 0x100000D;
	const static int SHIRT = 0x100000E;
	const static int VEST = 0x100000F;
	const static int WOOKIEGARB = 0x1000010;
	const static int MISCCLOTHING = 0x1000011;
	const static int SKIRT = 0x1000012;
	const static int ITHOGARB = 0x1000013;

	virtual void parseBaseline3(Message* message) {
	}

	virtual void parseBaseline6(Message* message) {
	}

	bool addObject(SceneObject* object, int containmentType);
	bool removeObject(SceneObject* object);

	StringId& getObjectName() {
		return objectName;
	}

	inline uint64 getObjectID() {
		return objectID;
	}

	inline uint32 getMovementCounter() {
		return movementCounter;
	}

	inline ZoneClient* getClient() {
		return client;
	}

	inline SceneObject* getParent() {
		return parent;
	}

	inline uint32 getArrangementDescriptorSize() {
		return arrangementDescriptors.size();
	}

	inline uint32 getSlottedObjectsSize() {
		return slottedObjects.size();
	}

	inline SceneObject* getSlottedObject(int idx) {
		return slottedObjects.get(idx);
	}

	inline uint32 getContainerObjectsSize() {
		return containerObjects.size();
	}

	inline SceneObject* getContainerObject(int idx) {
		return containerObjects.get(idx);
	}

	inline String& getArrangementDescriptor(int idx) {
		return arrangementDescriptors.get(idx);
	}

	inline void setObjectID(uint64 oid) {
		objectID = oid;
	}

	inline void setClient(ZoneClient* cl) {
		client = cl;
	}

	inline void setParent(SceneObject* par) {
		parent = par;
	}

	inline void setContainmentType(int type) {
		containmentType = type;
	}

	inline void setZone(Zone* zn) {
		zone = zn;
	}
};

#endif /*SCENEOBJECT_H_*/
