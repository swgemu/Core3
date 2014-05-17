sergeantMooreConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "theme_park_nym_conv_handler",
	screens = {}
}

leave_me_alone = ConvoScreen:new {
	id = "leave_me_alone",
	leftDialog = "@celebrity/imperial_bribe:leave_me_alone", -- Go away.  I'm not talking to anyone today.
	stopConversation = "false",
	options = {
	}
}
sergeantMooreConvoTemplate:addScreen(leave_me_alone);

nunya = ConvoScreen:new {
	id = "nunya",
	leftDialog = "@celebrity/imperial_bribe:nunya", -- Who are you? Some sort of Imperial assassin? I'm not going to make your job easier by confirming my identity. Now leave me alone.
	stopConversation = "true",
	options = {
	}
}
sergeantMooreConvoTemplate:addScreen(nunya);

what_you_got = ConvoScreen:new {
	id = "what_you_got",
	leftDialog = "@celebrity/imperial_bribe:what_you_got", -- Credits, eh? I am a bit light in the pocket today. But the price of knowledge is steep. What are you offering?
	stopConversation = "false",
	options = {
	}
}
sergeantMooreConvoTemplate:addScreen(what_you_got);

you_got_nothing = ConvoScreen:new {
	id = "you_got_nothing",
	leftDialog = "@celebrity/imperial_bribe:you_got_nothing", -- You don't have any money!
	stopConversation = "true",
	options = {
	}
}
sergeantMooreConvoTemplate:addScreen(you_got_nothing);

the_good_stuff = ConvoScreen:new {
	id = "the_good_stuff",
	leftDialog = "@celebrity/imperial_bribe:the_good_stuff", -- Alright. I can tell you that I worked for an Imperial Research base, but that we didn't use requisitioned Imperial soldiers for guards. Instead, we hired the most dangerous mercenaries we could find. The base is also guarded by reprogrammed droidekas that assaults anyone who approaches. The droidekas are so efficient we sent some to the Imperial mines as well as some places on Dantooine...
	stopConversation = "false",
	options = {
		{"@celebrity/imperial_bribe:tell_me_droideka", "droideka_story_long"}, -- Dantooine?
		{"@celebrity/imperial_bribe:tell_me_base", "base_story_long"}, -- Tell me about the base and its guards.
	}
}
sergeantMooreConvoTemplate:addScreen(the_good_stuff);

droideka_story_long = ConvoScreen:new {
	id = "droideka_story_long",
	leftDialog = "@celebrity/imperial_bribe:droideka_story_long", -- Sure.  There's a bio-genics research facil- er...nevermind.
	stopConversation = "false",
	options = {
	}
}
sergeantMooreConvoTemplate:addScreen(droideka_story_long);

base_story_long = ConvoScreen:new {
	id = "base_story_long",
	leftDialog = "@celebrity/imperial_bribe:base_story_long", -- The base is actually one of the Imperial Inquisitors' pet projects. They chose to build the facility on Lok because the planet has an abundance of noxious chemicals. However, the Inquisitors loathe General Otto, who is technically in power here. They believe he has a brain the size of a meewit, and I'm inclined to agree. In order to bypass Otto and avoid his meddling, the Inquisitors avoided all official requisitions when building the facility. Freelance engineers were hired to build the base, and brutal mercenaries prevent any Rebel spies from interfering with the research. The plan seems to be working: I doubt Otto even realizes that the base exists.
	stopConversation = "false",
	options = {
	}
}
sergeantMooreConvoTemplate:addScreen(base_story_long);

thats_all = ConvoScreen:new {
	id = "thats_all",
	leftDialog = "@celebrity/imperial_bribe:thats_all", -- Now go. I can't be seen talking to the likes of you.
	stopConversation = "true",
	options = {
	}
}
sergeantMooreConvoTemplate:addScreen(thats_all);

medium_info = ConvoScreen:new {
	id = "medium_info",
	leftDialog = "@celebrity/imperial_bribe:medium_info", -- A modest fee. You'll probably want to know about the Imperial facility where I once served the Empire. The base guarded by droidekas? Is that what you're here for?
	stopConversation = "false",
	options = {
		{"@celebrity/imperial_bribe:short_base_info", "short_base_story"}, -- Tell me about the Imperial base.
		{"@celebrity/imperial_bribe:short_droideka_info", "short_droideka_story"}, -- Droidekas?
	}
}
sergeantMooreConvoTemplate:addScreen(medium_info);

short_base_story = ConvoScreen:new {
	id = "short_base_story",
	leftDialog = "@celebrity/imperial_bribe:short_base_story", -- It's a research facility. That's all I can reveal. The base is responsible for manufacturing high-grade explosives for the Empire, including grenades. But there is no obvious Imperial presence at the base. No Imperial soldiers, no guards. The entire base is staffed by freelance mercenaries.
	stopConversation = "false",
	options = {
		{"@celebrity/imperial_bribe:tell_me_more_base", "need_more_money"}, -- No Imperials at the base? Explain.
	}
}
sergeantMooreConvoTemplate:addScreen(short_base_story);

short_droideka_story = ConvoScreen:new {
	id = "short_droideka_story",
	leftDialog = "@celebrity/imperial_bribe:short_droideka_story", -- Yes, the so-called "destroyer droids" used by the Trade Federation during the Clone Wars. The Empire has a stockpile of the droids and has reprogrammed them to guard various installations across the galaxy, including the research station and a mine here on Lok. The droidekas are programmed to attack anyone who shouldn't be there. They work so well, we also sent some to the mine to guard the slaves there.
	stopConversation = "false",
	options = {
		{"@celebrity/imperial_bribe:tell_me_more_droideka", "need_more_cash"}, -- How can I get past the Droideka?
	}
}
sergeantMooreConvoTemplate:addScreen(short_droideka_story);

need_more_money = ConvoScreen:new {
	id = "need_more_money",
	leftDialog = "@celebrity/imperial_bribe:need_more_money",
	stopConversation = "false",
	options = {
	-- Add this via conv handler, need to check for credits. if none then return you_got_nothing
	--{"@celebrity/imperial_bribe:add_100_bribe", "end_base_info"}, -- What about another 100 credits?
	}
}
sergeantMooreConvoTemplate:addScreen(need_more_money);

need_more_cash = ConvoScreen:new {
	id = "need_more_cash",
	leftDialog = "@celebrity/imperial_bribe:need_more_cash",
	stopConversation = "false",
	options = {
	-- Add this via conv handler, need to check for credits. if none then return you_got_nothing
	--{"@celebrity/imperial_bribe:add_100_bribe", "end_base_info"}, -- What about another 100 credits?
	}
}
sergeantMooreConvoTemplate:addScreen(need_more_cash);

end_base_info = ConvoScreen:new {
	id = "end_base_info",
	leftDialog = "@celebrity/imperial_bribe:end_base_info", -- There's a feud between General Otto and other Imperials. To keep Otto from meddling in the affairs of the Lok research facility, it was built it in relative secrecy and staffed it with mercenaries rather than requisitioned soldiers.
	stopConversation = "false",
	options = {
		{"@celebrity/imperial_bribe:anymore_base", "no_more_base"}, -- Can you tell me anything else about the base?
	}
}
sergeantMooreConvoTemplate:addScreen(end_base_info);

no_more_base = ConvoScreen:new {
	id = "no_more_base",
	leftDialog = "@celebrity/imperial_bribe:no_more_base", -- That's all I'm saying. You don't need to know any more than that.
	stopConversation = "false",
	options = {
	}
}
sergeantMooreConvoTemplate:addScreen(no_more_base);

end_droideka_info = ConvoScreen:new {
	id = "end_droideka_info",
	leftDialog = "@celebrity/imperial_bribe:end_droideka_info", -- There's no option but to fight it.  But that Droideka, it's pretty tough.  I think they've made some special mods to it.  I'm not saying what, I'm just saying I heard...
	stopConversation = "false",
	options = {
		{"@celebrity/imperial_bribe:anymore_droideka", "no_more_droideka"}, --How can I destroy the Droideka?
	}
}
sergeantMooreConvoTemplate:addScreen(end_droideka_info);

no_more_droideka = ConvoScreen:new {
	id = "no_more_droideka",
	leftDialog = "@celebrity/imperial_bribe:no_more_droideka", -- I'm not saying anything else.  Sorry.
	stopConversation = "false",
	options = {
	}
}
sergeantMooreConvoTemplate:addScreen(no_more_droideka);

addConversationTemplate("sergeantMooreConvoTemplate", sergeantMooreConvoTemplate);
