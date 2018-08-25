bestineRumor05ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestineRumorConvoHandler",
	screens = {}
}

init_election_phase = ConvoScreen:new {
	id = "init_election_phase",
	leftDialog = "@conversation/bestine_rumor05:s_a65f8ef3", -- As a crafter, I'm going to vote for the Director of Commerce, Sean Trenwell. I definitely need more business and, with his influence, more merchants will be brought in, naturally bringing out more buyers. I really think you should vote. Talk with the governor at the capitol for more information regarding the election.
	stopConversation = "true",
	options = {}
}
bestineRumor05ConvoTemplate:addScreen(init_election_phase);

init_office_phase = ConvoScreen:new {
	id = "init_office_phase",
	leftDialog = "@conversation/bestine_rumor05:s_a3f92c54", -- I've heard that Sean Trenwell funded the establishment of the new market place with his own fortune. Maybe you should check the new market place out. I hear the merchants there are searching for rare objects... coins, bones or something like that.
	stopConversation = "true",
	options = {}
}
bestineRumor05ConvoTemplate:addScreen(init_office_phase);

addConversationTemplate("bestineRumor05ConvoTemplate", bestineRumor05ConvoTemplate);
