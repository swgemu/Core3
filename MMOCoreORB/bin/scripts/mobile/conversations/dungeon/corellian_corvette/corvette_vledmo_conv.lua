corvetteVledmoConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "corvetteVledmoConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/corvette_vledmo_neutral_rescue_target:s_c5413576", --Hehe, you came to 'rescue' me? Yeah I'm sure Jabba was real worried. Not like I needed the help... was just about to bust out of here myself.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_vledmo_neutral_rescue_target:s_3d453e53","regular_channels"}, -- Well Jabba thought it was best we'd escort you back to safety.
		{"@conversation/corvette_vledmo_neutral_rescue_target:s_4751b5d0","space_hero"}, -- Yeah right... sure you were.
	}
}
corvetteVledmoConvoTemplate:addScreen(intro);

already_rescued = ConvoScreen:new {
	id = "already_rescued",
	leftDialog = "@conversation/corvette_vledmo_neutral_rescue_target:s_46770350", -- Look...instead of trying to make polite conversation, how about you let me actually finish escaping? Sound good? Okay.
	stopConversation = "true",
	options = { }
}
corvetteVledmoConvoTemplate:addScreen(already_rescued);

regular_channels = ConvoScreen:new {
	id = "regular_channels",
	leftDialog = "@conversation/corvette_vledmo_neutral_rescue_target:s_3a6b92ce", -- I'm sure he did. You can tell him to get in touch with me through the regular channels. I'm not going anywhere near his stinking sand castle for a while. Now if you excuse me, I have an escape pod to catch.
	stopConversation = "true",
	options = {}
}
corvetteVledmoConvoTemplate:addScreen(regular_channels);

space_hero = ConvoScreen:new {
	id = "space_hero",
	leftDialog = "@conversation/corvette_vledmo_neutral_rescue_target:s_ecd754dd", -- Listen punk, I don't need to wait on some blaster waving, wannabe space hero to rescue me. I've been getting myself out of this kind of situation since you were toe-high to a bantha. Now get out of my way, I have an escape pod to catch.
	stopConversation = "true",
	options = {}
}
corvetteVledmoConvoTemplate:addScreen(space_hero);

addConversationTemplate("corvetteVledmoConvoTemplate", corvetteVledmoConvoTemplate);
