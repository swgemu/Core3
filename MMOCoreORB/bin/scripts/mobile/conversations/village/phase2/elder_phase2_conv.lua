villageElderPhase2ConvoTemplate = ConvoTemplate:new {
	initialScreen = "intro",
	templateType = "Lua",
	luaClassHandler = "villageElderConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/village_elder_2:s_5d7558d4", -- Thanks for those supplies. They really are coming in handy.
	stopConversation = "false",
	options = {
		{"@conversation/village_elder_2:s_8caad960", "recent_attack"}, -- What supplies? I didn't bring you any supplies.
		{"@conversation/village_elder_2:s_5e0af20b", "sitting_ducks"}, -- You bet. Anything else I can do to help?
		-- Add via convo handler
		--{"@conversation/village_elder_2:s_9dc8bf5d", ""}, -- I seem to have misplaced my Force crystal. May I have another?
	}
}
villageElderPhase2ConvoTemplate:addScreen(intro);

sitting_ducks = ConvoScreen:new {
	id = "sitting_ducks",
	leftDialog = "@conversation/village_elder_2:s_bd4cef4a", -- Yes, please. That Sith Shadow gang is still trying to destroy us. We're running low on supplies because our convoys can't get through, and we're sitting ducks right now if they decide to attack.
	stopConversation = "false",
	options = {
		{"@conversation/village_elder_2:s_4ecdf473", "too_busy_defending"}, -- We need to take the fight to them.
		{"@conversation/village_elder_2:s_1607b22e", "you_have_a_point"}, -- Those supplies are key to everything else.
		{"@conversation/village_elder_2:s_5bdbe99a", "current_shape"}, -- I'd like to help rebuild the defenses.
		{"@conversation/village_elder_2:s_c7c2a3b0", "very_appreciative"}, -- I'd like to help gather supplies and resources.
	}
}
villageElderPhase2ConvoTemplate:addScreen(sitting_ducks);

current_shape = ConvoScreen:new {
	id = "current_shape",
	leftDialog = "@conversation/village_elder_2:s_a601e626", -- Good idea. We wouldn't stand up to any attack in our current shape. Talk to Quharek. He's at the construction site north of here along the wall.
	stopConversation = "true",
	options = {}
}
villageElderPhase2ConvoTemplate:addScreen(current_shape);

very_appreciative = ConvoScreen:new {
	id = "very_appreciative",
	leftDialog = "@conversation/village_elder_2:s_278134b4", -- I am sure the people would be very appreciative for whatever you could find. Please speak to Eozlin to the northwest.
	stopConversation = "true",
	options = {}
}
villageElderPhase2ConvoTemplate:addScreen(very_appreciative);

too_busy_defending = ConvoScreen:new {
	id = "too_busy_defending",
	leftDialog = "@conversation/village_elder_2:s_2f1f1ed", -- Yes... yes, maybe they will be too busy defending themselves to attack us again. Please speak to Dageerin as soon as possible. He is over by the communal buildings A few meters west of here.
	stopConversation = "true",
	options = {}
}
villageElderPhase2ConvoTemplate:addScreen(too_busy_defending);

you_have_a_point = ConvoScreen:new {
	id = "you_have_a_point",
	leftDialog = "@conversation/village_elder_2:s_a60bdc2c", -- You have a point. I think you should talk to Whip by the front gate south of here.
	stopConversation = "true",
	options = {}
}
villageElderPhase2ConvoTemplate:addScreen(you_have_a_point);

recent_attack = ConvoScreen:new {
	id = "recent_attack",
	leftDialog = "@conversation/village_elder_2:s_96bf47c1", -- Oh, excuse me then. There's been so many coming and going lately I have lost track. We're rebuilding after a recent attack.
	stopConversation = "false",
	options = {
		{"@conversation/village_elder_2:s_cc6522f9", "still_out_there"}, -- Who would attack an agro-colony?
	}
}
villageElderPhase2ConvoTemplate:addScreen(recent_attack);

still_out_there = ConvoScreen:new {
	id = "still_out_there",
	leftDialog = "@conversation/village_elder_2:s_c3add11e", -- A gang called the Sith Shadows. They are still out there, planning their next attack I am sure.
	stopConversation = "false",
	options = {
		{"@conversation/village_elder_2:s_9940e942", "excellent_idea"}, -- You need to find them and stop them at their source.
		{"@conversation/village_elder_2:s_70509760", "sure_couldnt_hurt"}, -- Sounds like you need better defenses. I can help you rebuild them.
	}
}
villageElderPhase2ConvoTemplate:addScreen(still_out_there);

excellent_idea = ConvoScreen:new {
	id = "excellent_idea",
	leftDialog = "@conversation/village_elder_2:s_d6a8b96b", -- That's an excellent idea. Perhaps if we attack them directly we can take some of their attention away from their attacks on our supply convoys. They have been either destroying or turning back all of the convoys that have been headed to us.
	stopConversation = "false",
	options = {
		{"@conversation/village_elder_2:s_4ecdf473", "thats_the_spirit"}, -- We need to take the fight to them.
		{"@conversation/village_elder_2:s_1607b22e", "very_logical"}, -- Those supplies are key to everything else.
	}
}
villageElderPhase2ConvoTemplate:addScreen(excellent_idea);

thats_the_spirit = ConvoScreen:new {
	id = "thats_the_spirit",
	leftDialog = "@conversation/village_elder_2:s_7471e00a", -- That's the spirit! Show them we won't lay down for this injustice. Speak to Dageerin to the west, over by the communal buildings.
	stopConversation = "true",
	options = {}
}
villageElderPhase2ConvoTemplate:addScreen(thats_the_spirit);

very_logical = ConvoScreen:new {
	id = "very_logical",
	leftDialog = "@conversation/village_elder_2:s_70a99316", -- Very logical. We are in desperate need of those supplies. Whip can get you set up for that. He's by the front gate just a few meters south of here.
	stopConversation = "true",
	options = {}
}
villageElderPhase2ConvoTemplate:addScreen(very_logical);

sure_couldnt_hurt = ConvoScreen:new {
	id = "sure_couldnt_hurt",
	leftDialog = "@conversation/village_elder_2:s_1414eb3a", -- It sure couldn't hurt. Thank you for your help. We need both craftsmen and supplies. What would you prefer to do?
	stopConversation = "false",
	options = {
		{"@conversation/village_elder_2:s_5bdbe99a", "construction_site"}, -- I'd like to help rebuild the defenses.
		{"@conversation/village_elder_2:s_c7c2a3b0", "dangerously_low"}, -- I'd like to help gather supplies and resources.
	}
}
villageElderPhase2ConvoTemplate:addScreen(sure_couldnt_hurt);

construction_site = ConvoScreen:new {
	id = "construction_site",
	leftDialog = "@conversation/village_elder_2:s_57c6f33", -- Great, you need to speak with Quharek. You can find him at the construction site to the north along the wall..
	stopConversation = "true",
	options = {}
}
villageElderPhase2ConvoTemplate:addScreen(construction_site);

dangerously_low = ConvoScreen:new {
	id = "dangerously_low",
	leftDialog = "@conversation/village_elder_2:s_c8f614a1", -- Thank you so much. Our supplies are running dangerously low. Our first priority was to rebuild the dwellings that got destroyed in the attack, so now we are short on both building materials and supplies. Please check with Eozlin on what you can help with. You can find him to the northwest outside his hut.
	stopConversation = "true",
	options = {}
}
villageElderPhase2ConvoTemplate:addScreen(dangerously_low);

already_have_crystal = ConvoScreen:new {
	id = "already_have_crystal",
	leftDialog = "@conversation/village_elder_2:s_199fe2af", -- I sense you already have a crystal and do not need another.
	stopConversation = "true",
	options = {}
}
villageElderPhase2ConvoTemplate:addScreen(already_have_crystal);

give_new_crystal = ConvoScreen:new {
	id = "give_new_crystal",
	leftDialog = "@conversation/village_elder_2:s_bdd3bae5", -- Here you are. Remember you may use the crystal to view your progress.
	stopConversation = "true",
	options = {}
}
villageElderPhase2ConvoTemplate:addScreen(give_new_crystal);

addConversationTemplate("villageElderPhase2ConvoTemplate", villageElderPhase2ConvoTemplate);
