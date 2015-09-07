villageSivarraPhase1ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "villageSivarraConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_d46bb0c5", -- Hello, I'm the head physician here. Are you one of the new Medics sent to help out?
	stopConversation = "false",
	options = {
		{"@conversation/fs_medic_puzzle_head_medic:s_1024d197", "are_you_sure"}, -- Yes, I'm here to help
		{"@conversation/fs_medic_puzzle_head_medic:s_3228a43d", "lost"} -- No, sorry I'm in the wrong place.
	}
}
villageSivarraPhase1ConvoTemplate:addScreen(intro);

lost = ConvoScreen:new {
	id = "lost",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic.stf:s_db216f5", -- Well, I wouldn't loiter around here. Too many sick people.
	stopConversation = "true",
	options = {}
}

villageSivarraPhase1ConvoTemplate:addScreen(lost);

not_master_medic = ConvoScreen:new {
	id = "not_master_medic",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_47a32bb0", -- You don't seem to have enough medical training. I'm sorry, but I don't think you are going to be able to help me. I need at least a Master Medic, if not someone with more experience.
	stopConversation = "true",
	options = {}
}
villageSivarraPhase1ConvoTemplate:addScreen(not_master_medic);

are_you_sure = ConvoScreen:new {
	id = "are_you_sure",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_1718c6ed", -- Good. Before we get started, I should let you know that you will be too busy to help out any of the other villagers. Also, I will talk with Noldan and he can help you out with some persuasion techniques if you help out. Are you sure you would like to help?
	stopConversation = "false",
	options = {
	{"@conversation/fs_medic_puzzle_head_medic:s_69ab9125", "sorry_to_hear"}, -- 	No, I have some other things to take care of.
	{"@conversation/fs_medic_puzzle_head_medic:s_86129116", "great_explain"} -- Yes, I would like to continue.
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
	{"@conversation/fs_medic_puzzle_head_medic:s_7857c2a9", "with_use"} -- How are you treating them?
	}
}
villageSivarraPhase1ConvoTemplate:addScreen(great_explain);


with_use = ConvoScreen:new {
	id = "with_use",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic:s_17db6d3c", -- 	With the use of high and lower quality components, and careful experimentation, you can specialize the treatment to cure specific symptoms. You should also be able to change what sort of side effects it produces. See if you can treat five patients, and good luck with that. Talk to the medical droids. They will help you administer the medicine.
	stopConversation = "false",
	options = {
	{"@conversation/fs_medic_puzzle_head_medic:s_cc64464a", "talk_droids"} -- Yes, let's get started
	}
}
villageSivarraPhase1ConvoTemplate:addScreen(with_use);


talk_droids = ConvoScreen:new {
	id = "talk_droids",
	leftDialog = "@conversation/fs_medic_puzzle_head_medic.stf:s_d08f8eb6", -- 	Good luck. Talk with the medical droids for help.
	stopConversation = "true",
	options = {}
}
villageSivarraPhase1ConvoTemplate:addScreen(talk_droids);

addConversationTemplate("llageSivarraPhase1ConvoTemplate", llageSivarraPhase1ConvoTemplate);