villageGadgetSpecialistPhase4ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "villageGadgetSpecialistPhase4ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/fs_gadget_specialist:s_5a562246", -- "I've much to do... can I help you?"
	stopConversation = "false",
	options = {
	--Option depends on quest step
	--{"@conversation/fs_gadget_specialist:s_79fe19ed", "who_gave_idea"}, -- "Yes, I was told you could help me obtain a replacement computer core."
	--{"@conversation/fs_gadget_specialist:s_c7baf80c", "collect_all_components"}, -- "What do I do with this tracking device kit?"
	--{"@conversation/fs_gadget_specialist:s_bab2829b", "any_ticket_droid"}, -- "How do I get tracking data for a fallen satellite?"
	--{"@conversation/fs_gadget_specialist:s_7f396fce", "simply_use_device"}, -- "How do I use this tracking device?"
	--{"@conversation/fs_gadget_specialist:s_b867b2e4", "ask_chief_engineer"}, -- "How do I make this computer core work with the village computer?"
	--{"@conversation/fs_gadget_specialist:s_fe739220", "bask_in_glory"}, -- "The computer core is ready... now what?"
	--{"@conversation/fs_gadget_specialist:s_5542b04b", "quite_alright"}, -- "Oh, my apologies. I'll let you get back to work."
	}
}
villageGadgetSpecialistPhase4ConvoTemplate:addScreen(intro);

quite_alright = ConvoScreen:new {
	id = "quite_alright",
	leftDialog = "@conversation/fs_gadget_specialist:s_1283cb1c", -- "That's quite alright. Good day to you."
	stopConversation = "true",
	options = {}
}
villageGadgetSpecialistPhase4ConvoTemplate:addScreen(quite_alright);

who_gave_idea = ConvoScreen:new {
	id = "who_gave_idea",
	leftDialog = "@conversation/fs_gadget_specialist:s_b49f7181", -- "A replacement computer core? Who gave you that idea?"
	stopConversation = "false",
	options = {
		{"@conversation/fs_gadget_specialist:s_85bd3ae2", "i_know_place"}, -- "The chief engineer from a village on Dathomir. The village of Aurilia."
		{"@conversation/fs_gadget_specialist:s_55082d0b", "good_day_then"}, -- "Er... no one. I'm sorry to have bothered you."
	}
}
villageGadgetSpecialistPhase4ConvoTemplate:addScreen(who_gave_idea);

good_day_then = ConvoScreen:new {
	id = "good_day_then",
	leftDialog = "@conversation/fs_gadget_specialist:s_3d8991fc", -- "I... um... see. Well. Good day then."
	stopConversation = "true",
	options = {}
}
villageGadgetSpecialistPhase4ConvoTemplate:addScreen(good_day_then);

i_know_place = ConvoScreen:new {
	id = "i_know_place",
	leftDialog = "@conversation/fs_gadget_specialist:s_4389624e", -- "Aurilia on Dathomir... yeah, I know the place. Well, know of it anyway. I've done business with them in the past. They need a replacement computer core?"
	stopConversation = "false",
	options = {
		{"@conversation/fs_gadget_specialist:s_a1dd9b9e", "wish_i_could_help"}, -- "That's correct. Their current one was damaged during an attack on the village."
	}
}
villageGadgetSpecialistPhase4ConvoTemplate:addScreen(i_know_place);

wish_i_could_help = ConvoScreen:new {
	id = "wish_i_could_help",
	leftDialog = "@conversation/fs_gadget_specialist:s_be68030a", -- "Well, I wish I could help, but I don't have anything like that in stock. Rarely do to be honest. I tend to tinker more with smaller devices. Large systems like a town... or village... computer require far more attention than I'm willing to give."
	stopConversation = "false",
	options = {
		{"@conversation/fs_gadget_specialist:s_be1b8c5a", "think_a_minute"}, -- "Is there nothing that can be done to find a replacement for Aurilia?"
		{"@conversation/fs_gadget_specialist:s_4d7434d2", "not_much_i_can_do"}, -- "That's disappointing. But I guess if you don't have one, then you don't have one."
	}
}
villageGadgetSpecialistPhase4ConvoTemplate:addScreen(wish_i_could_help);

not_much_i_can_do = ConvoScreen:new {
	id = "not_much_i_can_do",
	leftDialog = "@conversation/fs_gadget_specialist:s_533919fc", -- "Tell the Aurilia engineer that I wish I could have been more helpful, but not much I can really do about something like that."
	stopConversation = "true",
	options = {}
}
villageGadgetSpecialistPhase4ConvoTemplate:addScreen(not_much_i_can_do);

think_a_minute = ConvoScreen:new {
	id = "think_a_minute",
	leftDialog = "@conversation/fs_gadget_specialist:s_e5c058a8", -- "Hmm... let me think a minute. You know, there might just be something I can help you with after all. Most satellites have a central computer that is heavily shielded to withstand the extreme nature of their orbit. Once a satellite falls from orbit and is abandoned, anyone can purchase the rights to them. I've done so myself on various occassions."
	stopConversation = "false",
	options = {
		{"@conversation/fs_gadget_specialist:s_fff0f4f2", "nothings_easier"}, -- "How do I purchase the rights to a fallen and abandoned satellite?"
		{"@conversation/fs_gadget_specialist:s_46bdeee4", "be_on_your_way"}, -- "Sounds like a terrible idea. Thanks for nothing."
	}
}
villageGadgetSpecialistPhase4ConvoTemplate:addScreen(think_a_minute);

nothings_easier = ConvoScreen:new {
	id = "nothings_easier",
	leftDialog = "@conversation/fs_gadget_specialist:s_e79d337", -- "Nothing's easier. you simply go to any starport and speak with the ticket droid. These droids have access to a galactic-wide database that maintains records about satellites in orbit around most known planets. For a fee, you can purchase the rights to one that has fallen and gone unclaimed."
	stopConversation = "false",
	options = {
		{"@conversation/fs_gadget_specialist:s_b9f237f", "one_other_thing"}, -- "Sounds reasonable. I'm off to the starport."
		{"@conversation/fs_gadget_specialist:s_46bdeee4", "be_on_your_way"}, -- "Sounds like a terrible idea. Thanks for nothing."
	}
}
villageGadgetSpecialistPhase4ConvoTemplate:addScreen(nothings_easier);

be_on_your_way = ConvoScreen:new {
	id = "be_on_your_way",
	leftDialog = "@conversation/fs_gadget_specialist:s_9d19b512", -- "Ha. Whatever. Be on your way, then."
	stopConversation = "true",
	options = {}
}
villageGadgetSpecialistPhase4ConvoTemplate:addScreen(be_on_your_way);

one_other_thing = ConvoScreen:new {
	id = "one_other_thing",
	leftDialog = "@conversation/fs_gadget_specialist:s_bdedc5e2", -- "Wait! Before speaking with the droid, there's one other thing. You'll need a downed satellite tracking device. When you purchase the rights to one, the droid will upload tracking data to your tracking device. It will then help you to locate the fallen satellite. I can provide you with a kit for just such a device for a small fee. Say, 530 credits?"
	stopConversation = "false",
	options = {
		--{"@conversation/fs_gadget_specialist:s_a8749106", "place_in_inventory"}, -- "Sounds fair enough. I'll take one."
		--{"@conversation/fs_gadget_specialist:s_a8749106", "not_enough_funds"}, -- "Sounds fair enough. I'll take one."
		--{"@conversation/fs_gadget_specialist:s_a8749106", "not_enough_space"}, -- "Sounds fair enough. I'll take one."
		--{"@conversation/fs_gadget_specialist:s_8fe6a678", "offering_to_help"}, -- "You must think I just fell off of a bantha! I'll not be scammed so easily."
	}
}
villageGadgetSpecialistPhase4ConvoTemplate:addScreen(one_other_thing);

place_in_inventory = ConvoScreen:new {
	id = "place_in_inventory",
	leftDialog = "@conversation/fs_gadget_specialist:s_bdcd33ef", -- "Excellent. I'll just place it in your inventory. Good luck finding a satellite and that replacement computer core."
	stopConversation = "true",
	options = {}
}
villageGadgetSpecialistPhase4ConvoTemplate:addScreen(place_in_inventory);

offering_to_help = ConvoScreen:new {
	id = "offering_to_help",
	leftDialog = "@conversation/fs_gadget_specialist:s_6d9d310", -- "Ha. I was just offering to help. You can't expect me to ignore my livelihood and give this kind of thing away for nothing. My price is more than fair. But whatever. Good day."
	stopConversation = "true",
	options = {}
}
villageGadgetSpecialistPhase4ConvoTemplate:addScreen(offering_to_help);

not_enough_funds = ConvoScreen:new {
	id = "not_enough_funds",
	leftDialog = "@conversation/fs_gadget_specialist:s_b518079a", -- "You don't seem to have enough funds at the moment. I'd love to help, but I can't give the kit away for nothing. Come back when you have more funds."
	stopConversation = "true",
	options = {}
}
villageGadgetSpecialistPhase4ConvoTemplate:addScreen(not_enough_funds);

not_enough_space = ConvoScreen:new {
	id = "not_enough_space",
	leftDialog = "@conversation/fs_gadget_specialist:s_faaeb65f", -- "You don't have enough space in your inventory for the kit. Make some room and then come speak with me again."
	stopConversation = "true",
	options = {}
}
villageGadgetSpecialistPhase4ConvoTemplate:addScreen(not_enough_space);

return_to_buy = ConvoScreen:new {
	id = "return_to_buy",
	leftDialog = "@conversation/fs_gadget_specialist:s_7045a2d7", -- "Welcome back. Still interested in a downed satellite tracking device? The price is 530 credits."
	stopConversation = "false",
	options = {
		--{"@conversation/fs_gadget_specialist:s_a8749106", "place_in_inventory"}, -- "Sounds fair enough. I'll take one."
		--{"@conversation/fs_gadget_specialist:s_a8749106", "not_enough_funds"}, -- "Sounds fair enough. I'll take one."
		--{"@conversation/fs_gadget_specialist:s_a8749106", "not_enough_space"}, -- "Sounds fair enough. I'll take one."
		--{"@conversation/fs_gadget_specialist:s_8fe6a678", "offering_to_help"}, -- "You must think I just fell off of a bantha! I'll not be scammed so easily."
	}
}
villageGadgetSpecialistPhase4ConvoTemplate:addScreen(return_to_buy);

collect_all_components = ConvoScreen:new {
	id = "collect_all_components",
	leftDialog = "@conversation/fs_gadget_specialist:s_4bcdc402", -- "You need to collect or craft all of the required components and place them in the kit. Once you have all of the components, the kit's automated system will build the tracking device."
	stopConversation = "true",
	options = {}
}
villageGadgetSpecialistPhase4ConvoTemplate:addScreen(collect_all_components);

any_ticket_droid = ConvoScreen:new {
	id = "any_ticket_droid",
	leftDialog = "@conversation/fs_gadget_specialist:s_65f76975", -- "Go to any ticket droid at a starport. They have access to the database with information about fallen and abandoned satellites around the galaxy. You can purchase the rights to one of them from the droid."
	stopConversation = "true",
	options = {}
}
villageGadgetSpecialistPhase4ConvoTemplate:addScreen(any_ticket_droid);

simply_use_device = ConvoScreen:new {
	id = "simply_use_device",
	leftDialog = "@conversation/fs_gadget_specialist:s_f9732f00", -- "Simply use the device's menu and choose to activate the tracking device. If you're on the wrong planet, it will tell you which planet the satellite is on. Once you're on the correct planet, the device can then pinpoint the exact location of the satellite."
	stopConversation = "true",
	options = {}
}
villageGadgetSpecialistPhase4ConvoTemplate:addScreen(simply_use_device);

ask_chief_engineer = ConvoScreen:new {
	id = "ask_chief_engineer",
	leftDialog = "@conversation/fs_gadget_specialist:s_70253663", -- "The chief engineer at Aurilia can probably give you more information, but I believe you'll have to modify the core's current interface so that it will be compatible with the village's computer. Usually there's a simple menu on the core itself that will allow you to try and modify it."
	stopConversation = "true",
	options = {}
}
villageGadgetSpecialistPhase4ConvoTemplate:addScreen(ask_chief_engineer);

bask_in_glory = ConvoScreen:new {
	id = "bask_in_glory",
	leftDialog = "@conversation/fs_gadget_specialist:s_d8a8c77e", -- "Now you can bring it to Aurilia's chief engineer and then bask in the glory of a job well done."
	stopConversation = "true",
	options = {}
}
villageGadgetSpecialistPhase4ConvoTemplate:addScreen(bask_in_glory);

addConversationTemplate("villageGadgetSpecialistPhase4ConvoTemplate", villageGadgetSpecialistPhase4ConvoTemplate);
