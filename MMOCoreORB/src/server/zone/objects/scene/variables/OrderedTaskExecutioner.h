/*
 * OrderedTask.h
 *
 *  Created on: Apr 14, 2015
 *      Author: TheAnswer
 */

#ifndef SRC_SERVER_ZONE_OBJECTS_SCENE_VARIABLES_ORDEREDTASKEXECUTIONER_H_
#define SRC_SERVER_ZONE_OBJECTS_SCENE_VARIABLES_ORDEREDTASKEXECUTIONER_H_

#include "engine/core/Task.h"
#include "engine/engine.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "system/lang/ref/WeakReference.h"


namespace server {
 namespace zone {
  namespace objects {
   namespace scene {

   class SceneObject;

    namespace variables {

    class OrderedTaskExecutioner : public Task {
    protected:
    	WeakReference<server::zone::objects::scene::SceneObject*> sceneObject;

    	const char* taskName;
    public:
    	OrderedTaskExecutioner(SceneObject* sceneObject);

    	void run();

    	const char* getTaskName();
    };

    }
    }
   }
  }
 }


#endif /* SRC_SERVER_ZONE_OBJECTS_SCENE_VARIABLES_ORDEREDTASKEXECUTIONER_H_ */
