/*
 * MapLocationTable.h
 *
 *  Created on: 18/06/2010
 *      Author: victor
 */

#ifndef MAPLOCATIONTABLE_H_
#define MAPLOCATIONTABLE_H_

#include "MapLocationEntry.h"


namespace server {
namespace zone {
namespace objects {
namespace scene {

class SceneObject;

} // namespace scene
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::scene;
/*
 * type2
 * 0 = "[]:" (no string) Medic looking icon
1 = "Unknown" Green X icon
2 = Bank
3 = Cantina
4 = Capitol
5 = Cloning Facility
6 = Parking Garage
7 = Guild Hall
	8 = Combat
	9 = Commerce
	10 = Theater
	11 = University


12 = Hotel
13 = Medical Center
14 = Shuttleport
15 = Starport
16 = Theme Park
17 = City
18 = Invisible? Requires Sub-divisions?
19 = Trainer
	20 = Brawler
	21 = Artisan
	22 = Scout
	23 = Marksman
	24 = Entertainer
	25 = Medic
	62 = Starfighter Engineer Trainer
	63 = Shipwright Trainer
	64 = Privateer Pilot Trainer
	65 = Rebel Pilot Trainer
	66 = Imperial Pilot Trainer


26 = Junk Shop
27 = Tavern
28 = Barracks
29 = Vendor
	30 =  Armor
	31 = Clothing
	32 = Components
	33 = Droids
	34 = Equipment
	35 = Food
	36 = Housing
	37 = Resources
	38 = Tools
	39 = Weapons
	40 = Junk
	52 = Pets / Pet Supplies
	53 = Medical Supplies


41 = Terminal
	42 = Bank Terminal
	43 = Bazaar Terminal
	44 = Mission Terminal


45 = Rebel
	47 = Rebel Headquarters


46 = Imperial
	48 = Imperial Headquarters


49 = Camp
50 = City Hall
51 = Theater (again?)
54 = Invisible (?)
55 = Parking Garage (again?)
56 = Museum
57 = Salon
58 = Space
	59 = Space Recruiter
	60 = Starship Chassis Broker
	61 = Starship Chassis (??)
	67 = Ships (??)
 */

class MapLocationTable : public VectorMap<String, SortedVector<MapLocationEntry> >, public ReadWriteLock {
public:
	void addObject(SceneObject* object);

	void dropObject(SceneObject* object);
};

#endif /* MAPLOCATIONTABLE_H_ */
