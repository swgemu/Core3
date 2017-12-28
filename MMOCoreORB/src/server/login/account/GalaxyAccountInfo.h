/*
 * GalaxyAccountInfo.h
 *
 *  Created on: 4/30/2016
 *      Author: gslomin
 */

#ifndef GALAXYACCOUNTINFO_H_
#define GALAXYACCOUNTINFO_H_

#include "system/lang.h"
#include "system/lang/Object.h"
#include "system/lang/String.h"
#include "system/platform.h"
#include "system/util/SynchronizedVectorMap.h"

namespace sys {
namespace io {
class ObjectInputStream;
class ObjectOutputStream;
}  // namespace io
namespace util {
template <class K, class V> class VectorMap;
}  // namespace util
}  // namespace sys

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
