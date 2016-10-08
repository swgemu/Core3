fsVillageConvo5FemaleTemplate = ConvoTemplate:new {
	initialScreen = "intro",
	templateType = "Lua",
	luaClassHandler = "conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/fs_village_convo5_f:s_afe7471", -- Are you really from another planet?
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo5_f:s_5f65644b", "want_to_be_pilot" }, -- Yup. Are you interested in space travel?
		{ "@conversation/fs_village_convo5_f:s_f02cea2", "not_from_village" }, -- No, I'm from here.
		{ "@conversation/fs_village_convo5_f:s_1aebf838", "goodbye" }, -- Wishing I was back there right now. I'll talk to you later.
	}
}
fsVillageConvo5FemaleTemplate:addScreen(intro);

want_to_be_pilot = ConvoScreen:new {
	id = "want_to_be_pilot",
	leftDialog = "@conversation/fs_village_convo5_f:s_fb77af66", -- Oh yes. I want to be a spaceship pilot.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo5_f:s_6bbd64da", "just_a_farmer" }, -- So why don't you go learn how to pilot? It's not that hard.
	}
}
fsVillageConvo5FemaleTemplate:addScreen(want_to_be_pilot);

just_a_farmer = ConvoScreen:new {
	id = "just_a_farmer",
	leftDialog = "@conversation/fs_village_convo5_f:s_de00afa9", -- Well I'm just a farmer, I've never heard of a farmer becoming a spaceship pilot.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo5_f:s_c4ca664e", "hope_i_get_chance" }, -- You'd be surprised. Some of the galaxies best pilots were farmers. I think you would have a good chance.
		{ "@conversation/fs_village_convo5_f:s_71d67ffc", "born_lucky" }, -- Yea, not much you can learn farming that would help you be a pilot. If I were you I'd just stay here and be the best farmer you can be.
	}
}
fsVillageConvo5FemaleTemplate:addScreen(just_a_farmer);

hope_i_get_chance = ConvoScreen:new {
	id = "hope_i_get_chance",
	leftDialog = "@conversation/fs_village_convo5_f:s_1c688d82", -- Really?! Wow, I hope I get the chance!
	stopConversation = "true",
	options = {}
}
fsVillageConvo5FemaleTemplate:addScreen(hope_i_get_chance);

born_lucky = ConvoScreen:new {
	id = "born_lucky",
	leftDialog = "@conversation/fs_village_convo5_f:s_42584442", -- That's what I thought. I suppose you just have to be born lucky.
	stopConversation = "true",
	options = {}
}
fsVillageConvo5FemaleTemplate:addScreen(born_lucky);

not_from_village = ConvoScreen:new {
	id = "not_from_village",
	leftDialog = "@conversation/fs_village_convo5_f:s_55a1b0c", -- You're not from the village, I would have seen you before.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo5_f:s_f4998e85", "got_to_be_going" }, -- No, I'm from the Imperial prison.
		{ "@conversation/fs_village_convo5_f:s_f8f7c983", "not_much_here" }, -- I've been gone a long time.
	}
}
fsVillageConvo5FemaleTemplate:addScreen(not_from_village);

got_to_be_going = ConvoScreen:new {
	id = "got_to_be_going",
	leftDialog = "@conversation/fs_village_convo5_f:s_38f5722b", -- What?! I... I've got to be going. Daddy told me to never talk to a prisoner. You have a... bye!
	stopConversation = "true",
	options = {}
}
fsVillageConvo5FemaleTemplate:addScreen(got_to_be_going);

not_much_here = ConvoScreen:new {
	id = "not_much_here",
	leftDialog = "@conversation/fs_village_convo5_f:s_ef3f73aa", -- I bet. not much here except for the prison and the nightsisters.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo5_f:s_409c13d6", "prison_near_here" }, -- What prison?
		{ "@conversation/fs_village_convo5_f:s_66242968", "witches_with_magic" }, -- Who are the nightsisters?
	}
}
fsVillageConvo5FemaleTemplate:addScreen(not_much_here);

prison_near_here = ConvoScreen:new {
	id = "prison_near_here",
	leftDialog = "@conversation/fs_village_convo5_f:s_38602b56", -- There is a prison Northwest of here. when I was real little they say a man came here from the prison. We helped him and now he is safe.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo5_f:s_126e325b", "too_little" }, -- How did they help him?
		{ "@conversation/fs_village_convo5_f:s_f04bc948", "i_didnt_help" }, -- You shouldn't help Imperial prisoners.
		{ "@conversation/fs_village_convo5_f:s_f6fc4ef7", "what" }, -- Any prison help is good help!
	}
}
fsVillageConvo5FemaleTemplate:addScreen(prison_near_here);

too_little = ConvoScreen:new {
	id = "too_little",
	leftDialog = "@conversation/fs_village_convo5_f:s_eca871b0", -- I don't know. I was too little and they took me away when he arrived. I never saw him again.
	stopConversation = "true",
	options = {}
}
fsVillageConvo5FemaleTemplate:addScreen(too_little);

i_didnt_help = ConvoScreen:new {
	id = "i_didnt_help",
	leftDialog = "@conversation/fs_village_convo5_f:s_6d6ef87a", -- I didn't help him. I was a little kid. He didn't look like he would hurt anyone though.
	stopConversation = "true",
	options = {}
}
fsVillageConvo5FemaleTemplate:addScreen(i_didnt_help);

what = ConvoScreen:new {
	id = "what",
	leftDialog = "@conversation/fs_village_convo5_f:s_900f01d1", -- What?
	stopConversation = "true",
	options = {}
}
fsVillageConvo5FemaleTemplate:addScreen(what);

witches_with_magic = ConvoScreen:new {
	id = "witches_with_magic",
	leftDialog = "@conversation/fs_village_convo5_f:s_97efc39d", -- They are witches that use evil magic. I hear the adults talking about them once in a while. They always say they are going to force us to do something, but I can never figure out what.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo5_f:s_98eb2667", "can_do_tricks" }, -- Force you to do something? What do you mean?
		{ "@conversation/fs_village_convo5_f:s_63df3a78", "cant_stop_them" }, -- Well, I wouldn't worry. If those witches come for you I will stop them.
	}
}
fsVillageConvo5FemaleTemplate:addScreen(witches_with_magic);

can_do_tricks = ConvoScreen:new {
	id = "can_do_tricks",
	leftDialog = "@conversation/fs_village_convo5_f:s_df5087e7", -- I don't know. I just keep hearing them say force this, and force that. I think the adults would stop them from forcing us to do anything though. Sometimes they can do tricks...
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo5_f:s_3b00b466", "have_to_go" }, -- They can do tricks? Like what kind of tricks.
	}
}
fsVillageConvo5FemaleTemplate:addScreen(can_do_tricks);

have_to_go = ConvoScreen:new {
	id = "have_to_go",
	leftDialog = "@conversation/fs_village_convo5_f:s_cb9faa", -- I have to go. They said I shouldn't talk about the good tricks.
	stopConversation = "true",
	options = {}
}
fsVillageConvo5FemaleTemplate:addScreen(have_to_go);

cant_stop_them = ConvoScreen:new {
	id = "cant_stop_them",
	leftDialog = "@conversation/fs_village_convo5_f:s_a78b5781", -- You can't stop them. Only the grown ups that know the good tricks can stop them. Uh oh. I have to go now. Bye!
	stopConversation = "true",
	options = {}
}
fsVillageConvo5FemaleTemplate:addScreen(cant_stop_them);

goodbye = ConvoScreen:new {
	id = "goodbye",
	leftDialog = "@conversation/fs_village_convo5_f:s_e6772f13", -- Goodbye.
	stopConversation = "true",
	options = {}
}
fsVillageConvo5FemaleTemplate:addScreen(goodbye);

addConversationTemplate("fsVillageConvo5FemaleTemplate", fsVillageConvo5FemaleTemplate);
