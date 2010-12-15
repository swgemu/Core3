/*
 * PortalLayout.h
 *
 *  Created on: 02/12/2010
 *      Author: victor
 */

#ifndef PORTALLAYOUT_H_
#define PORTALLAYOUT_H_

#include "../IffTemplate.h"

class FloorMesh;
class MeshAppearanceTemplate;

class PortalLayout : public IffTemplate, public Logger {
	int cellTotalNumber;
	Vector<FloorMesh*> floorMeshes; // indexed by cells started by 0
	Vector<MeshAppearanceTemplate*> appearanceTemplates;

public:
	PortalLayout() {
		cellTotalNumber = 0;

		setLoggingName("PortalLayout");
	}

	void readObject(IffStream* templateData) {
		parse(templateData);
	}

	void parse(IffStream* iffStream);

	void parseCELSForm(IffStream* iffStream);

	inline int getCellTotalNumber() {
		return cellTotalNumber;
	}

	inline FloorMesh* getFloorMesh(int cellIndex) {
		return floorMeshes.get(cellIndex);
	}

	inline MeshAppearanceTemplate* getMeshAppearanceTemplate(int cellIndex) {
		return appearanceTemplates.get(cellIndex);
	}

	inline int getAppearanceTemplatesSize() {
		return appearanceTemplates.size();
	}

};

#endif /* PORTALLAYOUT_H_ */
