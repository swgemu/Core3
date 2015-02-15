heroOfTatFarmerConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "heroOfTatFarmerConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/quest_hero_of_tatooine_farmer:s_4de6ecbe", -- Please, oh please. You've got to help me! I'm desperate!
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_farmer:s_9e0bb613", "family_is_gone"}, -- Slow down. What's the matter?
		{"@conversation/quest_hero_of_tatooine_farmer:s_ca776e30", "moisture_farmer"}, -- Who are you?
		{"@conversation/quest_hero_of_tatooine_farmer:s_b658a801", "ill_go_myself"} -- Sorry, I can't help you.
	}
}
heroOfTatFarmerConvoTemplate:addScreen(intro);

ill_go_myself = ConvoScreen:new {
	id = "ill_go_myself",
	leftDialog = "@conversation/quest_hero_of_tatooine_farmer:s_cadf41fb", -- I guess I'll have to go myself then. Wish me luck.
	stopConversation = "true",
	options = {
	}
}
heroOfTatFarmerConvoTemplate:addScreen(ill_go_myself);

family_is_gone = ConvoScreen:new {
	id = "family_is_gone",
	leftDialog = "@conversation/quest_hero_of_tatooine_farmer:s_91139d19", -- It's my wife and daughter, they're gone! I was out checking the moisture crop and when I got back to the house I found a note saying they'd been kidnapped! They're being held for ransom!
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_farmer:s_28fe80fc", "of_course_terrible"}, -- That's terrible!
		{"@conversation/quest_hero_of_tatooine_farmer:s_c6144200", "it_was_sennex"}, -- Do you know who took your family?
		{"@conversation/quest_hero_of_tatooine_farmer:s_f4a9d6e8", "tracks_leading_away"}, -- Do you know where your family was taken?
		{"@conversation/quest_hero_of_tatooine_farmer:s_cdbae137", "ill_go_myself"} -- Sorry, I can't help right now.
	}
}
heroOfTatFarmerConvoTemplate:addScreen(family_is_gone);

it_was_sennex = ConvoScreen:new {
	id = "it_was_sennex",
	leftDialog = "@conversation/quest_hero_of_tatooine_farmer:s_31e2a586", -- I don't know for sure. There was a name scribbled at the bottom of the note that was left. It said, 'Sennex'. But I don't know what that means. I don't know anyone named Sennex.
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_farmer:s_f4a9d6e8", "tracks_leading_away"}, -- Do you know where your family was taken?
		{"@conversation/quest_hero_of_tatooine_farmer:s_cf9c96f0", "no_money_for_ransom"}, -- What can I do to help?
		{"@conversation/quest_hero_of_tatooine_farmer:s_cdbae137", "ill_go_myself"} -- Sorry, I can't help right now.
	}
}
heroOfTatFarmerConvoTemplate:addScreen(it_was_sennex);

tracks_leading_away = ConvoScreen:new {
	id = "tracks_leading_away",
	leftDialog = "@conversation/quest_hero_of_tatooine_farmer:s_b394e1eb", -- No, I don't. There were lots of tracks leading away from our house heading this way though. I think there might be a cave or something in this direction. They might be holed up in there.
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_farmer:s_c6144200", "it_was_sennex"}, -- Do you know who took your family?
		{"@conversation/quest_hero_of_tatooine_farmer:s_cf9c96f0", "no_money_for_ransom"}, -- What can I do to help?
		{"@conversation/quest_hero_of_tatooine_farmer:s_cdbae137", "ill_go_myself"} -- Sorry, I can't help right now.
	}
}
heroOfTatFarmerConvoTemplate:addScreen(tracks_leading_away);

ransom_cost = ConvoScreen:new {
	id = "ransom_cost",
	leftDialog = "@conversation/quest_hero_of_tatooine_farmer:s_bed5a497", -- The note says that I need to pay ten thousand credits. But I barely break even as a moisture farmer. I don't have that kind of money!
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_farmer:s_c1d778b6", "a_lot_of_money"}, -- I will give you the ransom money.
		{"@conversation/quest_hero_of_tatooine_farmer:s_2f051629", "very_dangerous"}, -- I will go rescue your family for you.
		{"@conversation/quest_hero_of_tatooine_farmer:s_cdbae137", "ill_go_myself"} -- Sorry, I can't help right now.
	}
}
heroOfTatFarmerConvoTemplate:addScreen(ransom_cost);

no_money_for_ransom = ConvoScreen:new {
	id = "no_money_for_ransom",
	leftDialog = "@conversation/quest_hero_of_tatooine_farmer:s_5a04437", -- Well, I don't have the money to pay the ransom, and if I don't pay, they said they would sell my wife and daughter into slavery. So I'm on my way to try and rescue them myself, although I don't think that I'll be able to put up a good fight.
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_farmer:s_2f051629", "very_dangerous"}, -- I will go rescue your family for you.
		{"@conversation/quest_hero_of_tatooine_farmer:s_9930ca3d", "ransom_cost"}, -- How much is the ransom?
		{"@conversation/quest_hero_of_tatooine_farmer:s_4b28f5f9", "ill_go_myself"} -- It doesn't sound like there's much that I can do.
	}
}
heroOfTatFarmerConvoTemplate:addScreen(no_money_for_ransom);

very_dangerous = ConvoScreen:new {
	id = "very_dangerous",
	leftDialog = "@conversation/quest_hero_of_tatooine_farmer:s_498b2572", -- Are you sure? I appreciate your selflessness, but it will probably be very dangerous. Though I agree that you are probably better equipped to go than I.
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_farmer:s_17089ea4", "sincerest_gratitude"}, -- Yes, I will go save your wife and daughter.
		{"@conversation/quest_hero_of_tatooine_farmer:s_a6faa65a", "ransom_cost"}, -- How much did you say the ransom was?
		{"@conversation/quest_hero_of_tatooine_farmer:s_2fdb8fbd", "ill_go_myself"} -- On second thought, I don't think I can help right now.
	}
}
heroOfTatFarmerConvoTemplate:addScreen(very_dangerous);

sincerest_gratitude = ConvoScreen:new {
	id = "sincerest_gratitude",
	leftDialog = "@conversation/quest_hero_of_tatooine_farmer:s_3abf0d9c", -- Thank you so very much. You have my sincerest gratitude. But do be careful, for my family's sake. Here, I'll transmit a location to your datapad. I think that the brutes that did this might be holed up in a cave there.
	stopConversation = "true",
	options = {
	}
}
heroOfTatFarmerConvoTemplate:addScreen(sincerest_gratitude);

a_lot_of_money = ConvoScreen:new {
	id = "a_lot_of_money",
	leftDialog = "@conversation/quest_hero_of_tatooine_farmer:s_545b2c24", -- Really? I would be forever grateful, but that's a lot of money. Are you sure?
	stopConversation = "false",
	options = {
		-- Handled by convo handler
		--{"@conversation/quest_hero_of_tatooine_farmer:s_5cdaed70", "in_your_debt"}, -- Yes, I am sure. [give 10000 credits]
		-- or
		--{"@conversation/quest_hero_of_tatooine_farmer:s_2e1d6626", "ill_go_myself"}, -- Oops. Looks like I don't have that much money either.
		--{"@conversation/quest_hero_of_tatooine_farmer:s_d5adc7c6", "very_dangerous"}, -- Actually, I'd rather go rescue your family for you.
		--{"@conversation/quest_hero_of_tatooine_farmer:s_2fdb8fbd", "ill_go_myself"} -- On second thought, I don't think I can help right now.
	}
}
heroOfTatFarmerConvoTemplate:addScreen(a_lot_of_money);

in_your_debt = ConvoScreen:new {
	id = "in_your_debt",
	leftDialog = "@conversation/quest_hero_of_tatooine_farmer:s_27d7b600", -- Thank you! Oh, thank you so much. I will be in your debt always. I'm going to go make arrangements to pay the ransom money now. Thank you again for your kindness.
	stopConversation = "true",
	options = {
	}
}
heroOfTatFarmerConvoTemplate:addScreen(in_your_debt);

thanks_for_offering = ConvoScreen:new {
	id = "thanks_for_offering",
	leftDialog = "@conversation/quest_hero_of_tatooine_farmer:s_9ead1175", -- Oh well. Thanks anyway for offering. I guess there's nothing left for me to do but go and try to rescue my wife and daughter myself.
	stopConversation = "true",
	options = {
	}
}
heroOfTatFarmerConvoTemplate:addScreen(thanks_for_offering);

moisture_farmer = ConvoScreen:new {
	id = "moisture_farmer",
	leftDialog = "@conversation/quest_hero_of_tatooine_farmer:s_7d7b9050", -- I'm a moisture farmer. And not even a very good one. I can't help but think that if I was at home instead of checking the evaporators, this never would have happened.
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_farmer:s_ba7f35a5", "family_is_gone"}, -- Tell me what's wrong.
		{"@conversation/quest_hero_of_tatooine_farmer:s_b658a801", "ill_go_myself"} -- Sorry, I can't help you.
	}
}
heroOfTatFarmerConvoTemplate:addScreen(moisture_farmer);

of_course_terrible = ConvoScreen:new {
	id = "of_course_terrible",
	leftDialog = "@conversation/quest_hero_of_tatooine_farmer:s_f26c1a9", -- Don't you think I know that? My family has been kidnapped! The only two things in my life that I hold dear! Of course it's terrible!
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_farmer:s_53fb3746", "sorry_im_upset"}, -- Don't yell at me. I didn't kidnap them.
		{"@conversation/quest_hero_of_tatooine_farmer:s_b7068b53", "it_was_sennex"}, -- Calm down. Do you know who took your family?
		{"@conversation/quest_hero_of_tatooine_farmer:s_c4fbf8c5", "tracks_leading_away"}, -- Calm down. Do you know where your family was taken?
		{"@conversation/quest_hero_of_tatooine_farmer:s_b658a801", "ill_go_myself"} -- Sorry, I can't help you.
	}
}
heroOfTatFarmerConvoTemplate:addScreen(of_course_terrible);

sorry_im_upset = ConvoScreen:new {
	id = "sorry_im_upset",
	leftDialog = "@conversation/quest_hero_of_tatooine_farmer:s_8e117483", -- You're right. I'm sorry, but of course you realize why I'm upset.
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_farmer:s_c6144200", "it_was_sennex"}, -- Do you know who took your family?
		{"@conversation/quest_hero_of_tatooine_farmer:s_f4a9d6e8", "tracks_leading_away"}, -- Do you know where your family was taken?
		{"@conversation/quest_hero_of_tatooine_farmer:s_46d3276e", "ill_go_myself"} -- Sorry, I don't think I can help right now.
	}
}
heroOfTatFarmerConvoTemplate:addScreen(sorry_im_upset);

intro_has_quest = ConvoScreen:new {
	id = "intro_has_quest",
	leftDialog = "@conversation/quest_hero_of_tatooine_farmer:s_ab3e1351", -- Yes, hello. You are going to go rescue my wife and daughter are you not?
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_farmer:s_7c31a6a3", "here_is_loc_again"}, -- Can you show me where you think the cave is again?
		{"@conversation/quest_hero_of_tatooine_farmer:s_2fdb8fbd", "thanks_for_offering"} -- On second thought, I don't think I can help right now.
	}
}
heroOfTatFarmerConvoTemplate:addScreen(intro_has_quest);

intro_someone_else_started = ConvoScreen:new {
	id = "intro_someone_else_started",
	leftDialog = "@conversation/quest_hero_of_tatooine_farmer:s_7f1f06ba", -- Oh, hello. Yes, I did have a problem, but a very kind soul has already offered to help. Thank you very much, though.
	stopConversation = "true",
	options = {
	}
}
heroOfTatFarmerConvoTemplate:addScreen(intro_someone_else_started);

here_is_loc_again = ConvoScreen:new {
	id = "here_is_loc_again",
	leftDialog = "@conversation/quest_hero_of_tatooine_farmer:s_916b0cc0", -- Sure. Here is the location of the cave where I think the brutes might be hiding. Now please save my family, and do be careful.
	stopConversation = "true",
	options = {
	}
}
heroOfTatFarmerConvoTemplate:addScreen(here_is_loc_again);

intro_completed = ConvoScreen:new {
	id = "intro_completed",
	leftDialog = "@conversation/quest_hero_of_tatooine_farmer:s_da11deae", -- Hello! I wanted to thank you again for helping to rescue my family. We are all deeply indebted to you.
	stopConversation = "true",
	options = {
	}
}
heroOfTatFarmerConvoTemplate:addScreen(intro_completed);

addConversationTemplate("heroOfTatFarmerConvoTemplate", heroOfTatFarmerConvoTemplate);