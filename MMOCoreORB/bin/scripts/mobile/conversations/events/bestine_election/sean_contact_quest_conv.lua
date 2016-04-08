seanContactConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "sean_contact_conv_handler",
	screens = {}
}

sean_notinOffice = ConvoScreen:new {
	id = "sean_notinOffice",
	leftDialog = "@conversation/sean_contact:s_f1baf7f", --Elections, Sand People raids, museums! So many new things are happening in Bestine. Listen to the townsfolk. They may have interesting things to say.
	stopConversation = "true",
	options = { }
}
seanContactConvoTemplate:addScreen(sean_notinOffice);


sean_inOffice_noItem = ConvoScreen:new {
	id = "sean_inOffice_noItem",
	leftDialog = "@conversation/sean_contact:s_c17cd032", --I'm waiting for someone else. I've heard, however, that Sean Trenwell is in need of assistance at the capitol.
	stopConversation = "true",
	options = { }
}
seanContactConvoTemplate:addScreen(sean_inOffice_noItem);

sean_inOffice_hasItem = ConvoScreen:new {
	id = "sean_inOffice_hasItem",
	leftDialog = "@conversation/sean_contact:s_1e325cde", --So he's got himself into more trouble I see. I just heard the news. Let me have that disk. He'll be grateful to you.
	stopConversation = "false",
	options = {
		{"@conversation/sean_contact:s_829888a9","seanContact_itemDestroyed"}, -- Here you go.
	}
}
seanContactConvoTemplate:addScreen(sean_inOffice_hasItem);

seanContact_itemDestroyed = ConvoScreen:new {
	id = "seanContact_itemDestroyed",
	leftDialog = "@conversation/sean_contact:s_3e134731", -- It's finished. Go tell him the good news. He and his career are safe.
	stopConversation = "true",
	options = { }
}
seanContactConvoTemplate:addScreen(seanContact_itemDestroyed);

addConversationTemplate("seanContactConvoTemplate", seanContactConvoTemplate);
