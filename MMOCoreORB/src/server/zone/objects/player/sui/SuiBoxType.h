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

#ifndef SUIBOXTYPE_H_
#define SUIBOXTYPE_H_

class SuiBoxType {
public:

	static const int MOTD = 0x0000;
	static const int CONSENT = 0x0001;

	static const int CLONE_REQUEST = 0x0002;

	static const int START_MUSIC = 0x0003;
	static const int START_DANCING = 0x0004;
	static const int CHANGE_MUSIC = 0x0005;
	static const int CHANGE_DANCING = 0x0006;

	static const int SURVEY_TOOL_RANGE = 0x0007;

	static const int GUILD_CREATION_INPUT_FOR_TAG = 0x0008;
	static const int GUILD_CREATION_INPUT_FOR_NAME = 0x0009;
	static const int GUILD_SPONSORING_MEMBER_INPUT_FOR_NAME = 0x0010;
	static const int VERIFY_SPONSOR_TARGET_FOR_GUILD_MEMBERSHIP = 0x0011;
	static const int SPONSORED_GUILD_MEMBERS = 0x0012;
	static const int SPONSORED_GUILD_MEMBERS_ACCEPT = 0x0013;
	static const int GUILD_DISBAND = 0x0014;
	static const int GUILD_NAME_CHANGE = 0x0015;
	static const int GUILD_NAME_CHANGE_NAME = 0x0016;
	static const int GUILD_INFORMATION_MEMBERS = 0x0017;
	static const int GUILD_MEMBER_OPTIONS = 0x0018;
	static const int GUILD_PERMISSION_SELECTION = 0x0019;
	static const int REMOVE_FROM_GUILD = 0x0020;
	static const int GUILD_TRANSFER_LEADER = 0x0021;
	static const int GUILD_TRANSFER_LEADER_VERIFY = 0x0022;

	static const int TICKET_PURCHASE_MESSAGE = 0x0023;
	static const int TICKET_COLLECTOR_RESPONSES = 0x0024;

	static const int COLOR_PICKER1 = 0x0025;
	static const int COLOR_PICKER2 = 0x0026;

	static const int BANK_TRANSFER = 0x0027;

	static const int BLUE_FROG_ITEM_REQUEST = 0x0028;

	static const int WOUND_TERMINAL_REQUEST = 0x0029;
	static const int STATE_TERMINAL_REQUEST = 0x0030;
	static const int DIAGNOSE = 0x0031;

	static const int FREE_RESOURCE = 0x0032;
	static const int GIVE_FREE_RESOURCE = 0x0033;

	static const int TEACH_SKILL = 0x0034;
	static const int TEACH_PLAYER = 0x0035;
	static const int DENY_TRAINING_LIST = 0x0036;

};

#endif /*SuiBoxType_H_*/
