/*
 * ForageArea.h
 *
 *  Created on: 02/14/2011
 *      Author: Anakis
 */

#ifndef FORAGEAREA_H_
#define FORAGEAREA_H_


class ForageArea : public Object {

protected:

	static const uint8 SIZE = 10;     //Determines the side length of the forage area 'box' (in meters).
	static const uint8 EXPIRE = 30;   //Determines the age when each area expires (in minutes).
	String planet;
	short xCoord;
	short yCoord;
	Time expiration;

public:

	uint8 uses;

     ForageArea(short playerX, short playerY, const String& plt) {
    	 xCoord = playerX;
    	 yCoord = playerY;
    	 planet = plt;
    	 expiration.addMiliTime(EXPIRE*60000);
    	 uses = 1;
     }

     int checkPermission(short playerX, short playerY, const String& playerPlanet) {

    	 //Check if area is expired.
    	 if (expiration.isPast())
    	 	return 0;

    	 //Check if player is inside this area.
    	 if (abs(xCoord - playerX) >= SIZE)
    	 	return 1;
    	 else if (abs(yCoord - playerY) >= SIZE)
    	 	return 1;
    	 else if (planet != playerPlanet)
    	 	return 1;

    	 //Check if player is allowed to forage here again.
    	 if (uses < 3)
    	 	return 2;
    	 else
    	 	return 3;

         //return 0: If zone is time expired so it can be deleted.
         //return 1: If player is not in this zone so we can ignore it.
         //return 2: If player is in this zone but hasn't used it 3 times (allow).
         //return 3: If player is in this zone and has used it 3 times (deny).

     }

};

#endif /* FORAGEAREA_H_ */
