/*
 * AppearanceTemplate.h
 *
 *  Created on: 11/12/2010
 *      Author: victor
 */

#ifndef APPEARANCETEMPLATE_H_
#define APPEARANCETEMPLATE_H_

#include "engine/engine.h"
#include "templates/IffTemplate.h"
#include "templates/collision/BoundingVolumes.h"
#include "templates/collision/BoundingVolumeFactory.h"

class AppearanceTemplate/* : public IffTemplate*/ {
	String floorName;
	String fileName;
	BaseBoundingVolume *volume;
	BaseBoundingVolume *collisionVolume;
public:
	
	virtual uint32 getType() {
		return 'APPR';
	}
	
	String getFloorMesh() {
		return floorName;
	}
	const BaseBoundingVolume* getBoundingVolume() {
		return volume;
	}
	
	const BaseBoundingVolume* getCollisionVolume() {
		return collisionVolume;
	}
	
	
	virtual void readObject(IffStream* iffStream) {
		
		fileName = iffStream->getFileName();
		
		iffStream->openForm('APPR');
		uint32 formType = iffStream->getNextFormType();
		if (formType == '0003') {
			iffStream->openForm('0003');
			volume = BoundingVolumeFactory::getVolume(iffStream);
			collisionVolume = BoundingVolumeFactory::getVolume(iffStream);
			
			
			iffStream->openForm('HPTS');
			
			// Skip loading hardpoints
			iffStream->closeForm('HPTS');
			
			iffStream->openForm('FLOR');
			iffStream->openChunk('DATA');
			bool hasFloor = iffStream->getByte();
			if(hasFloor)
				iffStream->getString(floorName);
			iffStream->closeChunk('DATA');
			iffStream->closeForm('FLOR');
			
			iffStream->closeForm('0003');
		} else {
			String msg = "AppearanceTemplate::readObject unknown version ("+String::hexvalueOf((int64)formType)+")";
			throw Exception(msg);
		}
		//ignoring this atm
		iffStream->closeForm('APPR');

	}

	virtual ~AppearanceTemplate() {

	}

	//void readObject(IffStream* templateData) = 0;

	virtual AppearanceTemplate* getFirstMesh() {
		return NULL;
	}
};

#endif /* APPEARANCETEMPLATE_H_ */
