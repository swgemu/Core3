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

#ifndef PLAYERHAM_H_
#define PLAYERHAM_H_

static int professionHams[][9] = {
		{ 600, 300, 300, 800, 400, 300, 900, 400, 500 },
		{ 1000, 500, 400, 800, 350, 350, 500, 300, 300 },
		{ 500, 300, 300, 1000, 400, 400, 800, 400, 400 },
		{ 1000, 450, 300, 800, 450, 300, 600, 300, 300 },
		{ 600, 300, 300, 700, 300, 300, 1000, 500, 500 },
		{ 800, 300, 350, 800, 400, 400, 700, 350, 400 },
		{ 800, 350, 350, 800, 350, 350, 800, 350, 350 }
};

static int raceHamMods[][9] = {
		{ 100, 100, 100, 100, 100, 100, 100, 100, 100 },
		{ 250, 300, 400, 0, 0, 0, 0, 0, 100 },
		{ 0, 0, 250, 250, 300, 0, 100, 0, 0 },
		{ 0, 0, 0, 300, 300, 100, 100, 100, 0 },
		{ 200, 0, 0, 300, 0, 0, 0, 0, 400 },
		{ 0, 0, 0, 200, 200, 450, 0, 0, 50 },
		{ 0, 0, 0, 0, 0, 150, 300, 300, 150 },
		{ 350, 350, 150, 200, 100, 100, 100, 150, 100 },
		{ 150, 0, 0, 250, 50, 50, 200, 100, 100 },
		{ 0, 0, 0, 0, 0, 150, 300, 300, 150 }
};

#endif /*PLAYERHAM_H_*/
