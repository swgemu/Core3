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

#ifndef RADIALMANAGER_H_
#define RADIALMANAGER_H_

#include "engine/engine.h"

class RadialItem;
class MountCreature;
class ObjectMenuResponse;
class Player;
class SceneObject;
class GuildTerminal;
class BankTerminal;
class SurveyTool;
class CraftingTool;
class Weapon;
class Armor;
class InstallationObject;
class HarvesterObject;
class VehicleDeed;

class RadialManager {

private:
	ObjectMenuResponse* parseDefaults(Player* player, uint64 objectid, Packet* pack);

public:
	RadialManager();

	void handleRadialRequest(Player* player, Packet* pack);
	void handleRadialSelect(Player* player, Packet* pack);

	void sendDefaultRadialResponse(Player* player, ObjectMenuResponse* omr);
	void sendRadialResponseForBazaar(uint64 objectId, Player* player);

	void handleSelection(int radialID, Player* player, SceneObject* obj);
	void handleVehicleStore(SceneObject* obj);
	void handleVehicleGenerate(SceneObject* obj);
	void handleTrade(Player* player, SceneObject* obj);
	void handleWearableColorChange(Player* player, SceneObject* obj);
	void handleSlicing(Player* player, SceneObject* obj);
	void handleRepair(Player* player, SceneObject* obj);
	void handleVehicleRepair(SceneObject* obj);
	void handleRemovePowerup(Player* player, SceneObject* obj);

	// Installation radial handling
	void handleManageHarvester(Player* player, SceneObject* obj);
	void handleStructureStatus(Player* player, SceneObject* obj);
	void handleStructureDestroy(Player* player, SceneObject* obj);
	void handleSetName(Player* player, SceneObject* obj);
	void handleStructureManageMaintenance(Player* player, SceneObject* obj);
	void handleStructureAddEnergy(Player* player, SceneObject* obj);

	void sendRadialResponseForVehicleDeed(Player* player, VehicleDeed* deed, ObjectMenuResponse* omr);

	void handleOpenCraftingToolHopper(Player* player, SceneObject* obj);
	void handleHarvest(Player* player, SceneObject* obj, int type);

	//Guildterminal
	void handleGuildCreationTag(Player* player);
	void handleGuildSponsor(Player* player);
	void handleGuildSponsored(Player* player);
	void handleGuildInformation(Player* player);
	void handleGuildDisband(Player* player);
	void handleGuildNameChange(Player* player);
	void handleGuildInformationMembers(Player* player);
	void handleGuildTransferLeader(Player* player);

	//Bankterminal
	void handleBankStorage(Player* player);

	//Surveytools
	void sendRadialResponseForSurveyTools(Player* player, SurveyTool* surveyTool, ObjectMenuResponse* omr);
	void sendRadialResponseForSurveyToolRange(Player* player, SceneObject* obj);

	//Dice
	void handleDiceRoll(Player* player, SceneObject* obj, int dnum);
	void handleDiceConfigure(Player* player, SceneObject* obj, int dsides);

	//Watch / Listen
	void handleEntertainerActions(Player* player, SceneObject* obj);

	void handleItemDrop(Player* player, SceneObject* obj);

	//Teach
	void handleTeach(SceneObject* obj, Player* trainer);

	//camp
	void handleDisbandCamp(Player* player,SceneObject* obj);

	//Insurance
	void handleInsureAllItems(Player* player, SceneObject* obj);


	//Structure Terminal
	void handleStructurePermissionList(Player* player, SceneObject* obj, uint8 listtype);
	void handleStructurePrivacy(Player* player, SceneObject* obj);
	void handleStructureTransferRequest(Player* player, SceneObject* obj);
	void handleStructureDeclareResidence(Player* player, SceneObject* obj);
	void handleStructurePayMaintenance(Player* player, SceneObject* obj);
	void handleStructureCreateVendor(Player* player, SceneObject* obj);
	void handleGiveVendorMaintenance(Player* player, SceneObject* obj);
};

#endif /*RADIALMANAGER_H_*/
