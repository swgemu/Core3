phyHudgenConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Normal",
	luaClassHandler = "",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@theme_park/warren/warren:worker_start", -- Don't hurt me!
	stopConversation = "false",
	options = {
		{"@theme_park/warren/warren:worker_reply_1", "contract_worker"}, -- Who are you?
		{"@theme_park/warren/warren:worker_reply_2", "called_warren"}, -- What is this place?
	}
}
phyHudgenConvoTemplate:addScreen(init);

called_warren = ConvoScreen:new {
	id = "called_warren",
	leftDialog = "@theme_park/warren/warren:worker_2", -- All the workers call this place 'The Warren'.
	stopConversation = "false",
	options = {
		{"@theme_park/warren/warren:worker_2_reply_2", "imperial_bigwig"}, -- What happened here?
	}
}
phyHudgenConvoTemplate:addScreen(called_warren);

imperial_bigwig = ConvoScreen:new {
	id = "imperial_bigwig",
	leftDialog = "@theme_park/warren/warren:worker_6", -- An Imperial bigwig came to visit Teraud, and something bad happened. Crazed lab animals burst out of the elevator going down and attacked the workers, killing many of them.
	stopConversation = "true",
	options = {}
}
phyHudgenConvoTemplate:addScreen(imperial_bigwig);

contract_worker = ConvoScreen:new {
	id = "contract_worker",
	leftDialog = "@theme_park/warren/warren:worker_1", -- I am a contract worker hired by Colonel Teraud to keep expanding this facility.... which is crazy given how big it is already.
	stopConversation = "false",
	options = {
		{"@theme_park/warren/warren:worker_1_reply_1", "trapped_below"}, -- Are there more workers in here?
	}
}
phyHudgenConvoTemplate:addScreen(contract_worker);

trapped_below = ConvoScreen:new {
	id = "trapped_below",
	leftDialog = "@theme_park/warren/warren:worker_3", -- There are many workers trapped below.
	stopConversation = "false",
	options = {
		{"@theme_park/warren/warren:worker_3_reply_1", "elevator_locked"}, -- What do you mean 'trapped'?
	}
}
phyHudgenConvoTemplate:addScreen(trapped_below);

elevator_locked = ConvoScreen:new {
	id = "elevator_locked",
	leftDialog = "@theme_park/warren/warren:worker_4", -- The elevator down is locked. And it can only be unlocked from the Master Control Room by using the four pass-keys. But you'll never get to the Master Control Room without the Turret Defense passcode!
	stopConversation = "false",
	options = {
		{"@theme_park/warren/warren:worker_4_reply_1", "dead_by_elevator"}, -- What is the passcode?
	}
}
phyHudgenConvoTemplate:addScreen(elevator_locked);

dead_by_elevator = ConvoScreen:new {
	id = "dead_by_elevator",
	leftDialog = "@theme_park/warren/warren:worker_5", -- I don't know. The only one who knew the passcode is dead by the elevator now. Oh this is hopeless!
	stopConversation = "true",
	options = {}
}
phyHudgenConvoTemplate:addScreen(dead_by_elevator);

addConversationTemplate("phyHudgenConvoTemplate", phyHudgenConvoTemplate);
