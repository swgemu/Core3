/*
 * DroidLabratory.h
 *
 *  Created on: Aug 20, 2014
 *      Author: swgemu
 */

#ifndef DROIDLABRATORY_H_
#define DROIDLABRATORY_H_

#include "ResourceLabratory.h"
namespace server {
namespace zone {
namespace managers {
namespace crafting {
namespace labratories {

class DroidLabratory: public ResourceLabratory {
public:
	DroidLabratory();
	virtual ~DroidLabratory();
	int getCreationCount(ManufactureSchematic* manufactureSchematic);
};

}
}
}
}
}
using namespace server::zone::managers::crafting::labratories;


#endif /* DROIDLABRATORY_H_ */
