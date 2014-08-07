/*
 * InterplanetrySurveyTask.h
 *
 *  Created on: 6/8/2014
 *      Author: washu
 */

#ifndef INTERPLANETARYSURVERYTASK_H_
#define INTERPLANETARYSURVERYTASK_H_

#include "engine/engine.h"
#include "server/ServerCore.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"
class InterplanetarySurveyTask : public Task {
	ManagedReference<InterplanetarySurvey*> surveyData;

public:

	InterplanetarySurveyTask(InterplanetarySurvey* survey) {
		surveyData = survey;
	}

	void run() {
		// Determine what planet and type, and pull results
		ManagedReference<ResourceManager*> rmanager = ServerCore::getZoneServer()->getResourceManager();
		Vector<ManagedReference<ResourceSpawn*> > resources;
		rmanager->getResourceListByType(resources, surveyData->getSurveyToolType(), surveyData->getPlanet());
		// format email and send
		ManagedReference<ResourceSpawn*> resourceSpawn;
		// We need to sort this by family name
		HashTable<String, Vector<String>* > mapped;
		for(int i=0;i<resources.size();i++) {
			resourceSpawn = resources.get(i);
			String family = resourceSpawn->getFamilyName();
			String name = resourceSpawn->getName();
			Vector<String>* list = mapped.get(family);
			if (list != NULL) {
				list->add(name);
			} else {
				list = new Vector<String>();
				list->add(name);
				mapped.put(family,list);
			}
		}
		// Create Email:
		StringBuffer body;
		UnicodeString sender(String("Interplanetary Survey Droid"));
		Reference<StringIdManager* > stringIdManager = StringIdManager::instance();
		String planetName = stringIdManager->getStringId(String("@planet_n:" + surveyData->getPlanet()).hashCode()).toString();
		UnicodeString subject(String("Interplanetary Survey: " + planetName  + " - " + surveyData->getSurveyType()));
		body << "Incoming planetary survey report...\n\n";
		body << "\\#pcontrast3 Planet: \\#pcontrast1 " << planetName <<"\n";
		body << "\\#pcontrast3 Resource Class: \\#pcontrast1 " << surveyData->getSurveyType() << "\n\n";
		body << "\\#pcontrast3 Resources located...\\#.\n\n";
		HashTableIterator<String, Vector<String>* > iterator = mapped.iterator();
		while(iterator.hasNext()) {
			String key = iterator.getNextKey();
			Vector<String>* values = mapped.get(key);
			if (values->size() > 0) {
				body << key << "\n";
				for(int i=0;i<values->size();i++) {
					body << "\\#pcontrast1 " << values->get(i) << "\\#.\n";
				}
			}
		}
		UnicodeString bodyString(body.toString());
		ManagedReference<ChatManager*> chat = ServerCore::getZoneServer()->getChatManager();
		chat->sendMail(sender.toString(), subject, bodyString, surveyData->getRequestor());
		// mark it as run and delete from the database
		surveyData->setExecuted(true);
		if (surveyData->isPersistent())
			ObjectManager::instance()->destroyObjectFromDatabase(surveyData->_getObjectID());
	}

};

#endif /* INTERPLANETARYSURVERYTASK_H_ */
