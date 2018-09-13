imperialInformantConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "imperialInformantConvoHandler",
	screens = {}
}

m1_informant_invalid = ConvoScreen:new {
	id = "m1_informant_invalid",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m1_informant_invalid", -- I said, what are you looking at? If I wanted to chat, I would have baked up wastril bread and we'd be having a tea party by now! I don't have any tea, so that's out of the question. Now get!
	stopConversation = "true",
	options = {}
}

imperialInformantConvoTemplate:addScreen(m1_informant_invalid);

m1_informant = ConvoScreen:new {
	id = "m1_informant",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m1_informant", -- So you're the one the coordinator sent to relay the message, huh? The Empire must be getting desperate!
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m1_informant_report", "m1_informant_report"}, -- What have you learned?
		{"@theme_park/alderaan/act2/imperial_missions:m1_informant_reprimand", "m1_informant_reprimand"}, -- Words like that can land you in hot water.
	}
}

imperialInformantConvoTemplate:addScreen(m1_informant);

m1_informant_report = ConvoScreen:new {
	id = "m1_informant_report",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m1_informant_report_response", -- It seems the rebels are planning on slicing an Imperial Communications terminal in order to deliver a message to someone. I wasn't able to find out who the message was for though.
	stopConversation = "true",
	options = {}
}

imperialInformantConvoTemplate:addScreen(m1_informant_report);

m1_informant_reprimand = ConvoScreen:new {
	id = "m1_informant_reprimand",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m1_informant_reprimand_response", -- Hey, I was just joking with you! I hold the empire in the highest esteem as everyone knows.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m1_informant_report", "m1_informant_report"}, -- What have you learned?
	}
}

imperialInformantConvoTemplate:addScreen(m1_informant_reprimand);

addConversationTemplate("imperialInformantConvoTemplate", imperialInformantConvoTemplate);
