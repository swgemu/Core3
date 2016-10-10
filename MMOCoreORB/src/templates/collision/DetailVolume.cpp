#include "DetailVolume.h"

void DetailVolume::read(IffStream* iff) {
	iff->openForm('0000');
	iff->openForm('CPST');
	CompositeVolume::read(iff);
	iff->closeForm('CPST');
	iff->closeForm('0000');
}
#ifdef OSG_RENDERER
osg::ref_ptr<osg::Node> DetailVolume::draw() const {
	osg::ref_ptr<osg::Group> group(new osg::Group);

	for(int i=1; i<volumes.size(); i++) {
		group->addChild(volumes.get(i)->draw());
	}
	return group;
}
#endif