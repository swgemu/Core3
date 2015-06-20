villageElderPhase1ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "villageElderConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/village_elder_1:s_55273aaf", -- Did you see them?
	stopConversation = "false",
	options = {
		{"@conversation/village_elder_1:s_b6101821", "sith_animals"}, -- Did I see whom?
		-- Add via convo handler
		--{"@conversation/village_elder_1:s_9dc8bf5d", ""}, -- I seem to have misplaced my Force crystal. May I have another?
	}
}
villageElderPhase1ConvoTemplate:addScreen(intro);

sith_animals = ConvoScreen:new {
	id = "sith_animals",
	leftDialog = "@conversation/village_elder_1:s_72752682", -- Those Sith animals! They destroyed our village! They came out of nowhere... overwhelmed our defenses. We thought we were protected... but, we stood no chance.
	stopConversation = "false",
	options = {
		{"@conversation/village_elder_1:s_5357267d", "not_real_sith"}, -- The Sith have been extinct for ages. Their fire has gone out of the galaxy.
		{"@conversation/village_elder_1:s_e477ab86", "quite_well_defended"}, -- What kind of defenses are you talking about? This looks like a lost agro-colony.
	}
}
villageElderPhase1ConvoTemplate:addScreen(sith_animals);

not_real_sith = ConvoScreen:new {
	id = "not_real_sith",
	leftDialog = "@conversation/village_elder_1:s_455d6edc", -- They aren't real Sith. They just have some strange devotion to that evil race.
	stopConversation = "false",
	options = {
		{"@conversation/village_elder_1:s_f0e7a84", "everything_in_ruins"}, -- Ah, I see. real or not, from the looks of things they certainly were out for blood.
	}
}
villageElderPhase1ConvoTemplate:addScreen(not_real_sith);

everything_in_ruins = ConvoScreen:new {
	id = "everything_in_ruins",
	leftDialog = "@conversation/village_elder_1:s_f8ff425b", -- They sure got it. We're devastated. Most everything is in ruins, and many of our people are hurt.
	stopConversation = "false",
	options = {
		{"@conversation/village_elder_1:s_83ac5888", "sensor_array_damaged"}, -- I'm not too bad with a hydrospanner and power mallet.
		{"@conversation/village_elder_1:s_2eaf06cc", "at_healer_tent"}, -- I can help treat the wounded.
		{"@conversation/village_elder_1:s_854985e0", "best_defenders_fell"}, -- I can help defend if they come back.
		{"@conversation/village_elder_1:s_858f16f4", "captured_villagers"}, -- I am a good scout, maybe I can locate these gangers for you.
	}
}
villageElderPhase1ConvoTemplate:addScreen(everything_in_ruins);

sensor_array_damaged = ConvoScreen:new {
	id = "sensor_array_damaged",
	leftDialog = "@conversation/village_elder_1:s_ab969608", -- Our sensor array was damaged in the attack and our chief engineer was killed. Maybe you could see if you could fix it. It's East of here, against the wall.
	stopConversation = "true",
	options = {}
}
villageElderPhase1ConvoTemplate:addScreen(sensor_array_damaged);

at_healer_tent = ConvoScreen:new {
	id = "at_healer_tent",
	leftDialog = "@conversation/village_elder_1:s_7587a16a", -- Thank you, that would be very helpful. Our medic has some droids to help her, but I am sure she would appreciate your help. Her name is Sivarra Mecheaux, and she can be found at the healers tent West from here along the wall.
	stopConversation = "true",
	options = {}
}
villageElderPhase1ConvoTemplate:addScreen(at_healer_tent);

best_defenders_fell = ConvoScreen:new {
	id = "best_defenders_fell",
	leftDialog = "@conversation/village_elder_1:s_47f6c42", -- Many of our best defenders fell in the battle. We could certainly use the help. Check with Captain Sarguillo right over there.
	stopConversation = "true",
	options = {}
}
villageElderPhase1ConvoTemplate:addScreen(best_defenders_fell);

captured_villagers = ConvoScreen:new {
	id = "captured_villagers",
	leftDialog = "@conversation/village_elder_1:s_959b429b", -- What we really need is someone to find our captured villagers.
	stopConversation = "false",
	options = {
		{"@conversation/village_elder_1:s_3c6f20b4", "speak_to_whip"}, -- I will find the captives for you.
	}
}
villageElderPhase1ConvoTemplate:addScreen(captured_villagers);

speak_to_whip = ConvoScreen:new {
	id = "speak_to_whip",
	leftDialog = "@conversation/village_elder_1:s_43fe619a", -- Thank you. There has been enough loss of life already without their blood being spilled as well. Speak to Whip just South of here near the front entrance.
	stopConversation = "true",
	options = {}
}
villageElderPhase1ConvoTemplate:addScreen(speak_to_whip);

quite_well_defended = ConvoScreen:new {
	id = "quite_well_defended",
	leftDialog = "@conversation/village_elder_1:s_9ce75ab2", -- We were actually quite well defended. But they burned right through our shield. The turrets couldn't stop them and were destroyed. Then they reached the walls near the entrances. After that, all that was left was the pillaging and looting.
	stopConversation = "false",
	options = {
		{"@conversation/village_elder_1:s_a43672b0", "bear_witness"}, -- They aren't Sith, but they are certainly ruthless and powerful.
	}
}
villageElderPhase1ConvoTemplate:addScreen(quite_well_defended);

bear_witness = ConvoScreen:new {
	id = "bear_witness",
	leftDialog = "@conversation/village_elder_1:s_f0d5416", -- That they are and the ruins you see here bear witness to that statement.
	stopConversation = "false",
	options = {
		{"@conversation/village_elder_1:s_83ac5888", "sensor_array_damaged"}, -- I'm not too bad with a hydrospanner and power mallet.
		{"@conversation/village_elder_1:s_2eaf06cc", "at_healer_tent"}, -- I can help treat the wounded.
		{"@conversation/village_elder_1:s_854985e0", "best_defenders_fell"}, -- I can help defend if they come back.
		{"@conversation/village_elder_1:s_858f16f4", "captured_villagers"}, -- I am a good scout, maybe I can locate these gangers for you.
	}
}
villageElderPhase1ConvoTemplate:addScreen(bear_witness);

already_have_crystal = ConvoScreen:new {
	id = "already_have_crystal",
	leftDialog = "@conversation/village_elder_1:s_199fe2af", -- I sense you already have a crystal and do not need another.
	stopConversation = "true",
	options = {}
}
villageElderPhase1ConvoTemplate:addScreen(already_have_crystal);

give_new_crystal = ConvoScreen:new {
	id = "give_new_crystal",
	leftDialog = "@conversation/village_elder_1:s_bdd3bae5", -- Here you are. Remember you may use the crystal to view your progress.
	stopConversation = "true",
	options = {}
}
villageElderPhase1ConvoTemplate:addScreen(give_new_crystal);

addConversationTemplate("villageElderPhase1ConvoTemplate", villageElderPhase1ConvoTemplate);