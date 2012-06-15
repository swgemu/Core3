/*
 * AlertStateComponent.h
 *
 *  Created on: May 17, 2012
 *      Author: da
 */

#ifndef ALERTSTATECOMPONENT_H_
#define ALERTSTATECOMPONENT_H_

#include "AiStateComponent.h"

class AlertStateComponent : public AiStateComponent {
public:
	uint16 onEnter(AiActor* actor);

	uint16 doRecovery(AiActor* actor);

	uint16 doMovement(AiActor* actor);
};


#endif /* ALERTSTATECOMPONENT_H_ */
