tutorialBankerConvoTemplate = ConvoTemplate:new {
	initialScreen = "intro",
	templateType = "Lua",
	luaClassHandler = "conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_1_start", -- Well it seems your ship wasn't carrying contraband after all. Pity we didn't discover that sooner...
	stopConversation = "false",
	options = {
		{ "@newbie_tutorial/newbie_convo:banker_1_reply_1", "suspected_smuggling" }, -- What did you do to my ship?
		{ "@newbie_tutorial/newbie_convo:banker_1_reply_2", "explain_terminals" }, -- What is this terminal for?
	}
}
tutorialBankerConvoTemplate:addScreen(intro);

suspected_smuggling = ConvoScreen:new {
	id = "suspected_smuggling",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_2_start", -- Well we suspected you were smuggling, so we boarded the transport you were travelling aboard, of course. Don't worry, we've cleared you of all charges.
	stopConversation = "false",
	options = {
		{ "@newbie_tutorial/newbie_convo:banker_2_reply_1", "afraid_not" }, -- Can I get back on board the transport now?
	}
}
tutorialBankerConvoTemplate:addScreen(suspected_smuggling);

afraid_not = ConvoScreen:new {
	id = "afraid_not",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_2_more", -- I'm afraid not. It seems your ship was badly damaged and most of your possessions were destroyed.
	stopConversation = "false",
	options = {
		{ "@newbie_tutorial/newbie_convo:banker_2_reply_2", "dont_worry" }, -- What am I supposed to do now?
	}
}
tutorialBankerConvoTemplate:addScreen(afraid_not);

dont_worry = ConvoScreen:new {
	id = "dont_worry",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_2_explain", -- Don't worry! We've taken care of everything. We've given you more than enough credits to reimburse you for your loss. You can deposit them at this banking terminal.
	stopConversation = "false",
	options = {
		{ "@newbie_tutorial/newbie_convo:banker_2_reply_3", "buy_what_you_need" }, -- What about my supplies and equipment?
	}
}
tutorialBankerConvoTemplate:addScreen(dont_worry);

buy_what_you_need = ConvoScreen:new {
	id = "buy_what_you_need",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_2_explain_2", -- When you get to a planet, look for a commodities market and buy anything you might possibly need.
	stopConversation = "true",
	options = {}
}
tutorialBankerConvoTemplate:addScreen(buy_what_you_need);

explain_terminals = ConvoScreen:new {
	id = "explain_terminals",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_2_explain_terminals", -- For your convenience, we'll allow you to access this starport's bank terminal.
	stopConversation = "false",
	options = {
		{ "@newbie_tutorial/newbie_convo:banker_1_reply_3", "explain_bank" }, -- Bank?
		{ "@newbie_tutorial/newbie_convo:banker_1_reply_4", "explain_bazaar" }, -- Item dispenser?
	}
}
tutorialBankerConvoTemplate:addScreen(explain_terminals);

explain_bank = ConvoScreen:new {
	id = "explain_bank",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_2_explain_bank", -- Once we realized you were innocent, we reimbursed you with a generous number of credits for the destruction of your gear. You can deposit them in this bank terminal.
	stopConversation = "false",
	options = {
		{ "@newbie_tutorial/newbie_convo:banker_bank_reply_1", "explain_why_bank" }, -- Why should I bank?
	}
}
tutorialBankerConvoTemplate:addScreen(explain_bank);

explain_why_bank = ConvoScreen:new {
	id = "explain_why_bank",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_2_more_bank", -- You should definitely use the bank's safety deposit feature to keep your items safe from harm. It's also a good idea to deposit your credits into your bank accout before shopping at the commodities market since the market deducts credits from your bank account for all purchases.
	stopConversation = "false",
	options = {
		{ "@newbie_tutorial/newbie_convo:banker_2_bank_question", "explain_bank_deduction" }, -- What if I want to buy something?
	}
}
tutorialBankerConvoTemplate:addScreen(explain_why_bank);

explain_bank_deduction = ConvoScreen:new {
	id = "explain_bank_deduction",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_2_bank_answer", -- You don't need cash on hand to buy things. You can purchase items from the commodities market on any planet, and the credits will be deducted from your bank automatically.
	stopConversation = "false",
	options = {
		{ "@newbie_tutorial/newbie_convo:banker_bank_question_2", "explain_bank_store" }, -- Can I store items in the bank?
	}
}
tutorialBankerConvoTemplate:addScreen(explain_bank_deduction);

explain_bank_store = ConvoScreen:new {
	id = "explain_bank_store",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_bank_answer_2", -- Any items you store in this bank will be transferred to your new bank. Once you get to your planet, join any bank there and we'll send these items along.
	stopConversation = "true",
	options = {}
}
tutorialBankerConvoTemplate:addScreen(explain_bank_store);

explain_bazaar = ConvoScreen:new {
	id = "explain_bazaar",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_bazaar_1", -- Once you've deposited your money at the bank terminal, browse the Item Dispenser to see if there is any equipment you'd like to purchase.
	stopConversation = "false",
	options = {
		{ "@newbie_tutorial/newbie_convo:banker_bazaar_reply_1", "more_than_generous" }, -- You didn't give me very much money.
	}
}
tutorialBankerConvoTemplate:addScreen(explain_bazaar);

more_than_generous = ConvoScreen:new {
	id = "more_than_generous",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_bazaar_2", -- I think The Empire is being more than generous. Do you know how much it cost us to capture the transport you were on, kill the crew, search for secret cargo holds... not to mention pulling you out of the fire!
	stopConversation = "false",
	options = {
		{ "@newbie_tutorial/newbie_convo:banker_bazaar_reply_2", "how_should_we_know" }, -- But that transport wasn't smuggling anything!
	}
}
tutorialBankerConvoTemplate:addScreen(more_than_generous);

how_should_we_know = ConvoScreen:new {
	id = "how_should_we_know",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_bazaar_3", -- Ah, but now, how were we supposed to know that without capturing the transport first?
	stopConversation = "true",
	options = {}
}
tutorialBankerConvoTemplate:addScreen(how_should_we_know);

addConversationTemplate("tutorialBankerConvoTemplate", tutorialBankerConvoTemplate);
