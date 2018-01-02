bestineStoneMerchantConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestineStoneMerchantConvoHandler",
	screens = {}
}

init_default = ConvoScreen:new {
	id = "init_election_phase",
	leftDialog = "@conversation/bestine_stone_merchant:s_8762f9f", -- I'm in the business of collecting rare stones. Unfortunately, I haven't had much business lately. I guess I should find another business.
	stopConversation = "false",
	options = {
	--{"@conversation/bestine_stone_merchant:s_f660c800", "what_kind"}, -- I may have the stones you are looking for.
	--{"@conversation/bestine_stone_merchant:s_90ce1297", "dont_know_where"}, -- I guess so. I'll look for some.
	--{"@conversation/bestine_stone_merchant:s_4242e25b", "keep_searching"}, -- Probably. Bye!
	}
}
bestineStoneMerchantConvoTemplate:addScreen(init_election_phase);

init_return = ConvoScreen:new {
	id = "init_return",
	leftDialog = "@conversation/bestine_stone_merchant:s_f56c7c9f", -- Do you have more stones for me?
	stopConversation = "false",
	options = {
	--{"@conversation/bestine_stone_merchant:s_b6e7bea1", "take_off_your_hands"}, -- Yes, I do. I have a carved stone.
	--{"@conversation/bestine_stone_merchant:s_af25c425", "take_off_your_hands"}, -- Yes, I do. I have a smooth stone.
	--{"@conversation/bestine_stone_merchant:s_eaee4954", "be_sure_to_come_back"}, -- No, just looking around. See ya later!
	}
}
bestineStoneMerchantConvoTemplate:addScreen(init_return);

be_sure_to_come_back = ConvoScreen:new {
	id = "be_sure_to_come_back",
	leftDialog = "@conversation/bestine_stone_merchant:s_b04b4ef5", -- Alright. If you have any stones, be sure to come back!
	stopConversation = "true",
	options = {}
}
bestineStoneMerchantConvoTemplate:addScreen(be_sure_to_come_back);

what_kind = ConvoScreen:new {
	id = "what_kind",
	leftDialog = "@conversation/bestine_stone_merchant:s_e21cea57", -- You do?! What kind of stones?
	stopConversation = "false",
	options = {
	--{"@conversation/bestine_stone_merchant:s_b6f71f8a", "take_off_your_hands"}, -- I have a carved stone.
	--{"@conversation/bestine_stone_merchant:s_af35650e", "take_off_your_hands"}, -- I have a smooth stone.
	}
}
bestineStoneMerchantConvoTemplate:addScreen(what_kind);

take_off_your_hands = ConvoScreen:new {
	id = "take_off_your_hands",
	leftDialog = "@conversation/bestine_stone_merchant:s_cc49587f", -- Wow! That's just what I'm looking for! I can take it off your hands if you want. I need to test every one very carefully. So what do you say? Which one do you want to give me?
	stopConversation = "false",
	options = {
	--{"@conversation/bestine_stone_merchant:s_211ab5b4", "carved_guard_it"}, -- I'll give you the carved stone.
	--{"@conversation/bestine_stone_merchant:s_38d8cf30", "smooth_guard_it"}, -- I'll give you the smooth stone.
	--{"@conversation/bestine_stone_merchant:s_8c741032", "seek_me_out"}, -- I'm going to keep it.
	}
}
bestineStoneMerchantConvoTemplate:addScreen(take_off_your_hands);

smooth_guard_it = ConvoScreen:new {
	id = "smooth_guard_it",
	leftDialog = "@conversation/bestine_stone_merchant:s_bb2c2468", -- Thank you! Here, I'll give you this. We'll say you bought it from me by giving me the stone. It's rare so guard it closely.
	stopConversation = "true",
	options = {}
}
bestineStoneMerchantConvoTemplate:addScreen(smooth_guard_it);

carved_guard_it = ConvoScreen:new {
	id = "carved_guard_it",
	leftDialog = "@conversation/bestine_stone_merchant:s_bb2c2468", -- Thank you! Here, I'll give you this. We'll say you bought it from me by giving me the stone. It's rare so guard it closely.
	stopConversation = "true",
	options = {}
}
bestineStoneMerchantConvoTemplate:addScreen(carved_guard_it);

seek_me_out = ConvoScreen:new {
	id = "seek_me_out",
	leftDialog = "@conversation/bestine_stone_merchant:s_d7a9bace", -- Oh... okay. Well, if you decide you'd rather get it off your hands, feel free to seek me out! I'll surely buy them off you.
	stopConversation = "true",
	options = {}
}
bestineStoneMerchantConvoTemplate:addScreen(seek_me_out);

dont_know_where = ConvoScreen:new {
	id = "dont_know_where",
	leftDialog = "@conversation/bestine_stone_merchant:s_9e6e06eb", -- You will? Too bad I don't know where they are. I heard a rumor that Victor Visalis may know. He's over at the capitol. He doesn't usually talk about things other than the election. Maybe if he won the election... oh well. If you ever find any, I'm here.
	stopConversation = "true",
	options = {}
}
bestineStoneMerchantConvoTemplate:addScreen(dont_know_where);

keep_searching = ConvoScreen:new {
	id = "keep_searching",
	leftDialog = "@conversation/bestine_stone_merchant:s_1cb401b5", -- I'll keep searching!
	stopConversation = "true",
	options = {}
}
bestineStoneMerchantConvoTemplate:addScreen(keep_searching);

addConversationTemplate("bestineStoneMerchantConvoTemplate", bestineStoneMerchantConvoTemplate);
