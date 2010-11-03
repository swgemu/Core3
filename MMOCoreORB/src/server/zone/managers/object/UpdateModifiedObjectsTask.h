/*
 * UpdateModifiedObjectsTask.h
 *
 *  Created on: Oct 14, 2010
 *      Author: oru
 */

#ifndef UPDATEMODIFIEDOBJECTSTASK_H_
#define UPDATEMODIFIEDOBJECTSTASK_H_

class UpdateModifiedObjectsTask : public Task {
public:
	UpdateModifiedObjectsTask() {
	}

	void run() {
		ObjectManager::instance()->updateModifiedObjectsToDatabase(true);
	}
};


#endif /* UPDATEMODIFIEDOBJECTSTASK_H_ */
