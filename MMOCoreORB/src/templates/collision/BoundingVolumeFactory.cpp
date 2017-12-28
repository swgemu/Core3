#include "BoundingVolumeFactory.h"

#include <stddef.h>

#include "BaseBoundingVolume.h"
#include "engine/log/Logger.h"
#include "engine/util/iffstream/IffStream.h"
#include "system/lang/String.h"
#include "system/platform.h"
#include "templates/collision/BoxVolume.h"
#include "templates/collision/CollisionMeshVolume.h"
#include "templates/collision/ComponentVolume.h"
#include "templates/collision/CompositeVolume.h"
#include "templates/collision/CylinderVolume.h"
#include "templates/collision/DetailVolume.h"
#include "templates/collision/SphereVolume.h"

BaseBoundingVolume* BoundingVolumeFactory::getVolume(IffStream *iff) {
	static Logger logger("BoundingVolumeFactory");

	BaseBoundingVolume *volume = NULL;
	uint32 type = iff->getNextFormType();
	switch(type) {
		case 'NULL':
			iff->openForm('NULL');
			iff->closeForm('NULL');
			return NULL;
		case 'EXBX':
			volume = new BoxVolume();
			break;
		case 'CPST':
			volume = new CompositeVolume();
			break;
		case 'CMSH':
			volume = new CollisionMeshVolume();
			break;
		case 'CMPT':
			volume = new ComponentVolume();
			break;
		case 'DTAL':
			volume = new DetailVolume();
			break;
		case 'XCYL':
			volume = new CylinderVolume();
			break;
		case 'EXSP':
			volume = new SphereVolume();
			volume->read(iff);
			return volume;
		default: {
			logger.error(iff->getFileName() + " - INVALID VOLUME TYPE " + String::hexvalueOf((int64)type));
			iff->openForm(type);
			iff->closeForm(type);
			return NULL;
		}
	}
	iff->openForm(type);
	volume->read(iff);
	iff->closeForm(type);

	return volume;
}
