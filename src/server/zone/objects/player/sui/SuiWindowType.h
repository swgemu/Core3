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

#ifndef SUIWINDOWTYPE_H_
#define SUIWINDOWTYPE_H_

class SuiWindowType {
public:

	static const int MOTD = 0;
	static const int CONSENT = 1;

	static const int CLONE_REQUEST = 2;
	static const int CLONE_CONFIRM = 3;

	static const int START_MUSIC = 4;
	static const int START_DANCING = 5;
	static const int CHANGE_MUSIC = 6;
	static const int CHANGE_DANCING = 7;

	static const int SURVEY_TOOL_RANGE = 8;

	static const int GUILD_CREATION_INPUT_FOR_TAG = 9;
	static const int GUILD_CREATION_INPUT_FOR_NAME = 10;
	static const int GUILD_SPONSORING_MEMBER_INPUT_FOR_NAME = 11;
	static const int VERIFY_SPONSOR_TARGET_FOR_GUILD_MEMBERSHIP = 12;
	static const int SPONSORED_GUILD_MEMBERS = 13;
	static const int SPONSORED_GUILD_MEMBERS_ACCEPT = 14;
	static const int GUILD_DISBAND = 15;
	static const int GUILD_NAME_CHANGE = 16;
	static const int GUILD_NAME_CHANGE_NAME = 17;
	static const int GUILD_INFORMATION_MEMBERS = 18;
	static const int GUILD_MEMBER_OPTIONS = 19;
	static const int GUILD_PERMISSION_SELECTION = 20;
	static const int REMOVE_FROM_GUILD = 21;
	static const int GUILD_TRANSFER_LEADER = 22;
	static const int GUILD_TRANSFER_LEADER_VERIFY = 23;

	static const int TICKET_PURCHASE_MESSAGE = 24;
	static const int TICKET_COLLECTOR_RESPONSES = 25;

	static const int COLOR_PICKER1 = 26;
	static const int COLOR_PICKER2 = 27;

	static const int BANK_TRANSFER = 28;

	static const int BLUE_FROG_ITEM_REQUEST = 29;

	static const int WOUND_TERMINAL_REQUEST = 30;
	static const int STATE_TERMINAL_REQUEST = 31;
	static const int DIAGNOSE = 32;

	static const int FREE_RESOURCE = 33;
	static const int GIVE_FREE_RESOURCE = 34;

	static const int TEACH_SKILL = 35;
	static const int TEACH_PLAYER = 36;
	static const int DENY_TRAINING_LIST = 37;

	static const int OBJECT_NAME = 38;
	static const int ADD_ENERGY = 40;
	static const int INSTALLATION_STATUS = 41;

	static const int INSURANCE_MENU = 44;
	static const int INSURE_ALL_CONFIRM = 45;

	static const int BANK_TIP_CONFIRM = 46;

	static const int SLICING_MENU = 47;

	static const int RANGER_WHAT_TO_TRACK = 48;

	static const int SET_MOTD = 49;

	static const int PERMISSION_LIST = 50;

	static const int CAMP_INFO = 51;

	static const int FACTORY_SCHEMATIC2BUTTON = 52;
	static const int FACTORY_SCHEMATIC3BUTTON = 53;
	static const int FACTORY_INGREDIENTS = 54;

	static const int TUNE_CRYSTAL = 60;
	static const int INSERT_COLOR_CRYSTAL = 61;

	static const int JUNK_DEALER_SELL_LIST = 70;

	static const int COMMANDSLIST = 80;
	static const int BANLIST = 81;
	static const int ACCOUNTLIST = 82;
	static const int CHARACTERLIST = 83;

	static const int FISHING = 90;

	static const int CHARACTERBUILDERITEMSELECT = 100;

	static const int SAMPLERADIOACTIVECONFIRM = 110;
	static const int SURVEY_TOOL_CONCENTRATED_MINIGAME = 111;
	static const int SURVEY_TOOL_CONCENTRATED_MINIGAME2 = 112;

	static const int STRUCTURE_STATUS = 115;
	static const int STRUCTURE_DESTROY_CONFIRM = 116;
	static const int STRUCTURE_DESTROY_CODE = 117;
	static const int STRUCTURE_MANAGE_MAINTENANCE = 118;

	static const int COMMAND_FIND = 119;

	static const int GAMBLINGROULETTE = 120;
	static const int GAMBLINGSLOT = 121;
	static const int GAMBLINGSLOTPAYOUT = 122;

	static const int CITY_CREATE = 123;
	static const int CITY_ENABLEZONING = 124;
	static const int CITY_SETNAME = 125;
};

#endif /*SuiWindowType_H_*/
