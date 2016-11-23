heraldTatooine2ConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "herald_tatooine2_conv_handler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/heraldtatooine2:s_13fcbd87", -- Psst! Hey you! Yeah you! C'mere. You look as if you'd be suitable to join Jabba's forces. But keep your voice down. The Empire rules this place and doesn't take likely to members of the Hutt family.
	stopConversation = "false",
	options = {
		{"@conversation/heraldtatooine2:s_72ac291d", "not_exciting"}, -- I can already tell that I don't want to get into this mess.
		{"@conversation/heraldtatooine2:s_42bcb8b6", "talk_to_jabba"}, -- Yeah, I'm interested.
	}
}
heraldTatooine2ConvoTemplate:addScreen(init);

not_exciting = ConvoScreen:new {
	id = "not_exciting",
	leftDialog = "@conversation/heraldtatooine2:s_19ca58d8", -- You're not very exciting. I'll wait for someone else, then. Bye!
	stopConversation = "true",
	options = {}
}
heraldTatooine2ConvoTemplate:addScreen(not_exciting);

talk_to_jabba = ConvoScreen:new {
	id = "talk_to_jabba",
	leftDialog = "@conversation/heraldtatooine2:s_9ac6e8f5", -- Well, you'd have to talk to Jabba about that. I can't just sign you up. But I can tell you the location of our hideout. Maybe you can scope it out and see if you like it. It's gonna cost you, though. In fact, I have a couple of places you might be interested in.
	stopConversation = "false",
	options = {
		{"@conversation/heraldtatooine2:s_d0c6151b", "come_back"}, -- Sorry, don't have any credits on me.
		{"@conversation/heraldtatooine2:s_edb238bc", "list_locs"}, -- Go on.
	}
}
heraldTatooine2ConvoTemplate:addScreen(talk_to_jabba);

come_back = ConvoScreen:new {
	id = "come_back",
	leftDialog = "@conversation/heraldtatooine2:s_c599cc9e", -- Oh. Well, come back when you do. I have other deals to conduct.
	stopConversation = "true",
	options = {}
}
heraldTatooine2ConvoTemplate:addScreen(come_back);

list_locs = ConvoScreen:new {
	id = "list_locs",
	leftDialog = "@conversation/heraldtatooine2:s_f026df25", -- First, the Hutt Hideout. Yeah, I know. Selling out my own people. I have to make a living, you know! I also have information regarding the Rebel Military Base and a Tusken Bunker. What do y'say?
	stopConversation = "false",
	options = {
		{"@conversation/heraldtatooine2:s_7f115744", "sixty_credits"}, -- Hutt Hideout.
		{"@conversation/heraldtatooine2:s_8d322c6b", "thirty_fifty_credits"}, -- Rebel Military Base.
		{"@conversation/heraldtatooine2:s_d1f219dd", "thirty_credits"}, -- Tusken Bunker.
	}
}
heraldTatooine2ConvoTemplate:addScreen(list_locs);

sixty_credits = ConvoScreen:new {
	id = "sixty_credits",
	leftDialog = "@conversation/heraldtatooine2:s_5ee77a06", -- That'll be, uh.. 20 credits? No--60 credits!
	stopConversation = "false",
	options = {
		{"@conversation/heraldtatooine2:s_34cffb60", "so_cheap"}, -- No way!
		{"@conversation/heraldtatooine2:s_4ff8cd88", "sixty_credits_please"}, -- I suppose.
	}
}
heraldTatooine2ConvoTemplate:addScreen(sixty_credits);

so_cheap = ConvoScreen:new {
	id = "so_cheap",
	leftDialog = "@conversation/heraldtatooine2:s_6b184c6", -- You're so cheap! I'm desperate here! You think I'm going to sell out my own people for less than 60 credits? You're nuts! Get lost!
	stopConversation = "true",
	options = {}
}
heraldTatooine2ConvoTemplate:addScreen(so_cheap);

sixty_credits_please = ConvoScreen:new {
	id = "sixty_credits_please",
	leftDialog = "@conversation/heraldtatooine2:s_74ed5d50", -- 60 credits, please. And don't think about cheating on me, here. This information is dangerous to be passing around, especially without pay.
	stopConversation = "false",
	options = {
		--{"@conversation/heraldtatooine2:s_c3dbbcab", "loc1"}, -- Fine, here.
		--{"@conversation/heraldtatooine2:s_c3dbbcab", "no_money"}, -- Fine, here.
		--{"@conversation/heraldtatooine2:s_30c59b36", "sad_story"}, -- I don't have the money.
	}
}
heraldTatooine2ConvoTemplate:addScreen(sixty_credits_please);

loc1 = ConvoScreen:new {
	id = "loc1",
	leftDialog = "@conversation/heraldtatooine2:s_32a1ecd", -- Look at that. You actually have the money. Well, you didn't specify if you wanted a direct location, so I gave you a general location instead! HAHA! So long, sucker!
	stopConversation = "true",
	options = {}
}
heraldTatooine2ConvoTemplate:addScreen(loc1);

no_money = ConvoScreen:new {
	id = "no_money",
	leftDialog = "@conversation/heraldtatooine2:s_241afd0a", -- I didn't expect you to have the money. You're just a commoner, afterall.
	stopConversation = "true",
	options = {}
}
heraldTatooine2ConvoTemplate:addScreen(no_money);

sad_story = ConvoScreen:new {
	id = "sad_story",
	leftDialog = "@conversation/heraldtatooine2:s_3a28c7c4", -- That's a sad story. I'll find someone else to buy my information, then.
	stopConversation = "true",
	options = {}
}
heraldTatooine2ConvoTemplate:addScreen(sad_story);

thirty_fifty_credits = ConvoScreen:new {
	id = "thirty_fifty_credits",
	leftDialog = "@conversation/heraldtatooine2:s_ea388738", -- I'll give you the information for... 30 credits. That's right. 30 credits for a general location and 50 credits for an exact location.
	stopConversation = "false",
	options = {
		{"@conversation/heraldtatooine2:s_c41d4bce", "find_someone_else"}, -- No. I'm out of here.
		{"@conversation/heraldtatooine2:s_f2044f4a", "fifty_credits_please"}, -- I'll have... an exact location, please.
		{"@conversation/heraldtatooine2:s_b05cb415", "be_thirty_credits"}, -- Give me the "general location special".
	}
}
heraldTatooine2ConvoTemplate:addScreen(thirty_fifty_credits);

find_someone_else = ConvoScreen:new {
	id = "find_someone_else",
	leftDialog = "@conversation/heraldtatooine2:s_b81c8c9", -- I'll find someone else to buy my information!
	stopConversation = "true",
	options = {}
}
heraldTatooine2ConvoTemplate:addScreen(find_someone_else);

fifty_credits_please = ConvoScreen:new {
	id = "fifty_credits_please",
	leftDialog = "@conversation/heraldtatooine2:s_17daabb0", -- 50 credits, please.
	stopConversation = "false",
	options = {
		--{"@conversation/heraldtatooine2:s_4440ce87", "go_away"}, -- I changed my mind.
		--{"@conversation/heraldtatooine2:s_81a382e3", "loc2"}, -- Here you are.
		--{"@conversation/heraldtatooine2:s_81a382e3", "jip_me"}, -- Here you are.
	}
}
heraldTatooine2ConvoTemplate:addScreen(fifty_credits_please);

go_away = ConvoScreen:new {
	id = "go_away",
	leftDialog = "@conversation/heraldtatooine2:s_88788d03", -- Pfft! Go away. I see another client. I can't waste my time with you.
	stopConversation = "true",
	options = {}
}
heraldTatooine2ConvoTemplate:addScreen(go_away);

loc2 = ConvoScreen:new {
	id = "loc2",
	leftDialog = "@conversation/heraldtatooine2:s_c799721b", -- Ahh! I will download the information into your datapad. Thank you for your business!
	stopConversation = "true",
	options = {}
}
heraldTatooine2ConvoTemplate:addScreen(loc2);

jip_me = ConvoScreen:new {
	id = "jip_me",
	leftDialog = "@conversation/heraldtatooine2:s_1c6f5661", -- You don't have enough money. Are you trying to jip me? Who do you think I am? Get out of here!
	stopConversation = "true",
	options = {}
}
heraldTatooine2ConvoTemplate:addScreen(jip_me);

be_thirty_credits = ConvoScreen:new {
	id = "be_thirty_credits",
	leftDialog = "@conversation/heraldtatooine2:s_6cf09e8e", -- That'll be 30 credits. Do you have the money?
	stopConversation = "false",
	options = {
		--{"@conversation/heraldtatooine2:s_d9903b42", "loc3"}, -- Yes, I do. Here you are.
		--{"@conversation/heraldtatooine2:s_d9903b42", "dont_have_money"}, -- Yes, I do. Here you are.
		--{"@conversation/heraldtatooine2:s_fb859e03", "bury_you"}, -- Actually, I don't. Bye!
	}
}
heraldTatooine2ConvoTemplate:addScreen(be_thirty_credits);

loc3 = ConvoScreen:new {
	id = "loc3",
	leftDialog = "@conversation/heraldtatooine2:s_aae6686e", -- Excellent! The information has been downloaded. Thank you for your business! I hope you can find it okay! You should have paid for a direct location. HAH!
	stopConversation = "true",
	options = {}
}
heraldTatooine2ConvoTemplate:addScreen(loc3);

dont_have_money = ConvoScreen:new {
	id = "dont_have_money",
	leftDialog = "@conversation/heraldtatooine2:s_38bef1fe", -- What?! You don't have the money? Ugh! Go away!
	stopConversation = "true",
	options = {}
}
heraldTatooine2ConvoTemplate:addScreen(dont_have_money);

bury_you = ConvoScreen:new {
	id = "bury_you",
	leftDialog = "@conversation/heraldtatooine2:s_6892af1b", -- I hope the Hutts find you and bury you in the desert!
	stopConversation = "true",
	options = {}
}
heraldTatooine2ConvoTemplate:addScreen(bury_you);

thirty_credits = ConvoScreen:new {
	id = "thirty_credits",
	leftDialog = "@conversation/heraldtatooine2:s_5abff6d6", -- I ought to give you the location for free just to see you get a whoopin'! HA! Anyway, the Tusken Bunker is on sale for 30 credits. How about it?
	stopConversation = "false",
	options = {
		{"@conversation/heraldtatooine2:s_c885bfb0", "get_lost"}, -- I'm going to pass.
		{"@conversation/heraldtatooine2:s_8be640b8", "thatll_be_thirty"}, -- Sure.
	}
}
heraldTatooine2ConvoTemplate:addScreen(thirty_credits);

get_lost = ConvoScreen:new {
	id = "get_lost",
	leftDialog = "@conversation/heraldtatooine2:s_c9a787f0", -- Fine, then. Get lost. I'm trying to run a business here.
	stopConversation = "true",
	options = {}
}
heraldTatooine2ConvoTemplate:addScreen(get_lost);

thatll_be_thirty = ConvoScreen:new {
	id = "thatll_be_thirty",
	leftDialog = "@conversation/heraldtatooine2:s_3d3f67a4", -- That'll be... 30 credits!
	stopConversation = "false",
	options = {
		--{"@conversation/heraldtatooine2:s_63855d3f", "not_surprised"}, -- Oh, look at that. I don't have the money.
		--{"@conversation/heraldtatooine2:s_177f6371", "loc4"}, -- I guess. Here.
		--{"@conversation/heraldtatooine2:s_177f6371", "cheapskate"}, -- I guess. Here.
	}
}
heraldTatooine2ConvoTemplate:addScreen(thatll_be_thirty);

not_surprised = ConvoScreen:new {
	id = "not_surprised",
	leftDialog = "@conversation/heraldtatooine2:s_c9ff39ea", -- I'm not surprised.
	stopConversation = "true",
	options = {}
}
heraldTatooine2ConvoTemplate:addScreen(not_surprised);

loc4 = ConvoScreen:new {
	id = "loc4",
	leftDialog = "@conversation/heraldtatooine2:s_5d7da0", -- Thank you! Here's your information. Now, get lost. I have other business to attend to.
	stopConversation = "true",
	options = {}
}
heraldTatooine2ConvoTemplate:addScreen(loc4);

cheapskate = ConvoScreen:new {
	id = "cheapskate",
	leftDialog = "@conversation/heraldtatooine2:s_e3dda380", -- I should--ugh! You don't have enough money! Get lost, you cheapskate!
	stopConversation = "true",
	options = {}
}
heraldTatooine2ConvoTemplate:addScreen(cheapskate);

addConversationTemplate("heraldTatooine2ConvoTemplate", heraldTatooine2ConvoTemplate);
