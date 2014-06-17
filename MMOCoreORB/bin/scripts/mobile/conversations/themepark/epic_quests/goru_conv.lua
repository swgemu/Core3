goruConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "epic_quest_zicx_bug_bomb_goru",
	screens = {}
}

omg_dont_kill_me = ConvoScreen:new {
	id = "omg_dont_kill_me",
	leftDialog = "@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:omg_dont_kill_me", -- Oh no! They sent you to kill me didn't they?! I knew that those bloodthirsty thugs would catch up to me some day.
	stopConversation = "false",
	options = {
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:what_thugs", "all_thugs"}, -- What bloodthirsty thugs are you talking about?
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:make_me_a_bomb", "bombs_are_cool"}, -- I want you to make something for me. A special weapon.
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:just_passing", "dont_tell_anyone"}, -- Relax, old man. I'm just passing through.
	}
}
goruConvoTemplate:addScreen(omg_dont_kill_me);

all_thugs = ConvoScreen:new {
	id = "all_thugs",
	leftDialog = "@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:all_thugs", -- The Empire, the Rebellion, the Hutts, the Black Sun... my enemies are everywhere. Seems everyone has a vibro-axe to grind for one thing or another that I did in my youth. What are you here for if not to kill me?
	stopConversation = "false",
	options = {
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:make_me_a_bomb", "bombs_are_cool"}, -- I want you to make something for me. A special weapon.
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:just_passing", "dont_tell_anyone"}, -- Relax, old man. I'm just passing through.
	}
}
goruConvoTemplate:addScreen(all_thugs);

bombs_are_cool = ConvoScreen:new {
	id = "bombs_are_cool",
	leftDialog = "@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:bombs_are_cool", -- Oh so my life is worth something to you, yes? (Just like the old days) If you mean the Zicx bug bomb, I can make it for you. It requires the bile of a mature Sarlacc, and a hearty measure of live Zicx. But... heh... there are no Zicx and no Sarlacc on this planet. You must visit my friend Jowir Ar'Lensa on Tatooine. Give him one of my calling cards and he can help you.
	stopConversation = "false",
	options = {
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:where_is_jowir", "in_wayfar"}, -- Where can I find Jowir on Tatooine?
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:sarlacc_bile", "no_idea"}, -- How do I get bile from a Sarlacc?
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:no_thanks", "go_away_then"}, -- No, thanks for offering though.
	}
}
goruConvoTemplate:addScreen(bombs_are_cool);

in_wayfar = ConvoScreen:new {
	id = "in_wayfar",
	leftDialog = "@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:in_wayfar", -- Like me, he has made many powerful enemies on both sides of the war. Fortunately, his research is valuable to the Hutts - so they're protecting him. He is apparently working on some special process that drastically improves the effectiveness of certain varieties of spice. He lives somewhere in the town of Wayfar... I think.
	stopConversation = "false",
	options = {
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:on_my_way", "hurry_up"}, -- I'll be on my way, then.
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:sarlacc_bile", "no_idea"}, -- How do I get bile from a Sarlacc?
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:no_thanks", "go_away_then"}, -- No, thanks for offering though.
	}
}
goruConvoTemplate:addScreen(in_wayfar);

no_idea = ConvoScreen:new {
	id = "no_idea",
	leftDialog = "@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:no_idea", -- Like me, he has made many powerful enemies on both sides of the war. Fortunately, his research is valuable to the Hutts - so they're protecting him. He is apparently working on some special process that drastically improves the effectiveness of certain varieties of spice. He lives somewhere in the town of Wayfar... I think.
	stopConversation = "false",
	options = {
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:on_my_way", "hurry_up"}, -- I'll be on my way, then.
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:where_is_jowir", "in_wayfar"}, -- Where can I find Jowir on Tatooine?
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:no_thanks", "go_away_then"}, -- No, thanks for offering though.
	}
}
goruConvoTemplate:addScreen(no_idea);

go_away_then = ConvoScreen:new {
	id = "go_away_then",
	leftDialog = "@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:go_away_then", -- Don't waste any more of my time then, please.
	stopConversation = "true",
	options = {
	}
}
goruConvoTemplate:addScreen(go_away_then);

dont_tell_anyone = ConvoScreen:new {
	id = "dont_tell_anyone",
	leftDialog = "@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:dont_tell_anyone", -- Good. Please don't tell anyone that you know of me. I can exchange a very powerful and rare weapon for your silence. Are you interested?
	stopConversation = "false",
	options = {
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:what_weapon", "zicx_bomb"}, -- What is this weapon?
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:still_passing", "go_away_then"}, -- No thanks. Like I said, I'm just passing through.
	}
}
goruConvoTemplate:addScreen(dont_tell_anyone);

zicx_bomb = ConvoScreen:new {
	id = "zicx_bomb",
	leftDialog = "@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:zicx_bomb", -- The infamous Zicx grenade. Outlawed by the Empire, reviled by the Alliance... and coveted by the Hutts and Black Sun. I still have many of the original explosive case prototypes. The critical components are missing, though. I need a bunch of live Zicx and a jar of Sarlacc bile. Together with the special firing mechanism and casing, I'll craft an outstanding weapon for you.
	stopConversation = "false",
	options = {
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:sounds_good", "see_jowir"}, -- Sounds good. Where do I start?
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:still_passing", "go_away_then"}, -- No thanks. Like I said, I'm just passing through.
	}
}
goruConvoTemplate:addScreen(zicx_bomb);

see_jowir = ConvoScreen:new {
	id = "see_jowir",
	leftDialog = "@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:see_jowir", -- Go see my friend Jowir Ar'Lensa on Tatooine. You'll find him hiding out in Wayfar - protected by the Hutts. He is researching insects to help enhance spice production... so they keep him safe. Give him my calling card. Tell him that you want the Zicx and he will help you.
	stopConversation = "false",
	options = {
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:on_my_way", "hurry_up"}, -- I'll be on my way, then.
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:still_passing", "go_away_then"}, -- No thanks. Like I said, I'm just passing through.
	}
}
goruConvoTemplate:addScreen(see_jowir);

are_you_done = ConvoScreen:new {
	id = "are_you_done",
	leftDialog = "@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:are_you_done", -- Have you found all the ingredients we need? When you get them, just hand them to me.
	stopConversation = "false",
	options = {
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:need_help", "more_info"}, -- I need to be reminded what I'm doing...
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:need_more_time", "hurry_up"}, -- I need some more time to get this done.
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:i_quit", "fine_quit_then"}, -- Sorry, I can't keep doing this work.
	}
}
goruConvoTemplate:addScreen(are_you_done);

more_info = ConvoScreen:new {
	id = "more_info",
	leftDialog = "@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:more_info", -- The Zicx Bug Bomb requires the bile of a mature Sarlacc, and a hearty measure of live Zicx. But... heh... there are no Zicx and no Sarlacc on this planet. You must visit my friend Jowir Ar'Lensa on Tatooine. Give him one of my calling cards and he can help you.
	stopConversation = "false",
	options = {
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:on_my_way", "hurry_up"}, -- I'll be on my way, then.
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:i_quit", "fine_quit_then"}, -- Sorry, I can't keep doing this work.
	}
}
goruConvoTemplate:addScreen(more_info);

fine_quit_then = ConvoScreen:new {
	id = "fine_quit_then",
	leftDialog = "@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:fine_quit_then", -- I don't care what you do, just stop bothering me.
	stopConversation = "true",
	options = {
	}
}
goruConvoTemplate:addScreen(fine_quit_then);

get_the_bile = ConvoScreen:new {
	id = "get_the_bile",
	leftDialog = "@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:get_the_bile", -- You gave me the Zicx, but I still need the Sarlacc bile in order to make your weapon.
	stopConversation = "false",
	options = {
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:ill_get_bile", "hurry_up"}, -- I'll go get the zicx for you.
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:i_quit", "fine_quit_then"}, -- Sorry, I can't keep doing this work.
	}
}
goruConvoTemplate:addScreen(get_the_bile);

get_the_bugs = ConvoScreen:new {
	id = "get_the_bugs",
	leftDialog = "@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:get_the_bugs", -- You gave me the Sarlacc digestive fluid, but I still need the Zicx to complete your weapon.
	stopConversation = "false",
	options = {
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:ill_get_bile", "hurry_up"}, -- I'll go get the zicx for you.
		{"@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:i_quit", "fine_quit_then"}, -- Sorry, I can't keep doing this work.
	}
}
goruConvoTemplate:addScreen(get_the_bugs);

heres_your_bomb = ConvoScreen:new {
	id = "heres_your_bomb",
	leftDialog = "@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:heres_your_bomb", -- It's ready, now! Here you go... Remember - you don't know me. You've never heard of me... and you definitely did not get this special weapon from me. Farewell.
	stopConversation = "true",
	options = {
	}
}
goruConvoTemplate:addScreen(heres_your_bomb);

please_begone = ConvoScreen:new {
	id = "please_begone",
	leftDialog = "@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:please_begone", -- Please... begone! I can't keep making these weapons for you. People will find out about me - and then I'll make weapons for NO ONE! Goodbye.
	stopConversation = "true",
	options = {
	}
}
goruConvoTemplate:addScreen(please_begone);

hurry_up = ConvoScreen:new {
	id = "hurry_up",
	leftDialog = "@epic_quest/zicx_bug_bomb/rori_goru_rainstealer:hurry_up", -- Please, don't take too long. I'm worried that someone will find me.
	stopConversation = "true",
	options = {
	}
}
goruConvoTemplate:addScreen(hurry_up);

addConversationTemplate("goruConvoTemplate", goruConvoTemplate);