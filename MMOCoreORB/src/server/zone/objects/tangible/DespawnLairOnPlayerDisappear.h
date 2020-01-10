/*
 * DespawnLairOnPlayerDisappear.h
 *
 *  Created on: 13/07/2010
 *      Author: victor
 */

#ifndef DESPAWNLAIRONPLAYERDISAPPEAR_H_
#define DESPAWNLAIRONPLAYERDISAPPEAR_H_

#include "server/zone/objects/scene/SceneObject.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace tangible {


class DespawnLairOnPlayerDisappear : public Task {
	WeakReference<SceneObject*> lair;

public:
    DespawnLairOnPlayerDisappear(SceneObject* l);
    void run();
};

   }
  }
 }
}

using namespace server::zone::objects::tangible;

#endif /* DESPAWNLAIRONPLAYERDISAPPEAR_H_ */
