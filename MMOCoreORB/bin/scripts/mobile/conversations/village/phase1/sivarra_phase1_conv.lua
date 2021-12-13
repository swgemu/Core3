villageSivarraPhase1ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "villageSivarraPhase1ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_d46bb0c5", -- Hello, I'm the head physician here. Are you one of the new Medics sent to help out?
	stopConversation = "false",
	options = {
		{"@conversation/fs_medic_puzzle_head_medic:s_1024d197", "are_you_sure"}, -- Yes, I'm here to help.
		{"@conversation/fs_medic_puzzle_head_medic:s_3228a43d", "i_wouldnt_loiter"} -- No, sorry I'm in the wrong place.
	}
}
villageSivarraPhase1ConvoTemplate:addScreen(intro);

intro_not_master_medic = ConvoScreen:new {
	id = "intro_not_master_medic",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_47a32bb0", -- You don't seem to have enough medical training. I'm sorry, but I don't think you are going to be able to help me. I need at least a Master Medic, if not someone with more experience.
	stopConversation = "true",
	options = {}
}
villageSivarraPhase1ConvoTemplate:addScreen(intro_not_master_medic);

intro_has_another_quest = ConvoScreen:new {
	id = "intro_has_another_quest",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_8a54510d", -- You look to be rather busy at the moment, come back to me when you aren't so busy.
	stopConversation = "true",
	options = {}
}
villageSivarraPhase1ConvoTemplate:addScreen(intro_has_another_quest);

intro_cant_talk = ConvoScreen:new {
	id = "intro_cant_talk",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_3b984995", -- I'm sorry, I don't know you. I only work with people I know.
	stopConversation = "true",
	options = {}
}
villageSivarraPhase1ConvoTemplate:addScreen(intro_cant_talk);

intro_did_all_sets = ConvoScreen:new {
	id = "intro_did_all_sets",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_3496f642", -- You've already done more than anyone ever expected, please take some time to rest, everyone needs to take a moment to rest.
	stopConversation = "true",
	options = {}
}
villageSivarraPhase1ConvoTemplate:addScreen(intro_did_all_sets);

intro_inv_full = ConvoScreen:new {
	id = "intro_inv_full",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_36b08dde", -- You seem to have a few too many items in your bag there, why don't you free up some room, then come talk to me again.
	stopConversation = "true",
	options = {}
}
villageSivarraPhase1ConvoTemplate:addScreen(intro_inv_full);

intro_completed_third_set = ConvoScreen:new {
	id = "intro_completed_third_set",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_cc506105", -- My, you are tenacious. Well, I have something that will prove useful to you, this plant is rather difficult to grow, but if you are up to the challenge, and it seems you are, the fruit is... well, you will see.
	stopConversation = "true",
	options = {}
}
villageSivarraPhase1ConvoTemplate:addScreen(intro_completed_third_set);

intro_completed_second_set = ConvoScreen:new {
	id = "intro_completed_second_set",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_a7afcfea", -- Splendid! Here, I think you may find some use of this, I know it's not much, but it should help. We still have more to do if you are interested, just let me know.
	stopConversation = "true",
	options = {}
}
villageSivarraPhase1ConvoTemplate:addScreen(intro_completed_second_set);

intro_completed_first_set = ConvoScreen:new {
	id = "intro_completed_first_set",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_fc604056", -- Wonderful! You are well under way into understanding your potential. You may wish to talk to Noldan to learn more. If you are looking for more work, let me know.
	stopConversation = "true",
	options = {}
}
villageSivarraPhase1ConvoTemplate:addScreen(intro_completed_first_set);

intro_in_progress = ConvoScreen:new {
	id = "intro_in_progress",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_2fee0236", -- Hmmm? Oh, talk to the medical droids if you are stuck. Medical records show you have %TO more to go.
	stopConversation = "false",
	options = {
		{"@conversation/fs_medic_puzzle_head_medic:s_3c93827f", "thanks"} -- Okay.
	}
}
villageSivarraPhase1ConvoTemplate:addScreen(intro_in_progress);

thanks = ConvoScreen:new {
	id = "thanks",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_c4682ea6", -- Thanks!
	stopConversation = "true",
	options = {}
}
villageSivarraPhase1ConvoTemplate:addScreen(thanks);

i_wouldnt_loiter = ConvoScreen:new {
	id = "i_wouldnt_loiter",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_db216f5", -- Well, I wouldn't loiter around here. Too many sick people.
	stopConversation = "true",
	options = {}
}
villageSivarraPhase1ConvoTemplate:addScreen(i_wouldnt_loiter);

are_you_sure = ConvoScreen:new {
	id = "are_you_sure",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_1718c6ed", -- Good. Before we get started, I should let you know that you will be too busy to help out any of the other villagers. Also, I will talk with Noldan and he can help you out with some persuasion techniques if you help out. Are you sure you would like to help?
	stopConversation = "false",
	options = {
		{"@conversation/fs_medic_puzzle_head_medic:s_86129116", "great_explain"}, -- Yes, I would like to continue.
		{"@conversation/fs_medic_puzzle_head_medic:s_69ab9125", "sorry_to_hear"}, -- 	No, I have some other things to take care of.
	}
}
villageSivarraPhase1ConvoTemplate:addScreen(are_you_sure);

sorry_to_hear = ConvoScreen:new {
	id = "sorry_to_hear",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_41e66cca", -- Sorry to hear that. I know everyone here can use some help.
	stopConversation = "true",
	options = {}
}
villageSivarraPhase1ConvoTemplate:addScreen(sorry_to_hear);

great_explain = ConvoScreen:new {
	id = "great_explain",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_728f65ee", -- 	Great! Let me explain what has happened. It seems in the last attack there were multiple uses of some rather potent chemical weapons. Those you see lying around here are still sick. Unfortunately, normal medicines are not helping them.
	stopConversation = "false",
	options = {
		{"@conversation/fs_medic_puzzle_head_medic:s_7857c2a9", "highly_potent"} -- How are you treating them?
	}
}
villageSivarraPhase1ConvoTemplate:addScreen(great_explain);

highly_potent = ConvoScreen:new {
	id = "highly_potent",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_94d417d1", -- Well, I devised a highly potent, yet also highly dangerous counteragent to many of the symptoms. The only problem is that it has some side effects that are almost as bad as what they currently have. However, through multiple treatments, I've been able to cure some. Here, this draft schematic will allow you to work with the medical droids to help.
	stopConversation = "false",
	options = {
		{"@conversation/fs_medic_puzzle_head_medic:s_d17142db", "with_use"}, -- What do I do with this?
		{"@conversation/fs_medic_puzzle_head_medic:s_c4682ea6", "talk_droids"} -- Thanks!
	}
}
villageSivarraPhase1ConvoTemplate:addScreen(highly_potent);

with_use = ConvoScreen:new {
	id = "with_use",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_17db6d3c", -- 	With the use of high and lower quality components, and careful experimentation, you can specialize the treatment to cure specific symptoms. You should also be able to change what sort of side effects it produces. See if you can treat five patients, and good luck with that. Talk to the medical droids. They will help you administer the medicine.
	stopConversation = "true",
	options = {}
}
villageSivarraPhase1ConvoTemplate:addScreen(with_use);

talk_droids = ConvoScreen:new {
	id = "talk_droids",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_d08f8eb6", -- Good luck. Talk with the medical droids for help.
	stopConversation = "true",
	options = {}
}
villageSivarraPhase1ConvoTemplate:addScreen(talk_droids);

talk_droids_again = ConvoScreen:new {
	id = "talk_droids_again",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_464f7bf4", -- Good, Please talk to the medical droids again and they will help you.
	stopConversation = "true",
	options = {}
}
villageSivarraPhase1ConvoTemplate:addScreen(talk_droids_again);

talk_droids_round_three = ConvoScreen:new {
	id = "talk_droids_round_three",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_464f7bf4", -- Good, Please talk to the medical droids again and they will help you.
	stopConversation = "true",
	options = {}
}
villageSivarraPhase1ConvoTemplate:addScreen(talk_droids_round_three);

intro_start_third_set = ConvoScreen:new {
	id = "intro_start_third_set",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_e15eb34d", -- Back again are we? Well I have a special plant you may find useful, but you will need to prove you are worthy. Go heal at least another five patients then come talk to me again.
	stopConversation = "false",
	options = {
		{"@conversation/fs_medic_puzzle_head_medic:s_86129116", "talk_droids_round_three"}, -- Yes, I would like to continue.
		{"@conversation/fs_medic_puzzle_head_medic:s_69ab9125", "sorry_to_hear"}, -- No, I have some other things to take care of.
	}
}
villageSivarraPhase1ConvoTemplate:addScreen(intro_start_third_set);

intro_start_second_set = ConvoScreen:new {
	id = "intro_start_second_set",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_ddb49891", -- Oh, you are still here? well if you like, go ahead and heal at least five more patients then come talk to me again, I have a little trinket you might find useful.
	stopConversation = "false",
	options = {
		{"@conversation/fs_medic_puzzle_head_medic:s_86129116", "talk_droids_again"}, -- Yes, I would like to continue.
		{"@conversation/fs_medic_puzzle_head_medic:s_69ab9125", "sorry_to_hear"}, -- No, I have some other things to take care of.
	}
}
villageSivarraPhase1ConvoTemplate:addScreen(intro_start_second_set);

addConversationTemplate("villageSivarraPhase1ConvoTemplate", villageSivarraPhase1ConvoTemplate);
