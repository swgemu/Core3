villageSarguilloPhase2ConvoTemplate = ConvoTemplate:new {
	initialScreen = "intro",
	templateType = "Lua",
	luaClassHandler = "conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/village_sarguillo_2:s_ffe08b69", -- Check sector 4. The sensor array is indicating movement in that area. Probably just more brackasets.
	stopConversation = "false",
	options = {
		{ "@conversation/village_sarguillo_2:s_55d76f7", "kind_of_busy" }, -- Are you talking to me?
	}
}
villageSarguilloPhase2ConvoTemplate:addScreen(intro);

kind_of_busy = ConvoScreen:new {
	id = "kind_of_busy",
	leftDialog = "@conversation/village_sarguillo_2:s_1cf74704", -- No. Kind of busy here coordinating patrols. What can I do for you?
	stopConversation = "false",
	options = {
		{ "@conversation/village_sarguillo_2:s_c96d6885", "speak_to_elder" }, -- I'm here to offer my assistance.
	}
}
villageSarguilloPhase2ConvoTemplate:addScreen(kind_of_busy);

speak_to_elder = ConvoScreen:new {
	id = "speak_to_elder",
	leftDialog = "@conversation/village_sarguillo_2:s_7c5b4636", -- You should speak to the Elder. He can give you all the help you need.
	stopConversation = "false",
	options = {
		{ "@conversation/village_sarguillo_2:s_59b666a8", "speak_with_dageerin" }, -- I've already talked to the Elder. I want to help with combat.
	}
}
villageSarguilloPhase2ConvoTemplate:addScreen(speak_to_elder);

speak_with_dageerin = ConvoScreen:new {
	id = "speak_with_dageerin",
	leftDialog = "@conversation/village_sarguillo_2:s_ee7d6b1f", -- Good. Glad to have you aboard, but you'll need to speak with Dageerin for your assignment. He's over by the communal huts northwest of here. He has temporarily assumed command of the assault groups while I organize the defense.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase2ConvoTemplate:addScreen(speak_with_dageerin);

addConversationTemplate("villageSarguilloPhase2ConvoTemplate", villageSarguilloPhase2ConvoTemplate);
