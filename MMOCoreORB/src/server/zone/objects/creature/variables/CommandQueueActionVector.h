/*
 * CommandQueueActionVector.h
 *
 *  Created on: May 30, 2011
 *      Author: theanswer
 */

#ifndef COMMANDQUEUEACTIONVECTOR_H_
#define COMMANDQUEUEACTIONVECTOR_H_

#include "engine/engine.h"
#include "CommandQueueAction.h"

class CommandQueueActionVector : public Vector<Reference<CommandQueueAction*> > {

};


#endif /* COMMANDQUEUEACTIONVECTOR_H_ */
