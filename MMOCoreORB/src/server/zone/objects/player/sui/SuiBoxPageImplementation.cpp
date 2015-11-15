#include "server/zone/objects/player/sui/SuiBoxPage.h"
#include "server/zone/packets/ui/SuiCreatePageMessage.h"

BaseMessage* SuiBoxPageImplementation::generateMessage() {
	SuiCreatePageMessage* message = new SuiCreatePageMessage(pageData.get());
	hasGenerated = true;

	return message;
}
