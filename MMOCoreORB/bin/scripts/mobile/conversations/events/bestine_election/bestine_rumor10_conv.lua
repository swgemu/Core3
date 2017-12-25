bestineRumor10ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestineRumorConvoHandler",
	screens = {}
}

init_election_phase = ConvoScreen:new {
	id = "init_election_phase",
	leftDialog = "@conversation/bestine_rumor10:s_9a864cde", -- I'm really curious about the history of Bestine. If Sean Trenwell wins, I'm going to volunteer my efforts to uncover the mysteries surrounding this city. He really cares about Bestine and would do well in the new role if he wins the election. You should really take the time to vote at the capitol. Talk with the governor. She knows all the details.
	stopConversation = "true",
	options = {}
}
bestineRumor10ConvoTemplate:addScreen(init_election_phase);

init_office_phase = ConvoScreen:new {
	id = "init_office_phase",
	leftDialog = "@conversation/bestine_rumor10:s_3fb4ad13", -- We need a library or someplace where we can learn about the history of Bestine. It's really not known as well as say the history of Mos Eisley. I think that'll be my goal. To teach everyone about history.
	stopConversation = "true",
	options = {}
}
bestineRumor10ConvoTemplate:addScreen(init_office_phase);

addConversationTemplate("bestineRumor10ConvoTemplate", bestineRumor10ConvoTemplate);
