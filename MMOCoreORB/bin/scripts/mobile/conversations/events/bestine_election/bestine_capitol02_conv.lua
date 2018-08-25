bestineCapitol02ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestineRumorConvoHandler",
	screens = {}
}

init_election_phase = ConvoScreen:new {
	id = "init_election_phase",
	leftDialog = "@conversation/bestine_capitol02:s_bdbf995f", -- The capitol is buzzing about the new election! I'm glad you've come! I hope you're going to vote. The eligible candidates are Victor Visalis and Sean Trenwell. The governor is collecting votes, and the winner will work closely with her on a new project. You should go talk with her.
	stopConversation = "true",
	options = {}
}
bestineCapitol02ConvoTemplate:addScreen(init_election_phase);

init_office_phase = ConvoScreen:new {
	id = "init_office_phase",
	leftDialog = "@conversation/bestine_capitol02:s_d18211cb", -- The Empire has taken a new direct standing against the people. I really hope the poor folk won't be too oppressed by the changes. We'll have to see what happens.
	stopConversation = "true",
	options = {}
}
bestineCapitol02ConvoTemplate:addScreen(init_office_phase);

addConversationTemplate("bestineCapitol02ConvoTemplate", bestineCapitol02ConvoTemplate);
