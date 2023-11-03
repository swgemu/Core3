ceth_laike_conv = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "CethLaikeConvoHandler",
	screens = {}
}

neutral_greeting = ConvoScreen:new {
	id = "neutral_greeting",
	leftDialog = "@conversation/c_sink_reb:s_1114", -- Good afternoon!  Nice day, isn't it?  I'm sorry, but I don't have anything that you can do.  I am looking for someone more sympathetic to the Alliance.

	options = {
	}
}
ceth_laike_conv:addScreen(neutral_greeting)


addConversationTemplate("ceth_laike_conv", ceth_laike_conv)