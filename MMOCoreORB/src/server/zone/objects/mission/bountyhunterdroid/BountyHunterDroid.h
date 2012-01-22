/*
 * BountyHunterDroid.h
 *
 *  Created on: Jan 20, 2012
 *      Author: loshult
 */

#ifndef BOUNTYHUNTERDROID_H_
#define BOUNTYHUNTERDROID_H_

namespace server {
namespace zone {
namespace objects {
namespace mission {
namespace bountyhunterdroid {

/**
 * Class implementing the functionality of the bounty hunter droids.
 */
class BountyHunterDroid {
public:

	static const int CALLDROID = 0;
	static const int TRANSMITBIOLOGICALSIGNATURE = 1;
	static const int FINDTARGET = 2;
	static const int FINDANDTRACKTARGET = 3;

};

} // namespace bountyhunterdroid
} // namespace mission
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::mission::bountyhunterdroid;

#endif /* BOUNTYHUNTERDROID_H_ */
