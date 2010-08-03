/*
 * LairObjectsToSpawnMap.h
 *
 *  Created on: 15/07/2010
 *      Author: victor
 */

#ifndef LAIROBJECTSTOSPAWNMAP_H_
#define LAIROBJECTSTOSPAWNMAP_H_

class LairObjectsToSpawnMap : public VectorMap<int, Vector<uint32> > {
public:
	const static int MAXPLANETS = 10;

	LairObjectsToSpawnMap() {
		setNoDuplicateInsertPlan();

		for (int i = 0; i < MAXPLANETS; ++i)
			put(i, Vector<uint32>());
	}

	void addTemplate(int planetID, uint32 templateCRC) {
		if (planetID == -1) {
			insertTemplateToAllPlanets(templateCRC);
			return;
		}

		int idx = find(planetID);

		Vector<uint32>* lairs = &elementAt(idx).getValue();
		lairs->add(templateCRC);
	}

	void insertTemplateToAllPlanets(uint32 templateCRC) {
		for (int i = 0; i < MAXPLANETS; ++i) {
			Vector<uint32>* lairs = &elementAt(i).getValue();

			lairs->add(templateCRC);
		}
	}

	uint32 getRandomTemplate(int planetID) {
		Vector<uint32>* lairs = NULL;

		if (planetID == -1)
			lairs = &elementAt(System::random(size() -1)).getValue();
		else {
			int idx = find(planetID);

			if (idx == -1)
				return 0;

			lairs = &elementAt(idx).getValue();
		}

		if (lairs->size() == 0)
			return 0;

		return lairs->get(System::random(lairs->size() - 1));
	}
};

#endif /* LAIROBJECTSTOSPAWNMAP_H_ */
