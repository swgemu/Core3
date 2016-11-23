biogenicHerald3ConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "biogenic_herald3_conv_handler",
	screens = {}
}

no_faction = ConvoScreen:new {
	id = "no_faction",
	leftDialog = "@conversation/biogenic_herald_03:s_ededde72", -- Hello. How are you doing today?
	stopConversation = "true",
	options = {}
}
biogenicHerald3ConvoTemplate:addScreen(no_faction);

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/biogenic_herald_03:s_569d6129", -- Hello. You are sympathetic to the Rebellion are you not? I have information that may be of interest to you if you are willing to hear it.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_03:s_c2f063ae", "imperial_types"}, -- Sure, tell me what you know.
		{"@conversation/biogenic_herald_03:s_e35ee05f", "sure_sure"}, -- I don't have time now, I'm sorry.
	}
}
biogenicHerald3ConvoTemplate:addScreen(init);

imperial_types = ConvoScreen:new {
	id = "imperial_types",
	leftDialog = "@conversation/biogenic_herald_03:s_7fd67d96", -- Well, a couple of Imperial types were in here not long ago, and I overheard their conversation. It sounded like they were talking about something going down on Yavin IV.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_03:s_9e41444d", "imperial_agent"}, -- Did they say what was happening?
		{"@conversation/biogenic_herald_03:s_b3ba542c", "sure_sure"}, -- I'm sorry, but I've got to go.
	}
}
biogenicHerald3ConvoTemplate:addScreen(imperial_types);

sure_sure = ConvoScreen:new {
	id = "sure_sure",
	leftDialog = "@conversation/biogenic_herald_03:s_8ae9c189", -- Sure, sure, I understand. I'll still be here if you get a chance to come back.
	stopConversation = "true",
	options = {}
}
biogenicHerald3ConvoTemplate:addScreen(sure_sure);

imperial_agent = ConvoScreen:new {
	id = "imperial_agent",
	leftDialog = "@conversation/biogenic_herald_03:s_1711fd92", -- I didn't catch everything that they were saying, but I did hear something about an Imperial agent overseeing a bio-genetics research facility. And something about... Geo, uh... Geonosians, yea. That's it.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_03:s_2b10b66c", "they_didnt"}, -- Did they mention where the facility is?
		{"@conversation/biogenic_herald_03:s_f8365ece", "not_sure"}, -- What else did they say?
		{"@conversation/biogenic_herald_03:s_1b751405", "my_pleasure"}, -- Thanks for the information. Good-bye.
	}
}
biogenicHerald3ConvoTemplate:addScreen(imperial_agent);

they_didnt = ConvoScreen:new {
	id = "they_didnt",
	leftDialog = "@conversation/biogenic_herald_03:s_d6d8b3ab", -- No, they didn't. In fact, I don't even think they know where it is exactly. Sounds like it's a big secret, but they said something about asking the locals. Something about a Mining Outpost, too.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_03:s_f8365ece", "not_sure"}, -- What else did they say?
		{"@conversation/biogenic_herald_03:s_1b751405", "my_pleasure"}, -- Thanks for the information. Good-bye.
	}
}
biogenicHerald3ConvoTemplate:addScreen(they_didnt);

not_sure = ConvoScreen:new {
	id = "not_sure",
	leftDialog = "@conversation/biogenic_herald_03:s_2991cadd", -- I'm really not sure. It got a little loud in here and I couldn't make out what they were saying, but one of them looked really mad. If you ask me something big is about to go down.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_03:s_2b10b66c", "on_yavin"}, -- Did they mention where the facility is?
		{"@conversation/biogenic_herald_03:s_1b751405", "my_pleasure"}, -- Thanks for the information. Good-bye.
	}
}
biogenicHerald3ConvoTemplate:addScreen(not_sure);

my_pleasure = ConvoScreen:new {
	id = "my_pleasure",
	leftDialog = "@conversation/biogenic_herald_03:s_a5ee5a5b", -- My pleasure. Take care!
	stopConversation = "true",
	options = {}
}
biogenicHerald3ConvoTemplate:addScreen(my_pleasure);

on_yavin = ConvoScreen:new {
	id = "on_yavin",
	leftDialog = "@conversation/biogenic_herald_03:s_3d816e72", -- No, they didn't. In fact, I don't even think they know where it is exactly, except for on Yavin IV. Sounds like it's a big secret, but they said something about asking the locals. Something about a Mining Outpost, too.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_03:s_1b751405", "look_into"}, -- Thanks for the information. Good-bye.
	}
}
biogenicHerald3ConvoTemplate:addScreen(on_yavin);

look_into = ConvoScreen:new {
	id = "look_into",
	leftDialog = "@conversation/biogenic_herald_03:s_5ea784e0", -- My pleasure. If it sounds like something you want to look into, you might like to ask around that Mining Outpost on Yavin IV yourself.
	stopConversation = "true",
	options = {}
}
biogenicHerald3ConvoTemplate:addScreen(look_into);

addConversationTemplate("biogenicHerald3ConvoTemplate", biogenicHerald3ConvoTemplate);
