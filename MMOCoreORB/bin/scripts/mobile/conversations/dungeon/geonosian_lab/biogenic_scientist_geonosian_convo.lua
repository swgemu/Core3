biogenicScientistGeonosianConvoTemplate = ConvoTemplate:new {
	initialScreen = "thanks_for_rescuing",
	templateType = "Lua",
	luaClassHandler = "conv_handler",
	screens = {}
}

thanks_for_rescuing = ConvoScreen:new {
	id = "thanks_for_rescuing",
	leftDialog = "@conversation/biogenic_scientist_geonosian:s_a59fc522", -- Thank... thank you for rescuing me, but... I've been hurt... I don't know... if I can make it out...
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_geonosian:s_f612da3", "no_i_doubt_that"}, -- Hang in there, you'll be alright.
		{"@conversation/biogenic_scientist_geonosian:s_720b306c", "no_but_thats_ok"}, -- Stop blathering. You'll live.
		{"@conversation/biogenic_scientist_geonosian:s_ab9b9023", "wait_take_this"} -- I hope you make it. Good-bye.
	}
}

biogenicScientistGeonosianConvoTemplate:addScreen(thanks_for_rescuing);

no_i_doubt_that = ConvoScreen:new {
	id = "no_i_doubt_that",
	leftDialog = "@conversation/biogenic_scientist_geonosian:s_7ddd5bf5", -- No, I doubt that. But it's OK... I was trying to salvage data from... what's left of the computers. This was... all I could get... before the monsters attacked. You take it... put it to good use...
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_geonosian:s_4c6bb27a", "be_careful"}, -- OK, I'll take it.
		{"@conversation/biogenic_scientist_geonosian:s_52a88e99", "its_terrible"} -- Thank you, I will.
	}
}

biogenicScientistGeonosianConvoTemplate:addScreen(no_i_doubt_that);

wait_take_this = ConvoScreen:new {
	id = "wait_take_this",
	leftDialog = "@conversation/biogenic_scientist_geonosian:s_71f20c60", -- Wait, wait... Take this... I was trying to salvage data from... what's left of the computers. This was... all I could get... before the monsters attacked... Put it to good use...
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_geonosian:s_4c6bb27a", "be_careful"}, -- OK, I'll take it.
		{"@conversation/biogenic_scientist_geonosian:s_52a88e99", "its_terrible"} -- Thank you, I will.
	}
}

biogenicScientistGeonosianConvoTemplate:addScreen(wait_take_this);

no_but_thats_ok = ConvoScreen:new {
	id = "no_but_thats_ok",
	leftDialog = "@conversation/biogenic_scientist_geonosian:s_3b597458", -- No, no. But that's OK... I was trying to salvage data from... what's left of the computers. This was... all I could get... before the monsters attacked. You take it... put it to good use...
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_geonosian:s_4c6bb27a", "be_careful"}, -- OK, I'll take it.
		{"@conversation/biogenic_scientist_geonosian:s_52a88e99", "its_terrible"} -- Thank you, I will.
	}
}

biogenicScientistGeonosianConvoTemplate:addScreen(no_but_thats_ok);

be_careful = ConvoScreen:new {
	id = "be_careful",
	leftDialog = "@conversation/biogenic_scientist_geonosian:s_30d18e8f", -- Be careful... terrible creature... locked in... 78660...
	stopConversation = "true",
	options = {
	}
}

biogenicScientistGeonosianConvoTemplate:addScreen(be_careful);

its_terrible = ConvoScreen:new {
	id = "its_terrible",
	leftDialog = "@conversation/biogenic_scientist_geonosian:s_5d99d708", -- It's... terrible... it's locked in... 78660...
	stopConversation = "true",
	options = {
	}
}

biogenicScientistGeonosianConvoTemplate:addScreen(its_terrible);

addConversationTemplate("biogenicScientistGeonosianConvoTemplate", biogenicScientistGeonosianConvoTemplate);
