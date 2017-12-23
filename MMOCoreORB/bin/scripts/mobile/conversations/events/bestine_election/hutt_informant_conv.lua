huttInformantConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "huttInformantConvoHandler",
	screens = {}
}

init_default = ConvoScreen:new {
	id = "init_default",
	leftDialog = "@conversation/hutt_informant:s_7b45b993", -- Get lost. I have no business to conduct with you. Too many people in arms about the Sand People attacking Bestine. It'll be easy for me, I can just leave just as easily as I've come. Go away. I have things to do, people to bribe.
	stopConversation = "true",
	options = {}
}
huttInformantConvoTemplate:addScreen(init_default);

init_sean_in_office_has_item = ConvoScreen:new {
	id = "init_sean_in_office_has_item",
	leftDialog = "@conversation/hutt_informant:s_fb7697b2", -- I can take care of this... mess for you.
	stopConversation = "false",
	options = {
		{"@conversation/hutt_informant:s_f660c800", "do_dirty_work"}, -- What mess?
	}
}
huttInformantConvoTemplate:addScreen(init_sean_in_office_has_item);

do_dirty_work = ConvoScreen:new {
	id = "do_dirty_work",
	leftDialog = "@conversation/hutt_informant:s_dfffcfb", -- Why do the dirty work of a politician when I can do it for you? Let me take that disk off your hands. In fact, I know I may have something with which I can pay you for your... generosity.
	stopConversation = "false",
	options = {
		{"@conversation/hutt_informant:s_139f41b9", "why_wouldnt_i"}, -- Why do you want the disk?
		{"@conversation/hutt_informant:s_54b54bd0", "dont_blame_me"}, -- Here take it. Give me my payment.
		{"@conversation/hutt_informant:s_4ddc07ed", "out_of_my_sight"}, -- I won't give it to you.
	}
}
huttInformantConvoTemplate:addScreen(do_dirty_work);

why_wouldnt_i = ConvoScreen:new {
	id = "why_wouldnt_i",
	leftDialog = "@conversation/hutt_informant:s_70142360", -- Why wouldn't I? It contains pertinent information regarding a highly-regarded politician and I'm one of Jabba's informants. Again, I ask... why wouldn't I want it?
	stopConversation = "false",
	options = {
		{"@conversation/hutt_informant:s_54b54bd0", "dont_blame_me"}, -- Here take it. Give me my payment.
		{"@conversation/hutt_informant:s_4ddc07ed", "out_of_my_sight"}, -- I won't give it to you.
	}
}
huttInformantConvoTemplate:addScreen(why_wouldnt_i);

dont_blame_me = ConvoScreen:new {
	id = "dont_blame_me",
	leftDialog = "@conversation/hutt_informant:s_53f349b7", -- Oh and don't blame me if you can't use this thing. It was all I had on me. Go sell it or something. You didn't deserve that great of a reward. It's been a pleasure doing business with you. Good day.
	stopConversation = "true",
	options = {}
}
huttInformantConvoTemplate:addScreen(dont_blame_me);

out_of_my_sight = ConvoScreen:new {
	id = "out_of_my_sight",
	leftDialog = "@conversation/hutt_informant:s_eed9dce1", -- You're a fool. Get out of my sight.
	stopConversation = "true",
	options = {}
}
huttInformantConvoTemplate:addScreen(out_of_my_sight);

addConversationTemplate("huttInformantConvoTemplate", huttInformantConvoTemplate);