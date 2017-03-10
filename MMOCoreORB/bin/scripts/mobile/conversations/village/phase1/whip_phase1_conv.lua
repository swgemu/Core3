villageWhipPhase1ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "villageWhipPhase1ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/village_whip:s_35ee8c91", -- Blast it all, the count is still coming up short. Oh, I'm sorry, hello.
	stopConversation = "false",
	options = {
		{"@conversation/village_whip:s_22a5c907", "serious_problem"}, -- Hello.
		{"@conversation/village_whip:s_a1ba7ed2", "repelled_an_attack"}, -- What's the matter?
		{"@conversation/village_whip:s_455e077f", "very_well"}, -- I'm sorry, I thought you were someone else.
	}
}
villageWhipPhase1ConvoTemplate:addScreen(intro);

intro_has_other_quest = ConvoScreen:new {
	id = "intro_has_other_quest",
	leftDialog = "@conversation/village_whip:s_bfdaca25", -- Say, could you... oh, it looks like you're already pretty busy. On your way then.
	stopConversation = "true",
	options = {}
}
villageWhipPhase1ConvoTemplate:addScreen(intro_has_other_quest);

serious_problem = ConvoScreen:new {
	id = "serious_problem",
	leftDialog = "@conversation/village_whip:s_74140308", -- Forgive my distraction. It seems we have quite a serious problem on our hands.
	stopConversation = "false",
	options = {
		{"@conversation/village_whip:s_7b35cfbc", "repelled_an_attack"}, -- What is the problem?
		{"@conversation/village_whip:s_5d0073c6", "good_bye"}, -- I'm sorry to hear that. Good-bye.
	}
}
villageWhipPhase1ConvoTemplate:addScreen(serious_problem);

repelled_an_attack = ConvoScreen:new {
	id = "repelled_an_attack",
	leftDialog = "@conversation/village_whip:s_39f2cf64", -- Our struggle against the Sith Shadows has waged for many moons. We just recently repelled an attack against our village, but not without some losses, I'm afraid.
	stopConversation = "false",
	options = {
		{"@conversation/village_whip:s_edb238bc", "came_up_short"}, -- Go on.
		{"@conversation/village_whip:s_5d0073c6", "good_bye"}, -- I'm sorry to hear that. Good-bye.
	}
}
villageWhipPhase1ConvoTemplate:addScreen(repelled_an_attack);

came_up_short = ConvoScreen:new {
	id = "came_up_short",
	leftDialog = "@conversation/village_whip:s_40681425", -- I took a head count of both the survivors and the casualties, and the number came up short of what was expected. I fear the worst has happened.
	stopConversation = "false",
	options = {
		{"@conversation/village_whip:s_77e48d5b", "people_taken_prisoner"}, -- What do you mean?
		{"@conversation/village_whip:s_8dace66", "as_do_i"}, -- I hope they turn up. Good-bye.
	}
}
villageWhipPhase1ConvoTemplate:addScreen(came_up_short);

people_taken_prisoner = ConvoScreen:new {
	id = "people_taken_prisoner",
	leftDialog = "@conversation/village_whip:s_e9a9130f", -- I'm afraid that the missing people have been taken prisoner by the Sith Shadows during the last raid on the village. To make matters worse, we don't have enough manpower right now to mount an effective search party to go look for them.
	stopConversation = "false",
	options = {
		{"@conversation/village_whip:s_a767cb3c", "find_missing_people"}, -- Is there anything that I can do to help?
		{"@conversation/village_whip:s_551d5a8f", "higher_sith_gifted"}, -- No one noticed they were taken captive?
		{"@conversation/village_whip:s_1dac49d2", "as_do_i"}, -- I hope you find them soon. Good-bye.
	}
}
villageWhipPhase1ConvoTemplate:addScreen(people_taken_prisoner);

higher_sith_gifted = ConvoScreen:new {
	id = "higher_sith_gifted",
	leftDialog = "@conversation/village_whip:s_9359f893", -- Some of the higher ranking Sith Shadows are gifted in the ways of the Force. It is not unlikely that they were able to influence a few of the weaker members of our village.
	stopConversation = "false",
	options = {
		{"@conversation/village_whip:s_a767cb3c", "find_missing_people"}, -- Is there anything that I can do to help?
		{"@conversation/village_whip:s_1dac49d2", "as_do_i"}, -- I hope you find them soon. Good-bye.
	}
}
villageWhipPhase1ConvoTemplate:addScreen(higher_sith_gifted);

find_missing_people = ConvoScreen:new {
	id = "find_missing_people",
	leftDialog = "@conversation/village_whip:s_dc8490a", -- I've got my responsibilities here at the village that I need to look after. What we really need is someone that can go out and find the missing people, and bring them back if possible.
	stopConversation = "false",
	options = {
		{"@conversation/village_whip:s_d18b8c00", "excellent_news"}, -- That sounds like something that I could do.
		{"@conversation/village_whip:s_bf15feab", "wont_deceive_you"}, -- Would that be dangerous?
		{"@conversation/village_whip:s_9129fd1b", "good_day"}, -- That sounds like a job for someone else.
	}
}
villageWhipPhase1ConvoTemplate:addScreen(find_missing_people);

wont_deceive_you = ConvoScreen:new {
	id = "wont_deceive_you",
	leftDialog = "@conversation/village_whip:s_7e76f08e", -- I will not deceive you. If the villagers have been captured by the Sith Shadows, there will undoubtedly be guards there. I'm sure they wouldn't let you go without a fight.
	stopConversation = "false",
	options = {
		{"@conversation/village_whip:s_91bf5d37", "excellent_news"}, -- I think that I can help you.
		{"@conversation/village_whip:s_54d57caf", "good_day"}, -- I don't think that I can help with this task.
	}
}
villageWhipPhase1ConvoTemplate:addScreen(wont_deceive_you);

excellent_news = ConvoScreen:new {
	id = "excellent_news",
	leftDialog = "@conversation/village_whip:s_8ccc4e47", -- That is excellent news. I appreciate all the help that we can get. There are five people missing from the village. If you can bring them all back alive, I will help you learn to use the Force to enhance your survival skills.
	stopConversation = "false",
	options = {
		{"@conversation/village_whip:s_d38b8e62", "not_taken_lightly"}, -- I understand. I will find the missing villagers.
		{"@conversation/village_whip:s_2fdb8fbd", "just_come_back"}, -- On second thought, I don't think I can help right now.
	}
}
villageWhipPhase1ConvoTemplate:addScreen(excellent_news);

not_taken_lightly = ConvoScreen:new {
	id = "not_taken_lightly",
	leftDialog = "@conversation/village_whip:s_eefb2830", -- You must realize that this is not a task to be taken lightly. If you help me with this, you will not be able to assist anyone else for a while. Do you understand?
	stopConversation = "false",
	options = {
		{"@conversation/village_whip:s_34ea67b6", "good_place_to_start"}, -- Yes, that is fine.
		{"@conversation/village_whip:s_d7ce4a0d", "i_see_come_back"}, -- Oh, in that case I'd rather not.
	}
}
villageWhipPhase1ConvoTemplate:addScreen(not_taken_lightly);

good_place_to_start = ConvoScreen:new {
	id = "good_place_to_start",
	leftDialog = "@conversation/village_whip:s_3e543459", -- Wonderful. You may want to begin by finding where the Sith Shadows went after we drove them away from the village. Our trackers have found a set of tracks leading off in this direction. That would be a good place to start.
	stopConversation = "true",
	options = {}
}
villageWhipPhase1ConvoTemplate:addScreen(good_place_to_start);

i_see_come_back = ConvoScreen:new {
	id = "i_see_come_back",
	leftDialog = "@conversation/village_whip:s_321d7941", -- I see. Well come back if you change your mind.
	stopConversation = "true",
	options = {}
}
villageWhipPhase1ConvoTemplate:addScreen(i_see_come_back);

just_come_back = ConvoScreen:new {
	id = "just_come_back",
	leftDialog = "@conversation/village_whip:s_106cd909", -- I understand. Just come back if you change your mind.
	stopConversation = "true",
	options = {}
}
villageWhipPhase1ConvoTemplate:addScreen(just_come_back);

good_day = ConvoScreen:new {
	id = "good_day",
	leftDialog = "@conversation/village_whip:s_981b299f", -- I understand. Good day to you.
	stopConversation = "true",
	options = {}
}
villageWhipPhase1ConvoTemplate:addScreen(good_day);

as_do_i = ConvoScreen:new {
	id = "as_do_i",
	leftDialog = "@conversation/village_whip:s_33b9135e", -- As do I. Good-bye.
	stopConversation = "true",
	options = {}
}
villageWhipPhase1ConvoTemplate:addScreen(as_do_i);

good_bye = ConvoScreen:new {
	id = "good_bye",
	leftDialog = "@conversation/village_whip:s_c2db6878", -- Good-bye.
	stopConversation = "true",
	options = {}
}
villageWhipPhase1ConvoTemplate:addScreen(good_bye);

very_well = ConvoScreen:new {
	id = "very_well",
	leftDialog = "@conversation/village_whip:s_a32ebe9e", -- Very well. Good-bye.
	stopConversation = "true",
	options = {}
}
villageWhipPhase1ConvoTemplate:addScreen(very_well);

intro_not_eligible = ConvoScreen:new {
	id = "intro_not_eligible",
	leftDialog = "@conversation/village_whip:s_b8360516", -- I don't mean to be rude, but you're getting in my way.
	stopConversation = "true",
	options = {}
}
villageWhipPhase1ConvoTemplate:addScreen(intro_not_eligible);

intro_quest_completed = ConvoScreen:new {
	id = "intro_quest_completed",
	leftDialog = "@conversation/village_whip:s_ab0312ab", -- You rescued all the villagers! That's fantastic. There are many families that owe you a debt of gratitude.
	stopConversation = "true",
	options = {}
}
villageWhipPhase1ConvoTemplate:addScreen(intro_quest_completed);

intro_quest_aborted = ConvoScreen:new {
	id = "intro_quest_aborted",
	leftDialog = "@conversation/village_whip:s_ccc7b5db", -- Uh oh... it looks like something happened during the transmission to your datapad. Here, let me try again...
	stopConversation = "true",
	options = {}
}
villageWhipPhase1ConvoTemplate:addScreen(intro_quest_aborted);

intro_quest_failed = ConvoScreen:new {
	id = "intro_quest_failed",
	leftDialog = "@conversation/village_whip:s_4d0a11ef", -- You failed? That is disappointing, but we shouldn't dwell on it. There are still more that are missing. Our trackers have found a new set of tracks leading in this direction.
	stopConversation = "true",
	options = {}
}
villageWhipPhase1ConvoTemplate:addScreen(intro_quest_failed);

intro_quest_continue = ConvoScreen:new {
	id = "intro_quest_continue",
	leftDialog = "@conversation/village_whip:s_6862142d", -- Excellent work, but I still count %DI still missing. Our trackers have found a new set of tracks in this direction. This might help you find the next Shadow camp.
	stopConversation = "true",
	options = {}
}
villageWhipPhase1ConvoTemplate:addScreen(intro_quest_continue);

intro_quest_inprogress = ConvoScreen:new {
	id = "intro_quest_inprogress",
	leftDialog = "@conversation/village_whip:s_ea9470bd", -- Go on now! You've got to go find those missing villagers!
	stopConversation = "true",
	options = {}
}
villageWhipPhase1ConvoTemplate:addScreen(intro_quest_inprogress);

addConversationTemplate("villageWhipPhase1ConvoTemplate", villageWhipPhase1ConvoTemplate);
