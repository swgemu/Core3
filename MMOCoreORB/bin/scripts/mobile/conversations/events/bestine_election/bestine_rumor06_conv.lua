bestineRumor06ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestineRumorConvoHandler",
	screens = {}
}

init_election_phase = ConvoScreen:new {
	id = "init_election_phase",
	leftDialog = "@conversation/bestine_rumor06:s_c3f5586a", -- 	If Victor Visalis wins this election, a higher degree of defense will be added. The Tusken Raiders are getting restless and may launch an attack soon. I really fear for the city of Bestine. You look... confused. Talk with the governor at the capitol. She knows all the details.
	stopConversation = "true",
	options = {}
}
bestineRumor06ConvoTemplate:addScreen(init_election_phase);

init_office_phase = ConvoScreen:new {
	id = "init_office_phase",
	leftDialog = "@conversation/bestine_rumor06:s_e63228d2", -- The museum holds frequent contests. I bought a painting that had been on showcase last month. It's really beautiful!
	stopConversation = "true",
	options = {}
}
bestineRumor06ConvoTemplate:addScreen(init_office_phase);

addConversationTemplate("bestineRumor06ConvoTemplate", bestineRumor06ConvoTemplate);
