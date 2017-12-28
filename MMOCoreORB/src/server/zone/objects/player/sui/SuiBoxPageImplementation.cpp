#include "server/zone/objects/player/sui/SuiBoxPage.h"
#include "server/zone/packets/ui/SuiCreatePageMessage.h"
#include "system/lang/ref/Reference.h"

namespace engine {
namespace service {
namespace proto {
class BaseMessage;
}  // namespace proto
}  // namespace service
}  // namespace engine

BaseMessage* SuiBoxPageImplementation::generateMessage() {
	SuiCreatePageMessage* message = new SuiCreatePageMessage(pageData.get());
	hasGenerated = true;

	return message;
}
