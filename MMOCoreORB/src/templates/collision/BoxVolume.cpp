#include "BoxVolume.h"

void BoxVolume::read(IffStream *iff) {
	iff->openForm('0001');
	BaseBoundingVolume::read(iff);
	iff->openChunk('BOX ');
	float minx = iff->getFloat();
	float miny = iff->getFloat();
	float minz = iff->getFloat();
	
	float maxx = iff->getFloat();
	float maxy = iff->getFloat();
	float maxz = iff->getFloat();
	bbox = AABB(Vector3(minx, miny, minz), Vector3(maxx, maxy, maxz));
	iff->closeChunk('BBOX');
	iff->closeForm('0001');
}

//osg::ref_ptr<osg::Node> BoxVolume::draw() {
//	return bbox.draw();
//}