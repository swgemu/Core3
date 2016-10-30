fsVillageConvo3MaleTemplate = ConvoTemplate:new {
	initialScreen = "intro",
	templateType = "Lua",
	luaClassHandler = "conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/fs_village_convo3_m:s_a6600b37", -- Hello. What brings you to our village?
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo3_m:s_ce4f7c2b", "on_a_pilgrimage" }, -- Looking for information about the Force.
		{ "@conversation/fs_village_convo3_m:s_351f9414", "work_the_land" }, -- What do you folks do way out here in the middle of nowhere?
		{ "@conversation/fs_village_convo3_m:s_29e5bb06", "later_friend" }, -- Nothing really. As a matter of fact I was on the way out.
	}
}
fsVillageConvo3MaleTemplate:addScreen(intro);

work_the_land = ConvoScreen:new {
	id = "work_the_land",
	leftDialog = "@conversation/fs_village_convo3_m:s_c2be1811", -- Well we work the land, trade with some few freighter captains, but mostly we stay out of the way.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo3_m:s_30d6ee6", "the_war_mostly" }, -- Stay out of the way? Why would you want to do that?
		{ "@conversation/fs_village_convo3_m:s_2b466883", "blew_up_a_planet" }, -- Sounds like you're hiding from something more than just the war.
	}
}
fsVillageConvo3MaleTemplate:addScreen(work_the_land);

blew_up_a_planet = ConvoScreen:new {
	id = "blew_up_a_planet",
	leftDialog = "@conversation/fs_village_convo3_m:s_4ac0f748", -- Would we need a reason other than the war? I mean they blew up a planet! 
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo3_m:s_e14b17f4", "spare_me_zeal" }, -- Which means it's even more important to fight. We cannot let a regime with so little regard for sapient life continue to hold the galaxy hostage. We must stop them!
	}
}
fsVillageConvo3MaleTemplate:addScreen(blew_up_a_planet);

spare_me_zeal = ConvoScreen:new {
	id = "spare_me_zeal",
	leftDialog = "@conversation/fs_village_convo3_m:s_bf567533", -- Spare me the righteous zeal. I've been there son. Lost my wife. It'll take a lot more than a pretty speech to get me to let what little family I got left to go. I think we're done here.
	stopConversation = "true",
	options = {}
}
fsVillageConvo3MaleTemplate:addScreen(spare_me_zeal);

the_war_mostly = ConvoScreen:new {
	id = "the_war_mostly",
	leftDialog = "@conversation/fs_village_convo3_m:s_93ec538d", -- The war mostly. Most of us have lost family or friends to the war. We've resolved to not lose anyone else.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo3_m:s_76a2d8f9", "most_of_us_have" }, -- Why don't you fight? Take a side instead of sitting out here hiding?
	}
}
fsVillageConvo3MaleTemplate:addScreen(the_war_mostly);

most_of_us_have = ConvoScreen:new {
	id = "most_of_us_have",
	leftDialog = "@conversation/fs_village_convo3_m:s_3d31f978", -- Most of us have. We've paid our dues in blood and pain. We're done with it. It's one thing to risk your own life in a war, but once you have children it becomes something else entirely to let them do the same.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo3_m:s_d3683f06", "wont_risk_children" }, -- You should always fight for what you believe in. Once you give up on that, you give up on everything.
	}
}
fsVillageConvo3MaleTemplate:addScreen(most_of_us_have);

wont_risk_children = ConvoScreen:new {
	id = "wont_risk_children",
	leftDialog = "@conversation/fs_village_convo3_m:s_116fa06f", -- I'll not risk my children to this frenzy of destruction. 
	stopConversation = "true",
	options = {}
}
fsVillageConvo3MaleTemplate:addScreen(wont_risk_children);

on_a_pilgrimage = ConvoScreen:new {
	id = "on_a_pilgrimage",
	leftDialog = "@conversation/fs_village_convo3_m:s_9cabeaee", -- The Force? Are you on a pilgrimage son? The only Force you'll find around here are those blasted nightsisters and they sure won't welcome any adherents.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo3_m:s_f7ae6df2", "lucky_like_that" }, -- You sure? I heard the people of this village had ways of making things go their way.
	}
}
fsVillageConvo3MaleTemplate:addScreen(on_a_pilgrimage);

lucky_like_that = ConvoScreen:new {
	id = "lucky_like_that",
	leftDialog = "@conversation/fs_village_convo3_m:s_a9268707", -- Yea, we're lucky like that. I'm sorry, but I sure don't know what your fishin for here. Maybe you should go speak to the elder.
	stopConversation = "true",
	options = {}
}
fsVillageConvo3MaleTemplate:addScreen(lucky_like_that);

later_friend = ConvoScreen:new {
	id = "later_friend",
	leftDialog = "@conversation/fs_village_convo3_m:s_e1ee18d4", -- Later, friend.
	stopConversation = "true",
	options = {}
}
fsVillageConvo3MaleTemplate:addScreen(later_friend);

addConversationTemplate("fsVillageConvo3MaleTemplate", fsVillageConvo3MaleTemplate);
