biogenicEngineerTechConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "BiogenicEngineerTechConvoHandler",
	screens = {}
}

knocked_out_power = ConvoScreen:new {
	id = "knocked_out_power",
	leftDialog = "@conversation/biogenic_engineertech:s_235c610d", -- That earthquake we just had knocked out our power reactor. The backup system came online, but we're rapidly losing power throughout the complex.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_engineertech:s_a767cb3c", "you_can_help"}, -- Is there anything that I can do to help?
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
	}
}

biogenicEngineerTechConvoTemplate:addScreen(return_init);

security_door_lock = ConvoScreen:new {
	id = "security_door_lock",
	leftDialog = "@conversation/biogenic_engineertech:s_f8f36834", -- All of the security doors have different locking algorithms. I've had to work on that first door before, so I'm pretty familiar with how it works. However, once you're though there, you're on your own.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_engineertech:s_b3d8b98a", "come_back_with_codes"}, -- Alright, I'll come back when I've found your assistant.
		{"@conversation/biogenic_engineertech:s_bf0dd8c0", "thanks_anyway"} -- I'm sorry. I've got to go.
	}
}

biogenicEngineerTechConvoTemplate:addScreen(security_door_lock);

yes_here_are_codes = ConvoScreen:new {
	id = "yes_here_are_codes",
	leftDialog = "@conversation/biogenic_engineertech:s_a3101911", -- Why, uh... yes it is! Here are the codes! And as promised, here is a key that will let you past the first security door.
	stopConversation = "true",
	options = {
	}
}

biogenicEngineerTechConvoTemplate:addScreen(yes_here_are_codes);

oh_yes_codes = ConvoScreen:new {
	id = "oh_yes_codes",
	leftDialog = "@conversation/biogenic_engineertech:s_c8edf6a4", -- Oh yes! The computer codes! Now we will be able to get the reactor back online. In exchange for your help, let me give you this key. Since the lockdown is in effect, it will let you get past the first security door.
	stopConversation = "true",
	options = {
	}
}

biogenicEngineerTechConvoTemplate:addScreen(oh_yes_codes);

can_make_key = ConvoScreen:new {
	id = "can_make_key",
	leftDialog = "@conversation/biogenic_engineertech:s_5933b1d0", -- I could easily make you a key to get you past the first security door, but I would ask you to do something for me first.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_engineertech:s_df0aaba0", "security_door_lock"}, -- Only the first door?
		{"@conversation/biogenic_engineertech:s_dc2e08dd", "assistant_codes"} -- OK, what do you need me to do?
	}
}

biogenicEngineerTechConvoTemplate:addScreen(can_make_key);

init_talk = ConvoScreen:new {
	id = "init_talk",
	leftDialog = "@conversation/biogenic_engineertech:s_3d90816", -- Blast, the coolant pump is offline too. We'll need to get that... oh, what are you doing here?
	stopConversation = "false",
	options = {
	}
}

biogenicEngineerTechConvoTemplate:addScreen(init_talk);

thanks_for_stopping = ConvoScreen:new {
	id = "thanks_for_stopping",
	leftDialog = "@conversation/biogenic_engineertech:s_f4e8ce21", -- OK, thanks for stopping by.
	stopConversation = "true",
	options = {
	}
}

biogenicEngineerTechConvoTemplate:addScreen(thanks_for_stopping);

wandered_bad_spot = ConvoScreen:new {
	id = "wandered_bad_spot",
	leftDialog = "@conversation/biogenic_engineertech:s_5fe76a83", -- You've wandered into a bad spot I'm afraid. That earthquake knocked out our power reactor and we're rapidly losing power throughout the complex.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_engineertech:s_a767cb3c", "you_can_help"}, -- Is there anything that I can do to help?
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
		{"@conversation/biogenic_engineertech:s_30c757f6", "security_grid_offline"}, -- What else has been affected?
		{"@conversation/biogenic_engineertech:s_8e26cc3d", "well_alright"} -- Well, I hope you get it fixed. Good bye.
	}
}

biogenicEngineerTechConvoTemplate:addScreen(you_can_help);

containment_power = ConvoScreen:new {
	id = "containment_power",
	leftDialog = "@conversation/biogenic_engineertech:s_347a730", -- Unfortunately, that means that the power to our containment system failed. No doubt you've probably seen some pretty fearsome creatures wandering around.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_engineertech:s_30c757f6", "security_grid_offline"}, -- What else has been affected?
		{"@conversation/biogenic_engineertech:s_8e26cc3d", "well_alright"} -- Well, I hope you get it fixed. Good bye.
	}
}

biogenicEngineerTechConvoTemplate:addScreen(containment_power);

ok_goodbye = ConvoScreen:new {
	id = "ok_goodbye",
	leftDialog = "@conversation/biogenic_engineertech:s_b78f009b", -- Alright. Good-bye.
	stopConversation = "true",
	options = {
	}
}

biogenicEngineerTechConvoTemplate:addScreen(ok_goodbye);

security_grid_offline = ConvoScreen:new {
	id = "security_grid_offline",
	leftDialog = "@conversation/biogenic_engineertech:s_1615f465", -- It looks like the security grid is offline too. I don't know how that will effect the sentry droids, but the security doors are probably locked down. Without a special key you wouldn't be able to get much further into the complex.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_engineertech:s_eb038dde", "can_make_key"}, -- Where could I get one of those keys?
		{"@conversation/biogenic_engineertech:s_8e26cc3d", "well_alright"} -- Well, I hope you get it fixed. Good bye.
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

assistant_codes = ConvoScreen:new {
	id = "assistant_codes",
	leftDialog = "@conversation/biogenic_engineertech:s_75c607ac", -- My assistant has some computer codes that we need to restart the reactor. If you bring me his datapad with those codes, I will gladly make you a security key.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_engineertech:s_b3d8b98a", "come_back_with_codes"}, -- Alright, I'll come back when I've found your assistant.
		{"@conversation/biogenic_engineertech:s_bf0dd8c0", "thanks_anyway"} -- I'm sorry. I've got to go.
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
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_engineertech:s_d7f1b726", "come_back_when_find"}, -- I'll see what I can do, but I'm not making any promises.
		{"@conversation/biogenic_engineertech:s_c1eda1a3", "alright_good_bye"} -- I'll give it a try anyway. Good-bye.
	}
}

biogenicEngineerTechConvoTemplate:addScreen(thanks_anyway);

could_use_help = ConvoScreen:new {
	id = "could_use_help",
	leftDialog = "@conversation/biogenic_engineertech:s_6569e789", -- We could certainly use the help, that's for sure. That earthquake knocked out our power reactor and we're rapidly losing power throughout the complex.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_engineertech:s_a767cb3c", "you_can_help"}, -- Is there anything that I can do to help?
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

alright_good_bye = ConvoScreen:new {
	id = "alright_good_bye",
	leftDialog = "@conversation/biogenic_engineertech:s_b78f009b", -- Alright. Good-bye.
	stopConversation = "true",
	options = {
	}
}

biogenicEngineerTechConvoTemplate:addScreen(alright_good_bye);

addConversationTemplate("biogenicEngineerTechConvoTemplate", biogenicEngineerTechConvoTemplate);