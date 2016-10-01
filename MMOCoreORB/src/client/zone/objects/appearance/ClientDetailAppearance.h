#ifndef CLIENTDETAILAPPEARANCE_H_
#define CLIENTDETAILAPPEARANCE_H_
#include "ClientAppearance.h"
#include "templates/appearance/DetailAppearanceTemplate.h"

class ClientDetailAppearance : public ClientAppearance{
	Vector<ClientAppearance*> lodMeshes;
public:
	ClientDetailAppearance(const AppearanceTemplate *tmpl) : ClientAppearance(tmpl) {
		const DetailAppearanceTemplate *dtal = cast<const DetailAppearanceTemplate*>(tmpl);
		//assert(dtal != NULL);
		
		const AppearanceTemplate *child = dtal->getFirstMesh();
		
		if (child != NULL) {
			ClientAppearance *appearance = AppearanceManager::instance()->getAppearance(child);
		
			if(appearance != NULL)
				lodMeshes.add(appearance);
		}
	}
	
	osg::ref_ptr<osg::Node> draw() {
		osg::ref_ptr<osg::Group> group(new osg::Group);
		
		for (int i=0; i<lodMeshes.size(); i++) {
			if(lodMeshes.get(i) != NULL) {
				group->addChild(lodMeshes.get(i)->draw());
			}
		}
		
		return group;
	}
};
#endif
