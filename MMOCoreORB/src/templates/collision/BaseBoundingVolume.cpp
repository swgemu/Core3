#include "BaseBoundingVolume.h"

void BaseBoundingVolume::read(IffStream *iff) {
	iff->openForm('EXSP');
	iff->openForm('0001');
	iff->openChunk('SPHR');
	float x = iff->getFloat();
	float y = iff->getFloat();
	float z = iff->getFloat();
	float radius = iff->getFloat();

	bsphere = Sphere(Vector3(x, y, z), radius);

	iff->closeChunk('SPHR');
	iff->closeForm('0001');
	iff->closeForm('EXSP');
}
