io_tsomcren_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "iotsomcrenConvoHandler",
	screens = {}
}

i_bet_an = ConvoScreen:new {
	id = "i_bet_an",
	leftDialog = "@conversation/greeter_coronet_shipwright_indifferent:s_44511b5f", -- I bet an ale would taste really good right now. I don't understand why we have to wait here with the merchant guy. It's not like us being here will speed up the delivery of his cargo. We've wasted good cantina time standing outside of a starport. Bummer.
	stopConversation = "false",
	options = {
		{"@conversation/greeter_coronet_shipwright_indifferent:s_22fde798", "why_dont_you"}, -- Why don't you just go wait at the cantina?
	}
}
io_tsomcren_convo_template:addScreen(i_bet_an);

why_dont_you = ConvoScreen:new {
	id = "why_dont_you",
	leftDialog = "@conversation/greeter_coronet_shipwright_indifferent:s_642ae5d4", -- Well, we do kind of have some work that's on hold until we get those parts. But in truth, I don't think it would make that big a difference if we had an ale or three while we wait. Every time I say something, though, my friend kind of freaks out. Wants me to quit lecturing him or something. I had to give up.
	stopConversation = "false",
	options = {
		{"@conversation/greeter_coronet_shipwright_indifferent:s_5a2c3b35", "thats_too_bad"}, -- That's too bad. I hope your parts arrive soon.
	}
}
io_tsomcren_convo_template:addScreen(why_dont_you);

thats_too_bad = ConvoScreen:new {
	id = "thats_too_bad",
	leftDialog = "@conversation/greeter_coronet_shipwright_indifferent:s_101a8685", -- Thanks. Personally, I just wanna get out of here and either get to work or kick back and enjoy the break.
	stopConversation = "true",
	options = {
	}
}
io_tsomcren_convo_template:addScreen(thats_too_bad);

wow_you_helped = ConvoScreen:new {
	id = "wow_you_helped",
	leftDialog = "@conversation/greeter_coronet_shipwright_indifferent:s_7", -- Wow, you helped find our missing shipment. That's really great. It's too bad that it's all being held as evidence by CorSec, but at least we know where it is.
	stopConversation = "true",
	options = {
	}
}
io_tsomcren_convo_template:addScreen(wow_you_helped);

addConversationTemplate("io_tsomcren_convo_template", io_tsomcren_convo_template);
