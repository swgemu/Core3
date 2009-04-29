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

#ifndef PETCOMMANDHELPER_H_
#define PETCOMMANDHELPER_H_

#include "system/lang.h"
#include "CreaturePet.h"

class PetCommandHelper : public Vector<String> {
public:
	//novice ch
	static const int PETATTACK = 0;
	static const int PETFOLLOW = 1;
	static const int PETSTORE = 2;
	static const int PETRELEASE = 3;

	//taming tree
	static const int PETSPECIALATTACK1 = 4;
	static const int PETSPECIALATTACK2 = 5;

	//training tree
	static const int PETSTAY = 6;
	static const int PETGUARD = 7;
	static const int PETPATROL = 8;
	static const int PETPATROLPOINTADD = 9;
	static const int PETPATROLPOINTCLEAR = 10;
	static const int PETFORMATION1= 11;
	static const int PETFORMATION2= 12;

	//training tree
	static const int PETTRICK1 = 13;
	static const int PETEMBOLDEN = 14;
	static const int PETTRICK2 = 15;
	static const int PETENRAGE = 16;

	//management tree
	static const int PETGROUP = 17;
	static const int PETFOLLOWOTHER = 18;
	static const int PETFRIEND = 19;

	//master
	static const int PETRANGEDATTACK = 20;
	static const int PETTRANSFER = 21;
protected:
	//Vector<String>* commandList;

public:
	PetCommandHelper();
	virtual ~PetCommandHelper();

	String& getBaseCommand(int command);
	void trainCommand(int command, String& commandMessage);

	void trainName(CreaturePet* pet);
};

#endif /* PETCOMMANDHELPER_H_ */
