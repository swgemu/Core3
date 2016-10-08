villageElderPhase3ConvoTemplate = ConvoTemplate:new {
	initialScreen = "intro",
	templateType = "Lua",
	luaClassHandler = "villageElderConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/village_elder_3:s_b77f095d", -- Watch out! Someone dropped a box of phase relay filaments around here. They can get into your electronics and short them out.
	stopConversation = "false",
	options = {
		{"@conversation/village_elder_3:s_78eeb91e", "building_from_scratch"}, -- Phase relay filaments? They are only used for repairing starship shields.
		{"@conversation/village_elder_3:s_32705167", "building_shield"}, -- What are phase relay filaments?
	-- Add via convo handler
	--{"@conversation/village_elder_3:s_9dc8bf5d", ""}, -- I seem to have misplaced my Force crystal. May I have another?
	}
}
villageElderPhase3ConvoTemplate:addScreen(intro);

building_shield = ConvoScreen:new {
	id = "building_shield",
	leftDialog = "@conversation/village_elder_3:s_cc50daed", -- We're building a Mark 4 shield generator to defend our village. They are used in that.
	stopConversation = "false",
	options = {
		{"@conversation/village_elder_3:s_afcc98d2", "recently_assaulted"}, -- A shield generator for an agro-colony? You must grow really juicy Maroj Melons.
	}
}
villageElderPhase3ConvoTemplate:addScreen(building_shield);

recently_assaulted = ConvoScreen:new {
	id = "recently_assaulted",
	leftDialog = "@conversation/village_elder_3:s_893aaeea", -- Usually I'd laugh at that, friend. No, we actually do have need of it. We were recently assaulted by a gang calling itself the Sith Shadows. They killed many of our people and destroyed our crops and much of the village.
	stopConversation = "false",
	options = {
		{"@conversation/village_elder_3:s_e1b39e83", "impressive_confidence"}, -- Well you don't need a shield for that. You just need me!
		{"@conversation/village_elder_3:s_cf4025df", "would_be_helpful"}, -- I'd be willing to sweep the area for their spies and outposts.
	}
}
villageElderPhase3ConvoTemplate:addScreen(recently_assaulted);

impressive_confidence = ConvoScreen:new {
	id = "impressive_confidence",
	leftDialog = "@conversation/village_elder_3:s_efa47d4e", -- Your confidence is impressive. I hope it's not empty bravado. Speak to Captain Sarguillo right over there. He'll give you all the blood and guts you can stand.
	stopConversation = "true",
	options = {}
}
villageElderPhase3ConvoTemplate:addScreen(impressive_confidence);

would_be_helpful = ConvoScreen:new {
	id = "would_be_helpful",
	leftDialog = "@conversation/village_elder_3:s_abd57d77", -- That would be most helpful. Speak to Dageerin to the west over by the communal huts.
	stopConversation = "true",
	options = {}
}
villageElderPhase3ConvoTemplate:addScreen(would_be_helpful);

building_from_scratch = ConvoScreen:new {
	id = "building_from_scratch",
	leftDialog = "@conversation/village_elder_3:s_4d973713", -- That's what we're doing. Well, building one from scratch really. We've got the beginnings of a Mark 4 shield generator right over there.
	stopConversation = "false",
	options = {
		{"@conversation/village_elder_3:s_6857cea2", "like_your_enthusiasm"}, -- You're kidding. I've got to get in on this! where do I sign up?
		{"@conversation/village_elder_3:s_5d8d739e", "supply_convoys"}, -- How are you getting the resources for such a massive project?
	}
}
villageElderPhase3ConvoTemplate:addScreen(building_from_scratch);

like_your_enthusiasm = ConvoScreen:new {
	id = "like_your_enthusiasm",
	leftDialog = "@conversation/village_elder_3:s_6acff81", -- I like your enthusiasm. Speak to Quharek near the shield generator construction site. I am sure he will appreciate the help.
	stopConversation = "true",
	options = {}
}
villageElderPhase3ConvoTemplate:addScreen(like_your_enthusiasm);

supply_convoys = ConvoScreen:new {
	id = "supply_convoys",
	leftDialog = "@conversation/village_elder_3:s_f5d9b5d4", -- Supply convoys mostly. When they can get through the Sith Shadow attacks that is. The margin between what we have and what we need always stays slim, however.
	stopConversation = "false",
	options = {
		{"@conversation/village_elder_3:s_6aefa2ce", "shield_resources"}, -- Well, I could see about finding resources. What do you need?
	}
}
villageElderPhase3ConvoTemplate:addScreen(supply_convoys);

shield_resources = ConvoScreen:new {
	id = "shield_resources",
	leftDialog = "@conversation/village_elder_3:s_ac2de13b", -- Mostly resources for the shield. Speak to Eozlin to the northwest of here. He should be able to tell you the specifics.
	stopConversation = "true",
	options = {}
}
villageElderPhase3ConvoTemplate:addScreen(shield_resources);

already_have_crystal = ConvoScreen:new {
	id = "already_have_crystal",
	leftDialog = "@conversation/village_elder_3:s_199fe2af", -- I sense you already have a crystal and do not need another.
	stopConversation = "true",
	options = {}
}
villageElderPhase3ConvoTemplate:addScreen(already_have_crystal);

give_new_crystal = ConvoScreen:new {
	id = "give_new_crystal",
	leftDialog = "@conversation/village_elder_3:s_bdd3bae5", -- Here you are. Remember you may use the crystal to view your progress.
	stopConversation = "true",
	options = {}
}
villageElderPhase3ConvoTemplate:addScreen(give_new_crystal);

addConversationTemplate("villageElderPhase3ConvoTemplate", villageElderPhase3ConvoTemplate);
