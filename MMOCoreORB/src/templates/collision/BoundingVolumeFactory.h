/*
 * BoundingVolumeFactory.h
 *
 *  Created on: 3/20/16
 *      Author: gslomin
 */

#ifndef BOUNDINGVOLUMEFACTORY_H_
#define BOUNDINGVOLUMEFACTORY_H_

#include "BaseBoundingVolume.h"
#include "engine/util/iffstream/IffStream.h"

class BaseBoundingVolume;
namespace engine {
namespace util {
class IffStream;
}  // namespace util
}  // namespace engine

class BoundingVolumeFactory {
public:
	BoundingVolumeFactory() { }
	static BaseBoundingVolume* getVolume(IffStream *iff);
};

#endif /* BOUNDINGVOLUMEFACTORY_H_ */
