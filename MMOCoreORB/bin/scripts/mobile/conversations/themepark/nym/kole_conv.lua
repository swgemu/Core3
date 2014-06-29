koleConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "theme_park_nym_conv_handler",
	screens = {}
}

----------
--Kole convo if Jinkins quest not done
----------
quest_tease = ConvoScreen:new {
	id = "quest_tease",
	leftDialog = "@celebrity/kole:quest_tease", -- I ain't got nothing for you yet. Go talk to Jinkins. He's always handing out blue milk runs for outlanders like you.
	stopConversation = "true",
	options = {
	}
}
koleConvoTemplate:addScreen(quest_tease);

----------
--Kole convos if quest done
----------
good_work = ConvoScreen:new {
	id = "good_work",
	leftDialog = "@celebrity/kole:good_work", -- I wasn't sure about you, but recoverin' that gas from the mining facility was a pretty dangerous mission. I'm actually surprised you survived. Good work.
	stopConversation = "false",
	options = {
		{"@celebrity/kole:what_now", "youre_done"}, -- What should I do now?
		{"@celebrity/kole:see_ya", "good_bye"}, -- I'll talk to you later.
	}
}
koleConvoTemplate:addScreen(good_work);

youre_done = ConvoScreen:new {
	id = "youre_done",
	leftDialog = "@celebrity/kole:youre_done", -- I don't have any more assignments, but Nym wants to talk to you.
	stopConversation = "false",
	options = {
		{"@celebrity/kole:see_ya", "good_bye"}, -- I'll talk to you later.
	}
}
koleConvoTemplate:addScreen(youre_done);

good_bye = ConvoScreen:new {
	id = "good_bye",
	leftDialog = "@celebrity/kole:good_bye", -- Good luck, fringer.
	stopConversation = "true",
	options = {
	}
}
koleConvoTemplate:addScreen(good_bye);

----------
--Kole main convo
----------
first_time_hello = ConvoScreen:new {
	id = "first_time_hello",
	leftDialog = "@celebrity/kole:first_time_hello", -- Eh, what do we have here? Some soft outlander that has crawled into our stronghold? What do you want, fringer?
	stopConversation = "false",
	options = {
		{"@celebrity/kole:who_are_you", "im_kole"}, -- Who are you?
	}
}
koleConvoTemplate:addScreen(first_time_hello);

im_kole = ConvoScreen:new {
	id = "im_kole",
	leftDialog = "@celebrity/kole:im_kole", -- According to the Imperial criminal databank, my name's Kole, and that's the only name you need to know. I'm Nym's first mate, which means that I slip a vibro-blade between the ribs of anyone who he don't like. So watch yourself. Me and Jinkins, we've been around long enough to bury hundreds of outlanders just like you.
	stopConversation = "false",
	options = {
		{"@celebrity/kole:who_is_nym", "nym_is_chief"}, -- Tell me about Nym.
		{"@celebrity/kole:who_is_jinkins", "jinkins_is_friend"}, -- Who is Jinkins?
	}
}
koleConvoTemplate:addScreen(im_kole);

jinkins_is_friend = ConvoScreen:new {
	id = "jinkins_is_friend",
	leftDialog = "@celebrity/kole:jinkins_is_friend", -- Jinkins is the bald Bith standing over there. He's Nym's chief engineer, builds us our weapons and droids. He don't have that killer instinct, but he does have something more dangerous: information. In fact, he's probably got some work for you, if you're lucky.
	stopConversation = "false",
	options = {
		{"@celebrity/kole:who_is_nym", "nym_is_chief"}, -- Tell me about Nym.
	}
}
koleConvoTemplate:addScreen(jinkins_is_friend);

nym_is_chief = ConvoScreen:new {
	id = "nym_is_chief",
	leftDialog = "@celebrity/kole:nym_is_chief", -- Nym's the captain of the Lok Revenants, our crew. Before that thing on Naboo, we was pirates, mainly robbing freighters that passed by Lok. But then Nym went to war with the Trade Federation. It took ten years, but we finally chewed through the droids and spit 'em out of the system. Nym's been like the king of Lok ever since.
	stopConversation = "false",
	options = {
		{"@celebrity/kole:who_is_jinkins", "jinkins_is_friend"}, -- Who is Jinkins?
	}
}
koleConvoTemplate:addScreen(nym_is_chief);

quest_info = ConvoScreen:new {
	id = "quest_info",
	leftDialog = "@celebrity/kole:quest_info", -- Good. I need you to check something out for us. Jinkins sliced some data from an Imperial droid and found out that it was on a ship trying to escape an Imperial mining installation here on Lok. Imperial labor camps ain't known for their safe working conditions... The droid says the miners hit some sort of gas pocket. The entire work crew had their brains boiled. They survived, but they're crazy. And the droid thinks that some of the Imperial officers were infected too. Any gas that drives Imperials out of their minds is a good thing to have around, so we want some samples of it.
	stopConversation = "false",
	options = {
		{"@celebrity/kole:dangerous_gas", "miners"}, -- How dangerous is this gas?
	}
}
koleConvoTemplate:addScreen(quest_info);

miners = ConvoScreen:new {
	id = "miners",
	leftDialog = "@celebrity/kole:miners", -- It looks like the mine has a cheap air filtration system. It barely meets Imperial code and didn't stop the gas from infecting the miners. But Jinkins thinks the filters trapped some of the gas. Just find the filtration system and look for some kinda sealed container. Oh, and now that the filters have had some time do their work, the air down there should be clean. If you're lucky, anyway.
	stopConversation = "false",
	options = {
		{"@celebrity/kole:mining_facility", "gas_info"}, -- Won't the facility be filled with poison?
	}
}
koleConvoTemplate:addScreen(miners);

gas_info = ConvoScreen:new {
	id = "gas_info",
	leftDialog = "@celebrity/kole:gas_info", -- You scared? I said don't worry about the gas. The filters should have scrubbed the air clean by now. The real danger is gonna be the miners. The gas has poisoned their brains. They've taken over the mine and will attack anyone who comes near the place. They're like wild dinkos...
	stopConversation = "false",
	options = {
		{"@celebrity/kole:ill_get_gas", "here_is_gas"}, -- Well, I can take a shot at getting this gas...
	}
}
koleConvoTemplate:addScreen(gas_info);

droid_info = ConvoScreen:new {
	id = "droid_info",
	leftDialog = "@celebrity/kole:droid_info", -- Since the imperials aren't sure what's going on with the mine, they've sent some of their droids to monitor the situation.  You may have to deal with them as well.
	stopConversation = "false",
	options = {
		{"@celebrity/kole:imperial_involvement", "imperial_stuff"}, -- What kind of droids?
	}
}
koleConvoTemplate:addScreen(droid_info);

imperial_stuff = ConvoScreen:new {
	id = "imperial_stuff",
	leftDialog = "@celebrity/kole:imperial_stuff", -- We don't know, exactly. But we do have an ex-Imperial in our pocket who might have some information for you. Sergeant Moore owes Nym several thousand credits. He'll probably tell you whatever you need to know, for a price. Since he left the Imperial army, he spends most of his time in the cantina.
	stopConversation = "false",
	options = {
		{"@celebrity/kole:resigned_officer", "officer_info"}, -- Why did he leave the army?
	}
}
koleConvoTemplate:addScreen(imperial_stuff);

officer_info = ConvoScreen:new {
	id = "officer_info",
	leftDialog = "@celebrity/kole:officer_info", -- The Empire found out that he was borrowing credits from Nym. He was going to be executed, but he has friends in the Tagge family. They put in a good word, and Moore was kicked out instead of killed. But, he still has good information about the Empire's droids.
	stopConversation = "false",
	options = {
		{"@celebrity/kole:ill_see_imperial", "here_is_imperial"}, -- Maybe I should go talk to him.
	}
}
koleConvoTemplate:addScreen(officer_info);

here_is_imperial = ConvoScreen:new {
	id = "here_is_imperial",
	leftDialog = "@celebrity/kole:here_is_imperial", -- I'll give you a waypoint to the cantina where he hangs out. He might be able to tell you about the droids or the mining facility.
	stopConversation = "false",
	options = {
		{"@celebrity/kole:anything_else", "not_really"}, -- Is there anything else you can tell me?
	}
}
koleConvoTemplate:addScreen(here_is_imperial);

here_is_gas = ConvoScreen:new {
	id = "here_is_gas",
	leftDialog = "@celebrity/kole:here_is_gas", -- Good. I'm gonna mark the location of the mine in your datapad. This will be a tough mission, though; if you have any friends, you'd might want to ask for their help. Or least tell them how you want your remains handled.
	stopConversation = "false",
	options = {
		{"@celebrity/kole:probe_droid", "droid_info"}, -- What other threats are out there?
	}
}
koleConvoTemplate:addScreen(here_is_gas);

not_really = ConvoScreen:new {
	id = "not_really",
	leftDialog = "@celebrity/kole:not_really", -- No. You've heard everything you need to know.
	stopConversation = "true",
	options = {
	}
}
koleConvoTemplate:addScreen(not_really);

-----------
-- Kole quest in progress
-----------

bring_gas = ConvoScreen:new {
	id = "bring_gas",
	leftDialog = "@celebrity/kole:bring_gas", -- Did you bring me the gas?
	stopConversation = "false",
	options = {
		{"@celebrity/kole:tell_me_again", "quest_info_again"}, -- Explain to me again what I need to do...
		{"@celebrity/kole:yes", "hand_it_over"}, -- Yeah, I have it here...
		{"@celebrity/kole:no", "get_back_to_work"}, -- No, I didn't get it yet.
	}
}
koleConvoTemplate:addScreen(bring_gas);

quest_info_again = ConvoScreen:new {
	id = "quest_info_again",
	leftDialog = "@celebrity/kole:quest_info_again", -- I want you to grab an "insanity gas" from a mine full of deranged miners. Find the filtration system and get a canister of that gas.
	stopConversation = "true",
	options = {
	}
}
koleConvoTemplate:addScreen(quest_info_again);

hand_it_over = ConvoScreen:new {
	id = "hand_it_over",
	leftDialog = "@celebrity/kole:hand_it_over", -- Good. Now, just give me the canister...
	stopConversation = "true",
	options = {
	}
}
koleConvoTemplate:addScreen(hand_it_over);

get_back_to_work = ConvoScreen:new {
	id = "get_back_to_work",
	leftDialog = "@celebrity/kole:get_back_to_work", -- Then get back out there and find it.. Look in the mine's filtration system.
	stopConversation = "true",
	options = {
	}
}
koleConvoTemplate:addScreen(get_back_to_work);

addConversationTemplate("koleConvoTemplate", koleConvoTemplate);
