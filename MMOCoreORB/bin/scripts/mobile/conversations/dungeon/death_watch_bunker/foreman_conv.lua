deathWatchForemanConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "deathWatchForemanConvoHandler",
	screens = {}
}


init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/death_watch_foreman:s_8dc6968d", -- Hey, what are you doing down here? You shouldn't be walking around down here unless you are working or the Mandalorians authorized you to be here and you certainly don't have the look of a miner.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_637e6c80", "whatever_you_say"}, -- I have received authorization from the Mandalorians.
		{"@conversation/death_watch_foreman:s_1c4d0bbb", "loosest_sense"}, -- You work for the Mandalorians?
	}
}
deathWatchForemanConvoTemplate:addScreen(init);

busy_hasnt_done_quest = ConvoScreen:new {
	id = "busy_hasnt_done_quest",
	leftDialog = "@conversation/death_watch_foreman:s_9e37f61f", -- Another stranger? The Mandalorians must be really slacking on their defenses lately. Oh well, none of my business. I am sorry but I really have to get back to work right now, maybe I will have time to talk to you later.
	stopConversation = "true",
	options = {
	}
}
deathWatchForemanConvoTemplate:addScreen(busy_hasnt_done_quest);

loosest_sense = ConvoScreen:new {
	id = "loosest_sense",
	leftDialog = "@conversation/death_watch_foreman:s_7a654750", -- Work in the loosest sense of the word. Although we are not really getting a whole lot of work done at this moment.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_2de77a24", "blasted_laser"}, -- Why aren't you getting any work done?
		{"@conversation/death_watch_foreman:s_7d65b570", "we_mine_alum"}, -- What sort of work are you doing?
	}
}
deathWatchForemanConvoTemplate:addScreen(loosest_sense);

not_that_bad = ConvoScreen:new {
	id = "not_that_bad",
	leftDialog = "@conversation/death_watch_foreman:s_e83ca277", -- I guess it isn't that bad. The Mandalorians don't pay us a whole lot but they generally don't directly mistreat any of us unless we do something to make them mad...which doesn't seem that hard to do. Hmmmm...now that I think about it this isn't the best life but it is better then telling them we quit.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_2de77a24", "blasted_laser"}, -- Why aren't you getting any work done?
	}
}
deathWatchForemanConvoTemplate:addScreen(not_that_bad);

we_mine_alum = ConvoScreen:new {
	id = "we_mine_alum",
	leftDialog = "@conversation/death_watch_foreman:s_dd6f26cc", -- We mine for the alum that the Mandalores use to make their armor. Basically, we get to work down in these nasty caves all day long so the Mandalorians can look nice.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_dc1d4717", "not_that_bad"}, -- Sounds to me like you should be happy your not working.
	}
}
deathWatchForemanConvoTemplate:addScreen(we_mine_alum);

blasted_laser = ConvoScreen:new {
	id = "blasted_laser",
	leftDialog = "@conversation/death_watch_foreman:s_1fe41c46", -- It's this blasted laser they have us working with. Dumb thing never works right and then when we finally did get it working again, Haldo went off his rocker, ripped its battery out, and took off with it.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_687ef712", "one_of_my_men"}, -- Haldo? Who is Haldo and why would he take the battery?
	}
}
deathWatchForemanConvoTemplate:addScreen(blasted_laser);

whatever_you_say = ConvoScreen:new {
	id = "whatever_you_say",
	leftDialog = "@conversation/death_watch_foreman:s_81b8b95b", -- Yeah, yeah...whatever you say there pally. I wouldn't want to be in your shoes if the Mandalorians catch you down here bothering their miners.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_57097d43", "braver_than_me"}, -- Don't worry about me and the Mandalorians. I can handle them.
	}
}
deathWatchForemanConvoTemplate:addScreen(whatever_you_say);

braver_than_me = ConvoScreen:new {
	id = "braver_than_me",
	leftDialog = "@conversation/death_watch_foreman:s_6d069da0", -- You're braver then I will ever be. But if you really are that tough, maybe you would like to help recover our drill battery that Haldo ran off with?
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_687ef712", "one_of_my_men"}, -- Haldo? Who is Haldo and why would he take the battery?
		{"@conversation/death_watch_foreman:s_baac9005", "what_i_expected"}, -- I don't really have time to rescue your battery.
	}
}
deathWatchForemanConvoTemplate:addScreen(braver_than_me);

what_i_expected = ConvoScreen:new {
	id = "what_i_expected",
	leftDialog = "@conversation/death_watch_foreman:s_f79fa021", -- That is pretty much what I expected. I would have been shocked if a complete stranger such as yourself offered to help us out.
	stopConversation = "true",
	options = {
	}
}
deathWatchForemanConvoTemplate:addScreen(what_i_expected);

one_of_my_men = ConvoScreen:new {
	id = "one_of_my_men",
	leftDialog = "@conversation/death_watch_foreman:s_c2d12633", -- Haldo was one of the men on my crew. My guess is that his rebreather wasn't working properly and he breathed too much of the alum fumes. Blasted air vents haven't been working right either, so we have been using our masks a lot.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_8bbe4b84", "be_a_lifesaver"}, -- Maybe I can help you track down Haldo.
		{"@conversation/death_watch_foreman:s_19ecd0cd", "asked_for_volunteers"}, -- Have you sent anyone out to try to find Haldo?
		{"@conversation/death_watch_foreman:s_baac9005", "what_i_expected"}, -- I don't really have time to rescue your battery.
	}
}
deathWatchForemanConvoTemplate:addScreen(one_of_my_men);

be_a_lifesaver = ConvoScreen:new {
	id = "be_a_lifesaver",
	leftDialog = "@conversation/death_watch_foreman:s_471cd71d", -- That would be a lifesaver. No one else is willing to go out and try to find him. Guys who get hit with alum sickness generally are unstable and sometimes can be quite dangerous.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_2236f9d7", "there_is_a_cure"}, -- If he is sick is there anyway to help him?
		{"@conversation/death_watch_foreman:s_1265571c", "didnt_say_by_force"}, -- So I will have to take the battery from him by force?
		{"@conversation/death_watch_foreman:s_71ad5afa", "what_i_expected"}, -- I am sorry but I don't really have time to help your sick co-worker.
	}
}
deathWatchForemanConvoTemplate:addScreen(be_a_lifesaver);

asked_for_volunteers = ConvoScreen:new {
	id = "asked_for_volunteers",
	leftDialog = "@conversation/death_watch_foreman:s_645da2b5", -- I asked for volunteers but no one was willing to go search. Not that I blame them, I don't even want to go out and try to find him. People with alum sickness become real messed up in the head. You never know what they are going to do. A lot of times they get really violent.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_2236f9d7", "there_is_a_cure"}, -- If he is sick is there anyway to help him?
		{"@conversation/death_watch_foreman:s_1265571c", "didnt_say_by_force"}, -- So I will have to take the battery from him by force?
		{"@conversation/death_watch_foreman:s_71ad5afa", "what_i_expected"}, -- I am sorry but I don't really have time to help your sick co-worker.
	}
}
deathWatchForemanConvoTemplate:addScreen(asked_for_volunteers);

there_is_a_cure = ConvoScreen:new {
	id = "there_is_a_cure",
	leftDialog = "@conversation/death_watch_foreman:s_45d9624a", -- Yeah, well there is a cure. We would have gone and got it, but the Mandalorians don't much care for us wandering around when we are supposed to be working, so none of us have gone up to get it.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_ce027a15", "great_remember_medicine"}, -- Ok I will go see what I can do for your co-worker.
		{"@conversation/death_watch_foreman:s_f73c5ae7", "cure_is_upstairs"}, -- Where can I find this cure if I decide to help out?
		{"@conversation/death_watch_foreman:s_71ad5afa", "what_i_expected"}, -- I am sorry but I don't really have time to help your sick co-worker.
	}
}
deathWatchForemanConvoTemplate:addScreen(there_is_a_cure);

didnt_say_by_force = ConvoScreen:new {
	id = "didnt_say_by_force",
	leftDialog = "@conversation/death_watch_foreman:s_c7f1e2ee", -- Hey now! I didn't say anything about using force on him. He is sick and there is a cure up in the medical lab. Granted there have been a few cases where alum sickness will make a person so demented that they can't come back, but Haldo has only been ill for a little while.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_ce027a15", "great_remember_medicine"}, -- Ok I will go see what I can do for your co-worker.
		{"@conversation/death_watch_foreman:s_f73c5ae7", "cure_is_upstairs"}, -- Where can I find this cure if I decide to help out?
		{"@conversation/death_watch_foreman:s_71ad5afa", "what_i_expected"}, -- I am sorry but I don't really have time to help your sick co-worker.
	}
}
deathWatchForemanConvoTemplate:addScreen(didnt_say_by_force);

cure_is_upstairs = ConvoScreen:new {
	id = "cure_is_upstairs",
	leftDialog = "@conversation/death_watch_foreman:s_44557f4a", -- It is located upstairs in the medical lab. One of the medical droids should be able to give it to you. They don't require any special code or anything to help you out. At least they didn't last time I used them but the Mandalorians don't really consult us when they make changes to things around here.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_ce027a15", "great_remember_medicine"}, -- Ok I will go see what I can do for your co-worker.
		{"@conversation/death_watch_foreman:s_71ad5afa", "what_i_expected"}, -- I am sorry but I don't really have time to help your sick co-worker.
	}
}
deathWatchForemanConvoTemplate:addScreen(cure_is_upstairs);

great_remember_medicine = ConvoScreen:new {
	id = "great_remember_medicine",
	leftDialog = "@conversation/death_watch_foreman:s_de774e37", -- Great. Now remember there is some medicine in the medical lab that should be able to help him out. And once you get that battery bring it on back to me so we can get this drill working again.
	stopConversation = "true",
	options = {}
}
deathWatchForemanConvoTemplate:addScreen(great_remember_medicine);

offer_quest_again = ConvoScreen:new {
	id = "offer_quest_again",
	leftDialog = "@conversation/death_watch_foreman:s_1511575f", -- Hey you are back again. You know Haldo is still running around down here with our battery. Are you sure you don't want to give us a hand and try to get it back for us?
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_26fa42a7", "return_great_remember_medicine"}, -- Yes I will see if I can find him for you.
		{"@conversation/death_watch_foreman:s_58a87fe", "return_one_of_my_men"}, -- So who is this Haldo guy who ran off with your battery?
		{"@conversation/death_watch_foreman:s_71ad5afa", "what_i_expected"}, -- I am sorry but I don't really have time to help your sick co-worker.
	}
}
deathWatchForemanConvoTemplate:addScreen(offer_quest_again);

return_great_remember_medicine = ConvoScreen:new {
	id = "return_great_remember_medicine",
	leftDialog = "@conversation/death_watch_foreman:s_de774e37", -- Great. Now remember there is some medicine in the medical lab that should be able to help him out. And once you get that battery bring it on back to me so we can get this drill working again.
	stopConversation = "true",
	options = {
	}
}
deathWatchForemanConvoTemplate:addScreen(return_great_remember_medicine);

return_one_of_my_men = ConvoScreen:new {
	id = "return_one_of_my_men",
	leftDialog = "@conversation/death_watch_foreman:s_c2d12633", -- Haldo was one of the men on my crew. My guess is that his rebreather wasn't working properly and he breathed too much of the alum fumes. Blasted air vents haven't been working right either, so we have been using our masks a lot.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_26fa42a7", "return_great_remember_medicine"}, -- Yes I will see if I can find him for you.
		{"@conversation/death_watch_foreman:s_71ad5afa", "what_i_expected"}, -- I am sorry but I don't really have time to help your sick co-worker.
	}
}
deathWatchForemanConvoTemplate:addScreen(return_one_of_my_men);

found_him_yet = ConvoScreen:new {
	id = "found_him_yet",
	leftDialog = "@conversation/death_watch_foreman:s_4f17ac67", -- Have you managed to find Haldo yet? We really need that battery back before the Mandalorians come down here to check up on our progress.
	stopConversation = "false",
	options = {
	-- Handled by convo handler
	--{"@conversation/death_watch_foreman:s_829888a9", "thank_you_didnt_kill"}, -- Here you go.
	--{"@conversation/death_watch_foreman:s_829888a9", "thank_you_killed"}, -- Here you go.
	--{"@conversation/death_watch_foreman:s_c825f420", "please_hurry"}, -- Not yet, but I am still looking for him.
	--{"@conversation/death_watch_foreman:s_baac9005", "what_i_expected"}, -- I don't really have time to rescue your battery.
	}
}
deathWatchForemanConvoTemplate:addScreen(found_him_yet);

please_hurry = ConvoScreen:new {
	id = "please_hurry",
	leftDialog = "@conversation/death_watch_foreman:s_fb5cf4cd", -- Ok, please hurry. I am sure that we don't have a whole lot of time left. Once you get the battery come back to me as quick as you can.
	stopConversation = "true",
	options = {
	}
}
deathWatchForemanConvoTemplate:addScreen(please_hurry);

thank_you_didnt_kill = ConvoScreen:new {
	id = "thank_you_didnt_kill",
	leftDialog = "@conversation/death_watch_foreman:s_27b9acbc", -- Thank you for helping Haldo and getting the battery back for us. Now we can get back to....oh no! The battery's connections are all covered with dirt and grime. Haldo must have got them dirty after he took it.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_bdb717fb", "bad_connection"}, -- What happens if the battery connections are dirty?
	}
}
deathWatchForemanConvoTemplate:addScreen(thank_you_didnt_kill);

thank_you_killed = ConvoScreen:new {
	id = "thank_you_killed",
	leftDialog = "@conversation/death_watch_foreman:s_3310d1b6", -- I guess I should thank you for getting us the battery back but you didn't have to kill Haldo. He was sick in the head from the fumes and the medicine from the medical droid could have cured him.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_d62e85a9", "suppose_you_did"}, -- You wanted the battery back and I got it back for you.
	}
}
deathWatchForemanConvoTemplate:addScreen(thank_you_killed);

suppose_you_did = ConvoScreen:new {
	id = "suppose_you_did",
	leftDialog = "@conversation/death_watch_foreman:s_9b4dd6c7", -- Yeah, I suppose you did. Let me take a look at it. Oh no, this battery isn't going to do us any good. Look here all the connections on it are covered with dirt and grime. Now it is going to have to be cleaned off.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_bdb717fb", "bad_connection"}, -- What happens if the battery connections are dirty?
	}
}
deathWatchForemanConvoTemplate:addScreen(suppose_you_did);

bad_connection = ConvoScreen:new {
	id = "bad_connection",
	leftDialog = "@conversation/death_watch_foreman:s_9cf7119e", -- We won't get a good solid connection and the drill won't fire is what will happen. I hate to ask but could you perhaps take this battery over to the workshop and have one of treadwell clean it up?
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_dd657c44", "speak_to_treadwell"}, -- Sure, I will come back to you as soon as I get it cleaned.
		{"@conversation/death_watch_foreman:s_728cbacc", "would_love_to"}, -- Why don't one of you go take it to the workshop?
		{"@conversation/death_watch_foreman:s_54ee97f2", "clean_when_can"}, -- I don't really have time to deal with this right now.
	}
}
deathWatchForemanConvoTemplate:addScreen(bad_connection);

return_need_battery_clean = ConvoScreen:new {
	id = "return_need_battery_clean",
	leftDialog = "@conversation/death_watch_foreman:s_d1eff807", -- Could you do us one more favor and take this battery over to the workshop. The treadwell in there can clean it off without any problems.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_dd657c44", "speak_to_treadwell"}, -- Sure, I will come back to you as soon as I get it cleaned.
		{"@conversation/death_watch_foreman:s_728cbacc", "would_love_to"}, -- Why don't one of you go take it to the workshop?
		{"@conversation/death_watch_foreman:s_54ee97f2", "clean_when_can"}, -- I don't really have time to deal with this right now.
	}
}
deathWatchForemanConvoTemplate:addScreen(return_need_battery_clean);

clean_when_can = ConvoScreen:new {
	id = "clean_when_can",
	leftDialog = "@conversation/death_watch_foreman:s_579c9bc5", -- Well that battery doesn't really do us alot of good in its current state. Why don't you hold onto it and if you do get a chance run it over to the workshop and get it cleaned. We would really appreciate it.
	stopConversation = "true",
	options = {}
}
deathWatchForemanConvoTemplate:addScreen(clean_when_can);

speak_to_treadwell = ConvoScreen:new {
	id = "speak_to_treadwell",
	leftDialog = "@conversation/death_watch_foreman:s_bc5213a", -- Just speak to the treadwell when you are in there and he will take care of the dirty battery. Oh and try not to kill him while you are there. We sort of need him for repairs around this place.
	stopConversation = "true",
	options = {}
}
deathWatchForemanConvoTemplate:addScreen(speak_to_treadwell);

would_love_to = ConvoScreen:new {
	id = "would_love_to",
	leftDialog = "@conversation/death_watch_foreman:s_23237572", -- I would love to but the Mandalorians keep track of who comes and goes from the workshop. If one of us goes in they will ask why and I would rather they didn't know about the whole Haldo incident. Since you are a stranger they will just correctly assume you are an intruder and try to kill you...which they probably have been doing anyways.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_4d8102d5", "up_for_danger"}, -- In an odd sort of way, that makes sense. Ok, I will do it.
		{"@conversation/death_watch_foreman:s_a618b93a", "clean_when_can"}, -- No thanks, I think I will avoid the workshop if it is monitored.
	}
}
deathWatchForemanConvoTemplate:addScreen(would_love_to);

up_for_danger = ConvoScreen:new {
	id = "up_for_danger",
	leftDialog = "@conversation/death_watch_foreman:s_787e689e", -- I figured you would be up for that whole danger thing. Once the treadwell has cleaned the battery, come on back to me so we can get that battery installed back into the drill.
	stopConversation = "true",
	options = {}
}
deathWatchForemanConvoTemplate:addScreen(up_for_danger);

return_battery_not_clean = ConvoScreen:new {
	id = "return_battery_not_clean",
	leftDialog = "@conversation/death_watch_foreman:s_7b9dc7c7", -- Have you managed to get that battery cleaned yet?
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_145fd34", "speak_to_treadwell"}, -- Not yet, but I will get this battery cleaned soon.
		{"@conversation/death_watch_foreman:s_54ee97f2", "clean_when_can"}, -- I don't really have time to deal with this right now.
	}
}
deathWatchForemanConvoTemplate:addScreen(return_battery_not_clean);

return_battery_cleaned_killed_haldo = ConvoScreen:new {
	id = "return_battery_cleaned_killed_haldo",
	leftDialog = "@conversation/death_watch_foreman:s_f46d76f6", -- Hey you are back. I was sort of half expecting you not to return. Oh yeah, this is excellent. The battery is clean and ready to be installed in the drill. And you didn't destroy the treadwell...thats a plus. Unfortunately there is one other issue that we are having.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_44bb7cbc", "uses_liquid_coolant"}, -- What is the other problem with the drill?
	}
}
deathWatchForemanConvoTemplate:addScreen(return_battery_cleaned_killed_haldo);

return_battery_cleaned_no_haldo_kill = ConvoScreen:new {
	id = "return_battery_cleaned_no_haldo_kill",
	leftDialog = "@conversation/death_watch_foreman:s_dd7c0dd3", -- Hey, you're back. I was sort of half expecting you not to return. Oh yeah, this is excellent. The battery is clean and ready to be installed in the drill. Unfortunately there is one other issue that we are having.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_44bb7cbc", "uses_liquid_coolant"}, -- What is the other problem with the drill?
	}
}
deathWatchForemanConvoTemplate:addScreen(return_battery_cleaned_no_haldo_kill);

uses_liquid_coolant = ConvoScreen:new {
	id = "uses_liquid_coolant",
	leftDialog = "@conversation/death_watch_foreman:s_286d283f", -- The drill uses a liquid coolant system in order to keep it from overheating and exploding. Well the problem is that we are not getting any pressure down here so if we turn on the drill...BOOM!
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_83d1549d", "pump_room_upstairs"}, -- What do you need in order to get water pressure down here?
		{"@conversation/death_watch_foreman:s_b491aba5", "old_technology"}, -- You are still using liquid coolant for you laser drill?
	}
}
deathWatchForemanConvoTemplate:addScreen(uses_liquid_coolant);

old_technology = ConvoScreen:new {
	id = "old_technology",
	leftDialog = "@conversation/death_watch_foreman:s_8deeb761", -- It's old technology. The Mandalorians don't exactly splurge on mining equipment. In fact if you havn't noticed already nothing around here is exactly in tip top shape.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_83d1549d", "pump_room_upstairs"}, -- What do you need in order to get water pressure down here?
	}
}
deathWatchForemanConvoTemplate:addScreen(old_technology);

pump_room_upstairs = ConvoScreen:new {
	id = "pump_room_upstairs",
	leftDialog = "@conversation/death_watch_foreman:s_e5e9e886", -- Upstairs there is a pump room. There are four pumps that all need to be on in order to get the water down to us. Unfortunately the circuit breakers on those things are all ancient and trip at the slightest surge. If you could maybe go up there and turn them all on for us I know we could get underway.
	stopConversation = "false",
	options = {
	-- Handled by convo handler
	--{"@conversation/death_watch_foreman:s_d4b1da9f", "tricky_pumps_haldo_kill"}, -- Ok fine I will do this for you but you are going to owe me.
	--{"@conversation/death_watch_foreman:s_d4b1da9f", "tricky_pumps_no_haldo_kill"}, -- Ok fine I will do this for you but you are going to owe me.
	--{"@conversation/death_watch_foreman:s_3055077f", "choice_is_yours"}, -- I don't really have time for this right now, sorry.
	}
}
deathWatchForemanConvoTemplate:addScreen(pump_room_upstairs);

choice_is_yours = ConvoScreen:new {
	id = "choice_is_yours",
	leftDialog = "@conversation/death_watch_foreman:s_23cbff5d", -- Choice is yours. We will figure out some other way to get them online I suppose.
	stopConversation = "true",
	options = {}
}
deathWatchForemanConvoTemplate:addScreen(choice_is_yours);

tricky_pumps_haldo_kill = ConvoScreen:new {
	id = "tricky_pumps_haldo_kill",
	leftDialog = "@conversation/death_watch_foreman:s_8405256c", -- Deal. Now listen those pumps can be tricky. Generally when you trip one of the valves it causes the one or ones next to it on the circuit to flip as well. You will have to play with it for a while in order to get them all online. There isn't much time...oh yeah, and try not to destroy the pumps while you are at it.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_9bea7011", "come_back_after_pumps"}, -- Ok, cool your jets. I am on it.
	}
}
deathWatchForemanConvoTemplate:addScreen(tricky_pumps_haldo_kill);

tricky_pumps_no_haldo_kill = ConvoScreen:new {
	id = "tricky_pumps_no_haldo_kill",
	leftDialog = "@conversation/death_watch_foreman:s_262e7b86", -- Deal. Now listen those pumps can be tricky. Generally when you trip one of the valves it causes the one or ones next to it on the circuit to flip as well. You will have to play with it for a while in order to get them all online. Also we really don't have a lot of time so if you are not back soon I am going to have to see if there is anything else I can do to get it on.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_9bea7011", "come_back_after_pumps"}, -- Ok, cool your jets. I am on it.
	}
}
deathWatchForemanConvoTemplate:addScreen(tricky_pumps_no_haldo_kill);

come_back_after_pumps = ConvoScreen:new {
	id = "come_back_after_pumps",
	leftDialog = "@conversation/death_watch_foreman:s_6864fcd4", -- Good. Once you get those pumps back online come on back and we will discuss what I owe you.
	stopConversation = "true",
	options = {}
}
deathWatchForemanConvoTemplate:addScreen(come_back_after_pumps);

try_pump_again = ConvoScreen:new {
	id = "try_pump_again",
	leftDialog = "@conversation/death_watch_foreman:s_4af1601a", -- So you are back? We still don't have any water pressure down here maybe you would like to head back up and try again?
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_e55f453d", "remember_tricky_pumps"}, -- Yes, I will give it another shot.
		{"@conversation/death_watch_foreman:s_b99aaac2", "choice_is_yours"}, -- No thanks, I can't figure out how to get those pumps to work.
	}
}
deathWatchForemanConvoTemplate:addScreen(try_pump_again);

remember_tricky_pumps = ConvoScreen:new {
	id = "remember_tricky_pumps",
	leftDialog = "@conversation/death_watch_foreman:s_6b8a415c", -- Remember those pumps can be tricky. Generally when you trip one of the valves it causes the one or ones next to it on the circuit to flip as well. You will have to play with it for a while in order to get them all online.
	stopConversation = "true",
	options = {}
}
deathWatchForemanConvoTemplate:addScreen(remember_tricky_pumps);

pump_timer_running = ConvoScreen:new {
	id = "pump_timer_running",
	leftDialog = "@conversation/death_watch_foreman:s_de4a182e", -- What are you doing back here. We still don't have any water pressure down here. I am telling you that we don't have very much time left.
	stopConversation = "true",
	options = {}
}
deathWatchForemanConvoTemplate:addScreen(pump_timer_running);

pump_success_haldo_kill = ConvoScreen:new {
	id = "pump_success_haldo_kill",
	leftDialog = "@conversation/death_watch_foreman:s_1b208070", -- Hey you managed to get all of the pumps online and to my knowledge didn't destroy all of them in the process. That is surprising considering your track record for violence. Well a deal is a deal so tell you what I will get you some of this ore that we are mining.
	stopConversation = "false",
	options = {
	-- Handled by convo handler
	--{"@conversation/death_watch_foreman:s_c04f0d0d", "ore_inv_full"}, -- I risked my life for some ore?
	--{"@conversation/death_watch_foreman:s_c04f0d0d", "used_in_armor"}, -- I risked my life for some ore?
	}
}
deathWatchForemanConvoTemplate:addScreen(pump_success_haldo_kill);

pump_success_no_haldo_kill = ConvoScreen:new {
	id = "pump_success_no_haldo_kill",
	leftDialog = "@conversation/death_watch_foreman:s_c1dc6296", -- I don't know how you managed to get those pumps working without the Mandalorians taking you out. You must be a lot tougher then you look. I can't thank you enough for all your help.
	stopConversation = "false",
	options = {
	-- Handled by convo handler
	--{"@conversation/death_watch_foreman:s_5597accd", "ore_inv_full"}, -- How about a reward?
	--{"@conversation/death_watch_foreman:s_5597accd", "sneak_some_ore"}, -- How about a reward?
	}
}
deathWatchForemanConvoTemplate:addScreen(pump_success_no_haldo_kill);

ore_inv_full = ConvoScreen:new {
	id = "ore_inv_full",
	leftDialog = "@conversation/death_watch_foreman:s_52f3e83e", -- This is the same ore that the Mandalores use to make their armor. I am willing to sneak you some but you are going to need to make some room in your inventory so I can.
	stopConversation = "true",
	options = {}
}
deathWatchForemanConvoTemplate:addScreen(ore_inv_full);

used_in_armor = ConvoScreen:new {
	id = "used_in_armor",
	leftDialog = "@conversation/death_watch_foreman:s_95879f15", -- Hey it is not just any ore. This is the stuff that the Mandalorians use in their armor. They keep a pretty careful track of what we mine but I know that I can sneak you some of this stuff without them noticing it.
	stopConversation = "false",
	options = {
	{"@conversation/death_watch_foreman:s_ed0d4e5a", "ore_reward"}, -- You make Mandalorian armor out of this ore?
	}
}
deathWatchForemanConvoTemplate:addScreen(used_in_armor);

sneak_some_ore = ConvoScreen:new {
	id = "sneak_some_ore",
	leftDialog = "@conversation/death_watch_foreman:s_b4feb773", -- We don't really have a whole lot to give but I will tell you what. I can sneak you some of this ore that we are mining. Now before you get all mad about just getting ore let me tell you that this is the stuff that the Mandalores use in their armor.
	stopConversation = "false",
	options = {
	{"@conversation/death_watch_foreman:s_ed0d4e5a", "ore_reward"}, -- You make Mandalorian armor out of this ore?
	}
}
deathWatchForemanConvoTemplate:addScreen(sneak_some_ore);

ore_reward = ConvoScreen:new {
	id = "ore_reward",
	leftDialog = "@conversation/death_watch_foreman:s_18426338", -- Hey all I know is that this stuff is used in the making of the armor. They keep a pretty tight watch on how much of this stuff we mine, but I know I can sneak you some every now and again. Here you go. If you check back with me occasionally, I should be able to sneak you out some more. Not too often mind you, but I will do my best.
	stopConversation = "true",
	options = {}
}
deathWatchForemanConvoTemplate:addScreen(ore_reward);

more_ore = ConvoScreen:new {
	id = "more_ore",
	leftDialog = "@conversation/death_watch_foreman:s_e1dd8e6e", -- Good to see you again my friend. I was able to secure some more of this ore for you. If you need some more check back with me later and maybe I can sneak some more out under the noses of the Mandalorians.
	stopConversation = "true",
	options = {}
}
deathWatchForemanConvoTemplate:addScreen(more_ore);

no_ore_yet = ConvoScreen:new {
	id = "no_ore_yet",
	leftDialog = "@conversation/death_watch_foreman:s_1d1d45a9", -- Hey it is you again. Glad to still you are still breathing. If you have come looking for ore I am sorry but I can't sneak you out any right now. The Mandalorians are running inventory right now and will notice anything that is missing. Check back with me later.
	stopConversation = "true",
	options = {}
}
deathWatchForemanConvoTemplate:addScreen(no_ore_yet);

more_ore_inv_full = ConvoScreen:new {
	id = "more_ore_inv_full",
	leftDialog = "@conversation/death_watch_foreman:s_5af847c7", -- You are going to have to clear out some inventory space in order for me to give you any more of this ore.
	stopConversation = "true",
	options = {}
}
deathWatchForemanConvoTemplate:addScreen(more_ore_inv_full);

addConversationTemplate("deathWatchForemanConvoTemplate", deathWatchForemanConvoTemplate);