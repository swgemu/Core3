/*
 * InterplanetrySurveyTask.h
 *
 *  Created on: 6/8/2014
 *      Author: washu
 */

#ifndef INTERPLANETARYSURVERYTASK_H_
#define INTERPLANETARYSURVERYTASK_H_

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
		HashTable<String, Reference<Vector<String>*> > mapped;
		HashTable<String, Reference<Vector<String>*> > typeMap;

		for(int i = 0; i < resources.size(); i++) {
			resourceSpawn = resources.get(i);
			String family = resourceSpawn->getFamilyName();
			String type = resourceSpawn->getFinalClass();
			String name = resourceSpawn->getName();
			// map type to family
			auto list = typeMap.get(family);
			if (list != nullptr) {
				if (!list->contains(type))
					list->add(type);
			} else {
				list = new Vector<String>();
				list->add(type);
				typeMap.put(family, list);
			}

			// map type to spawn name
			auto mlist = mapped.get(type);
			if (mlist != nullptr) {
				if (!mlist->contains(name))
					mlist->add(name);
			} else {
				mlist = new Vector<String>();
				mlist->add(name);
				mapped.put(type, mlist);
			}
		}
		// Create Email:
		StringBuffer body;

		String sender = "interplanetary survey droid";
		auto stringIdManager = StringIdManager::instance();

		String planetName = surveyData->getPlanet();

		if (!planetName.isEmpty()) {
			planetName[0] = toupper(planetName[0]);
		}

		String sType = surveyData->getSurveyType();
		// Some override for untranslated names
		if (sType == "floral_resources") {
			sType = "Floral";
		}
		if (sType == "energy_renewable_unlimited_solar") {
			sType = "Solar";
		}
		if (sType == "energy_renewable_unlimited_wind") {
			sType = "Wind";
		}

		StringBuffer tBuff;
		char tmp = 0;

		if (!sType.isEmpty()) {
			tmp = sType.charAt(0);
		}

		tmp = toupper(tmp);
		tBuff.append(tmp);

		if (sType.length() > 1) {
			tBuff.append(sType.subString(1));
		}

		String surveyType = tBuff.toString();
		UnicodeString subject(String("Interplanetary Survey: " + planetName  + " - " + surveyType));
		body << "Incoming planetary survey report...\n\n";
		body << "\\#pcontrast3 Planet: \\#pcontrast1 " << planetName <<"\n";
		body << "\\#pcontrast3 Resource Class: \\#pcontrast1 " << surveyType << "\n\n";
		body << "\\#pcontrast3 Resources located...\\#.\n\n";
		auto familyit = typeMap.iterator();

		while(familyit.hasNext()) {
			String family = familyit.getNextKey();
			auto tValues = typeMap.get(family);
			body << family << "\n";

			for(int i = 0; i < tValues->size(); i++) {
				String sType = tValues->get(i);
				body << "\t" << sType << "\n";
				auto values = mapped.get(sType);

				for(int j = 0; j < values->size(); j++) {
					body << "\t\t\\#pcontrast1 " << values->get(j) << "\\#.\n";
				}
			}
		}
		UnicodeString bodyString(body.toString());
		ManagedReference<ChatManager*> chat = ServerCore::getZoneServer()->getChatManager();
		chat->sendMail(sender, subject, bodyString, surveyData->getRequestor());
		// mark it as run and delete from the database
		surveyData->setExecuted(true);
		if (surveyData->isPersistent())
			ObjectManager::instance()->destroyObjectFromDatabase(surveyData->_getObjectID());
	}

};

#endif /* INTERPLANETARYSURVERYTASK_H_ */
