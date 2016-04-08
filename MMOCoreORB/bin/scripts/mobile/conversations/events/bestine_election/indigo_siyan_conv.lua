indigoSiyanConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_election_conv_handler",
	screens = {}
}

default_greeting = ConvoScreen:new {
	id = "default_greeting",
	leftDialog = "@conversation/indigo_siyan:s_f10cc45e", --Welcome! Please, help yourself to tea or pastries! Isn't the election exciting? Are you here to vote for Sean? Oh, pardon me! I'm so rude. I shouldn't ask that. I'm Sean's secretary. I'm so glad to be working for him. He has so many great ideas. Please speak with him as soon as possible. He'll tell you all the things he has in store for Bestine.
	stopConversation = "false",
	options = {
		{"@conversation/indigo_siyan:s_b9b27823","default_end"}, -- Thank you
	}
}
indigoSiyanConvoTemplate:addScreen(default_greeting);

default_end = ConvoScreen:new {
	id = "default_end",
	leftDialog = "@conversation/indigo_siyan:s_abf4a6a9", --My pleasure!
	stopConversation = "true",
	options = {}
}
indigoSiyanConvoTemplate:addScreen(default_end);

nquest_start = ConvoScreen:new {
	id = "nquest_start",
	leftDialog = "@conversation/indigo_siyan:s_e095f053", --Poor Victor. He's such a nice man, but don't tell Sean I said that. Mind you, I'm reluctantly giving you this information. Don't share it with anyone. Let's see what I may have for you. Okay. There's a Hutt in one of the cantinas you can talk to. I know that one of his troopers isn't necessarily loyal either. He's around the capitol.  And you may be able to rummage around Victor's office for nasty tidbits as well. That's all I know.
	stopConversation = "false",
	options = {
		{"@conversation/indigo_siyan:s_b9b27823","nquest_end"}, -- Thank you.
	}
}
indigoSiyanConvoTemplate:addScreen(nquest_start);

nquest_end = ConvoScreen:new {
	id = "nquest_end",
	leftDialog = "@conversation/indigo_siyan:s_fd9f62f9", --I guess. I feel bad now. Bye.
	stopConversation = "true",
	options = {}
}
indigoSiyanConvoTemplate:addScreen(nquest_end);

in_campaign = ConvoScreen:new {
	id = "in_campaign",
	leftDialog = "@conversation/indigo_siyan:s_bdba42ab", --Don't mind him. He can be a little pushy when it comes to these things. What he may not have told you is that you can go to Victor if you decide this campaign isn't for you. He'll probably have some task for you to do in order to join, but that's okay. Nothing too difficult, I'd hope. Anyway, let me see what sort of contacts I have for you.
	stopConversation = "false",
	options = {
		{"@conversation/indigo_siyan:s_540ac7e9","in_campaign2"}, -- Continue
	}
}
indigoSiyanConvoTemplate:addScreen(in_campaign);

in_campaign2 = ConvoScreen:new {
	id = "in_campaign2",
	leftDialog = "@conversation/indigo_siyan:s_7fe92f9e", --Let's see... There are several citizens that I can think of who have been affected by Sean's generosity. The Curator of the museum, for one. Sean's housemaid can tell you a story or two, and you can check over at the new market place. You only need one piece of evidence, so you can choose which suits you. Unfortunately, I don't have direct locations of them. You'll have to find them on your own. I hope this will help you in the long run.
	stopConversation = "false",
	options = {
		{"@conversation/indigo_siyan:s_81fdc59e","thank_you_end"}, --Thank you!
	}
}
indigoSiyanConvoTemplate:addScreen(in_campaign2);

next_election = ConvoScreen:new {
	id = "next_election",
	leftDialog = "@conversation/indigo_siyan:s_88b121e8", --I'm getting ready for the next election. Sean is running for the position. I have so much to do! Be sure to listen to the townsfolk. By rumor, they'll let you know when the voting is about to begin. I have to get back to work...
	stopConversation = "true",
	options = {}
}
indigoSiyanConvoTemplate:addScreen(next_election);

thank_you_end = ConvoScreen:new {
	id = "thank_you_end",
	leftDialog = "@conversation/indigo_siyan:s_83beea8a", --My pleasure. See you later!
	stopConversation = "true",
	options = {}
}
indigoSiyanConvoTemplate:addScreen(thank_you_end);

addConversationTemplate("indigoSiyanConvoTemplate", indigoSiyanConvoTemplate);
