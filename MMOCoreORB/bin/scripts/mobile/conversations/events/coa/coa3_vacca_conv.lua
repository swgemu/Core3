coa3VaccaConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "coa3VaccaConvoHandler",
	screens = {}
}

init_default = ConvoScreen:new {
	id = "init_default",
	leftDialog = "@conversation/coa3wvacca:s_8e697de4", -- Oh. Hello. I'm sorry, but they really don't want me to talk to anyone not associated with the project. You understand.
	stopConversation = "true",
	options = {}
}
coa3VaccaConvoTemplate:addScreen(init_default);

init_has_mission = ConvoScreen:new {
	id = "init_has_mission",
	leftDialog = "@conversation/coa3wvacca:s_be18866d", -- Ah, you're the one who is helping us fight the Empire for Dead Eye.
	stopConversation = "false",
	options = {
		{"@conversation/coa3wvacca:s_11d4164", "stores_of_flora"}, -- What's the status of Dead Eye?
		{"@conversation/coa3wvacca:s_bbc96393", "blinded_myself"}, -- Why did you choose the Rebellion?
	}
}
coa3VaccaConvoTemplate:addScreen(init_has_mission);

init_has_coa2 = ConvoScreen:new {
	id = "init_has_coa2",
	leftDialog = "@conversation/coa3wvacca:s_913b747e", -- You're the one who sent me the message from the Princess. I really have to thank you. I was deluding myself for far too long about the Empire. I'm glad I was able to give Dead Eye to the Rebellion .
	stopConversation = "false",
	options = {
		{"@conversation/coa3wvacca:s_11d4164", "stores_of_flora"}, -- What's the status of Dead Eye?
		{"@conversation/coa3wvacca:s_bbc96393", "blinded_myself"}, -- Why did you choose the Rebellion?
	}
}
coa3VaccaConvoTemplate:addScreen(init_has_coa2);

stores_of_flora = ConvoScreen:new {
	id = "stores_of_flora",
	leftDialog = "@conversation/coa3wvacca:s_11b13f7a", -- Right now we have some stores of Alderaanian Flora, but my home planet was the last place it grew. Once it runs out Dead Eye will be useless.
	stopConversation = "false",
	options = {
		{"@conversation/coa3wvacca:s_b2b7f750", "find_alternative"}, -- What can be done?
	}
}
coa3VaccaConvoTemplate:addScreen(stores_of_flora);

find_alternative = ConvoScreen:new {
	id = "find_alternative",
	leftDialog = "@conversation/coa3wvacca:s_d24fb27", -- If we can find an alternative flora resource, we can try to make another version. We have a number of research stations scattered about a number of planets testing various samples.
	stopConversation = "true",
	options = {}
}
coa3VaccaConvoTemplate:addScreen(find_alternative);

blinded_myself = ConvoScreen:new {
	id = "blinded_myself",
	leftDialog = "@conversation/coa3wvacca:s_ba517076", -- After reading the message from Princess Leia I realized that I had blinded myself to the evils of the Empire. After further communications I had my eyes opened to the real reason Alderaan was destroyed.
	stopConversation = "false",
	options = {
		{"@conversation/coa3wvacca:s_96405da8", "killed_planet"}, -- What was the reason?
	}
}
coa3VaccaConvoTemplate:addScreen(blinded_myself);

killed_planet = ConvoScreen:new {
	id = "killed_planet",
	leftDialog = "@conversation/coa3wvacca:s_6d583b5", -- It wasn't because of Rebel activity. It was a whim. A cold, heartless, whim of Grand Moff Tarkin. He wanted a demonstration of the Empire's power, so he killed an entire planet. I now know the truth, so I couldn't work for them anymore.
	stopConversation = "true",
	options = {}
}
coa3VaccaConvoTemplate:addScreen(killed_planet);

addConversationTemplate("coa3VaccaConvoTemplate", coa3VaccaConvoTemplate);
