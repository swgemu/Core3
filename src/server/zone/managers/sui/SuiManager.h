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

#ifndef SUIMANAGER_H_
#define SUIMANAGER_H_

#include "SuiManager.h"
#include "engine/engine.h"

class ZoneProcessServerImplementation;
class Player;

class SuiManager : public Logger {
	ZoneProcessServerImplementation* server;

public:
	SuiManager(ZoneProcessServerImplementation* serv);

	void handleSuiEventNotification(uint32 boxID, Player* player, uint32 cancel, const String& value, const String& value2);

	void handleStartMusic(uint32 boxID, Player* player, uint32 cancel, const String& song, bool change = false);
	void handleStartDancing(uint32 boxID, Player* player, uint32 cancel, const String& dance, bool change = false);

	void handleSurveyToolRange(uint32 boxID, Player* player, uint32 cancel, int range);

	void handleSliceWeapon(uint32 boxID, Player* player, uint32 cancel, int itemindex);
	void handleSliceArmor(uint32 boxID, Player* player, uint32 cancel, int itemindex);

	void handleRepairWeapon(uint32 boxID, Player* player, uint32 cancel, int itemindex);
	void handleRepairArmor(uint32 boxID, Player* player, uint32 cancel, int itemindex);

	void handleTicketPurchaseMessageBox(uint32 boxID, Player* player);
	void handleTicketCollectorRespones(uint32 boxID, Player* player, uint32 cancel, int ticketIndex);

	void handleCodeForRedeed(uint32 boxID, Player* player, uint32 cancel, const String& extra);
	void handleRedeedStructure(uint32 boxID, Player* player, uint32 cancel, const int extra);
	void handleRefreshStatusListBox(uint32 boxID, Player* player, uint32 cancel, const int extra);
	void handleSetObjectName(uint32 boxID, Player* player, uint32 cancel, const String& name);
	void handleAddMaintenance(uint32 boxID, Player* player,uint32 cancel, const String& name);
	void handleAddEnergy(uint32 boxID, Player* player,uint32 cancel, const String& name);


	void handleColorPicker(uint32 boxID, Player* player, uint32 cancel, const String& value, int var);

	void handleBankTransfer(uint32 boxID, Player* player, int cash, int bank);

	void handleBlueFrogItemRequest(uint32 boxID, Player* player, uint32 cancel, int itemIndex);
	void handleWoundTerminalRequest(uint32 boxID, Player* player, uint32 cancel, int itemIndex);
	void handleStateTerminalRequest(uint32 boxID, Player* player, uint32 cancel, int itemIndex);

	void handleDiagnose(uint32 boxID, Player* player);
	void handleFreeResource(uint32 boxID, Player* player, uint32 cancel, int index);
	void handleGiveFreeResource(uint32 boxID, Player* player, uint32 cancel, int index);

	void handleCloneRequest(uint32 boxID, Player* player, uint32 cancel, int value);
	void handleConsentBox(uint32 boxID, Player* player, uint32 cancel, int value);

	void handleDenyTrainingList(uint32 boxID, Player* player);

	void handleTeachPlayer(uint32 boxID, Player* player, int value, uint32 cancel);
	void handleTeachSkill(uint32 boxID, Player* player, uint32 cancel);

};

#endif /*SUIMANAGER_H_*/
