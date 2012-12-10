/*
 * SecurityTerminalDataComponent.h
 *
 *  Created on: Dec 10, 2012
 *      Author: root
 */

#ifndef SECURITYTERMINALDATACOMPONENT_H_
#define SECURITYTERMINALDATACOMPONENT_H_
#include "server/zone/objects/scene/components/DataObjectComponent.h"

class SecurityTerminalDataComponent : public DataObjectComponent {
protected:


public:
	SecurityTerminalDataComponent() {

	}

	virtual ~SecurityTerminalDataComponent() {

	}

	bool isSecurityTerminalData() {
		return true;
	}

};



#endif /* SECURITYTERMINALDATACOMPONENT_H_ */
