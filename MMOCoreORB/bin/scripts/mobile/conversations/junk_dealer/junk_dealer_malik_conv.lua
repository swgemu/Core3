junkDealerMalikConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "JunkDealerConvoHandler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/junk_malik_vistal:s_769000a5", -- You look to be a rough sort. Perhaps you would be interested in taking care of a little business problem that me and my associates have been having?
	stopConversation = "false",
	options = {
		{"@conversation/junk_malik_vistal:s_f836463", "like_to_hear"}, -- I am an expert at solving problems.
		{"@conversation/junk_malik_vistal:s_f66e6241", "own_skin"}, -- This sounds a bit fishy. I don't want to be involved.
	}
}
junkDealerMalikConvoTemplate:addScreen(init);

own_skin = ConvoScreen:new {
	id = "own_skin",
	leftDialog = "@conversation/junk_malik_vistal:s_af6451b5", -- I may not like it, but looking after ones own skin is something that I can understand. Maybe next time.
	stopConversation = "true",
	options = {}
}
junkDealerMalikConvoTemplate:addScreen(own_skin);

like_to_hear = ConvoScreen:new {
	id = "like_to_hear",
	leftDialog = "@conversation/junk_malik_vistal:s_9251cdb4", -- That is what I like to hear. Well the problem is pretty simple. My associates and myself are honest hard working citizens that are being harassed to no end by Corsecs. Why they are after us is completely beyond my comprehension.
	stopConversation = "false",
	options = {
		{"@conversation/junk_malik_vistal:s_b44309e2", "buy_proof"}, -- Let me guess. You want me to take care of the Corsecs?
		{"@conversation/junk_malik_vistal:s_91196436", "figured"}, -- I don't need the Corsecs looking into me for getting involved.
	}
}
junkDealerMalikConvoTemplate:addScreen(like_to_hear);

figured = ConvoScreen:new {
	id = "figured",
	leftDialog = "@conversation/junk_malik_vistal:s_420b90b8", -- Figured as much but it was worth a shot.
	stopConversation = "true",
	options = {}
}
junkDealerMalikConvoTemplate:addScreen(figured);

buy_proof = ConvoScreen:new {
	id = "buy_proof",
	leftDialog = "@conversation/junk_malik_vistal:s_18123132", -- Hey, I didn't say anything about taking care of no Corsecs. But if accidents did happen to befall them who is to say that I wouldn't buy some sort of proof that they are no more...purely as a collectors piece of course.
	stopConversation = "false",
	options = {
		{"@conversation/junk_malik_vistal:s_fc51be40", "start_sale_corsec"}, -- I think that I have just what you are looking for on me.
		{"@conversation/junk_malik_vistal:s_d36db42d", "right_sort"}, -- I don't have anything you want but I will keep an eye out.
	}
}
junkDealerMalikConvoTemplate:addScreen(buy_proof);

right_sort = ConvoScreen:new {
	id = "right_sort",
	leftDialog = "@conversation/junk_malik_vistal:s_9c1435e4", -- I knew that you were the right sort from the moment I saw you.
	stopConversation = "true",
	options = {}
}
junkDealerMalikConvoTemplate:addScreen(right_sort);

start_sale_corsec = ConvoScreen:new {
	id = "start_sale_corsec",
	leftDialog = "@conversation/junk_malik_vistal:s_9334c0a0", -- Let me take a look. I probably will be inclined to pay for anything Corsec that I locate on your person. Of course, this transaction has nothing to do with the unfortunate circumstances of which you came into possession of these items.
	stopConversation = "true",
	options = {}
}
junkDealerMalikConvoTemplate:addScreen(start_sale_corsec);

addConversationTemplate("junkDealerMalikConvoTemplate", junkDealerMalikConvoTemplate);
