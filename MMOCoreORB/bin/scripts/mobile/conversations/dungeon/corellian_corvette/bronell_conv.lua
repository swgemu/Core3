corvetteBronellConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "ticketGiverBronellConvoHandler",
	screens = {}
}

no_business = ConvoScreen:new {
	id = "no_business",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_382a91bd", -- I have no business with you at this time... and by that I mean Lord Jabba the Hutt has no need for me to do business with you at this time. Perhaps in the future, but not now.
	stopConversation = "true",
	options = {}
}

corvetteBronellConvoTemplate:addScreen(no_business);

already_busy = ConvoScreen:new {
	id = "already_busy",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_dc53bb6d", -- Oh, well I could use your help, but I see that you're already busy. Come back when you've finished your current task and maybe we can do business.
	stopConversation = "true",
	options = {}
}

corvetteBronellConvoTemplate:addScreen(already_busy);

start = ConvoScreen:new {
	id = "start",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_8c30ea7c", -- You there. I must demand your assistance with this mission of utmost importance. You will help, yes? This mission is vital to Lord Jabba and I am only speaking on his behalf. I, of course, get nothing out of this myself. So you will help, yes yes?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_d62f7d90","hutt_has_problem"}, -- Depends, tell me about this mission?
		{"@conversation/corvette_bronell_neutral_assassin:s_bd40a944","you_could_leave"} -- Sorry, I have other things to do.
	}
}

corvetteBronellConvoTemplate:addScreen(start);

you_could_leave = ConvoScreen:new {
	id = "you_could_leave",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_7d29adc4", -- Then maybe you could leave, yes?
	stopConversation = "true",
	options = {}
}

corvetteBronellConvoTemplate:addScreen(you_could_leave);

hutt_has_problem = ConvoScreen:new {
	id = "hutt_has_problem",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_bef20f69", -- Yes, indeed. Lord Hutt has a problem with a person who owes more than he could possibly pay, yes? You know what our venerable Lord does to those who can't pay debts, yes?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_24dbc07d","quiet"} -- I believe so.
	}
}

corvetteBronellConvoTemplate:addScreen(hutt_has_problem);

quiet = ConvoScreen:new {
	id = "quiet",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_560a7d6e", -- Quiet! I was not done yet, yes? This person is an officer in the Corellian Security Forces and thinks that will protect him, yes? He has incurred debts all over the galaxy, though, and I know a way to find him, yes?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_eece1fb8","three_gangs"} -- I don't know... have you?
	}
}

corvetteBronellConvoTemplate:addScreen(quiet);

three_gangs = ConvoScreen:new {
	id = "three_gangs",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_832183d2", -- Didn't I just say I have, yes? There are three lowly gangs of pirates, and this CorSec officer owes money to each of them, yes? These pirates can be found on Talus, Naboo, and Lok. Any of them may have documented his whereabouts, yes?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_f5dcf8ec","which_planet"}, -- Was that a question or a statement?
		{"@conversation/corvette_bronell_neutral_assassin:s_85bcb083","smelly_self"} -- Sounds too much like something I'd want no part of, sorry.
	}
}

corvetteBronellConvoTemplate:addScreen(three_gangs);

smelly_self = ConvoScreen:new {
	id = "smelly_self",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_969790d9", -- Fine, get your smelly self out of here, yes?
	stopConversation = "true",
	options = {}
}

corvetteBronellConvoTemplate:addScreen(smelly_self);

which_planet = ConvoScreen:new {
	id = "which_planet",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_f9bdde1d", -- Bah! Fine. Talus, Naboo, or Lok... which planet, yes?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_94bc6e8f","on_talus"}, -- Talus, yes? I mean, Talus?
		{"@conversation/corvette_bronell_neutral_assassin:s_2ad476a3","on_naboo"}, -- Naboo, ok.
		{"@conversation/corvette_bronell_neutral_assassin:s_ba696f5d","on_lok"} -- Lok, yes? Bah, look what you did to me.
	}
}

corvetteBronellConvoTemplate:addScreen(which_planet);

on_talus = ConvoScreen:new {
	id = "on_talus",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_f7203ef1", -- On Talus resides the despicable gang of pirates called Binayre. Scum they are, yes? Well below our notice normally, but this CorSec officer owes them a small amount of money. Perhaps they have information on CorSec operations that would tell us his location, yes?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_76e2b2f6","go_get_intel"}, -- Alright, I'll try and get the information we need.
		{"@conversation/corvette_bronell_neutral_assassin:s_9b8c1f57","which_planet"}, -- Could you go over the planets and pirates part again?
	}
}

corvetteBronellConvoTemplate:addScreen(on_talus);

on_naboo = ConvoScreen:new {
	id = "on_naboo",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_469c9070", -- A ragtag bunch of pirates has a hideout there, yes? They are mostly known for kidnapping Naboo royalty, but they indulge in gambling from time to time as well. This CorSec officer owes them money, yes? He has quite a gambling problem, yes?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_76e2b2f6","go_get_intel"}, -- Alright, I'll try and get the information we need.
		{"@conversation/corvette_bronell_neutral_assassin:s_9b8c1f57","which_planet"}, -- Could you go over the planets and pirates part again?
	}
}

corvetteBronellConvoTemplate:addScreen(on_naboo);

on_lok = ConvoScreen:new {
	id = "on_lok",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_e1341a5c", -- I learned of a third option from an informant... well, a former informant. While his tongue was still attached, yes? The Canyon Corsairs on Lok have also dealt with this gambling maniac, yes? They might have the correct information as well, yes?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_76e2b2f6","go_get_intel"}, -- Alright, I'll try and get the information we need.
		{"@conversation/corvette_bronell_neutral_assassin:s_9b8c1f57","which_planet"}, -- Could you go over the planets and pirates part again?
	}
}

corvetteBronellConvoTemplate:addScreen(on_lok);

go_get_intel = ConvoScreen:new {
	id = "go_get_intel",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_b1e7cb8c", -- Excellent! Now hurry my noble warrior, hurry for Bronell...I mean our magnificent Lord Hutt! Yes? Yes.
	stopConversation = "true",
	options = {}
}

corvetteBronellConvoTemplate:addScreen(go_get_intel);

back_already = ConvoScreen:new {
	id = "back_already",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_491ecf2b", -- You are back already, yes? You have the documents, yes?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_ffc988c3","splendid"}, -- No, not just yet. I'll be back.
		{"@conversation/corvette_bronell_neutral_assassin:s_9b8c1f57","which_planet"}, -- Could you go over the planets and pirates part again?
		{"@conversation/corvette_bronell_neutral_assassin:s_79855d10","reset"} -- I'm sorry, I just can't right now. Please erase all records of my progress.
	}
}

corvetteBronellConvoTemplate:addScreen(back_already);

splendid = ConvoScreen:new {
	id = "splendid",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_502c2a8d", -- Splendid but hurry, yes? Our magnificent Lord is not known for his patience, yes?
	stopConversation = "true",
	options = {}
}

corvetteBronellConvoTemplate:addScreen(splendid);

reset = ConvoScreen:new {
	id = "reset",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_44fa5eb9", -- As you wish. Though I do not understand why you'd want to delay, yes?
	stopConversation = "true",
	options = {}
}

corvetteBronellConvoTemplate:addScreen(reset);

has_intel = ConvoScreen:new {
	id = "has_intel",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_6333f589", -- Let me see that, yes?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_3f04cefb","bad_intel_1"}, -- Here, take a look at this Research Request.
		{"@conversation/corvette_bronell_neutral_assassin:s_fecfb00f","bad_intel_2"}, -- Here, take a look at this Purchase Request Form.
		{"@conversation/corvette_bronell_neutral_assassin:s_465d7ab2","good_intel"} -- Here, take a look at this Gambling Debt List.
	}
}

corvetteBronellConvoTemplate:addScreen(has_intel);

bad_intel_1 = ConvoScreen:new {
	id = "bad_intel_1",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_8c845e29", -- Hmm, yes, yes, completely useless. Here's some credits as compensation for you time. Anything else, yes?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_d27dcffe","other_documents"}, -- I had some other documents I came across.
		{"@conversation/corvette_bronell_neutral_assassin:s_c5ae9239","now_hurry"}, -- On my way to check one of the other hideouts.
	}
}

corvetteBronellConvoTemplate:addScreen(bad_intel_1);

bad_intel_2 = ConvoScreen:new {
	id = "bad_intel_2",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_e9499aa6", -- Let me see. Hmm, yes, yes...No! Did you even read this? Oh well, guess I have to compensate you for your time, yes? Now check the other hideouts!
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_d27dcffe","other_documents"}, -- I had some other documents I came across.
		{"@conversation/corvette_bronell_neutral_assassin:s_c5ae9239","now_hurry"} -- On my way to check one of the other hideouts.
	}
}

corvetteBronellConvoTemplate:addScreen(bad_intel_2);

now_hurry = ConvoScreen:new {
	id = "now_hurry",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_ce8f15d7", -- Good, now hurry, yes?
	stopConversation = "true",
	options = {}
}

corvetteBronellConvoTemplate:addScreen(now_hurry);

other_documents = ConvoScreen:new {
	id = "other_documents",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_dcf8e793", -- Oh? Let me see that, yes?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_3f04cefb","bad_intel_1"}, -- Here, take a look at this Research Request.
		{"@conversation/corvette_bronell_neutral_assassin:s_fecfb00f","bad_intel_2"}, -- Here, take a look at this Purchase Request Form.
		{"@conversation/corvette_bronell_neutral_assassin:s_465d7ab2","good_intel"} -- Here, take a look at this Gambling Debt List.
	}
}

corvetteBronellConvoTemplate:addScreen(other_documents);

good_intel = ConvoScreen:new {
	id = "good_intel",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_c79b5a4b", -- Splendid, let me see. Hmm, no, no...wait, yes! There he is! So that's where his ship is, yes? You must intercept this corvette and arrange his demise immediately, yes? If you succeed in this, Lord Jabba has allowed me to reward you generously, yes? Yes!
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_3c2e92a","go_to_corvette"}, -- Alright, but how do I get to the corvette?
		{"@conversation/corvette_bronell_neutral_assassin:s_3e2e8616","too_disappointed"} -- Sorry, I have other things to do. Erase all knowledge of my progress.
	}
}

corvetteBronellConvoTemplate:addScreen(good_intel);

go_to_corvette = ConvoScreen:new {
	id = "go_to_corvette",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_c1d18ea0", -- Go talk to Klaatu outside behind the palace and give him the travel authorization I provided you with, yes? He will make all the arrangements. If you succeed in your mission, return to me for your reward. Now hurry, who knows when the corvette will move on, yes?
	stopConversation = "true",
	options = {}
}

corvetteBronellConvoTemplate:addScreen(go_to_corvette);

too_disappointed = ConvoScreen:new {
	id = "too_disappointed",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_f8c79456", -- Our bountiful Lord will be most disappointed by your attitude, maybe a bit too disappointed, yes? I'll be forced to take all documents from you that relate to this endeavor, yes?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_bdde1d3a","go_to_corvette"}, -- You might be right. Fine, I'll get back to it.
		{"@conversation/corvette_bronell_neutral_assassin:s_a4929123","reset3"}, -- Fine, just don't hurt me.
	}
}

corvetteBronellConvoTemplate:addScreen(too_disappointed);

reset3 = ConvoScreen:new {
	id = "reset3",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_ecc1d177", -- Farewell, maybe I'll never see you again, yes?
	stopConversation = "true",
	options = {}
}

corvetteBronellConvoTemplate:addScreen(reset3);

still_here = ConvoScreen:new {
	id = "still_here",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_6f1692bf", -- Your still here? I thought I made clear time was not to be wasted looking at the dancers in the palace, yes?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_2972f7c","with_shuttle"}, -- Where was Klaatu again?
		{"@conversation/corvette_bronell_neutral_assassin:s_4a365e4b","disappointed"}, -- Sorry, you'll have to find someone else. I cannot continue with this mission.
	}
}

corvetteBronellConvoTemplate:addScreen(still_here);

with_shuttle = ConvoScreen:new {
	id = "with_shuttle",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_3ffc96c6", -- He's outside with the shuttle... back behind this building, Lord Jabba's palace! If you succeed in your mission, return to me for your reward, yes? Now hurry!
	stopConversation = "true",
	options = {}
}

corvetteBronellConvoTemplate:addScreen(with_shuttle);

disappointed = ConvoScreen:new {
	id = "disappointed",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_88ef705e", -- Our bountiful Lord will be most disappointed by your response, yes? Also, I must take all documents from you that are connected to this business, yes? Yes.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_12eb211c","reset2"} -- Yes? Yes! I've had enough, goodbye.
	}
}

corvetteBronellConvoTemplate:addScreen(disappointed);

reset2 = ConvoScreen:new {
	id = "reset2",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_ad79e41e", -- Give me all documents.
	stopConversation = "false",
	options = {}
}

corvetteBronellConvoTemplate:addScreen(reset2);

reward = ConvoScreen:new {
	id = "reward",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_1779cf3b", -- Lord Jabba is pleased to hear that the CorSec officer has been eliminated. Let this be a lesson to all who fail to pay their debts to Lord Jabba the Hutt, yes? Are you here to receive your reward, yes?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_b5022ce5","give_reward"} -- I am, yes. Hand it over!
	}
}

corvetteBronellConvoTemplate:addScreen(reward);

give_reward = ConvoScreen:new {
	id = "give_reward",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_249447d6", -- Very well. It has been well earned, yes? Yes.
	stopConversation = "true",
	options = {}
}

corvetteBronellConvoTemplate:addScreen(give_reward);

cant_give_reward = ConvoScreen:new {
	id = "cant_give_reward",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_73f00073", -- Hmm... you have truly earned your reward, but you do not have room for it in your inventory, yes? Please come back and speak with me after clearing some space, yes?
	stopConversation = "true",
	options = {}
}

corvetteBronellConvoTemplate:addScreen(cant_give_reward);

addConversationTemplate("corvetteBronellConvoTemplate", corvetteBronellConvoTemplate);

