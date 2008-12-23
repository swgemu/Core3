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

#ifndef FORAGEZONE_H_
#define FORAGEZONE_H_


class ForageZone {

protected:

	static const uint8 RADIUS = 10;   //Determines the size of the forage zones (in meters).
	static const uint8 EXPIRE = 30;   //Determines the age when each no-forage zone expires (in minutes).
	uint8 planet;
	float xCoord;
	float yCoord;
	Time timeStamp;

public:

	uint8 uses;

     ForageZone(float x, float y, int plt) {
    	xCoord = x;
        yCoord = y;
        planet = plt;
        uses = 1;
     }

     int zonePermission(float currentx, float currenty, int currentplanet) {

    	 //Check if zone is expired.
    	 uint32 age = timeStamp.miliDifference();
         if (age >= EXPIRE * 60 * 1000)
        	 return 0;

         //Check if player is in this zone.
    	 double distance = sqrt((square(xCoord - currentx)) + (square(yCoord - currenty)));
         if (distance >= RADIUS || currentplanet != planet)
        	 return 1;

         //Check if player has already foraged 3 times in this zone.
         if (uses < 3)
        	 return 2;
          else
        	 return 3;

         //return 0: If zone is time expired so it can be deleted.
         //return 1: If player is not in this zone so we can ignore it.
         //return 2: If player is in this zone but hasn't used it 3 times (allow).
         //return 3: If player is in this zone and has used it 3 times (deny).

     }


     float square(float a) {
    	 return a * a;
     }

};

#endif /* FORAGEZONE_H_ */
