bestineCapitol03ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestineRumorConvoHandler",
	screens = {}
}

init_election_phase = ConvoScreen:new {
	id = "init_election_phase",
	leftDialog = "@conversation/bestine_capitol03:s_a65103f5", -- All this talk about the new election. It's so boring! I should have volunteered at the museum instead! Ugh! You haven't heard about the election? You're lucky. The governor is taking votes so you need to speak with her. I'm going to take a break now...
	stopConversation = "true",
	options = {}
}
bestineCapitol03ConvoTemplate:addScreen(init_election_phase);

init_office_phase = ConvoScreen:new {
	id = "init_office_phase",
	leftDialog = "@conversation/bestine_capitol03:s_4fc77052", -- It's really quiet around here when there isn't an election going on. Well... it's quiet, at least, for us volunteers. You should come back when an election is going on. I should be at the University, studying. I'm not that good of a student. Oh well!
	stopConversation = "true",
	options = {}
}
bestineCapitol03ConvoTemplate:addScreen(init_office_phase);

addConversationTemplate("bestineCapitol03ConvoTemplate", bestineCapitol03ConvoTemplate);
