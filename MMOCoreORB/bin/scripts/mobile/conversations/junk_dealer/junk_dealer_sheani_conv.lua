junkDealerSheaniConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "JunkDealerSheaniConvoHandler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/junk_sheani_lake:s_d3c4bb84", -- Welcome traveler, I am Sheani, buyer and seller of finery from around the galaxy. Maybe you have heard of me? No...no matter. How may I be of service to you today?
	stopConversation = "false",
	options = {
		{"@conversation/junk_sheani_lake:s_45632ab8", "ask_for_loot"}, -- I think the question is how can I be of service to you?
		{"@conversation/junk_sheani_lake:s_f6c161d", "safe_travels"}, -- Nothing right now. I am just passing through.
	}
}
junkDealerSheaniConvoTemplate:addScreen(init);

safe_travels = ConvoScreen:new {
	id = "safe_travels",
	leftDialog = "@conversation/junk_sheani_lake:s_57feadd0", -- In that case safe travels to you. If you ever find yourself in possession of anything I might be interested in please contact me again.
	stopConversation = "true",
	options = {}
}
junkDealerSheaniConvoTemplate:addScreen(safe_travels);

ask_for_loot = ConvoScreen:new {
	id = "ask_for_loot",
	leftDialog = "@conversation/junk_sheani_lake:s_38c64dea", -- Oh how nice, you must be a seller. I am always in the market for used clothing, the occasional trinket, and any sort of jewelry. If you are interested I can offer you very fair pricing for anything you are looking to sell.
	stopConversation = "false",
	options = {
		--{"@conversation/junk_sheani_lake:s_370197a6", "start_sale"}, -- You know what? I think that I have just what you are looking for.
		--{"@conversation/junk_sheani_lake:s_d264cf44", "no_loot"}, -- I am afraid that I don't have anything you would like.
	}
}
junkDealerSheaniConvoTemplate:addScreen(ask_for_loot);

no_loot = ConvoScreen:new {
	id = "no_loot",
	leftDialog = "@conversation/junk_sheani_lake:s_d4565283", -- That is too bad. But if come across anything please stop by and let me have the first crack at buying them from you.
	stopConversation = "true",
	options = {}
}
junkDealerSheaniConvoTemplate:addScreen(no_loot);

start_sale = ConvoScreen:new {
	id = "start_sale",
	leftDialog = "@conversation/junk_sheani_lake:s_82f469f5", -- How wonderful! Let me take a look and I will make you the best offer that I can for anything that I might be interested in. You do seem to have a few nice pieces in here.
	stopConversation = "true",
	options = {}
}
junkDealerSheaniConvoTemplate:addScreen(start_sale);

addConversationTemplate("junkDealerSheaniConvoTemplate", junkDealerSheaniConvoTemplate);
