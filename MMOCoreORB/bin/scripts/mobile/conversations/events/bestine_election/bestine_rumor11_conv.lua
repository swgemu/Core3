bestineRumor11ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestineRumorConvoHandler",
	screens = {}
}

init_election_phase = ConvoScreen:new {
	id = "init_election_phase",
	leftDialog = "@conversation/bestine_rumor11:s_7f471bf9", -- I'm here to investigate the background story of Victor Visalis. He's running as the Officer of Defense in the upcoming election. I have a bad feeling bout him. Every politician has a bad side, some horrible story in their past. Anyway, you need to vote at the capitol. Talk with the governor for more information.
	stopConversation = "true",
	options = {}
}
bestineRumor11ConvoTemplate:addScreen(init_election_phase);

init_office_phase = ConvoScreen:new {
	id = "init_office_phase",
	leftDialog = "@conversation/bestine_rumor11:s_e2e56485", -- 	There are some really weird things going on. I think the Empire is becoming more and more strict with who and what come out of Bestine. Between you and me, anyone who's sympathetic with the Rebels should be careful. I've seen too many singled out and executed nowadays.
	stopConversation = "true",
	options = {}
}
bestineRumor11ConvoTemplate:addScreen(init_office_phase);

addConversationTemplate("bestineRumor11ConvoTemplate", bestineRumor11ConvoTemplate);
