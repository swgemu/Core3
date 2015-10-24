trialsPadawanSpiceMom02ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanSpiceMom02ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_spice_mom_02:s_168212d8", -- What are you lookin' for? Somethin' to keep you awake? Help you sleep? Help you walk, talk, eat, not eat, run faster, swim longer? Anything you want, need, or can dream up, I have and am willing to sell. For a price.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_02:s_1f593aa5", "intro_more"}, -- I'm not interested. But I believe I know someone who is?
		{"@conversation/padawan_spice_mom_02:s_d0812b8d", "intro_not"} -- I'm sorry, I think I have the wrong person.
	}
}
trialsPadawanSpiceMom02ConvoTemplate:addScreen(intro);

intro_more = ConvoScreen:new {
	id = "intro_more",
	leftDialog = "@conversation/padawan_spice_mom_02:s_a0730d59", -- Sola sent you didn't she?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_02:s_625ba59c", "more_done"}, -- I guess. Thought I can't imagine why she'd be dealing with you..
		{"@conversation/padawan_spice_mom_02:s_ca7eddd3", "intro_protect"} -- You leave her alone! She doesn't need a thug like you bothering her.
	}
}
trialsPadawanSpiceMom02ConvoTemplate:addScreen(intro_more);

intro_protect = ConvoScreen:new {
	id = "intro_protect",
	leftDialog = "@conversation/padawan_spice_mom_02:s_6242972e", -- Whatever you say friend. I'm not going to argue. I'll say this though... shouldn't be so quick to judge people you barely know. And believe me, Sola can take care of herself. She's willing to do what she feels needs doing.
	stopConversation = "true",
	options = {}
}
trialsPadawanSpiceMom02ConvoTemplate:addScreen(intro_protect);

intro_not = ConvoScreen:new {
	id = "intro_not",
	leftDialog = "@conversation/padawan_spice_mom_02:s_e66080c4", -- You sure about that? I've got what every man and woman in the Galaxy needs. Name your pleasure, my friend.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_02:s_798612aa", "intro_done"}, -- It's not for me, Sola sent me for her weekly supplies.
		{"@conversation/padawan_spice_mom_02:s_6168a073", "not_sure"} -- Now I'm certain I have the wrong guy.
	}
}
trialsPadawanSpiceMom02ConvoTemplate:addScreen(intro_not);

not_sure = ConvoScreen:new {
	id = "not_sure",
	leftDialog = "@conversation/padawan_spice_mom_02:s_a04364ee", -- You aren't in law enforcement now are you?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_02:s_bdb90e46", "intro_done_too"} -- No, Sola sent me here for her weekly supplies.
	}
}
trialsPadawanSpiceMom02ConvoTemplate:addScreen(not_sure);

intro_done_too = ConvoScreen:new {
	id = "intro_done_too",
	leftDialog = "@conversation/padawan_spice_mom_02:s_2c96cac3", -- Oh! You should have said so before friend, and you shouldn't be so quick to judge. Everyone has their hobbies; Miss Sola is a good friend of mine, and a loyal customer. Take this to her and tell her Evif sends his well wishes.
	stopConversation = "true",
	options = {}
}
trialsPadawanSpiceMom02ConvoTemplate:addScreen(intro_done_too);

intro_done = ConvoScreen:new {
	id = "intro_done",
	leftDialog = "@conversation/padawan_spice_mom_02:s_f5bb1061", -- Oh! You should have said so before friend. Miss Sola is a good friend of mine... and a loyal customer. Take this to her and tell her Evif sends his well wishes.
	stopConversation = "true",
	options = {}
}
trialsPadawanSpiceMom02ConvoTemplate:addScreen(intro_done);

more_done = ConvoScreen:new {
	id = "more_done",
	leftDialog = "@conversation/padawan_spice_mom_02:s_350fcbe3", -- She has her reasons. Miss Sola is a friend and a loyal customer. just take this to her and tell her Evif sends his well wishes.
	stopConversation = "true",
	options = {}
}
trialsPadawanSpiceMom02ConvoTemplate:addScreen(more_done);

noquest_player_talks = ConvoScreen:new {
	id = "noquest_player_talks",
	leftDialog = "@conversation/padawan_spice_mom_02:s_b56527e1", -- Anything you want, need, or can dream up, I have and am willing to sell. For a price.
	stopConversation = "true",
	options = {}
}
trialsPadawanSpiceMom02ConvoTemplate:addScreen(noquest_player_talks);

addConversationTemplate("trialsPadawanSpiceMom02ConvoTemplate", trialsPadawanSpiceMom02ConvoTemplate);
