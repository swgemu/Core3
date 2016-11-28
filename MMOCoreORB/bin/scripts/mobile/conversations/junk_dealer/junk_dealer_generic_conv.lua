junkDealerGenericConvoTemplate = ConvoTemplate:new {
	initialScreen = "ask_for_loot",
	templateType = "Lua",
	luaClassHandler = "JunkDealerGenericConvoHandler",
	screens = {}
}

ask_for_loot = ConvoScreen:new {
	id = "ask_for_loot",
	leftDialog = "@conversation/junk_dealer_generic:s_bef51e38", -- Welcome traveler. I am a buyer of goods that most would deem as junk. If you are interested I will look through what you have to offer and set a price for anything that I wish to buy. I also have come across some other items of interest that I am looking to get rid of.
	stopConversation = "false",
	options = {
		--{"@conversation/junk_dealer_generic:s_54fab04f", "start_sale"}, -- I have some things that you might be interested in.
		--{"@conversation/junk_dealer_generic:s_cd7a3f41", "no_loot"}, -- I am sorry but I don't think I have anything you would want.
		--{"@conversation/junk_dealer_generic:s_3aa18b2d", "inventor"}, -- What sort of items do you have that you are looking to get rid of?
	}
}
junkDealerGenericConvoTemplate:addScreen(ask_for_loot);

start_sale = ConvoScreen:new {
	id = "start_sale",
	leftDialog = "@conversation/junk_dealer_generic:s_84a67771", -- Alright, let me see what you are offering.
	stopConversation = "true",
	options = {}
}
junkDealerGenericConvoTemplate:addScreen(start_sale);

no_loot = ConvoScreen:new {
	id = "no_loot",
	leftDialog = "@conversation/junk_dealer_generic:s_4bd9d15e", -- That is to bad. Remember to come visit me in the future if you happen to come across anything I would be interested in.
	stopConversation = "true",
	options = {}
}
junkDealerGenericConvoTemplate:addScreen(no_loot);

inventor = ConvoScreen:new {
	id = "inventor",
	leftDialog = "@conversation/junk_dealer_generic:s_d9e6b751", -- An inventor recently sold me and my fellow junk dealers a large quantity of these special kits that were supposed to revolutionize crafting. Unfortunately, they are useless without the special components that they are designed to use.
	stopConversation = "false",
	options = {
		{"@conversation/junk_dealer_generic:s_6d53d062", "shipment"}, -- Why don't you just get some of the special components?
	}
}
junkDealerGenericConvoTemplate:addScreen(inventor);

shipment = ConvoScreen:new {
	id = "shipment",
	leftDialog = "@conversation/junk_dealer_generic:s_e29f48dc", -- Apparently this inventor had them all on a shipment that was coming in from the core worlds. As luck would have it the shipment was hijacked en route and all the components were lost to pirates. This caused the inventor to go out of business, leaving all of us stuck with these useless kits.
	stopConversation = "false",
	options = {
		{"@conversation/junk_dealer_generic:s_324b9b0f", "adventerous"}, -- What good would a useless kit do me?
	}
}
junkDealerGenericConvoTemplate:addScreen(shipment);

adventerous = ConvoScreen:new {
	id = "adventerous",
	leftDialog = "@conversation/junk_dealer_generic:s_12fe83a6", -- You seem to be the adventurous sort so I figured that you might be able to find the parts. I mean they had to go somewhere, although my guess is that they are probably all over the galaxy by now.
	stopConversation = "false",
	options = {
		{"@conversation/junk_dealer_generic:s_e1a103e5", "want_them_gone"}, -- Hmmmm, well how much do you want for these kits?
	}
}
junkDealerGenericConvoTemplate:addScreen(adventerous);

want_them_gone = ConvoScreen:new {
	id = "want_them_gone",
	leftDialog = "@conversation/junk_dealer_generic:s_4d65752", -- I just want them gone. They are taking up valuable space in my inventory so I will just give you one of each type if you want.
	stopConversation = "false",
	options = {
		{"@conversation/junk_dealer_generic:s_d347bee3", "kit_types"}, -- Ok sounds good. What sort of kits do you have?
		{"@conversation/junk_dealer_generic:s_b60b73f8", "not_taking_one"}, -- No thanks, I don't think that I need any of those kits.
	}
}
junkDealerGenericConvoTemplate:addScreen(want_them_gone);

not_taking_one = ConvoScreen:new {
	id = "not_taking_one",
	leftDialog = "@conversation/junk_dealer_generic:s_3633b5a5", -- Can't say that I blame you for not taking one. It's sad that I can't even give them away. If I ever see that inventor again I am going to make him really sorry.
	stopConversation = "true",
	options = {}
}
junkDealerGenericConvoTemplate:addScreen(not_taking_one);

kit_types = ConvoScreen:new {
	id = "kit_types",
	leftDialog = "@conversation/junk_dealer_generic:s_3fc7eb45", -- Well let's see here. I have one that makes an orange rug, one that makes a blue rug, one that can make a Nabooian sculpture, one that makes a table, and one that make some sort of model gong. I will only give you one kit at a time so if you want another you are going to have to get rid of the one you currently have first.
	stopConversation = "false",
	options = {
		{"@conversation/junk_dealer_generic:s_ee977dee", "give_orange"}, -- Let me have one of those orange rug kits.
		{"@conversation/junk_dealer_generic:s_8f39769", "give_blue"}, -- I will take one of the blue rug kits.
		{"@conversation/junk_dealer_generic:s_fe657cdd", "give_gong"}, -- I think I would like one of those model gong kits.
		{"@conversation/junk_dealer_generic:s_9ede4b84", "give_table"}, -- Let me have one that makes the table.
		{"@conversation/junk_dealer_generic:s_87c5851b", "give_sculpture"}, -- I think I will try out the one that makes the sculpture.
	}
}
junkDealerGenericConvoTemplate:addScreen(kit_types);

give_orange = ConvoScreen:new {
	id = "give_orange",
	leftDialog = "@conversation/junk_dealer_generic:s_14efaaa2", -- Ok, here you go. I guess in order to make it work you need to add ten special components to the kit. When you examine a kit, it has a list of what you need in order to complete the kit. It also has a read-out of whether it currently has a component or not. Oh, and if you do happen to make anything useful with that kit, I might be interested in buying that from you.
	stopConversation = "true",
	options = {}
}
junkDealerGenericConvoTemplate:addScreen(give_orange);

give_blue = ConvoScreen:new {
	id = "give_blue",
	leftDialog = "@conversation/junk_dealer_generic:s_14efaaa2", -- Ok, here you go. I guess in order to make it work you need to add ten special components to the kit. When you examine a kit, it has a list of what you need in order to complete the kit. It also has a read-out of whether it currently has a component or not. Oh, and if you do happen to make anything useful with that kit, I might be interested in buying that from you.
	stopConversation = "true",
	options = {}
}
junkDealerGenericConvoTemplate:addScreen(give_blue);

give_gong = ConvoScreen:new {
	id = "give_gong",
	leftDialog = "@conversation/junk_dealer_generic:s_14efaaa2", -- Ok, here you go. I guess in order to make it work you need to add ten special components to the kit. When you examine a kit, it has a list of what you need in order to complete the kit. It also has a read-out of whether it currently has a component or not. Oh, and if you do happen to make anything useful with that kit, I might be interested in buying that from you.
	stopConversation = "true",
	options = {}
}
junkDealerGenericConvoTemplate:addScreen(give_gong);

give_table = ConvoScreen:new {
	id = "give_table",
	leftDialog = "@conversation/junk_dealer_generic:s_14efaaa2", -- Ok, here you go. I guess in order to make it work you need to add ten special components to the kit. When you examine a kit, it has a list of what you need in order to complete the kit. It also has a read-out of whether it currently has a component or not. Oh, and if you do happen to make anything useful with that kit, I might be interested in buying that from you.
	stopConversation = "true",
	options = {}
}
junkDealerGenericConvoTemplate:addScreen(give_table);

give_sculpture = ConvoScreen:new {
	id = "give_sculpture",
	leftDialog = "@conversation/junk_dealer_generic:s_14efaaa2", -- Ok, here you go. I guess in order to make it work you need to add ten special components to the kit. When you examine a kit, it has a list of what you need in order to complete the kit. It also has a read-out of whether it currently has a component or not. Oh, and if you do happen to make anything useful with that kit, I might be interested in buying that from you.
	stopConversation = "true",
	options = {}
}
junkDealerGenericConvoTemplate:addScreen(give_sculpture);

addConversationTemplate("junkDealerGenericConvoTemplate", junkDealerGenericConvoTemplate);
