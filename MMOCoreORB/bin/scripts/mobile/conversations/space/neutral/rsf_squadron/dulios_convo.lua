dulios_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "duliosConvoHandler",
	screens = {}
}

pilot_not_rsf = ConvoScreen:new {
	id = "pilot_not_rsf",
	leftDialog = "@conversation/naboo_privateer_tier3:s_843db48d", -- I don't think I know you. And Mama told me not to talk to strangers. Beat it.
	stopConversation = "true",
	options = {}
}
dulios_convo_template:addScreen(pilot_not_rsf);

completed_dulios = ConvoScreen:new {
	id = "completed_dulios",
	leftDialog = "@conversation/naboo_privateer_tier3:s_4fc6a099", -- Aw. I think I'm actually going to miss you - maybe. But duty calls. You're now assigned to Admiral Diness Imler, down the hall - he'll be giving you orders from now on. See ya, %TU.
	stopConversation = "true",
	options = {}
}
dulios_convo_template:addScreen(completed_dulios);

train_warships_final = ConvoScreen:new {
	id = "train_warships_final",
	leftDialog = "@conversation/naboo_privateer_tier3:s_4fc6a099", -- Aw. I think I'm actually going to miss you...
	stopConversation = "true",
	options = {}
}
dulios_convo_template:addScreen(train_warships_final);

train_components_final = ConvoScreen:new {
	id = "train_components_final",
	leftDialog = "@conversation/naboo_privateer_tier3:s_4fc6a099", -- Aw. I think I'm actually going to miss you...
	stopConversation = "true",
	options = {}
}
dulios_convo_template:addScreen(train_components_final);

train_techniques_final = ConvoScreen:new {
	id = "train_techniques_final",
	leftDialog = "@conversation/naboo_privateer_tier3:s_4fc6a099", -- Aw. I think I'm actually going to miss you...
	stopConversation = "true",
	options = {}
}
dulios_convo_template:addScreen(train_techniques_final);

train_programming_final = ConvoScreen:new {
	id = "train_programming_final",
	leftDialog = "@conversation/naboo_privateer_tier3:s_4fc6a099", -- Aw. I think I'm actually going to miss you...
	stopConversation = "true",
	options = {}
}
dulios_convo_template:addScreen(train_programming_final);

--[[
	Quest Line Missions
]]

-- Mission 1: Capture a Black Sun Assassin (Recovery mission in Dantooine)

first_mission = ConvoScreen:new {
	id = "first_mission",
	leftDialog = "@conversation/naboo_privateer_tier3:s_a31b65f9", -- %TU. You're the new one.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_19425c2f", "im_dulios"}, -- You are?
		{"@conversation/naboo_privateer_tier3:s_731caa45", "have_mission"}, -- Got a mission for me?
	}
}
dulios_convo_template:addScreen(first_mission);

im_dulios = ConvoScreen:new {
	id = "im_dulios",
	leftDialog = "@conversation/naboo_privateer_tier3:s_88a726df", -- Hey, we'll see what you say when you're on this side of the desk. Let's get you started.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_b1da46d", "have_mission"}, -- Where do I start?
	}
}
dulios_convo_template:addScreen(im_dulios);

have_mission = ConvoScreen:new {
	id = "have_mission",
	leftDialog = "@conversation/naboo_privateer_tier3:s_666cac71", -- These guys pose a SERIOUS threat to the royal family - hell, to this entire planet.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_5bd69df6", "blacksun_threat"}, -- What do you need me to do?
	}
}
dulios_convo_template:addScreen(have_mission);

blacksun_threat = ConvoScreen:new {
	id = "blacksun_threat",
	leftDialog = "@conversation/naboo_privateer_tier3:s_e1e07205", -- All you need to do is stop his ship. The boys in the lab are putting together a little surprise for him, but it's up to you to deliver the package. Get over to the Dantooine System; we'll update you from there.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_7478d95d", "accept_first_mission"}, -- Loud and clear. Where to?
	}
}
dulios_convo_template:addScreen(blacksun_threat);

accept_first_mission = ConvoScreen:new {
	id = "accept_first_mission",
	leftDialog = "@conversation/naboo_privateer_tier3:s_46eb0ec8", -- First, go to Dantooine. Just follow the data in your nav system. And keep your eyes open. This guy's a professional.
	stopConversation = "true",
	options = {}
}
dulios_convo_template:addScreen(accept_first_mission);

failed_first_mission = ConvoScreen:new {
	id = "failed_first_mission",
	leftDialog = "@conversation/naboo_privateer_tier3:s_97e76dd", -- This Royal Security Forces assignment isn't so easy after all, is it?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_b144d69b", "try_first_again"}, -- Nothing I can't handle.
	}
}
dulios_convo_template:addScreen(failed_first_mission);

try_first_again = ConvoScreen:new {
	id = "try_first_again",
	leftDialog = "@conversation/naboo_privateer_tier3:s_46eb0ec8", -- First, go to Dantooine. Just follow the data in your nav system. And keep your eyes open. This guy's a professional.
	stopConversation = "true",
	options = {}
}
dulios_convo_template:addScreen(try_first_again);

complete_mission1 = ConvoScreen:new {
	id = "complete_mission1",
	leftDialog = "@conversation/naboo_privateer_tier3:s_8de81731", -- I'm really going to miss that Saymonz Varg.
	stopConversation = "false",
	options = {}
}
dulios_convo_template:addScreen(complete_mission1);

-- Mission 2: Inspect Diplomat Ships

second_mission = ConvoScreen:new {
	id = "second_mission",
	leftDialog = "@conversation/naboo_privateer_tier3:s_5075e20b", -- Your new mission targets a criminal of a different type. I'm talking about diplomats.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_66f6527f", "diplomats_know"}, -- Do the diplomats know?
		{"@conversation/naboo_privateer_tier3:s_9d9af42e", "where_diplomats"}, -- Where are these diplomats?
	}
}
dulios_convo_template:addScreen(second_mission);

diplomats_know = ConvoScreen:new {
	id = "diplomats_know",
	leftDialog = "@conversation/naboo_privateer_tier3:s_68d4ba6b", -- To be honest, it's probably not them. It's probably smugglers taking advantage of the opportunity, and hiding gear on their ship. Doesn't matter. Same difference.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_a41bb8c7", "how_suspicious"}, -- How can you be so suspicious?
	}
}
dulios_convo_template:addScreen(diplomats_know);

how_suspicious = ConvoScreen:new {
	id = "how_suspicious",
	leftDialog = "@conversation/naboo_privateer_tier3:s_83905129", -- Unlike you, I DO get paid the big bucks, %NU, and it's on account of my suspicious nature. Smugglers may be packing these ships with contraband.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_c089dba4", "just_am"}, -- I just am.
	}
}
dulios_convo_template:addScreen(how_suspicious);

just_am = ConvoScreen:new {
	id = "just_am",
	leftDialog = "@conversation/naboo_privateer_tier3:s_c65cf2da", -- What's not to like?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_9d9af42e", "where_diplomats"}, -- Where are these diplomats?
	}
}
dulios_convo_template:addScreen(just_am);

where_diplomats = ConvoScreen:new {
	id = "where_diplomats",
	leftDialog = "@conversation/naboo_privateer_tier3:s_76734574", -- En route. Fly out to the waypoint and get ready to inspect each and every one of them.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_6c251948", "accept_second_mission"}, -- You got it.
	}
}
dulios_convo_template:addScreen(where_diplomats);

accept_second_mission = ConvoScreen:new {
	id = "accept_second_mission",
	leftDialog = "@conversation/naboo_privateer_tier3:s_c4095762", -- Fly your ship out to the waypoint. Inspect the diplomats' ships. Use some pretext if you have to. See what you can find.
	stopConversation = "true",
	options = {}
}
dulios_convo_template:addScreen(accept_second_mission);

failed_second_mission = ConvoScreen:new {
	id = "failed_second_mission",
	leftDialog = "@conversation/naboo_privateer_tier3:s_53daee1c", -- You're starting to get a bad reputation.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_83b47a80", "stories_about_me"}, -- You telling stories about me?
	}
}
dulios_convo_template:addScreen(failed_second_mission);

stories_about_me = ConvoScreen:new {
	id = "stories_about_me",
	leftDialog = "@conversation/naboo_privateer_tier3:s_57d34626", -- I don't need to! People know those hunters are using you for target practice. Get back out there - and try fighting back this time.
	stopConversation = "true",
	options = {}
}
dulios_convo_template:addScreen(stories_about_me);

complete_mission2 = ConvoScreen:new {
	id = "complete_mission2",
	leftDialog = "@conversation/naboo_privateer_tier3:s_47152ac5", -- Oh yeah. The worst of the worst. That data you intercepted has led us to a real hornet's nest of assassins and terrorists.
	stopConversation = "false",
	options = {}
}
dulios_convo_template:addScreen(complete_mission2);

-- Mission 3: Hunt Rodian Assassin

third_mission = ConvoScreen:new {
	id = "third_mission",
	leftDialog = "@conversation/naboo_privateer_tier3:s_70e76a9a", -- OK, %NU, no more busywork. Time for some good old-fashioned killing. How does that sound?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_5a889c20", "rodians_feel"}, -- Like a dream come true.
		{"@conversation/naboo_privateer_tier3:s_5a2317e2", "killing_bad_guys"}, -- Depends. Am I killing bad guys?
	}
}
dulios_convo_template:addScreen(third_mission);

rodians_feel = ConvoScreen:new {
	id = "rodians_feel",
	leftDialog = "@conversation/naboo_privateer_tier3:s_b7137723", -- OK. Then let's get started. How do you feel about Rodians?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_589399fa", "love_em"}, -- Love 'em.
		{"@conversation/naboo_privateer_tier3:s_af5ccac", "hate_em"}, -- Hate 'em.
	}
}
dulios_convo_template:addScreen(rodians_feel);

killing_bad_guys = ConvoScreen:new {
	id = "killing_bad_guys",
	leftDialog = "@conversation/naboo_privateer_tier3:s_ab3f1614", -- Boy, do I. This is a good one. I'd like to do this myself.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_a09da7f1", "rodians_feel"}, -- You like that?
	}
}
dulios_convo_template:addScreen(killing_bad_guys);

love_em = ConvoScreen:new {
	id = "love_em",
	leftDialog = "@conversation/naboo_privateer_tier3:s_4bdc789d", -- Hope you're being sarcastic. You're looking for a Rodian assassin.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_51ca1520", "rodian_killed"}, -- An assassin? Who's he killed?
	}
}
dulios_convo_template:addScreen(love_em);

hate_em = ConvoScreen:new {
	id = "hate_em",
	leftDialog = "@conversation/naboo_privateer_tier3:s_bf22a8c8", -- Can't say I blame 'em. Got no use for them myself. But this Rodian's a real pain in the keister. We think he's killed two ambassadors already.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_24ee6c29", "shooting_politicians"}, -- Someone's always shooting at politicians.
	}
}
dulios_convo_template:addScreen(hate_em);

rodian_killed = ConvoScreen:new {
	id = "rodian_killed",
	leftDialog = "@conversation/naboo_privateer_tier3:s_96924c42", -- A couple of ambassadors, for starters. But that's not why we're interested in him. Word is, his next target is the Queen.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_b8c1a96f", "more_complicated"}, -- Hm. That makes it a little more complicated.
	}
}
dulios_convo_template:addScreen(rodian_killed);

shooting_politicians = ConvoScreen:new {
	id = "shooting_politicians",
	leftDialog = "@conversation/naboo_privateer_tier3:s_919b5558", -- It's not the ambassadors they're worried about. This guy's gunning for the Queen.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_ebe811bd", "more_complicated"}, -- That makes it a little more complicated.
	}
}
dulios_convo_template:addScreen(shooting_politicians);

more_complicated = ConvoScreen:new {
	id = "more_complicated",
	leftDialog = "@conversation/naboo_privateer_tier3:s_d5861157", -- The Royal Family is always a high-profile target, buddy. Believe me. The Queen's got more bounties on her head than you've got toes on your feet.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_692788e8", "find_charmer"}, -- Where can I find this charmer?
	}
}
dulios_convo_template:addScreen(more_complicated);

find_charmer = ConvoScreen:new {
	id = "find_charmer",
	leftDialog = "@conversation/naboo_privateer_tier3:s_f6976b78", -- Sounds like a plan. Go to the Dantooine system. Follow the coordinates on your ship's nav system; should lead you right to him. And you've got the element of surprise - I think.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_a5fe9928", "accept_third_mission"}, -- I'll take care of it.
	}
}
dulios_convo_template:addScreen(find_charmer);

accept_third_mission = ConvoScreen:new {
	id = "accept_third_mission",
	leftDialog = "@conversation/naboo_privateer_tier3:s_b679efe", -- See that you do.
	stopConversation = "true",
	options = {}
}
dulios_convo_template:addScreen(accept_third_mission);

failed_third_mission = ConvoScreen:new {
	id = "failed_third_mission",
	leftDialog = "@conversation/naboo_privateer_tier3:s_cae364a9", -- That Rodian is giving you a run for your money.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_18868d04", "i_was_better"}, -- I was better.
	}
}
dulios_convo_template:addScreen(failed_third_mission);

i_was_better = ConvoScreen:new {
	id = "i_was_better",
	leftDialog = "@conversation/naboo_privateer_tier3:s_2852c031", -- Prove it. Finish your job.
	stopConversation = "true",
	options = {}
}
dulios_convo_template:addScreen(i_was_better);

complete_mission3 = ConvoScreen:new {
	id = "complete_mission3",
	leftDialog = "@conversation/naboo_privateer_tier3:s_b61d6d4f", -- OK! That's one less Rodian messing up the place. Nice work. Time to get back to your training.
	stopConversation = "false",
	options = {}
}
dulios_convo_template:addScreen(complete_mission3);

-- Mission 4: Hunt Human Assassin Beldini

fourth_mission = ConvoScreen:new {
	id = "fourth_mission",
	leftDialog = "@conversation/naboo_privateer_tier3:s_333a7093", -- This is a good one; wish I could do it myself. You're going after a Rodian assassin.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_e7b0a6c9", "another_assassin"}, -- Another assassin?
		{"@conversation/naboo_privateer_tier3:s_719a036e", "who"}, -- Who?
	}
}
dulios_convo_template:addScreen(fourth_mission);

another_assassin = ConvoScreen:new {
	id = "another_assassin",
	leftDialog = "@conversation/naboo_privateer_tier3:s_acc52186", -- There's more?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_c551ea96", "beldini_target"}, -- Looks that way.
	}
}
dulios_convo_template:addScreen(another_assassin);

who = ConvoScreen:new {
	id = "who",
	leftDialog = "@conversation/naboo_privateer_tier3:s_5ed53186", -- A human, name of Beldini. The worst of the bunch. He'd kill ya as soon as look at ya.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_981c060d", "shoot_first"}, -- Then I guess I better shoot first.
	}
}
dulios_convo_template:addScreen(who);

beldini_target = ConvoScreen:new {
	id = "beldini_target",
	leftDialog = "@conversation/naboo_privateer_tier3:s_3c432969", -- Right. Your first target is a human, Beldini. Terrorist, killer, all-around bad guy.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_6bdcb65c", "just_tell_where"}, -- Just tell me where to go.
	}
}
dulios_convo_template:addScreen(beldini_target);

shoot_first = ConvoScreen:new {
	id = "shoot_first",
	leftDialog = "@conversation/naboo_privateer_tier3:s_46eb0ec8", -- First, go to Dantooine. Just follow the data in your nav system. And keep your eyes open. This guy's a professional.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_ff7bebda", "accept_fourth_mission"}, -- Don't let me down, ok? You'd hate to see a grown man cry.
	}
}
dulios_convo_template:addScreen(shoot_first);

just_tell_where = ConvoScreen:new {
	id = "just_tell_where",
	leftDialog = "@conversation/naboo_privateer_tier3:s_46eb0ec8", -- First, go to Dantooine. Just follow the data in your nav system. And keep your eyes open. This guy's a professional.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_f69a2921", "accept_fourth_mission"}, -- Glad to hear it.
	}
}
dulios_convo_template:addScreen(just_tell_where);

accept_fourth_mission = ConvoScreen:new {
	id = "accept_fourth_mission",
	leftDialog = "@conversation/naboo_privateer_tier3:s_3fa8b6f1", -- Coordinates are in your ship. You're clear to leave.
	stopConversation = "true",
	options = {}
}
dulios_convo_template:addScreen(accept_fourth_mission);

failed_fourth_mission = ConvoScreen:new {
	id = "failed_fourth_mission",
	leftDialog = "@conversation/naboo_privateer_tier3:s_145dcab", -- NO! I only like pilots that finish their missions! Get back out there!
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier3:s_b144d69b", "nothing_cant_handle"}, -- Nothing I can't handle.
	}
}
dulios_convo_template:addScreen(failed_fourth_mission);

nothing_cant_handle = ConvoScreen:new {
	id = "nothing_cant_handle",
	leftDialog = "@conversation/naboo_privateer_tier3:s_ff5d0ba8", -- Because those lowlifes are using you for target practice. Get back up there and take those guys out!
	stopConversation = "true",
	options = {}
}
dulios_convo_template:addScreen(nothing_cant_handle);

complete_mission4 = ConvoScreen:new {
	id = "complete_mission4",
	leftDialog = "@conversation/naboo_privateer_tier3:s_ae2d3229", -- I salute you, %TU. You're one heck of a pilot. Is there anything you DON'T know?
	stopConversation = "false",
	options = {}
}
dulios_convo_template:addScreen(complete_mission4);

--[[
	Conversation Enders
]]

not_tier3 = ConvoScreen:new {
	id = "not_tier3",
	leftDialog = "@conversation/naboo_privateer_tier3:s_406e1216", -- Looks like you took a wrong turn somewhere. Scram.
	stopConversation = "true",
	options = {}
}
dulios_convo_template:addScreen(not_tier3);

on_mission = ConvoScreen:new {
	id = "on_mission",
	leftDialog = "@conversation/naboo_privateer_tier3:s_327eb2d6", -- Oh yeah, that's right, I forgot. How about you GO DO THAT ALREADY.
	stopConversation = "true",
	options = {}
}
dulios_convo_template:addScreen(on_mission);

train_warships = ConvoScreen:new {
	id = "train_warships",
	leftDialog = "@conversation/naboo_privateer_tier3:s_89ff8475", -- Obviously. This pilot will give you a lesson. Afterwards, you come see me for your next mission.
	stopConversation = "true",
	options = {}
}
dulios_convo_template:addScreen(train_warships);

train_components = ConvoScreen:new {
	id = "train_components",
	leftDialog = "@conversation/naboo_privateer_tier3:s_9b1d2d87", -- Done. This pilot will give you a lesson. Afterwards, you come see me for your next mission.
	stopConversation = "true",
	options = {}
}
dulios_convo_template:addScreen(train_components);

train_techniques = ConvoScreen:new {
	id = "train_techniques",
	leftDialog = "@conversation/naboo_privateer_tier3:s_bd234730", -- You got it. This pilot will give you a lesson. Afterwards, you come see me for your next mission.
	stopConversation = "true",
	options = {}
}
dulios_convo_template:addScreen(train_techniques);

train_programming = ConvoScreen:new {
	id = "train_programming",
	leftDialog = "@conversation/naboo_privateer_tier3:s_dcf601cc", -- Don't we all! This pilot will give you a lesson. Afterwards, you come see me for your next mission.
	stopConversation = "true",
	options = {}
}
dulios_convo_template:addScreen(train_programming);

addConversationTemplate("dulios_convo_template", dulios_convo_template);
