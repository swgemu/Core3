coa3CaravanLeaderConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "coa3CaravanLeaderConvoHandler",
	screens = {}
}

-- Player has proper CoA state to talk to caravan leader

init_has_mission = ConvoScreen:new {
	id = "init_has_mission",
	leftDialog = "@conversation/coa3sharedcaravanleader:s_1dde12ed", -- Are you the one I'm waiting on? Transporting this much... umm cargo... over land is dangerous. There are a lot of people that would love to hijack this shipment. With us being broke down; it's only a matter of time before they find us.
	stopConversation = "false",
	options = {
		{"@conversation/coa3sharedcaravanleader:s_f3da7c8a", "heres_the_part"}, -- Yes, I'm here to make the repairs.
		{"@conversation/coa3sharedcaravanleader:s_da681077", "none_of_your_business"}, -- What are you transporting?
		{"@conversation/coa3sharedcaravanleader:s_29e36db9", "keep_on_passing"}, -- I'm just passing through.
	}
}
coa3CaravanLeaderConvoTemplate:addScreen(init_has_mission);

heres_the_part = ConvoScreen:new {
	id = "heres_the_part",
	leftDialog = "@conversation/coa3sharedcaravanleader:s_8264ab67", -- Thank the stars! Here's the part we need to get fixed. Repair that anti-gravity unit and let me know when you're finished. Then we can all get out of here and forget this whole mess ever happened.
	stopConversation = "true",
	options = {}
}
coa3CaravanLeaderConvoTemplate:addScreen(heres_the_part);

none_of_your_business = ConvoScreen:new {
	id = "none_of_your_business",
	leftDialog = "@conversation/coa3sharedcaravanleader:s_302369bd", -- That's none of your business. If you're not here to do the repairs, get lost!
	stopConversation = "true",
	options = {}
}
coa3CaravanLeaderConvoTemplate:addScreen(none_of_your_business);

keep_on_passing = ConvoScreen:new {
	id = "keep_on_passing",
	leftDialog = "@conversation/coa3sharedcaravanleader:s_ca41d9fd", -- Well you'll keep on passing through then if you know what's good for you. There's nothing to see here.
	stopConversation = "true",
	options = {}
}
coa3CaravanLeaderConvoTemplate:addScreen(keep_on_passing);

-- Player has part repaired in their inventory

init_has_part_repaired = ConvoScreen:new {
	id = "init_has_part_repaired",
	leftDialog = "@conversation/coa3sharedcaravanleader:s_d3ba3662", -- So is that part repaired yet?
	stopConversation = "false",
	options = {
		{"@conversation/coa3sharedcaravanleader:s_93eb6764", "take_this_disc"}, -- Yes, here it is.
	}
}
coa3CaravanLeaderConvoTemplate:addScreen(init_has_part_repaired);

take_this_disc = ConvoScreen:new {
	id = "take_this_disc",
	leftDialog = "@conversation/coa3sharedcaravanleader:s_e2c11475", -- Take this disc. It gives our new ETA and all the gritty details of this debacle of an operation. Most importantly, it explains I'm not at fault. I don't want this breakdown to tarnish my reputation. I'd rather die than to survive a hijacking and have to face Jabba. He'd hold me personally responsible for the loss of the cargo I'm sure! And don't get any ideas about reading that disk. That's all classified info and it's all encoded.
	stopConversation = "true",
	options = {}
}
coa3CaravanLeaderConvoTemplate:addScreen(take_this_disc);

-- Player has not repaired the part yet

init_has_part_not_repaired = ConvoScreen:new {
	id = "init_has_part_not_repaired",
	leftDialog = "@conversation/coa3sharedcaravanleader:s_d3ba3662", -- So is that part repaired yet?
	stopConversation = "false",
	options = {
		{"@conversation/coa3sharedcaravanleader:s_b5f15b19", "get_to_it"}, -- Not yet.
		{"@conversation/coa3sharedcaravanleader:s_48566ef9", "immensely_valuable"}, -- What's in it for me?
	}
}
coa3CaravanLeaderConvoTemplate:addScreen(init_has_part_not_repaired);

get_to_it = ConvoScreen:new {
	id = "get_to_it",
	leftDialog = "@conversation/coa3sharedcaravanleader:s_b4c62ef2", -- Well what are you waiting for, get to it! You're in as much danger as us just sitting out here in the open. The quicker that part is repaired, the better it will be for all of us.
	stopConversation = "true",
	options = {}
}
coa3CaravanLeaderConvoTemplate:addScreen(get_to_it);

immensely_valuable = ConvoScreen:new {
	id = "immensely_valuable",
	leftDialog = "@conversation/coa3sharedcaravanleader:s_b22dadc9", -- Listen. This cargo is immensely valuable to Jabba. You make these repairs and I'll give you a disk that explains everything. You turn that in and I'm sure they will give you a big reward for helping make this delivery a success.
	stopConversation = "true",
	options = {}
}
coa3CaravanLeaderConvoTemplate:addScreen(immensely_valuable);

init_returned_part = ConvoScreen:new {
	id = "init_returned_part",
	leftDialog = "@conversation/coa3sharedcaravanleader:s_869e12b2", -- Why are you still here? We have work to do so we can get moving and I don't need you bothering us. Get lost!
	stopConversation = "true",
	options = {}
}
coa3CaravanLeaderConvoTemplate:addScreen(init_returned_part);

init_wrong_person = ConvoScreen:new {
	id = "init_wrong_person",
	leftDialog = "@conversation/coa3sharedcaravanleader:s_e0d207ec", -- Didn't your mother ever tell you not to talk to strangers? Keep on moving the way you were headed and forget anything you've seen here.
	stopConversation = "true",
	options = {}
}
coa3CaravanLeaderConvoTemplate:addScreen(init_wrong_person);

addConversationTemplate("coa3CaravanLeaderConvoTemplate", coa3CaravanLeaderConvoTemplate);