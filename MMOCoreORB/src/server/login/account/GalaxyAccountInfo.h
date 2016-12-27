/*
 * GalaxyAccountInfo.h
 *
 *  Created on: 4/30/2016
 *      Author: gslomin
 */

#ifndef GALAXYACCOUNTINFO_H_
#define GALAXYACCOUNTINFO_H_

#include "system/lang.h"
#include "system/util/SynchronizedVectorMap.h"

class GalaxyAccountInfo : public Object {
	
protected:
	SynchronizedVectorMap<uint32, String> chosenVeteranRewards; // milestone, templateFile
	
public:
	
	GalaxyAccountInfo();
	
	void updateVetRewardsFromPlayer(const VectorMap<uint32, String> &newRewards);

	String getChosenVeteranReward(uint32 milestone);

	void addChosenVeteranReward(uint32 milestone, const String& rewardTemplate);

	bool hasChosenVeteranReward(const String& rewardTemplate);

	void clearVeteranReward(uint32 milestone);
	
	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);
};

#endif /* #define GALAXYACCOUNTINFO_H_ */
