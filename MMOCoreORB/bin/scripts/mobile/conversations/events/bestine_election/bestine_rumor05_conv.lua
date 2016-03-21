bestineRumor05ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_rumor_conv_handler",
	screens = {}
}

election_started = ConvoScreen:new {
	id = "election_started",
	leftDialog = "@conversation/bestine_rumor05:s_a65f8ef3", --As a crafter, I'm going to vote for the Director of Commerce, Sean Trenwell. I definitely need more business and, with his influence, more merchants will be brought in, naturally bringing out more buyers. I really think you should vote. Talk with the governor at the capitol for more information regarding the election.
	stopConversation = "true",
	options = {}
}

bestineRumor05ConvoTemplate:addScreen(election_started);

election_ended = ConvoScreen:new {
	id = "election_ended",
	leftDialog = "@conversation/bestine_rumor05:s_a3f92c54", -- NPC: I've heard that Sean Trenwell funded the establishment of the new market place with his own fortune. Maybe you should check the new market place out. I hear the merchants there are searching for rare objects... coins, bones or something like that.
	stopConversation = "true",
	options = {}
}

bestineRumor05ConvoTemplate:addScreen(election_ended);

addConversationTemplate("bestineRumor05ConvoTemplate", bestineRumor05ConvoTemplate);

