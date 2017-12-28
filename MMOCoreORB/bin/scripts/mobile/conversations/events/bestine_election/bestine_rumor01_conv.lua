bestineRumor01ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestineRumorConvoHandler",
	screens = {}
}

init_election_phase = ConvoScreen:new {
	id = "init_election_phase",
	leftDialog = "@conversation/bestine_rumor01:s_a886b683", -- 	If you care about the state of Bestine, then you should vote for one of the new candidates. You can go to the capitol and speak with the governor for more information. The winner of the election will reflect on Bestine, so choose wisely.
	stopConversation = "true",
	options = {}
}
bestineRumor01ConvoTemplate:addScreen(init_election_phase);

init_office_phase = ConvoScreen:new {
	id = "init_office_phase",
	leftDialog = "@conversation/bestine_rumor01:s_b1225bbd", -- I hear there's been way too many attacks on Bestine by the Sand People. It's really hurting our economy.
	stopConversation = "true",
	options = {}
}
bestineRumor01ConvoTemplate:addScreen(init_office_phase);

addConversationTemplate("bestineRumor01ConvoTemplate", bestineRumor01ConvoTemplate);
