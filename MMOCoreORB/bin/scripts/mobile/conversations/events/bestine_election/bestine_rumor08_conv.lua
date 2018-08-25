bestineRumor08ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestineRumorConvoHandler",
	screens = {}
}

init_election_phase = ConvoScreen:new {
	id = "init_election_phase",
	leftDialog = "@conversation/bestine_rumor08:s_71b4d773", -- If Victor Visalis wins the election, he'll recruit more Imperial Troops to guard Bestine. Do you think I can make the cut? I'd really love the chance to show the Empire what I'm worth! The election? You haven't heard? Oh. Well, go to the capitol and talk with the governor. She knows everything!
	stopConversation = "true",
	options = {}
}
bestineRumor08ConvoTemplate:addScreen(init_election_phase);

init_office_phase = ConvoScreen:new {
	id = "init_office_phase",
	leftDialog = "@conversation/bestine_rumor08:s_ba912d0c", -- 	I'm going to try and make it. Make the cut for the Empire, that is. I really want to be a trooper. I think I'd make a good one. Join the Empire!
	stopConversation = "true",
	options = {}
}
bestineRumor08ConvoTemplate:addScreen(init_office_phase);

addConversationTemplate("bestineRumor08ConvoTemplate", bestineRumor08ConvoTemplate);
