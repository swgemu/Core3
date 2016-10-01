#ifndef CLIENTCOMPONENTAPPEARANCE_H_
#define CLIENTCOMPONENTAPPEARANCE_H_

#include "ClientAppearance.h"
#include "templates/appearance/ComponentAppearanceTemplate.h"
#include "client/zone/managers/appearance/AppearanceManager.h"

class ClientComponentMeshAppearance : public Object {
	ClientAppearance *appearance;
	Matrix4 transform;
	Matrix4 inverseTransform;
public:
	ClientComponentMeshAppearance(const Matrix4& transform, const Matrix4& inverseTransform, const AppearanceTemplate *mesh){
		this->transform = Matrix4(transform);
		this->inverseTransform = Matrix4(inverseTransform);
		appearance = AppearanceManager::instance()->getAppearance(mesh);
	}
	
	ClientAppearance* getAppearance() const {
		return appearance;
	}
	
	const Matrix4& getTransform() const {
		return transform;
	}
	
	Matrix4 getTransform() {
		return transform;
	}
};

class ClientComponentAppearance : public ClientAppearance {
	
	Vector<Reference<ClientComponentMeshAppearance*> > components;
	
public:
	
	ClientComponentAppearance(const AppearanceTemplate *tmpl) : ClientAppearance(tmpl) {
		const ComponentAppearanceTemplate *comp = cast<const ComponentAppearanceTemplate*>(tmpl);
		assert(comp != NULL);
		const Vector<Reference<ComponentMeshAppearanceTemplate*> > templateComponents =  comp->getComponents();
		
		for(int i=0; i<templateComponents.size(); i++) {
			const ComponentMeshAppearanceTemplate *comp = templateComponents.get(i);
			components.add(new ClientComponentMeshAppearance(comp->getTransform(), comp->getInverseTransform(), comp->getMeshTemplate()));
		}
	}
	
	virtual osg::ref_ptr<osg::Node> draw()  {
		osg::ref_ptr<osg::Group> group(new osg::Group);
		
		for(int i=0; i<components.size(); i++) {
			osg::MatrixTransform * transform  = new osg::MatrixTransform( );
			const ClientComponentMeshAppearance *mesh = components.get(i);
			
			
			if(mesh->getAppearance() == NULL)
				continue;
			
			Matrix4 ourTransform = mesh->getTransform();
			
			osg::Matrix matrix(ourTransform[0][0], ourTransform[1][0], ourTransform[2][0], ourTransform[3][0],
							   ourTransform[0][1], ourTransform[1][1], ourTransform[2][1], ourTransform[3][1],
							   ourTransform[0][2], ourTransform[1][2], ourTransform[2][2], ourTransform[3][2],
							   0, 0, 0, 1);
			
			matrix(0, 2) = -matrix(0, 2);
			matrix(1, 2) = -matrix(1, 2);
			matrix(2, 0) = -matrix(2, 0);
			matrix(2, 1) = -matrix(2, 1);
			matrix(3, 2) = -matrix(3, 2);
			
			transform->setMatrix(matrix);
			
			transform->addChild(mesh->getAppearance()->draw());
			
			group->addChild(transform);
			
		}
		
		return group;
	}
};
#endif
