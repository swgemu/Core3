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

class PortalLayout : public IffTemplate, public Logger {
	int cellTotalNumber;
	Vector<FloorMesh*> floorMeshes; // indexed by cells

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

	int getCellNumber() {
		return cellTotalNumber;
	}
};

#endif /* PORTALLAYOUT_H_ */
