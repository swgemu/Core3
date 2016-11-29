junkDealerNathanConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "JunkDealerNathanConvoHandler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/junk_nathan_taike:s_5ceff11f", -- Well, well what do we have here? You certainly have the look of a hardened adventurer. Perhaps even one that is not opposed to helping out honest, hardworking farmers and make a few credits in the process?
	stopConversation = "false",
	options = {
		{"@conversation/junk_nathan_taike:s_c20cb2b0", "like_this"}, -- I have never been opposed to helping people...if the price is right.
		{"@conversation/junk_nathan_taike:s_5b767310", "so_be_it"}, -- You have me all wrong. I can't help anyone today.
	}
}
junkDealerNathanConvoTemplate:addScreen(init);

so_be_it = ConvoScreen:new {
	id = "so_be_it",
	leftDialog = "@conversation/junk_nathan_taike:s_eadc8d6e", -- So be it. There is always another that will come along and be willing to help us out.
	stopConversation = "true",
	options = {}
}
junkDealerNathanConvoTemplate:addScreen(so_be_it);

like_this = ConvoScreen:new {
	id = "like_this",
	leftDialog = "@conversation/junk_nathan_taike:s_47a68e94", -- Well it is like this. The honest folk who are trying to eek out a living out here are sick and tired of those thieving Jawas. They scrimp and save enough just to buy a piece of equipment that will make their lives easier only to have the Jawas steal it the next day. It isn't right.
	stopConversation = "false",
	options = {
		{"@conversation/junk_nathan_taike:s_e022ccee", "good_money"}, -- So you are looking for someone to take care of this Jawa problem?
		{"@conversation/junk_nathan_taike:s_b47d6575", "bah"}, -- Sounds to me like you need better security, not an exterminator.
	}
}
junkDealerNathanConvoTemplate:addScreen(like_this);

bah = ConvoScreen:new {
	id = "bah",
	leftDialog = "@conversation/junk_nathan_taike:s_735e3c59", -- Bah! I should have figured that a stranger wouldn't understand the extent of the problem.
	stopConversation = "true",
	options = {}
}
junkDealerNathanConvoTemplate:addScreen(bah);

good_money = ConvoScreen:new {
	id = "good_money",
	leftDialog = "@conversation/junk_nathan_taike:s_aaac386c", -- You could say that. I am willing to pay good money for proof that you are taking care of this Jawa problem. You bring me proof that you are taking care of this Jawa problem and I will be more then happy to buy that proof from you.
	stopConversation = "false",
	options = {
		{"@conversation/junk_nathan_taike:s_34475b33", "ask_for_loot"}, -- What sort of proof are you looking for?
		{"@conversation/junk_nathan_taike:s_e613f19", "wrong"}, -- Sorry not really interested in this sort of dealing.
	}
}
junkDealerNathanConvoTemplate:addScreen(good_money);

wrong = ConvoScreen:new {
	id = "wrong",
	leftDialog = "@conversation/junk_nathan_taike:s_808503a8", -- I guess I was wrong about the whole hardened adventurer thing.
	stopConversation = "true",
	options = {}
}
junkDealerNathanConvoTemplate:addScreen(wrong);

ask_for_loot = ConvoScreen:new {
	id = "ask_for_loot",
	leftDialog = "@conversation/junk_nathan_taike:s_3b924e4a", -- Well I have to be sure of where you get this proof from so I am not going to accept any old junk. Bring me back some of those Jawa blasters or those beads that they wear and I will buy those from you.
	stopConversation = "false",
	options = {
		--{"@conversation/junk_nathan_taike:s_ecf19442", "start_sale"}, -- I think that I just might have some of this proof that you ask for.
		--{"@conversation/junk_nathan_taike:s_69567be7", "no_loot"}, -- Ok, I will see what I can do to help all you honest farmers out.
	}
}
junkDealerNathanConvoTemplate:addScreen(ask_for_loot);

no_loot = ConvoScreen:new {
	id = "no_loot",
	leftDialog = "@conversation/junk_nathan_taike:s_2d363db3", -- I knew from the moment I saw you that you were just the type that we needed.
	stopConversation = "true",
	options = {}
}
junkDealerNathanConvoTemplate:addScreen(no_loot);

start_sale = ConvoScreen:new {
	id = "start_sale",
	leftDialog = "@conversation/junk_nathan_taike:s_33db8b80", -- Let me see what you have. And let me tell you, no one is going to pay better then I do for this sort of stuff.
	stopConversation = "true",
	options = {}
}
junkDealerNathanConvoTemplate:addScreen(start_sale);

addConversationTemplate("junkDealerNathanConvoTemplate", junkDealerNathanConvoTemplate);
