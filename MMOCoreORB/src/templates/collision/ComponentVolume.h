/*
 * ComponentVolume.h
 *
 *  Created on: 03/20/2016
 *      Author: gslomin
 */

#ifndef COMPONENTVOLUME_H_
#define COMPONENTVOLUME_H_

#include "CompositeVolume.h"

class ComponentVolume : public CompositeVolume {
public:
	bool isComponentVolume() { return true; }
	ComponentVolume() { }
	virtual void read(IffStream *iff);
};

#endif /* COMPONENTVOLUME_H_ */
