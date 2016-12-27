/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLANETTRAVELPOINTLISTRESPONSE_H_
#define PLANETTRAVELPOINTLISTRESPONSE_H_

#include "engine/service/proto/BaseMessage.h"

class TravelPoint {
	String name;
	
	float positionX;
	float positionY;
	float positionZ;
	
	uint32 tax;
	uint8 starport;
	
public:
	TravelPoint(const String& Name, float x, float z, float y, uint32 tax, uint8 starport) {
		name = Name;
		
		positionX = x;
		positionY = y;
		positionZ = z;
		
		this->tax = tax;
		this->starport = starport;
	}
	
	friend class PlanetTravelPointListResponse;
};

class PlanetTravelPointListResponse : public BaseMessage {
	Vector<TravelPoint*> travelPoints;
	
public:
	PlanetTravelPointListResponse() : BaseMessage() {
		insertShort(0x06);
		insertInt(0x4D32541F); //PlanetTravelPointListResponse

		insertAscii("naboo");
	}

	PlanetTravelPointListResponse(const String& planet) : BaseMessage() {
		insertShort(0x06);
		insertInt(0x4D32541F);  //PlanetTravelPointListResponse
        insertAscii(planet);

        setCompression(true);
	}
	
	~PlanetTravelPointListResponse() {
		while (travelPoints.size() > 0) {
			TravelPoint* point = travelPoints.remove(0);

			delete point;
		}
	}
    
    void addPoint(const String& name, float x, float z, float y, uint32 tax, uint8 starport) {
    	travelPoints.add(new TravelPoint(name, x, z, y, tax, starport));
    }
    
    void generateMessage() {
    	insertNames();
    	insertCoords();
    	insertTax();
    	insertStarport();
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
    
    void insertTax() {
    	insertInt(travelPoints.size());

    	for (int i = 0; i < travelPoints.size(); ++i) {
    		TravelPoint* point = travelPoints.get(i);

    		insertInt(point->tax);
    	}
    }
    
    void insertStarport() {
    	insertInt(travelPoints.size());

    	for (int i = 0; i < travelPoints.size(); ++i) {
    		TravelPoint* point = travelPoints.get(i);

    		insertByte(point->starport);
    	}
    }
	
};

#endif /*PLANETTRAVELPOINTLISTRESPONSE_H_*/
