bestineRumor10ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_rumor_conv_handler",
	screens = {}
}

election_started = ConvoScreen:new {
	id = "election_started",
	leftDialog = "@conversation/bestine_rumor10:s_9a864cde", --I'm really curious about the history of Bestine. If Sean Trenwell wins, I'm going to volunteer my efforts to uncover the mysteries surrounding this city. He really cares about Bestine and would do well in the new role if he wins the election. You should really take the time to vote at the capitol. Talk with the governor. She knows all the details.
	stopConversation = "true",
	options = {}
}

bestineRumor10ConvoTemplate:addScreen(election_started);

election_ended = ConvoScreen:new {
	id = "election_ended",
	leftDialog = "@conversation/bestine_rumor10:s_3fb4ad13", --We need a library or someplace where we can learn about the history of Bestine. It's really not known as well as say the history of Mos Eisley. I think that'll be my goal. To teach everyone about history. 
	stopConversation = "true",
	options = {}
}

bestineRumor10ConvoTemplate:addScreen(election_ended);

addConversationTemplate("bestineRumor10ConvoTemplate", bestineRumor10ConvoTemplate);
