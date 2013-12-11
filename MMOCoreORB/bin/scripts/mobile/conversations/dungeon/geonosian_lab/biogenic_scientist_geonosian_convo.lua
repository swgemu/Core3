--If this convo has errors - Loc-nar -- this is the NPC on the catwalk near the acklay door that gives the 78660 key code
biogenic_scientist_geonosian_ConversationTemplate = ConvoTemplate:new {
	initialScreen = "biogen_geo_start",
	templateType = "Lua",    
	luaClassHandler = "biogenic_scientist_geonosian_ConversationHandler",
	screens = {}
}

biogen_geo_start = ConvoScreen:new {
	id = "biogen_geo_start",
	leftDialog = "@conversation/biogenic_scientist_geonosian:s_a59fc522", -- Thank... thank you for rescuing me
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_geonosian:s_f612da3","biogen_geo_alright"}, -- Hang in there, you'll be alright
	} 
}

biogenic_scientist_geonosian_ConversationTemplate:addScreen(biogen_geo_start);

biogen_geo_alright = ConvoScreen:new {
	id = "biogen_geo_alright",
	leftDialog = "@conversation/biogenic_scientist_geonosian:s_5d99d708", --It's...terrible...it's locked in 78660...
	stopConversation = "false",
	options = {    
		{"@conversation/biogenic_scientist_geonosian:s_720b306c","biogen_geo_random"}, -- Stop blathering. You'll live    
		{"@conversation/biogenic_scientist_geonosian:s_ab9b9023","biogen_geo_wait"} -- I hope you make it, good-bye
	}
}

biogenic_scientist_geonosian_ConversationTemplate:addScreen(biogen_geo_alright);

biogen_geo_random = ConvoScreen:new {
	id = "biogen_geo_random",
	leftDialog = "", 
	stopConversation = "false",
	options = {
	}
}

biogenic_scientist_geonosian_ConversationTemplate:addScreen(biogen_geo_random);

biogen_geo_nono = ConvoScreen:new {
	id = "biogen_geo_nono",
	leftDialog = "@conversation/biogenic_scientist_geonosian:s_3b597458", -- No, no But that's ok
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_geonosian:s_4c6bb27a","biogen_geo_good_bye"} -- OK, I'll take it
	}    
}

biogenic_scientist_geonosian_ConversationTemplate:addScreen(biogen_geo_nono);

biogen_geo_doubt = ConvoScreen:new {
	id = "biogen_geo_doubt",
	leftDialog = "@conversation/biogenic_scientist_geonosian:s_7ddd5bf5", -- No, I doubt that
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_geonosian:s_4c6bb27a","biogen_geo_good_bye"} -- OK, I'll take it
	}
}

biogenic_scientist_geonosian_ConversationTemplate:addScreen(biogen_geo_doubt);

biogen_geo_wait = ConvoScreen:new {
	id = "biogen_geo_wait",
	leftDialog = "@conversation/biogenic_scientist_geonosian:s_71f20c60", -- Wait, wait... Take this...
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_geonosian:s_4c6bb27a","biogen_geo_good_bye"} -- OK, I'll take it
	}
}

biogenic_scientist_geonosian_ConversationTemplate:addScreen(biogen_geo_wait);

biogen_geo_good_bye = ConvoScreen:new {
	id = "biogen_geo_good_bye",
	leftDialog = "@conversation/biogenic_scientist_geonosian:s_30d18e8f", -- Becareful.. terrible creature.. locked in... 78660
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_geonosian:s_52a88e99",""} -- Thank you I will
	}
}

biogenic_scientist_geonosian_ConversationTemplate:addScreen(biogen_geo_good_bye);

biogen_geo_done = ConvoScreen:new {
	id = "biogen_geo_done",
	leftDialog = "@conversation/biogenic_scientist_geonosian:s_30d18e8f", -- Becareful.. terrible creature.. locked in... 78660
	stopConversation = "true",
	options = {
	}
}

biogenic_scientist_geonosian_ConversationTemplate:addScreen(biogen_geo_done);



addConversationTemplate("biogenic_scientist_geonosian_ConversationTemplate", biogenic_scientist_geonosian_ConversationTemplate);


