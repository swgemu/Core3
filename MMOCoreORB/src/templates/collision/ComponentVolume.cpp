#include "ComponentVolume.h"

#include "engine/util/iffstream/IffStream.h"
#include "templates/collision/CompositeVolume.h"

void ComponentVolume::read(IffStream* iff) {
	iff->openForm('0000');
	iff->openForm('CPST');
	CompositeVolume::read(iff);
	iff->closeForm('CPST');
	iff->closeForm('0000');
}
