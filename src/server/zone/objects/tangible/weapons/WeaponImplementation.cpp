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

#include "../../../ZoneClient.h"
#include "../../player/Player.h"

#include "../../../packets.h"

#include "WeaponImplementation.h"

void WeaponImplementation::sendTo(Player* player, bool doClose) {
	ZoneClient* client = player->getClient();
	if (client == NULL)
		return;

	SceneObjectImplementation::create(client);
	
	if (container != NULL)
		link(client, container);
	
	Message* weao3 = new WeaponObjectMessage3((Weapon*) _this);
	client->sendMessage(weao3);

	/*Message* weao6 = new WeaponObjectMessage6(this);
	client->sendMessage(weao6);*/
	
	generateAttributes(player);
	
	if (doClose)
		SceneObjectImplementation::close(client);
}

void WeaponImplementation::generateAttributes(SceneObject* obj) {
		
	if (obj->getObjectType() != SceneObjectImplementation::PLAYER)
		return;
		
	Player* play = (Player*) obj;
	
	AttributeListMessage* alm = new AttributeListMessage((Weapon*) _this);
	
	alm->insertAttribute("weapon_cert_status", "Yes");
	
	alm->insertAttribute("condition", "1000/1000");
	
	alm->insertAttribute("volume", "1");

	string ap;
	switch (armorPiercing) {
	case NONE:
		ap = "None";
		break;
	case LIGHT:
		ap = "Light";
		break;
	case MEDIUM:
		ap = "Medium";
		break;
	case HEAVY:
		ap = "Heavy";
		break;
	default:
		ap = "Unknown";
		break;
	}
	
	alm->insertAttribute("wpn_armor_pierce_rating", ap);
	
	alm->insertAttribute("wpn_attack_speed", attackSpeed);
					
	alm->insertAttribute("damage", "");
	alm->insertAttribute("wpn_damage_type", "Generic");

	alm->insertAttribute("wpn_damage_min", minDamage);

	alm->insertAttribute("wpn_damage_max", maxDamage);
	
	stringstream woundsratio;
	woundsratio << woundsRatio << "%";
	
	alm->insertAttribute("wpn_wound_chance", woundsratio);
	
	alm->insertAttribute("cat_wpn_rangemods", "");
	
	stringstream pblank;
	if (pointBlankAccuracy >= 0)
		pblank << "+";
	pblank << pointBlankAccuracy << " @ " << pointBlankRange;
	alm->insertAttribute("wpn_range_zero", pblank);
	
	stringstream ideal;
	if (idealAccuracy >= 0)
		ideal << "+";
	ideal << idealAccuracy << " @ " << idealRange;
	alm->insertAttribute("wpn_range_mid", ideal);
	
	stringstream maxrange;
	if (maxRangeAccuracy >= 0)
		maxrange << "+";
	maxrange << maxRangeAccuracy << " @ " << maxRange;
	alm->insertAttribute("wpn_range_max", maxrange);
	
	alm->insertAttribute("cat_wpn_attack_cost", "");
	
	alm->insertAttribute("pup_wpn_attack_cost_health", healthAttackCost);
	
	alm->insertAttribute("pup_wpn_attack_cost_action", actionAttackCost);
	
	alm->insertAttribute("pup_wpn_attack_cost_mind", mindAttackCost);
	
	play->sendMessage(alm);
	
}
