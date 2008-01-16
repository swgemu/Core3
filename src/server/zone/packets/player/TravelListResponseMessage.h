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

#ifndef TRAVELLISTRESPONSEMESSAGE_H_
#define TRAVELLISTRESPONSEMESSAGE_H_

#include "engine/engine.h"

class TravelPoint {
	string name;
	
	float positionX;
	float positionY;
	float positionZ;
	
	uint32 unknown1;
	uint8 unknown2;
	
public:
	TravelPoint(const string& Name, float x, float z, float y) {
		name = Name;
		
		positionX = x;
		positionY = y;
		positionZ = z;
		
		unknown1 = 0xC8;
		unknown2 = 1;
	}
	
	friend class TravelListResponseMessage;
};

class TravelListResponseMessage : public BaseMessage {
	Vector<TravelPoint*> travelPoints;
	
public:
    TravelListResponseMessage(const string& planet) : BaseMessage() {
		insertShort(0x06);
		insertInt(0x4D32541F);  // CRC
        insertAscii(planet);
        /*
        insertInt(2); 
	    insertAscii("Bestine");
	    insertAscii("Anchorhead");
	    //insertAscii("Coronet");
        
        insertInt(2);
        insertFloat(-1090);
        insertFloat(12.6);
        insertFloat(-3558);
               
        insertFloat(54);
        insertFloat(52.6);
        insertFloat(-5332);
        
        /*insertFloat(-338);
        insertFloat(28);
        insertFloat(-4634);*//*
  
        insertInt(2); 
        insertInt(0xC8);
        insertInt(0xC8);
        //insertInt(0xC8);
        
        insertInt(2); 
        insertByte(1); //??
        insertByte(1); //??
        //insertByte(1); //??*/
	}
    
    void addPoint(const string& name, float x, float z, float y) {
    	TravelPoint* point = new TravelPoint(name, x, z, y);
    	travelPoints.add(point);
    }
    
    void generateMessage() {
    	insertNames();
    	insertCoords();
    	insertUnknown1();
    	insertUnknown2();
    	
    	while (travelPoints.size() > 0) {
    		TravelPoint* point = travelPoints.get(0);
    		
    		travelPoints.remove(0);
    		delete point;
    	}
    }
    
    void insertNames() {
    	insertInt(travelPoints.size());
        	
    	for (int i = 0; i < travelPoints.size(); ++i) {
    		TravelPoint* point = travelPoints.get(i);
    		
    		insertAscii(point->name);
    	}
    }
    
    void insertCoords() {
    	insertInt(travelPoints.size());

    	for (int i = 0; i < travelPoints.size(); ++i) {
    		TravelPoint* point = travelPoints.get(i);

    		insertFloat(point->positionX);
    		insertFloat(point->positionZ);
    		insertFloat(point->positionY);
    	}
    }
    
    void insertUnknown1() {
    	insertInt(travelPoints.size());

    	for (int i = 0; i < travelPoints.size(); ++i) {
    		TravelPoint* point = travelPoints.get(i);

    		insertInt(point->unknown1);
    	}
    }
    
    void insertUnknown2() {
    	insertInt(travelPoints.size());

    	for (int i = 0; i < travelPoints.size(); ++i) {
    		TravelPoint* point = travelPoints.get(i);

    		insertByte(point->unknown2);
    	}
    }
	
};

#endif /*TRAVELLISTRESPONSEMESSAGE_H_*/
