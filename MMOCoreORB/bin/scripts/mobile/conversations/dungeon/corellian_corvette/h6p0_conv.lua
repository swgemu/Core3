corvetteRepairDroidConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "corvetteRepairDroidConvoHandler",
	screens = {}
}

pdroid_instructions = ConvoScreen:new {
	id = "pdroid_instructions",
	leftDialog = "@dungeon/corvette:pdroid_instructions",
	-- I'm afraid my counterpart here is missing his maintenance module.  If you could retrieve it he could make his way across the room and shut off the power surge.
	stopConversation = "true",
	options = {}
}
corvetteRepairDroidConvoTemplate:addScreen(pdroid_instructions);


pdroid_congrats = ConvoScreen:new {
	id = "pdroid_congrats",
	leftDialog = "@dungeon/corvette:pdroid_congrats", --Oh he did it!  Good work!
	stopConversation = "true",
	options = {}
}
corvetteRepairDroidConvoTemplate:addScreen(pdroid_congrats);

pdroid_excellent = ConvoScreen:new {
	id = "pdroid_excellent",
	leftDialog = "@dungeon/corvette:pdroid_excellent", --I can't tell you how happy we were to have served you.
	stopConversation = "true",
	options = {}
}
corvetteRepairDroidConvoTemplate:addScreen(pdroid_excellent);


addConversationTemplate("corvetteRepairDroidConvoTemplate", corvetteRepairDroidConvoTemplate);
