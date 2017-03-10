padawan_chef_01_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "padawan_chef_01_conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_chef_01:s_58e01006", -- He took it.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_chef_01:s_a7c3aea6", "latest_creation"}, -- Who took what?
		{"@conversation/padawan_chef_01:s_9bcbdc35", "uncalled_for"} -- Good for him.
	}
}
padawan_chef_01_convo_template:addScreen(intro);

uncalled_for = ConvoScreen:new {
	id = "uncalled_for",
	leftDialog = "@conversation/padawan_chef_01:s_56b146aa", -- Now, that was uncalled for.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_chef_01:s_78228c87", "latest_creation"}, -- You are right, I'm sorry.  Who took what?
		{"@conversation/padawan_chef_01:s_1ba9c89d", "just_cruel"} -- I don't care, I'm glad he took it.
	}
}
padawan_chef_01_convo_template:addScreen(uncalled_for);

just_cruel = ConvoScreen:new {
	id = "just_cruel",
	leftDialog = "@conversation/padawan_chef_01:s_8cddb8eb", -- Arrrgh. You... you're just cruel. Taking pleasure in another's misfortune.
	stopConversation = "true",
	options = {}
}
padawan_chef_01_convo_template:addScreen(just_cruel);

latest_creation = ConvoScreen:new {
	id = "latest_creation",
	leftDialog = "@conversation/padawan_chef_01:s_959fc17d", -- Some random thug came by here, and took my latest creation. It was a fantastic pie, and I won't be able to make another of its grandeur for quite some time. I put my heart and soul into that pie.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_chef_01:s_94e89675", "it_sure_is"}, -- That is one sad story.
	}
}
padawan_chef_01_convo_template:addScreen(latest_creation);

it_sure_is = ConvoScreen:new {
	id = "it_sure_is",
	leftDialog = "@conversation/padawan_chef_01:s_8a0862a1", -- It sure is. The pie is long gone, I can feel it in my blood. What I want is revenge. Revenge is the only thing that will taste as sweet as my precious lost pie. Are you willing to help?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_chef_01:s_d70dba34", "chased_thug"}, -- Yes.
		{"@conversation/padawan_chef_01:s_4c695dbd", "but_you_must"}, -- No.
	}
}
padawan_chef_01_convo_template:addScreen(it_sure_is);

chased_thug = ConvoScreen:new {
	id = "chased_thug",
	leftDialog = "@conversation/padawan_chef_01:s_b654720c", -- I chased the thug all the way to the edge of town. He ran off into the wilderness, and I quickly lost sight of him. But I managed to at least tag him with a small burst tracking device, so I know where you can find the bum.
	stopConversation = "true",
	options = {}
}
padawan_chef_01_convo_template:addScreen(chased_thug);

but_you_must = ConvoScreen:new {
	id = "but_you_must",
	leftDialog = "@conversation/padawan_chef_01:s_f68302e8", -- But you must... you have no choice, don't you see. Help me get my revenge. I need revenge! You must!! Arrrrrrgggh...
	stopConversation = "true",
	options = {}
}
padawan_chef_01_convo_template:addScreen(but_you_must);

intro_killed_target = ConvoScreen:new {
	id = "intro_killed_target",
	leftDialog = "@conversation/padawan_chef_01:s_be6b7d06", -- Problem solved? Did I get my revenge?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_chef_01:s_7c9388b6", "my_hero"}, -- Yes. He died screaming like a newborn bantha and begging for his life.
	}
}
padawan_chef_01_convo_template:addScreen(intro_killed_target);

my_hero = ConvoScreen:new {
	id = "my_hero",
	leftDialog = "@conversation/padawan_chef_01:s_edc10a84", -- My hero. Ah sweet and glorious day!
	stopConversation = "true",
	options = {}
}
padawan_chef_01_convo_template:addScreen(my_hero);

intro_spoke_to_target = ConvoScreen:new {
	id = "intro_spoke_to_target",
	leftDialog = "@conversation/padawan_chef_01:s_39d844c", -- So? Tell me what happened. Did he die painfully?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_chef_01:s_53e26aec", "want_my_revenge"}, -- No. I didn't hurt him. I'll not exact your petty revenge.
	}
}
padawan_chef_01_convo_template:addScreen(intro_spoke_to_target);

want_my_revenge = ConvoScreen:new {
	id = "want_my_revenge",
	leftDialog = "@conversation/padawan_chef_01:s_9bf6042f", -- But?!! No!!!! I want my revenge! I must have it! My precious vengeance! Who are you to stand in my way. Well, drat.
	stopConversation = "true",
	options = {}
}
padawan_chef_01_convo_template:addScreen(want_my_revenge);

intro_has_quest = ConvoScreen:new {
	id = "intro_has_quest",
	leftDialog = "@conversation/padawan_chef_01:s_39d844c", -- Is it over? Has that thug paid the price I asked?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_chef_01:s_bc5c7c4a", "dont_waste_time"}, -- Not just yet. I'm still working on it.
		{"@conversation/padawan_chef_01:s_3f4dfda1", "my_sweet_revenge"} -- No but I'm done. I'm not going to help you seek revenge.
	}
}
padawan_chef_01_convo_template:addScreen(intro_has_quest);

my_sweet_revenge = ConvoScreen:new {
	id = "my_sweet_revenge",
	leftDialog = "@conversation/padawan_chef_01:s_7c44e561", -- What?? I can't... ah no,  my sweet revenge!??!
	stopConversation = "true",
	options = {}
}
padawan_chef_01_convo_template:addScreen(my_sweet_revenge);

dont_waste_time = ConvoScreen:new {
	id = "dont_waste_time",
	leftDialog = "@conversation/padawan_chef_01:s_d5ab69d1", -- Okay. Don't waste too much time I don't know how long until he discovers that tracking device.
	stopConversation = "true",
	options = {}
}
padawan_chef_01_convo_template:addScreen(dont_waste_time);

not_quest_owner = ConvoScreen:new {
	id = "not_quest_owner",
	leftDialog = "@conversation/padawan_chef_01:s_32e459b5", -- It's gone... all gone.
	stopConversation = "true",
	options = {}
}
padawan_chef_01_convo_template:addScreen(not_quest_owner);

addConversationTemplate("padawan_chef_01_convo_template", padawan_chef_01_convo_template);
