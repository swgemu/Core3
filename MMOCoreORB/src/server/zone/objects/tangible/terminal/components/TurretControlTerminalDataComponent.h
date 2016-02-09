/*
 * TurretControlTerminalDataComponent.h
 *
 *  Created on: Jan 27, 2013
 *      Author: root
 */

#ifndef TURRETCONTROLTERMINALDATACOMPONENT_H_
#define TURRETCONTROLTERMINALDATACOMPONENT_H_
#include "server/zone/objects/scene/components/DataObjectComponent.h"

class TurretControlTerminalDataComponent : public DataObjectComponent {
protected:
	int turretIndex;
	unsigned int suiBoxID;

public:
	TurretControlTerminalDataComponent() {
		turretIndex = -1;
		suiBoxID = -1;
		addSerializableVariables();
	}

	virtual ~TurretControlTerminalDataComponent() {

	}

	bool isTurretControlTerminalData() {
		return true;
	}

	int getTurrteIndex(){
		return turretIndex;
	}

	void setTurretIndex(int indx){
		turretIndex = indx;
	}

	void setSuiBoxID(unsigned int id){
		suiBoxID = id;
	}

	unsigned int getSuiBoxID(){
		return suiBoxID;
	}


private:
	void addSerializableVariables(){
		addSerializableVariable("turretIndex",&turretIndex);
	}
};

#endif /* TURRETCONTROLTERMINALDATACOMPONENT_H_ */
