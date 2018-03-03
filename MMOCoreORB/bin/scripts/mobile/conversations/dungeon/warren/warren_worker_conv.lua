warrenWorkerConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "warrenWorkerConvoHandler",
	screens = {}
}

init_1 = ConvoScreen:new {
	id = "init_1",
	leftDialog = "@theme_park/warren/warren:worker_bark1", -- The Inquisitor's troops invaded... Teraud's loyalists managed to capture her and I think they carted her off to a prison cell...
	stopConversation = "true",
	options = {	}
}
warrenWorkerConvoTemplate:addScreen(init_1);

init_2 = ConvoScreen:new {
	id = "init_2",
	leftDialog = "@theme_park/warren/warren:worker_bark2", -- Watch out, those Stormtroopers are shooting on sight, even if you're a loyal Imperial Citizen!
	stopConversation = "true",
	options = {	}
}
warrenWorkerConvoTemplate:addScreen(init_2);

init_3 = ConvoScreen:new {
	id = "init_3",
	leftDialog = "@theme_park/warren/warren:worker_bark3", -- Teraud is a madman... he made us carve the brains out of living Krayt Dragons... who knows what he did with them...
	stopConversation = "true",
	options = {	}
}
warrenWorkerConvoTemplate:addScreen(init_3);

init_4 = ConvoScreen:new {
	id = "init_4",
	leftDialog = "@theme_park/warren/warren:worker_bark4", -- Teraud uses a mind control device to control his cyborgs. I think he planned to make us all his cyborg slaves.
	stopConversation = "true",
	options = {	}
}
warrenWorkerConvoTemplate:addScreen(init_4);

addConversationTemplate("warrenWorkerConvoTemplate", warrenWorkerConvoTemplate);
