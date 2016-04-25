ImoVledmoConversationTemplate = ConvoTemplate:new {
	initialScreen = "imo_start",
	templateType = "Lua",
	luaClassHandler = "ImoVledmoConversationHandler",
	screens = {}
}

imo_start = ConvoScreen:new {
	id = "imo_start",
	leftDialog = "@conversation/corvette_vledmo_neutral_rescue_target:s_c5413576", --Hehe, you came to 'rescue' me? Yeah I'm sure Jabba was real worried. Not like I needed the help... was just about to bust out of here myself.
	stopConversation = "false",
	options = { 
		{"@conversation/corvette_vledmo_neutral_rescue_target:s_3d453e53","vledmo_rescue"}, --Well Jabba thought it was best we'd escort you back to safety.
	}
}

ImoVledmoConversationTemplate:addScreen(imo_start);


already_rescued = ConvoScreen:new {
	id = "already_rescued",
	leftDialog = "@conversation/corvette_vledmo_neutral_rescue_target:s_46770350", 
	stopConversation = "true",
	options = { }
}

ImoVledmoConversationTemplate:addScreen(already_rescued);


vledmo_rescue = ConvoScreen:new {
	id = "vledmo_rescue",
	leftDialog = "@conversation/corvette_vledmo_neutral_rescue_target:s_3a6b92ce", -- I'm sure he did. You can tell him to get in touch with me through the regular channels. I'm not going anywhere near his stinking sand castle for a while. Now if you excuse me, I have an escape pod to catch.
	stopConversation = "true",
	options = {
	}
}

corvetteBronellConvoTemplate:addScreen(vledmo_rescue);
