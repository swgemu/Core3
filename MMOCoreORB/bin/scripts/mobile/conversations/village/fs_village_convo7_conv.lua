fsVillageConvo7Template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "fsVillageConvo7Handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/fs_village_convo7:s_6cf0908b", -- We're never going to get our planting done in time with everything else that's going on.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo7:s_2c9520b6", "never_in_time" }, -- Planting? You people are farmers?
		{ "@conversation/fs_village_convo7:s_c7fdb62e", "been_attacked" }, -- What has been going on?
	}
}
fsVillageConvo7Template:addScreen(intro);

never_in_time = ConvoScreen:new {
	id = "never_in_time",
	leftDialog = "@conversation/fs_village_convo7:s_a9fdde5e", -- Yes, but we'll never make the planting in time for this season now.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo7:s_52cf32e2", "we_manage" }, -- How can you grow anything in this dead brown dirt?
	}
}
fsVillageConvo7Template:addScreen(never_in_time);

we_manage = ConvoScreen:new {
	id = "we_manage",
	leftDialog = "@conversation/fs_village_convo7:s_20f19cdd", -- We manage. It takes plenty of high nutrient fertilizer and quite a bit of water, but it can be done.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo7:s_c031923", "what_do_you_mean" }, -- Why do you bother farming here?
	}
}
fsVillageConvo7Template:addScreen(we_manage);

what_do_you_mean = ConvoScreen:new {
	id = "what_do_you_mean",
	leftDialog = "@conversation/fs_village_convo7:s_77e48d5b", -- What do you mean?
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo7:s_af8eece8", "green_and_fertile" }, -- There are other more fertile areas of Dathomir.
	}
}
fsVillageConvo7Template:addScreen(what_do_you_mean);

green_and_fertile = ConvoScreen:new {
	id = "green_and_fertile",
	leftDialog = "@conversation/fs_village_convo7:s_bc23678f", -- This was too when we arrived. Green and fertile as the eye could see. You should have seen it, as lush a land that has ever been in the galaxy.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo7:s_e00ac98e", "dont_really_know" }, -- What happened?
	}
}
fsVillageConvo7Template:addScreen(green_and_fertile);

dont_really_know = ConvoScreen:new {
	id = "dont_really_know",
	leftDialog = "@conversation/fs_village_convo7:s_c24ab601", -- Well we don't really know, but the Elder believes some sort climatological shift occurred and we ended up like this.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo7:s_9f2c88cd", "shouldnt_speak" }, -- You don't sound so sure.
	}
}
fsVillageConvo7Template:addScreen(dont_really_know);

shouldnt_speak = ConvoScreen:new {
	id = "shouldnt_speak",
	leftDialog = "@conversation/fs_village_convo7:s_5d7bd117", -- Well... No, I shouldn't speak of it.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo7:s_1bb44cf9", "ill_tell_you" }, -- I am not sure I can help such secretive people.
	}
}
fsVillageConvo7Template:addScreen(shouldnt_speak);

ill_tell_you = ConvoScreen:new {
	id = "ill_tell_you",
	leftDialog = "@conversation/fs_village_convo7:s_bf08330a", -- Ok, ok. I will tell you. I think we were cursed by those evil Nightsisters. They found out we were in tune with the Force and wanted to destroy us, or at least drive us off.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo7:s_76887815", "wont_be_intimidated" }, -- You haven't left? I would find better land.
	}
}
fsVillageConvo7Template:addScreen(ill_tell_you);

wont_be_intimidated = ConvoScreen:new {
	id = "wont_be_intimidated",
	leftDialog = "@conversation/fs_village_convo7:s_fb0e2a0", -- I don't know about the rest but I stay more because of that very reason now than anything else. I will not be intimidated by anyone...or anything.
	stopConversation = "true",
	options = {}
}
fsVillageConvo7Template:addScreen(wont_be_intimidated);

been_attacked = ConvoScreen:new {
	id = "been_attacked",
	leftDialog = "@conversation/fs_village_convo7:s_76ef710f", -- We've been attacked by a group of mercenaries calling themselves the Sith Shadows.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo7:s_a232b8a1", "not_really_sith" }, -- Sith? Are you serious?
	}
}
fsVillageConvo7Template:addScreen(been_attacked);

not_really_sith = ConvoScreen:new {
	id = "not_really_sith",
	leftDialog = "@conversation/fs_village_convo7:s_50b2b480", -- I don't think they are really Sith, but they sure believe in the evil ideals of that race. They seem to want us all dead.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo7:s_ecdfe4b4", "go_see_elder" }, -- Well, I am sure I can help in some way.
	}
}
fsVillageConvo7Template:addScreen(not_really_sith);

go_see_elder = ConvoScreen:new {
	id = "go_see_elder",
	leftDialog = "@conversation/fs_village_convo7:s_d948941a", -- Go see the Village Elder near the center of the village. He can help you.
	stopConversation = "true",
	options = {}
}
fsVillageConvo7Template:addScreen(go_see_elder);

addConversationTemplate("fsVillageConvo7Template", fsVillageConvo7Template);