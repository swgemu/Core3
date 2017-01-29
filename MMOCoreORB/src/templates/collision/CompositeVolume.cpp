#include "CompositeVolume.h"
#include "BoundingVolumeFactory.h"

void CompositeVolume::read(IffStream *iff) {
	iff->openForm('0000');
	uint32 chunks = iff->getSubChunksNumber();
	for(int i=0; i<chunks; i++) {
			Reference<BaseBoundingVolume*> volume = BoundingVolumeFactory::getVolume(iff);
			volumes.add(volume);
	}
	iff->closeForm('0000');
}
#ifdef OSG_RENDERER
osg::ref_ptr<osg::Node> CompositeVolume::draw() const {
	osg::ref_ptr<osg::Group> group(new osg::Group);

	for(int i=0; i<volumes.size(); i++) {
		group->addChild(volumes.get(i)->draw());
	}
	return group;
}
#endif
