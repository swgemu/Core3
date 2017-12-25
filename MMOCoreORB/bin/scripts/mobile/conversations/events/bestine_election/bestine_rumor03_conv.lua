bestineRumor03ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestineRumorConvoHandler",
	screens = {}
}

init_election_phase = ConvoScreen:new {
	id = "init_election_phase",
	leftDialog = "@conversation/bestine_rumor03:s_cd086fbf", -- Merchants? A Museum? Historians?! C'mon! What we really need is added defense against Tusken Raiders! In the upcoming election, my vote is for Victor Visalis, Officer of Defense. You should vote too. Go ask the governor at the capitol for more information.
	stopConversation = "true",
	options = {}
}
bestineRumor03ConvoTemplate:addScreen(init_election_phase);

init_office_phase = ConvoScreen:new {
	id = "init_office_phase",
	leftDialog = "@conversation/bestine_rumor03:s_848f500b", -- Victor Visalis did well in office, I think. Well... other than hunting down rebels with his newly-hired band of troopers. It was pretty horrible for a while. But, what can ya do? This is an Imperial city after all.
	stopConversation = "true",
	options = {}
}
bestineRumor03ConvoTemplate:addScreen(init_office_phase);

addConversationTemplate("bestineRumor03ConvoTemplate", bestineRumor03ConvoTemplate);
