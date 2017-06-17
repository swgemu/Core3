/*
 * ComponentAppearanceTemplate.h
 *
 *  Created on: 10/12/2010
 *      Author: victor
 */

#ifndef COMPONENTAPPEARANCETEMPLATE_H_
#define COMPONENTAPPEARANCETEMPLATE_H_

#include "templates/appearance/AppearanceTemplate.h"
#include "templates/manager/TemplateManager.h"

class ComponentMeshAppearanceTemplate : public Object {
	Matrix4 transform;
	Matrix4 inverseTransform;
	AppearanceTemplate *mesh;
public:
	ComponentMeshAppearanceTemplate(const Matrix4 &transform, const Matrix4 &inverse, AppearanceTemplate *mesh) {
		this->transform = Matrix4(transform);
		this->inverseTransform = Matrix4(inverse);
		this->mesh = mesh;
	}

	const Matrix4& getTransform() const {
		return transform;
	}

	const Matrix4& getInverseTransform() const {
		return inverseTransform;
	}

	const AppearanceTemplate* getMeshTemplate() const {
		return mesh;
	}
};

class ComponentAppearanceTemplate : public AppearanceTemplate {
	Vector<Reference<ComponentMeshAppearanceTemplate*> > meshes;

public:
	virtual uint32 getType() const {
		return 'CMPA';
	}
	ComponentAppearanceTemplate() {
	}

	~ComponentAppearanceTemplate() {
	}

	const Vector<Reference<ComponentMeshAppearanceTemplate*> >& getComponents() const {
		return meshes;
	}

	void readObject(IffStream* templateData) {
		parse(templateData);
	}

	void parse(IffStream* iffStream) {
		iffStream->openForm('CMPA');

		uint32 version = iffStream->getNextFormType();
		iffStream->openForm(version);

		AppearanceTemplate::readObject(iffStream);

		if(iffStream->getNextFormType() == 'RADR') {
			iffStream->openForm('RADR');
			iffStream->closeForm('RADR');
		}

		int subChunks = iffStream->getRemainingSubChunksNumber();// dataChunk->getChunksSize();

		// load *all* components
		for (int i = 0; i < subChunks; ++i) {
			iffStream->openChunk('PART');

			// int var1 = iffStream->getInt();

			/*QString str;
	                    iffStream->getString(str);*/

			String meshFile;
			iffStream->getString(meshFile);

			AppearanceTemplate* templ = TemplateManager::instance()->getAppearanceTemplate("appearance/" + meshFile);

			if (templ == NULL) {
				System::out << "Template not found appearance/" << meshFile;
				continue;
			}
			Matrix4 mat;
			Matrix4 inverse;
			for (int x = 0; x < 3; x++) {
				for (int y = 0; y < 4; y++)
				{
					float val = iffStream->getFloat();
					inverse[x][y] = val;
					mat[y][x] = val;
				}
			}

			float x = mat[3][0];
			float y = mat[3][1];
			float z = mat[3][2];

			inverse[0][3] = inverse[1][3] = inverse[2][3] = 0;

			inverse[3][0] = -(mat[0][0] * x + mat[0][1] * y + mat[0][2] * z);
			inverse[3][1] = -(mat[1][0] * x + mat[1][1] * y + mat[1][2] * z);
			inverse[3][2] = -(mat[2][0] * x + mat[2][1] * y + mat[2][2] * z);

			meshes.add(new ComponentMeshAppearanceTemplate(mat, inverse, templ));

			iffStream->closeChunk('PART');
		}

		iffStream->closeForm(version);
		iffStream->closeForm('CMPA');
	}

	virtual bool testCollide(const Sphere& testsphere) const {
		for(int i=0; i<meshes.size(); i++) {
			const ComponentMeshAppearanceTemplate *mesh = meshes.get(i);

			Vector3 position = testsphere.getCenter() * mesh->getInverseTransform();
			Sphere sphere(position, testsphere.getRadius());
			if(mesh->getMeshTemplate()->testCollide(sphere))
				return true;
		}
		return false;
	}

	/**
	 * Checks for intersection against ray, stops on any intersection
	 * @return intersectionDistance, triangle which it intersects
	 */
	virtual bool intersects(const Ray& ray, float distance, float& intersectionDistance, Triangle*& triangle, bool checkPrimitives = false) const {

		for(int i=0; i<meshes.size(); i++) {
			const ComponentMeshAppearanceTemplate *mesh = meshes.getUnsafe(i);

			Vector3 start = ray.getOrigin() * mesh->getInverseTransform();
			Vector3 end = ray.getDirection() * mesh->getInverseTransform();
			Ray transformedRay(start, end);

			if(mesh->getMeshTemplate()->intersects(transformedRay, distance, intersectionDistance, triangle, checkPrimitives))
				return true;
		}

		return false;
	}

	/**
	 * Checks for all intersections
	 */
	virtual int intersects(const Ray& ray, float maxDistance, SortedVector<IntersectionResult>& result) const {

		for(int i=0; i<meshes.size(); i++) {
			const ComponentMeshAppearanceTemplate *mesh = meshes.get(i);

			Vector3 start = ray.getOrigin() * mesh->getInverseTransform();
			Vector3 end = ray.getDirection() * mesh->getInverseTransform();
			Ray transformedRay(start, end);

			if(mesh->getMeshTemplate()->intersects(transformedRay, maxDistance, result))
				return true;
		}
		
		return false;
	}

	virtual Vector<Reference<MeshData* > > getTransformedMeshData(const Matrix4& parentTransform) const {
		Vector<Reference<MeshData*> > transformedMeshData;
		for(int i=0; i<meshes.size(); i++) {

			ComponentMeshAppearanceTemplate *mesh = meshes.get(i);

			Matrix4 newMat = mesh->getTransform();
			newMat.swapLtoR();

			transformedMeshData.addAll(mesh->getMeshTemplate()->getTransformedMeshData(newMat * parentTransform));
		}

		return transformedMeshData;
	}

};

#endif /* COMPONENTAPPEARANCETEMPLATE_H_ */
