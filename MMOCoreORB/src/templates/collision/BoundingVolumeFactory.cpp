#include "BoundingVolumeFactory.h"
#include "BaseBoundingVolume.h"
#include "templates/collision/BoundingVolumes.h"

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
