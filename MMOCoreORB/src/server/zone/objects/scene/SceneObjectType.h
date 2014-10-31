/*
 * SceneObjectType.h
 *
 *  Created on: 30/10/2011
 *      Author: victor
 */

#ifndef SCENEOBJECTTYPE_H_
#define SCENEOBJECTTYPE_H_

class SceneObjectType {
public:

	const static int OBJECT = 0; // Needs Research
	const static int CORPSE = 1; // Needs Research
	const static int GROUPOBJECT = 0x02;
	const static int GUILDOBJECT = 0x03;
	const static int LAIR = 0x04;
	const static int STATICOBJECT = 0x05;
	const static int VENDOR = 7;
	const static int LOADBEACON = 8; // Needs Research

	/// Not in client ********
	const static int CELLOBJECT = 11; //This is marked as 0x00 in the client types xls
	const static int PLAYEROBJECT = 12;
	/// End not in client *******

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
	const static int PLAYERBUILDING = 0x202;
	const static int FACTIONBUILDING = 0x203;

	/// Not in client *********
	const static int TUTORIALBUILDING = 0x204;
	const static int HOSPITALBUILDING = 0x205;
	const static int RECREATIONBUILDING = 0x206;
	const static int TRAVELBUILDING = 0x208;
	const static int STARPORTBUILDING = 0x209;
	const static int CAPITOLBUILDING = 0x20A;
	const static int HOTELBUILDING = 0x20B;
	const static int THEATERBUILDING = 0x20C;
	const static int COMBATBUILDING = 0x20D;
	const static int COMMERCEBUILDING = 0x20E;
	const static int UNIVERSITYBUILDING = 0x20F;
	const static int GARAGEBUILDING = 0x210;
	const static int CITYHALLBUILDING = 0x211;
	const static int SALONBUILDING = 0x212;
	/// End not in client *************

	const static int CREATURE = 0x400;  // ENTITY
	const static int NPCCREATURE = 0x401; // CHARACTER
	const static int DROIDCREATURE = 0x402; // DROID
	const static int PROBOTCREATURE = 0x403; // PROBEDROID
	//const static int CREATURE = 0x404;

	/// Not in client **********
	const static int PLAYERCREATURE = 0x409; // CREATURE
	const static int TRAINERCREATURE = 0x40A;
	const static int JUNKDEALERCREATURE = 0x40C;
	const static int INFORMANTCREATURE = 0x40D;
	const static int VENDORCREATURE = 0x40E;
	/// End not in client ************

	const static int INTANGIBLE = 0x800;  // DATA
	const static int DRAFTSCHEMATIC = 0x801;
	const static int MANUFACTURINGSCHEMATIC = 0x802;
	const static int MISSIONOBJECT = 0x803;
	const static int TOKEN = 0x804;
	const static int WAYPOINT = 0x805;
	const static int DATA2 = 0x806;  // DATA
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

	/// Not in client **********
	const static int GARAGEINSTALLATION = 0x1006;
	const static int SHUTTLEINSTALLATION = 0x1007;
	/// End **************

	const static int TANGIBLE = 0x2000;  // MISC
	const static int AMMUNITION = 0x2001;
	const static int CHEMICAL = 0x2002;
	//const static int ? = 0x2003;
	//const static int ? = 0x2004;
	const static int CONTAINER = 0x2005;
	const static int CRAFTINGSTATION = 0x2006;
	//const static int ? = 0x2007;
	const static int ELECTRONICS = 0x2008;
	const static int FLORA = 0x2009;
	const static int FOOD = 0x200A;
	const static int FURNITURE = 0x200B;
	const static int INSTRUMENT = 0x200C;
	const static int PHARMACEUTICAL = 0x200D;
	//const static int ? = 0x200E;
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

	/// Not in client *****************
	const static int CAMOKIT = 0x2028;
	const static int LOOTKIT = 0x2029;
	const static int FISH = 0x202A;
	//const static int LAIR = 0x202B;
	const static int STIMPACK = 0x202C;
	const static int RANGEDSTIMPACK = 0x202D;
	const static int ENHANCEPACK = 0x202E;
	const static int CUREPACK = 0x202F;
	const static int DOTPACK = 0x2030;
	const static int WOUNDPACK = 0x2031;
	const static int STATEPACK = 0x2032;
	const static int REVIVEPACK = 0x2033;
	const static int STATICLOOTCONTAINER = 0x2034;
	const static int PLAYERLOOTCRATE = 0x2035;
	/// End Not in client **************

	const static int TERMINAL = 0x4000;
	const static int BANK = 0x4001;
	const static int BAZAAR = 0x4002; // COMMODITIESTERMINAL
	const static int CLONING = 0x4003;
	const static int INSURANCE = 0x4004;
	const static int MANAGEMENTTERMINAL = 0x4005;
	const static int MISSIONTERMINAL = 0x4006;
	const static int PERMISSIONSTERMINAL = 0x4007;
	const static int PLAYERTERMINALSTRUCTURE = 0x4008;
	const static int SHIPPINGTERMINAL = 0x4009;
	//const static int TRAVELTERMINAL = 0x400A; -- This is in the client, (See 0x4012)
	const static int SPACETERMINAL = 0x400B;

	/// Not in client **************
	const static int INTERACTIVETERMINAL = 0x400C;
	const static int NEWBIETUTORIALTERMINAL = 0x400F;
	const static int CHARACTERBUILDERTERMINAL = 0x4010;
	const static int TICKETCOLLECTOR = 0x4011;
	const static int TRAVELTERMINAL = 0x4012; // not in the client (See 0x400A)
	const static int GUILDTERMINAL = 0x4014;
	const static int CITYTERMINAL = 0x4015;
	const static int CITYVOTETERMINAL = 0x4016;
	const static int GAMBLINGTERMINAL = 0x4017;
	/// end not in client ***************

	const static int TOOL = 0x8000;
	const static int CRAFTINGTOOL = 0x8001;
	const static int SURVEYTOOL = 0x8002;
	const static int REPAIRTOOL = 0x8003;
	const static int CAMPKIT = 0x8004;
	const static int SHIPCOMPONENTREPAIRITEM = 0x8005;

	// Not in client ******************
	const static int SLICINGTOOL = 0x8006;
	const static int MOLECULARCLAMP = 0x8007;
	const static int FLOWANALYZER = 0x8008;
	const static int LASERKNIFE = 0x8009;
	const static int WEAPONUPGRADEKIT = 0x800A;
	const static int ARMORUPGRADEKIT = 0x800B;
	const static int RECYCLETOOL = 0x800C;
	const static int ANTIDECAYKIT = 0x800D;
	// End Not in client *****************

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

	const static int COMPONENT = 0x40000;
	const static int ARMORCOMPONENT = 0x40001;
	const static int CHEMISTRYCOMPONENT = 0x40002;
	const static int CLOTHINGCOMPONENT = 0x40003;
	const static int DROIDCOMPONENT = 0x40004;
	const static int ELECTRONICSCOMPONENT = 0x40005;
	const static int MUNITIONCOMPONENT = 0x40006;
	const static int STRUCTURECOMPONENT = 0x40007;
	const static int MELEEWEAPONCOMPONENT = 0x40008;
	const static int RANGEDWEAPONCOMPONENT = 0x40009;
	const static int TISSUECOMPONENT = 0x4000A;
	const static int GENETICCOMPONENT = 0x4000B;
	const static int LIGHTSABERCRYSTAL = 0x4000C;
	const static int COMMUNITYCRAFTINGCOMPONENT = 0x4000D;
	const static int DNACOMPONENT = 0x4000E;

	const static int WEAPONPOWERUP = 0x80000;
	const static int MELEEWEAPONPOWERUP = 0x80001;
	const static int RANGEDWEAPONPOWERUP = 0x80002;
	const static int THROWNWEAPONPOWERUP = 0x80003;
	const static int HEAVYWEAPONPOWERUP = 0x80004;
	const static int MINEPOWERUP = 0x80005;
	const static int SPECIALHEAVYWEAPONPOWERUP = 0x80006;

	const static int ARMORPOWERUP = 0x100000;
	const static int BODYARMORPOWERUP = 0x100001;
	const static int HEADARMORPOWERUP = 0x100002;
	const static int MISCARMORPOWERUP = 0x100003;
	const static int LEGARMORPOWERUP = 0x100004;
	const static int ARMARMORPOWERUP = 0x100005;
	const static int HANDARMORPOWERUP = 0x100006;
	const static int FOOTARMORPOWERUP = 0x100007;

	const static int JEWELRY = 0x200000;
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
	const static int QUESTREOURCE = 0x40000C; // Resource Container?

	// Not in client ************
	const static int RESOURCESPAWN = 0x410000;
	// **************************

	const static int DEED = 0x800000;
	const static int BUILDINGDEED = 0x800001;
	const static int INSTALLATIONDEED = 0x800002;
	const static int PETDEED = 0x800003;
	const static int DROIDDEED = 0x800004;
	const static int VEHICLEDEED = 0x800005;

	// Not in client **********
	const static int RESOURCEDEED = 0x800006;
	const static int EVENTPERKDEED = 0x800007;
	// ************************

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

	//Seems unused in server and not in client
	//const static int ITHOGARB = 0x1000013;


	// Not in client ************
	const static int BADGEAREA = 0x2000000;
	const static int REGIONAREA = 0x2000001;
	const static int MISSIONSPAWNAREA = 0x2000002;
	const static int MISSIONRECONAREA = 0x2000003;
	const static int SPAWNAREA = 0x2000004;
	const static int GARAGEAREA = 0x2000006;
	const static int ACTIVEAREA = 0x2000007;
	const static int CAMPAREA = 0x2000009;
	const static int FSVILLAGEAREA = 0x200000A;
	const static int SARLACCAREA = 0x200000B;

	const static int SHIP = 0x20000000;
	const static int SHIPFIGHTER = 0x20000001;
	const static int SHIPCAPITAL = 0x20000002;
	const static int SHIPSTATION = 0x20000003;
	const static int SHIPTRANSPORT = 0x20000004;
	//*******************************

	const static int SHIPATTACHMENT = 0x40000000;
	const static int SHIPREACTOR = 0x40000001;
	const static int SHIPENGINE = 0x40000002;
	const static int SHIPSHIELDGENERATOR = 0x40000003;
	const static int SHIPARMOR = 0x40000004;
	const static int SHIPWEAPON = 0x40000005;
	const static int SHIPWEAPONCAPACITOR = 0x40000006;
	const static int SHIPBOOSTER = 0x40000007;
	const static int SHIPDRIODINTERFACE = 0x40000008;
	const static int HANGER = 0x40000009;
	const static int TARGETINGSTATION = 0x4000000A;
	const static int BRIDGE = 0x4000000B;
	const static int SHIPCHASSIS = 0x4000000C;
	const static int SHIPMISSILE = 0x4000000D;
	const static int SHIPCOUNTERMEASURE = 0x4000000E;
	const static int SHIPWEAPONLAUNCHER = 0x4000000F;
	const static int SHIPCOUNTERMEASURELAUNCHER = 0x40000010;
};

#endif /* SCENEOBJECTTYPE_H_ */
