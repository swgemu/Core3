padawan_spice_mom_02_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "padawan_spice_mom_02_conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_spice_mom_02:s_168212d8", -- What are you lookin' for? Somethin' to keep you awake? Help you sleep? Help you walk, talk, eat, not eat, run faster, swim longer? Anything you want, need, or can dream up, I have and am willing to sell. For a price.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_02:s_d0812b8d", "sure_about_that"}, -- I'm sorry, I think I have the wrong person.
		{"@conversation/padawan_spice_mom_02:s_1f593aa5", "law_enforcement"}, -- I'm not interested. But I believe I know someone who is?
	}
}
padawan_spice_mom_02_convo_template:addScreen(intro);

sure_about_that = ConvoScreen:new {
	id = "sure_about_that",
	leftDialog = "@conversation/padawan_spice_mom_02:s_e66080c4", -- You sure about that?  I've got what every man and woman in the Galaxy needs.  Name your pleasure, my friend.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_02:s_798612aa", "good_friend"}, -- It's not for me, Sola sent me for her weekly supplies.
		{"@conversation/padawan_spice_mom_02:s_6168a073", "sola_sent_you"}, -- Now I'm certain I have the wrong guy.
	}
}
padawan_spice_mom_02_convo_template:addScreen(sure_about_that);

sola_sent_you = ConvoScreen:new {
	id = "sola_sent_you",
	leftDialog = "@conversation/padawan_spice_mom_02:s_a0730d59", -- 	Sola sent you didn't she?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_02:s_798612aa", "good_friend"}, -- It's not for me, Sola sent me for her weekly supplies.
		{"@conversation/padawan_spice_mom_02:s_6168a073", "sola_sent_you"}, -- Now I'm certain I have the wrong guy.
	}
}
padawan_spice_mom_02_convo_template:addScreen(sola_sent_you);

good_friend = ConvoScreen:new {
	id = "good_friend",
	leftDialog = "@conversation/padawan_spice_mom_02:s_f5bb1061", -- Oh! You should have said so before friend. Miss Sola is a good friend of mine... and a loyal customer. Take this to her and tell her Evif sends his well wishes.
	stopConversation = "true",
	options = {}
}
padawan_spice_mom_02_convo_template:addScreen(good_friend);

law_enforcement = ConvoScreen:new {
	id = "law_enforcement",
	leftDialog = "@conversation/padawan_spice_mom_02:s_a04364ee", -- You aren't in law enforcement now are you?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_02:s_bdb90e46", "quick_to_judge"}, -- No, Sola sent me here for her weekly supplies.
	}
}
padawan_spice_mom_02_convo_template:addScreen(law_enforcement);

quick_to_judge = ConvoScreen:new {
	id = "quick_to_judge",
	leftDialog = "@conversation/padawan_spice_mom_02:s_2c96cac3", -- Oh!  You should have said so before friend, and you shouldn't be so quick to judge.  
	stopConversation = "true",
	options = {}
}
padawan_spice_mom_02_convo_template:addScreen(quick_to_judge);

not_quest_owner = ConvoScreen:new {
	id = "not_quest_owner",
	leftDialog = "@conversation/padawan_spice_mom_02:s_b56527e1", -- Anything you want, need, or can dream up, I have and am willing to sell. For a price.
	stopConversation = "true",
	options = {}
}
padawan_spice_mom_02_convo_template:addScreen(not_quest_owner);

addConversationTemplate("padawan_spice_mom_02_convo_template", padawan_spice_mom_02_convo_template);
