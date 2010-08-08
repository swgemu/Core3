/*
 * AnimationTask.h
 *
 *  Created on: 08/08/2010
 *      Author: victor
 */

#ifndef ANIMATIONTASK_H_
#define ANIMATIONTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"

class AnimationTask : public Task {
	ManagedReference<CreatureObject*> creature;
	String animation;
public:
	AnimationTask(CreatureObject* creo, const String& anim) {
		creature = creo;
		animation = anim;
	}

	void run() {
		Locker locker(creature);

		creature->doAnimation(animation);
	}
};

#endif /* ANIMATIONTASK_H_ */
