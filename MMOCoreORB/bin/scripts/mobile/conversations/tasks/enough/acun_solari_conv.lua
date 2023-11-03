acun_solari_conv = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "AcunSolariConvoHandler",
	screens = {}
}

neutral_greeting = ConvoScreen:new {
	id = "neutral_greeting",
	leftDialog = "@conversation/c_sink_reb:s_1114", -- Good afternoon!  Nice day, isn't it?  I'm sorry, but I don't have anything that you can do.  I am looking for someone more sympathetic to the Alliance.
	stopConversation = "true",
	options = {}
}
acun_solari_conv:addScreen(neutral_greeting)

imperial_greeting = ConvoScreen:new {
	id = "imperial_greeting",
	leftDialog = "@conversation/c_sink_reb:s_1112", -- What makes you think I will talk to you, thug?
	stopConversation = "true",
	options = {}
}
acun_solari_conv:addScreen(imperial_greeting)

rebel_greeting = ConvoScreen:new {
	id = "rebel_greeting",
	leftDialog = "@conversation/c_sink_reb:s_1116", -- I have a simple assignment for you, if you are interested.  A good friend of mine needs an escort back here.
	stopConversation = "false",
	options = {
		{"@conversation/c_sink_reb:s_1118", "response_1"}, -- Escort from where?  What happened?
	}
}
acun_solari_conv:addScreen(rebel_greeting)

response_1 = ConvoScreen:new {
	id = "response_1",
	leftDialog = "@conversation/c_sink_reb:s_1120", -- He is a pilot and his ship was attacked.  He made it to the escape pod, but now he needs someone to lead him here.
	stopConversation = "false",
	options = {
		{"@conversation/c_sink_reb:s_1122", "response_start"}, -- Any friend of yours is a friend of mine!
		{"@conversation/c_sink_reb:s_1126", "response_deny"}, -- No thank you.  I have other things to do.  There's a war out there, you know.
	}
}
acun_solari_conv:addScreen(response_1)

response_start = ConvoScreen:new {
	id = "response_start",
	leftDialog = "@conversation/c_sink_reb:s_1124", -- Thank you!  I'll be sure to tell the higher-ups of your willingness to help.  The pod crashed north of here.  I'm sure he's keeping out of sight of the local Imperial forces.  I'll radio and let him know you are on your way.  He will follow you here.  I'll have a reward for you when you get back.
	stopConversation = "true",
	options = {}
}
acun_solari_conv:addScreen(response_start)

response_deny = ConvoScreen:new {
	id = "response_deny",
	leftDialog = "@conversation/c_sink_reb:s_1128", -- Sure.  What's one pilot whose life is in danger when you could be out killing to your heart's content?  Are you sure you are in the Rebellion?
	stopConversation = "true",
	options = {}
}
acun_solari_conv:addScreen(response_deny)

where_friend = ConvoScreen:new {
	id = "where_friend",
	leftDialog = "@conversation/c_sink_reb:s_1164", -- I don't see my friend with you.  I guess you should be heading out to get him.
	stopConversation = "false",
	options = {
		{"@conversation/c_sink_reb:s_1166", "new_waypoint"}, -- I need the location again.
	}
}
acun_solari_conv:addScreen(where_friend)

new_waypoint = ConvoScreen:new {
	id = "new_waypoint",
	leftDialog = "@conversation/c_sink_reb:s_1168", -- Go north and look for the crashed Escape Pod.
	stopConversation = "true",
	options = {}
}
acun_solari_conv:addScreen(new_waypoint)

no_pilot = ConvoScreen:new {
	id = "no_pilot",
	leftDialog = "@conversation/c_sink_reb:s_1130", -- Welcome back.  Tell me what happened.
	stopConversation = "false",
	options = {
		{"@conversation/c_sink_reb:s_1132", "time_for_action"}, -- I found a corpse at the crash site and I was attacked by Flails.
	}
}
acun_solari_conv:addScreen(no_pilot)

time_for_action = ConvoScreen:new {
	id = "time_for_action",
	leftDialog = "@conversation/c_sink_reb:s_1134", -- No!  After all that he went through in the war, to get killed by thugs?!  That's it!  I'm done waiting for someone else to take care of these criminals.  It's time to act!
	stopConversation = "false",
	options = {
		{"@conversation/c_sink_reb:s_1136", "explain_more"}, -- What are you talking about?
		{"@conversation/c_sink_reb:s_1156", "help_accept"}, -- What do you need me to do?
		{"@conversation/c_sink_reb:s_1160", "help_decline"}, -- I want no part of your vendetta.  One major enemy is enough.
	}
}
acun_solari_conv:addScreen(time_for_action)

explain_more = ConvoScreen:new {
	id = "explain_more",
	leftDialog = "@conversation/c_sink_reb:s_1138", -- These swoop gangs, smugglers, and pirates!  Beyond what they are doing to innocent people, they give us a bad name.
	stopConversation = "false",
	options = {
		{"@conversation/c_sink_reb:s_1140", "just_gangs1"}, -- What do you mean by that?
	}
}
acun_solari_conv:addScreen(explain_more)

just_gangs1 = ConvoScreen:new {
	id = "just_gangs1",
	leftDialog = "@conversation/c_sink_reb:s_1142", -- Obviously, to the Empire, we are criminals and a threat to their domination.  But to the citizens, we Rebels may be viewed as Freedom Fighters...or as the criminals that the Empire is making us to be.
	options = {
		{"@conversation/c_sink_reb:s_1144", "just_gangs2"}, -- What do the gangs have to do with that?
	}
}
acun_solari_conv:addScreen(just_gangs1)

just_gangs2 = ConvoScreen:new {
	id = "just_gangs2",
	leftDialog = "@conversation/c_sink_reb:s_1146", -- The more the actual pirates and criminal elements terrorize citizens while we do nothing to help them, the more we are lumped in with their ilk.
	options = {
		{"@conversation/c_sink_reb:s_1148", "help_accept"}, -- So, what do you want me to do about it?
		{"@conversation/c_sink_reb:s_1152", "help_decline"}, -- I want no part of your vendetta.  One major enemy is enough.
	}
}
acun_solari_conv:addScreen(just_gangs2)

help_accept = ConvoScreen:new {
	id = "help_accept",
	leftDialog = "@conversation/c_sink_reb:s_1150", -- I want you to go after them.  I know that you cannot eliminate the whole threat yourself, but strike at them.  I have identified two gangs here and on Talus that are strong enough to do some real damage, but not as strong as, say, the Hutt Syndicate.
	stopConversation = "true",
	options = {}
}
acun_solari_conv:addScreen(help_accept)

help_decline = ConvoScreen:new {
	id = "help_decline",
	leftDialog = "@conversation/c_sink_reb:s_1154", -- If we stand aside while evil people take advantage of others, we lose.  But it's your decision.  If you change your mind, let me know.
	stopConversation = "true",
	options = {}
}
acun_solari_conv:addScreen(help_decline)

ground_kill = ConvoScreen:new {
	id = "ground_kill",
	leftDialog = "@conversation/c_sink_reb:s_1170", -- How did it go?
	stopConversation = "false",
	options = {
		--{"@conversation/c_sink_reb:s_1172", "ground_failing"}, -- I haven't started yet.
		--{"@conversation/c_sink_reb:s_1176", "ground_progress"}, -- I'm still working my way through the bad guys.
		--{"@conversation/c_sink_reb:s_1180", "ground_finished"}, -- I have the marks and you have heard about the Flails, I assume.
	}
}
acun_solari_conv:addScreen(ground_kill)

ground_failing = ConvoScreen:new {
	id = "ground_failing",
	leftDialog = "@conversation/c_sink_reb:s_1174", -- Then maybe you should get to it.
	stopConversation = "true",
	options = {}
}
acun_solari_conv:addScreen(ground_failing)

ground_progress = ConvoScreen:new {
	id = "ground_progress",
	leftDialog = "@conversation/c_sink_reb:s_1178", -- I have nothing else to offer you now. Get going!
	stopConversation = "true",
	options = {}
}
acun_solari_conv:addScreen(ground_progress)

ground_finished = ConvoScreen:new {
	id = "ground_finished",
	leftDialog = "@conversation/c_sink_reb:s_1182", -- I did indeed and I'm glad to see that you are as enthusiastic as I am about stopping the growing gang problem.
	stopConversation = "false",
	options = {
		--{"@conversation/c_sink_reb:s_1184", "space_start"}, -- I'd like to do more to help.
		--{"@conversation/c_sink_reb:s_1188", "ground_done"}, -- I am happy to do my part.
	}
}
acun_solari_conv:addScreen(ground_finished)

ground_done = ConvoScreen:new {
	id = "ground_done",
	leftDialog = "@conversation/c_sink_reb:s_1190", -- Let me give you your reward for a job well done.  I think that I'm going to make this my cause.  Let Mon Mothma deal with the Empire.  I want to make sure that if we win, there is something worth having.  Come back to me sometime and I may have something for you to do.
	stopConversation = "true",
	options = {}
}
acun_solari_conv:addScreen(ground_done)

space_start = ConvoScreen:new {
	id = "space_start",
	leftDialog = "@conversation/c_sink_reb:s_1186", -- Good.  I want you to head into space then.  The Hidden Daggers have taken it into their heads to terrorize innocent pilots heading to Corellia.  Destroy them and then I'll reward your properly for your hard work.
	stopConversation = "true",
	options = {}
}
acun_solari_conv:addScreen(space_start)

space_wait = ConvoScreen:new {
	id = "space_wait",
	customDialogText = "It seems that you are not a pilot and the next task will take place among the stars...",
	stopConversation = "true",
	options = {}
}
acun_solari_conv:addScreen(space_wait)

addConversationTemplate("acun_solari_conv", acun_solari_conv)