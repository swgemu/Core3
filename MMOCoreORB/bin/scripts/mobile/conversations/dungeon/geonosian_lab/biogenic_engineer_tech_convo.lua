biogenicEngineerTechConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "BiogenicEngineerTechConvoHandler",
	screens = {}
}

return_didnt_accept = ConvoScreen:new {
	id = "return_didnt_accept",
	leftDialog = "@conversation/biogenic_engineertech:s_d4b22fda", -- Oh, you're back. We're still trying to get the reactor back online. Not much progress yet, I'm afraid.
	stopConversation = "false",
	options = {
	--{"@conversation/biogenic_engineertech:s_a7b6a9c7", "oh_yes_codes"}, -- I'm supposed to give this datapad to you.
	--{"@conversation/biogenic_engineertech:s_a767cb3c", "you_can_help"}, -- Is there anything that I can do to help?
	--{"@conversation/biogenic_engineertech:s_8e26cc3d", "hope_so_too"} -- Well, I hope you get it fixed. Good bye.
	}
}

biogenicEngineerTechConvoTemplate:addScreen(return_didnt_accept);

knocked_out_power = ConvoScreen:new {
	id = "knocked_out_power",
	leftDialog = "@conversation/biogenic_engineertech:s_235c610d", -- That earthquake we just had knocked out our power reactor. The backup system came online, but we're rapidly losing power throughout the complex.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_engineertech:s_dd67013", "containment_power"}, -- What does that mean?
		{"@conversation/biogenic_engineertech:s_926a3bb3", "ok_goodbye"} -- Sounds pretty bad. I'll leave you alone.
	}
}

biogenicEngineerTechConvoTemplate:addScreen(knocked_out_power);

things_under_control = ConvoScreen:new {
	id = "things_under_control",
	leftDialog = "@conversation/biogenic_engineertech:s_8c024a43", -- We've got things under control here now. You'd better go see if anyone else needs help. Thanks again.
	stopConversation = "true",
	options = {
	}
}

biogenicEngineerTechConvoTemplate:addScreen(things_under_control);

return_init = ConvoScreen:new {
	id = "return_init",
	leftDialog = "@conversation/biogenic_engineertech:s_2c2921ad", -- Were you able to find my apprentice? Did you get the datapad?
	stopConversation = "false",
	options = {
	--{"@conversation/biogenic_engineertech:s_da5959ed", "yes_here_are_codes"}, -- Is this the datapad that you're talking about?
	--{"@conversation/biogenic_engineertech:s_27707b65", "come_back_when_find"}, -- No, I haven't gotten the datapad yet.
	}
}

biogenicEngineerTechConvoTemplate:addScreen(return_init);

security_door_lock = ConvoScreen:new {
	id = "security_door_lock",
	leftDialog = "@conversation/biogenic_engineertech:s_f8f36834", -- All of the security doors have different locking algorithms. I've had to work on that first door before, so I'm pretty familiar with how it works. However, once you're though there, you're on your own.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_engineertech:s_884784be", "and_thank_you"} -- I see. Thank you for your help.
	}
}

biogenicEngineerTechConvoTemplate:addScreen(security_door_lock);

yes_here_are_codes = ConvoScreen:new {
	id = "yes_here_are_codes",
	leftDialog = "@conversation/biogenic_engineertech:s_a3101911", -- Why, uh... yes it is! Here are the codes! And as promised, here is a key that will let you past the first security door.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_engineertech:s_df0aaba0", "security_door_lock"}, -- Only the first door?
		{"@conversation/biogenic_engineertech:s_cd2b08bc", "thanks_again_for_help"}, -- Thank you for the key.
	}
}

biogenicEngineerTechConvoTemplate:addScreen(yes_here_are_codes);

oh_yes_codes = ConvoScreen:new {
	id = "oh_yes_codes",
	leftDialog = "@conversation/biogenic_engineertech:s_c8edf6a4", -- Oh yes! The computer codes! Now we will be able to get the reactor back online. In exchange for your help, let me give you this key. Since the lockdown is in effect, it will let you get past the first security door.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_engineertech:s_df0aaba0", "security_door_lock"}, -- Only the first door?
		{"@conversation/biogenic_engineertech:s_cd2b08bc", "thanks_again_for_help"}, -- Thank you for the key.
	}
}

biogenicEngineerTechConvoTemplate:addScreen(oh_yes_codes);

can_make_key = ConvoScreen:new {
	id = "can_make_key",
	leftDialog = "@conversation/biogenic_engineertech:s_5933b1d0", -- I could easily make you a key to get you past the first security door, but I would ask you to do something for me first.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_engineertech:s_d2de343f", "assistant_codes"}, -- What is it you would have me do?
		{"@conversation/biogenic_engineertech:s_bf0dd8c0", "well_alright"} -- I'm sorry. I've got to go.
	}
}

biogenicEngineerTechConvoTemplate:addScreen(can_make_key);

init_talk = ConvoScreen:new {
	id = "init_talk",
	leftDialog = "@conversation/biogenic_engineertech:s_3d90816", -- Blast, the coolant pump is offline too. We'll need to get that... oh, what are you doing here?
	stopConversation = "false",
	options = {
	--{"@conversation/biogenic_engineertech:s_a7b6a9c7", "oh_yes_codes"}, -- I'm supposed to give this datapad to you.
	--{"@conversation/biogenic_engineertech:s_428087e9", "knocked_out_power"}, -- What's happening here?
	--{"@conversation/biogenic_engineertech:s_56fde3ca", "could_use_help"}, -- I'm trying to help secure the facility.
	--{"@conversation/biogenic_engineertech:s_99c2fa91", "wandered_bad_spot"}, -- I just sort of wandered in, I guess.
	--{"@conversation/biogenic_engineertech:s_9d6ccb86", "thanks_for_stopping"}, -- I'm just leaving.
	}
}

biogenicEngineerTechConvoTemplate:addScreen(init_talk);

thanks_for_stopping = ConvoScreen:new {
	id = "thanks_for_stopping",
	leftDialog = "@conversation/biogenic_engineertech:s_f4e8ce21", -- OK, thanks for stopping by.
	stopConversation = "true",
	options = {}
}

biogenicEngineerTechConvoTemplate:addScreen(thanks_for_stopping);

wandered_bad_spot = ConvoScreen:new {
	id = "wandered_bad_spot",
	leftDialog = "@conversation/biogenic_engineertech:s_5fe76a83", -- You've wandered into a bad spot I'm afraid. That earthquake knocked out our power reactor and we're rapidly losing power throughout the complex.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_engineertech:s_dd67013", "containment_power"}, -- What does that mean?
		{"@conversation/biogenic_engineertech:s_926a3bb3", "ok_goodbye"} -- Sounds pretty bad. I'll leave you alone.
	}
}

biogenicEngineerTechConvoTemplate:addScreen(wandered_bad_spot);

you_can_help = ConvoScreen:new {
	id = "you_can_help",
	leftDialog = "@conversation/biogenic_engineertech:s_9541ca42", -- Actually, now that you mention it, there is. We have the materials here to repair the reactor, but I can't bring it online without the computer codes. My assistant currently has the codes on his datapad, but I don't know where he is.
	stopConversation = "false",
	options = {
	{"@conversation/biogenic_engineertech:s_dc2e08dd", "find_my_assistant"}, -- OK, what do you need me to do?
	{"@conversation/biogenic_engineertech:s_bf0dd8c0", "well_alright"}, -- I'm sorry. I've got to go.
	}
}
biogenicEngineerTechConvoTemplate:addScreen(you_can_help);

containment_power = ConvoScreen:new {
	id = "containment_power",
	leftDialog = "@conversation/biogenic_engineertech:s_347a730", -- Unfortunately, that means that the power to our containment system failed. No doubt you've probably seen some pretty fearsome creatures wandering around.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_engineertech:s_30c757f6", "security_grid_offline"}, -- What else has been affected?
		{"@conversation/biogenic_engineertech:s_a767cb3c", "you_can_help"}, -- Is there anything that I can do to help?
		{"@conversation/biogenic_engineertech:s_8e26cc3d", "well_alright"} -- Well, I hope you get it fixed. Good bye.
	}
}

biogenicEngineerTechConvoTemplate:addScreen(containment_power);

ok_goodbye = ConvoScreen:new {
	id = "ok_goodbye",
	leftDialog = "@conversation/biogenic_engineertech:s_b78f009b", -- Alright. Good-bye.
	stopConversation = "true",
	options = {}
}
biogenicEngineerTechConvoTemplate:addScreen(ok_goodbye);

hope_so_too = ConvoScreen:new {
	id = "hope_so_too",
	leftDialog = "@conversation/biogenic_engineertech:s_4c14f9fb", -- Yes, I hope so too.
	stopConversation = "true",
	options = {}
}
biogenicEngineerTechConvoTemplate:addScreen(hope_so_too);

security_grid_offline = ConvoScreen:new {
	id = "security_grid_offline",
	leftDialog = "@conversation/biogenic_engineertech:s_1615f465", -- It looks like the security grid is offline too. I don't know how that will effect the sentry droids, but the security doors are probably locked down. Without a special key you wouldn't be able to get much further into the complex.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_engineertech:s_eb038dde", "can_make_key"}, -- Where could I get one of those keys?
		{"@conversation/biogenic_engineertech:s_c1eda1a3", "alright_good_luck"} -- I'll give it a try anyway. Good-bye.
	}
}
biogenicEngineerTechConvoTemplate:addScreen(security_grid_offline);

well_alright = ConvoScreen:new {
	id = "well_alright",
	leftDialog = "@conversation/biogenic_engineertech:s_69a2ad00", -- Well, alright. Good-bye then.
	stopConversation = "true",
	options = {
	}
}
biogenicEngineerTechConvoTemplate:addScreen(well_alright);

find_my_assistant = ConvoScreen:new {
	id = "find_my_assistant",
	leftDialog = "@conversation/biogenic_engineertech:s_aa71d09d", -- I need to you to find my assistant, and bring his datapad back here to me. If you can get me those codes, I'll see if I can wire you a key that will let you through the first security door.
	stopConversation = "false",
	options = {
	--{"@conversation/biogenic_engineertech:s_da5959ed", "yes_here_are_codes"}, -- Is this the datapad that you're talking about?
	--{"@conversation/biogenic_engineertech:s_b3d8b98a", "come_back_with_codes"}, -- Alright, I'll come back when I've found your assistant.
	--{"@conversation/biogenic_engineertech:s_d7f1b726", "thanks_anyway"} -- I'll see what I can do, but I'm not making any promises.
	}
}
biogenicEngineerTechConvoTemplate:addScreen(find_my_assistant);

assistant_codes = ConvoScreen:new {
	id = "assistant_codes",
	leftDialog = "@conversation/biogenic_engineertech:s_75c607ac", -- My assistant has some computer codes that we need to restart the reactor. If you bring me his datapad with those codes, I will gladly make you a security key.
	stopConversation = "false",
	options = {
	--{"@conversation/biogenic_engineertech:s_da5959ed", "yes_here_are_codes"}, -- Is this the datapad that you're talking about?
	--{"@conversation/biogenic_engineertech:s_b3d8b98a", "come_back_with_codes"}, -- Alright, I'll come back when I've found your assistant.
	--{"@conversation/biogenic_engineertech:s_d7f1b726", "thanks_anyway"} -- I'll see what I can do, but I'm not making any promises.
	}
}
biogenicEngineerTechConvoTemplate:addScreen(assistant_codes);

come_back_when_find = ConvoScreen:new {
	id = "come_back_when_find",
	leftDialog = "@conversation/biogenic_engineertech:s_76e305ae", -- Come back as soon as you find it, and I'll get you a key for that security door.
	stopConversation = "true",
	options = {
	}
}

biogenicEngineerTechConvoTemplate:addScreen(come_back_when_find);

come_back_with_codes = ConvoScreen:new {
	id = "come_back_with_codes",
	leftDialog = "@conversation/biogenic_engineertech:s_e61f6f04", -- Thank you very much. Come back with the codes and I'll make you a security key.
	stopConversation = "true",
	options = {
	}
}

biogenicEngineerTechConvoTemplate:addScreen(come_back_with_codes);

thanks_anyway = ConvoScreen:new {
	id = "thanks_anyway",
	leftDialog = "@conversation/biogenic_engineertech:s_94350653", -- Alright, well thanks anyway. But don't forget that you won't be able to go much farther into the facility without a key to disable that security door.
	stopConversation = "true",
	options = {}
}

biogenicEngineerTechConvoTemplate:addScreen(thanks_anyway);

could_use_help = ConvoScreen:new {
	id = "could_use_help",
	leftDialog = "@conversation/biogenic_engineertech:s_6569e789", -- We could certainly use the help, that's for sure. That earthquake knocked out our power reactor and we're rapidly losing power throughout the complex.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_engineertech:s_dd67013", "containment_power"}, -- What does that mean?
		{"@conversation/biogenic_engineertech:s_926a3bb3", "ok_goodbye"} -- Sounds pretty bad. I'll leave you alone.
	}
}

biogenicEngineerTechConvoTemplate:addScreen(could_use_help);

thanks_again_for_help = ConvoScreen:new {
	id = "thanks_again_for_help",
	leftDialog = "@conversation/biogenic_engineertech:s_b8cdda4", -- Thanks again for your help. And good luck to you!
	stopConversation = "true",
	options = {
	}
}
biogenicEngineerTechConvoTemplate:addScreen(thanks_again_for_help);

and_thank_you = ConvoScreen:new {
	id = "and_thank_you",
	leftDialog = "@conversation/biogenic_engineertech:s_4fe2bd07", -- And thank you for yours. Good luck to you!
	stopConversation = "true",
	options = {
	}
}
biogenicEngineerTechConvoTemplate:addScreen(and_thank_you);

alright_good_luck = ConvoScreen:new {
	id = "alright_good_luck",
	leftDialog = "@conversation/biogenic_engineertech:s_5afc1718", -- Alright, good luck!
	stopConversation = "true",
	options = {
	}
}
biogenicEngineerTechConvoTemplate:addScreen(alright_good_luck);

addConversationTemplate("biogenicEngineerTechConvoTemplate", biogenicEngineerTechConvoTemplate);
