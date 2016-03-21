/*
 * AttributeListComponent.h
 *
 *  Created on: 1/29/2012
 *      Author: kyle
 */

#ifndef ATTIBUTELISTCOMPONENT_H_
#define ATTIBUTELISTCOMPONENT_H_

#include "SceneObjectComponent.h"

 namespace zone {
  namespace objects {
   namespace scene {
    class SceneObject;
   }

   namespace creature {
    class CreatureObject;
   }
  }

  namespace packets {
   namespace scene {
    class AttributeListMessage;
   }
  }

  class Zone;
 }


using namespace zone::objects::scene;
using namespace zone::objects::creature;
using namespace zone::packets::scene;


class AttributeListComponent : public SceneObjectComponent, public Logger {
public:

	/**
	 * Fills the Attributes
	 * @pre { this object is locked }
	 * @post { this object is locked, menuResponse is complete}
	 * @param menuResponse ObjectMenuResponse that will be sent to the client
	 */
	virtual void fillAttributeList(AttributeListMessage* alm, CreatureObject* creature, SceneObject* object) const;

};

#endif /* ATTIBUTELISTCOMPONENT_H_ */
