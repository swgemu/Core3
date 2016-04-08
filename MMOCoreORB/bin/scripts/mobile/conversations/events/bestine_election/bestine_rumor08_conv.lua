bestineRumor08ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_election_conv_handler",
	screens = {}
}

election_started = ConvoScreen:new {
	id = "election_started",
	leftDialog = "@conversation/bestine_rumor08:s_71b4d773", --If Victor Visalis wins the election, he'll recruit more Imperial Troops to guard Bestine. Do you think I can make the cut? I'd really love the chance to show the Empire what I'm worth! The election? You haven't heard? Oh. Well, go to the capitol and talk with the governor. She knows everything!
	stopConversation = "true",
	options = {}
}

bestineRumor08ConvoTemplate:addScreen(election_started);

default_greeting = ConvoScreen:new {
	id = "default_greeting",
	leftDialog = "@conversation/bestine_rumor08:s_ba912d0c", --I'm going to try and make it. Make the cut for the Empire, that is. I really want to be a trooper. I think I'd make a good one. Join the Empire!
	stopConversation = "true",
	options = {}
}

bestineRumor08ConvoTemplate:addScreen(default_greeting);

addConversationTemplate("bestineRumor08ConvoTemplate", bestineRumor08ConvoTemplate);
