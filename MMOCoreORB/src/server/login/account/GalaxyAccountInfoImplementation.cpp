#include "server/login/account/GalaxyAccountInfo.h"

GalaxyAccountInfoImplementation::GalaxyAccountInfoImplementation() {

}


void GalaxyAccountInfoImplementation::updateVetRewardsFromPlayer(VectorMap<unsigned int, String>& newRewards) {
	Locker lock(&vetMutex);

	if(chosenVeteranRewards.size() == 0)
		chosenVeteranRewards = newRewards;
}

bool GalaxyAccountInfoImplementation::hasChosenVeteranReward( const String& rewardTemplate ){

	for( int i = 0; i < chosenVeteranRewards.size(); i++){
		if( rewardTemplate == chosenVeteranRewards.get(i) ){
			return true;
		}
	}

	return false;

}
