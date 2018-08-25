seanContactConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "seanContactConvoHandler",
	screens = {}
}

init_sean_in_office_no_item = ConvoScreen:new {
	id = "init_sean_in_office_no_item",
	leftDialog = "@conversation/sean_contact:s_c17cd032", -- I'm waiting for someone else. I've heard, however, that Sean Trenwell is in need of assistance at the capitol.
	stopConversation = "true",
	options = {}
}
seanContactConvoTemplate:addScreen(init_sean_in_office_no_item);

init_sean_not_in_office = ConvoScreen:new {
	id = "init_sean_not_in_office",
	leftDialog = "@conversation/sean_contact:s_f1baf7f", -- Elections, Sand People raids, museums! So many new things are happening in Bestine. Listen to the townsfolk. They may have interesting things to say.
	stopConversation = "true",
	options = {}
}
seanContactConvoTemplate:addScreen(init_sean_not_in_office);

init_sean_in_office_has_item = ConvoScreen:new {
	id = "init_sean_in_office_has_item",
	leftDialog = "@conversation/sean_contact:s_1e325cde", -- So he's got himself into more trouble I see. I just heard the news. Let me have that disk. He'll be grateful to you.
	stopConversation = "false",
	options = {
		{"@conversation/sean_contact:s_829888a9", "its_finished"}, -- Here you go.
	}
}
seanContactConvoTemplate:addScreen(init_sean_in_office_has_item);

its_finished = ConvoScreen:new {
	id = "its_finished",
	leftDialog = "@conversation/sean_contact:s_3e134731", -- It's finished. Go tell him the good news. He and his career are safe.
	stopConversation = "true",
	options = {}
}
seanContactConvoTemplate:addScreen(its_finished);

addConversationTemplate("seanContactConvoTemplate", seanContactConvoTemplate);
