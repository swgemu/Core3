#include "server/login/account/GalaxyAccountInfo.h"

#include "engine/util/json_utils.h"

GalaxyAccountInfo::GalaxyAccountInfo() {

}

void GalaxyAccountInfo::updateVetRewardsFromPlayer(const VectorMap<unsigned int, String>& newRewards) {
	if (chosenVeteranRewards.size() == 0) {
		for (const auto& element : newRewards) {
			chosenVeteranRewards.put(element.getKey(), element.getValue());
		}
	}
}
void GalaxyAccountInfo::clearVeteranReward(uint32 milestone) {
	if (chosenVeteranRewards.contains(milestone))
		chosenVeteranRewards.drop( milestone );
}

bool GalaxyAccountInfo::hasChosenVeteranReward(const String& rewardTemplate) const {
	for (int i = 0; i < chosenVeteranRewards.size(); i++) {
		if (rewardTemplate == chosenVeteranRewards.get(i)) {
			return true;
		}
	}

	return false;
}

void GalaxyAccountInfo::addChosenVeteranReward( uint32 milestone, const String& rewardTemplate ) {
	chosenVeteranRewards.put(milestone, rewardTemplate);
}

String GalaxyAccountInfo::getChosenVeteranReward(uint32 milestone) const {
	return chosenVeteranRewards.get(milestone);
}

bool GalaxyAccountInfo::parseFromBinaryStream(ObjectInputStream* stream) {
	return chosenVeteranRewards.parseFromBinaryStream(stream);
}


bool GalaxyAccountInfo::toBinaryStream(ObjectOutputStream* stream) {
	return chosenVeteranRewards.toBinaryStream(stream);
}

void to_json(nlohmann::json& j, const GalaxyAccountInfo& p) {
	j["chosenVeteranRewards"] = p.chosenVeteranRewards.getMapUnsafe();
}


