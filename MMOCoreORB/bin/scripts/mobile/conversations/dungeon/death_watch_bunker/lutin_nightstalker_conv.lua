lutinNightstalkerConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "deathWatchLutinNightstalkerConvoHandler",
	screens = {}
}

wrong_faction = ConvoScreen:new {
	id = "wrong_faction",
	leftDialog = "@conversation/death_watch_rebel_herald:s_95369855", -- Hmm.. you don't seem to be 'one of us'. I must ask you to leave. I'm waiting for someone else. I have nothing more to say to you.
	stopConversation = "true",
	options = {
	}
}
lutinNightstalkerConvoTemplate:addScreen(wrong_faction);

cant_talk_busy = ConvoScreen:new {
	id = "cant_talk_busy",
	leftDialog = "@conversation/death_watch_rebel_herald:s_91db32fc", -- I can't speak right now. My current mission is demanding that I stay focused. I invite you to return at a later date. I may have a few tasks for you then.
	stopConversation = "true",
	options = {
	}
}
lutinNightstalkerConvoTemplate:addScreen(cant_talk_busy);

return_intro = ConvoScreen:new {
	id = "return_intro",
	leftDialog = "@conversation/death_watch_rebel_herald:s_8361bfd1", -- You have returned! Were you successful in rescuing our scientist?
	stopConversation = "false",
	options = {
	--Handled by convo handler
	--{"@conversation/death_watch_rebel_herald:s_9b06da0", "excellent_reward"}, -- Yes, I rescued the scientist successfully.
	--{"@conversation/death_watch_rebel_herald:s_dc839e59", "please_be_quick"}, -- No, I'm still looking into it.
	--{"@conversation/death_watch_rebel_herald:s_6f2c6f44", "more_information"}, -- I need more information regarding these Death Watch fellas.
	--{"@conversation/death_watch_rebel_herald:s_f70821a3", "this_distresses_me"}, -- I quit!
	}
}

lutinNightstalkerConvoTemplate:addScreen(return_intro);

excellent_reward = ConvoScreen:new {
	id = "excellent_reward",
	leftDialog = "@conversation/death_watch_rebel_herald:s_37b46abd", -- Excellent! Your reward as promised. I know it isn't much. I greatly appreciate your efforts.
	stopConversation = "true",
	options = {
	}
}
lutinNightstalkerConvoTemplate:addScreen(excellent_reward);

more_information = ConvoScreen:new {
	id = "more_information",
	leftDialog = "@conversation/death_watch_rebel_herald:s_2d06d9f7", -- The Death Watch Operatives are located on Endor in the northwestern part of the planet. Our scientist is somewhere within their hideout. I suspect he'll be heavily guarded. He needs to be rescued before he is executed. Please be quick about it! We haven't any time to lose.
	stopConversation = "true",
	options = {
	}
}
lutinNightstalkerConvoTemplate:addScreen(more_information);

please_be_quick = ConvoScreen:new {
	id = "please_be_quick",
	leftDialog = "@conversation/death_watch_rebel_herald:s_e99ef1de", -- I see. Please be quick in rescuing our ally. We will suffer greatly if he should perish.
	stopConversation = "true",
	options = {
	}
}
lutinNightstalkerConvoTemplate:addScreen(please_be_quick);

this_distresses_me = ConvoScreen:new {
	id = "this_distresses_me",
	leftDialog = "@conversation/death_watch_rebel_herald:s_88a6fa7d", -- This distresses me. Very well. You have been lifted from your mission.
	stopConversation = "true",
	options = {
	}
}
lutinNightstalkerConvoTemplate:addScreen(this_distresses_me);

quest_already_completed = ConvoScreen:new {
	id = "quest_already_completed",
	leftDialog = "@conversation/death_watch_rebel_herald:s_65aa1cd5", -- Thank you for your help earlier. We are very grateful.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_rebel_herald:s_28f5f7c5", "hideout_location"}, -- Where is the hideout again?
		{"@conversation/death_watch_rebel_herald:s_c1c188ab", "may_the_force"}, -- No problem. Bye!
	}
}
lutinNightstalkerConvoTemplate:addScreen(quest_already_completed);

hideout_location = ConvoScreen:new {
	id = "hideout_location",
	leftDialog = "@conversation/death_watch_rebel_herald:s_7089401b", -- The hideout is located on Endor and can be found northwestern part of the planet. Be careful. They can be a deadly bunch.
	stopConversation = "true",
	options = {
	}
}
lutinNightstalkerConvoTemplate:addScreen(hideout_location);

may_the_force = ConvoScreen:new {
	id = "may_the_force",
	leftDialog = "@conversation/death_watch_rebel_herald:s_2d4bb338", -- May the Force be with you!
	stopConversation = "true",
	options = {
	}
}
lutinNightstalkerConvoTemplate:addScreen(may_the_force);

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/death_watch_rebel_herald:s_bfe5e691", --Finally, you've come! We've been waiting for you!
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_rebel_herald:s_a0822589", "havent_you_heard"}, -- Uh, what?
	}
}
lutinNightstalkerConvoTemplate:addScreen(intro);

havent_you_heard = ConvoScreen:new {
	id = "havent_you_heard",
	leftDialog = "@conversation/death_watch_rebel_herald:s_940cb841", -- Haven't you heard about the kidnapping? You are of the Alliance, aren't you? Are you here to help us?
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_rebel_herald:s_823eed0c", "excellent_travel_to_bunker"}, -- Yes, I will help you!
		{"@conversation/death_watch_rebel_herald:s_62104343", "contact_kidnapped"}, -- Slow down. Help with what?
		{"@conversation/death_watch_rebel_herald:s_938e28a4", "find_someone_else"}, -- No, I can't. Find someone else.
	}
}
lutinNightstalkerConvoTemplate:addScreen(havent_you_heard);

excellent_travel_to_bunker = ConvoScreen:new {
	id = "excellent_travel_to_bunker",
	leftDialog = "@conversation/death_watch_rebel_herald:s_f4474b2c", -- Excellent! Travel to the Death Watch hideout on Endor. It can be found in the northwestern part of the planet. Be quick about it and rescue our scientist! There's no telling what will happen to him if we aren't swift.
	stopConversation = "true",
	options = {
	}
}
lutinNightstalkerConvoTemplate:addScreen(excellent_travel_to_bunker);

find_someone_else = ConvoScreen:new {
	id = "find_someone_else",
	leftDialog = "@conversation/death_watch_rebel_herald:s_afdd35a1", -- Pity. I will find someone else. Take care.
	stopConversation = "true",
	options = {
	}
}
lutinNightstalkerConvoTemplate:addScreen(find_someone_else);

contact_kidnapped = ConvoScreen:new {
	id = "contact_kidnapped",
	leftDialog = "@conversation/death_watch_rebel_herald:s_aa852a2c", -- One of our neutral contacts has been kidnapped by the Death Watch operatives on Endor. We need someone to rescue him. Naturally, we can only trust a fellow member of the Alliance. You came at the perfect time and would be an excellent candidiate to help us in our cause. Will you help us?
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_rebel_herald:s_823eed0c", "excellent_travel_to_bunker"}, -- Yes, I will help you!
		{"@conversation/death_watch_rebel_herald:s_6f2c6f44", "more_information"}, -- I need more information regarding these Death Watch fellas.
		{"@conversation/death_watch_rebel_herald:s_938e28a4", "find_someone_else"}, -- No, I can't. Find someone else.
	}
}
lutinNightstalkerConvoTemplate:addScreen(contact_kidnapped);

more_information = ConvoScreen:new {
	id = "more_information",
	leftDialog = "@conversation/death_watch_rebel_herald:s_37890704", -- Very well. A reasonable request, indeed. The Death Watch Operatives are located on Endor in the northwestern part of the planet. Our scientist is somewhere within their hideout. I suspect he'll be heavily guarded. He needs to be rescued before he is executed. We need someone to help us and we're looking to you as our only hope.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_rebel_herald:s_5c3cdba4", "excellent_travel_to_bunker"}, -- I will help you.
		{"@conversation/death_watch_rebel_herald:s_4f240e90", "find_someone_else"}, -- No, I can't. Find someone else.
	}
}
lutinNightstalkerConvoTemplate:addScreen(more_information);

addConversationTemplate("lutinNightstalkerConvoTemplate", lutinNightstalkerConvoTemplate);
