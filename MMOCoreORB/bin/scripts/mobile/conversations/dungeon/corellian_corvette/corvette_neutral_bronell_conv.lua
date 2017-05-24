corvetteBronellConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "ticketGiverBronellConvoHandler",
	screens = {}
}

already_busy = ConvoScreen:new {
	id = "already_busy",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_dc53bb6d", -- Oh, well I could use your help, but I see that you're already busy. Come back when you've finished your current task and maybe we can do business.
	stopConversation = "true",
	options = {}
}
corvetteBronellConvoTemplate:addScreen(already_busy);

convo_start = ConvoScreen:new {
	id = "convo_start",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_8c30ea7c", -- You there. I must demand your assistance with this mission of utmost importance. You will help, yes? This mission is vital to Lord Jabba and I am only speaking on his behalf. I, of course, get nothing out of this myself. So you will help, yes yes?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_d62f7d90","convo_start_2"}, -- Depends, tell me about this mission?
		{"@conversation/corvette_bronell_neutral_assassin:s_bd40a944","convo_exit"} -- Sorry, I have other things to do.
	}
}
corvetteBronellConvoTemplate:addScreen(convo_start);

convo_exit = ConvoScreen:new {
	id = "convo_exit",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_7d29adc4", -- Then maybe you could leave, yes?
	stopConversation = "true",
	options = {}
}
corvetteBronellConvoTemplate:addScreen(convo_exit);

convo_start_2 = ConvoScreen:new {
	id = "convo_start_2",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_bef20f69", -- Yes, indeed. Lord Hutt has a problem with a person who owes more than he could possibly pay, yes? You know what our venerable Lord does to those who can't pay debts, yes?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_f5dcf8ec","convo_start_3"}, -- Was that a question or a statement?
	}
}
corvetteBronellConvoTemplate:addScreen(convo_start_2);

convo_start_3 = ConvoScreen:new {
	id = "convo_start_3",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_560a7d6e", -- Quiet! I was not done yet, yes? This person is an officer in the Corellian Security Forces and thinks that will protect him, yes? He has incurred debts all over the galaxy, though, and I know a way to find him, yes?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_eece1fb8","quest_start"}, -- I don't know... have you?
	}
}
corvetteBronellConvoTemplate:addScreen(convo_start_3);

quest_start = ConvoScreen:new {
	id = "quest_start",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_832183d2", --Didn't I just say I have, yes? There are three lowly gangs of pirates, and this CorSec officer owes money to each of them, yes? These pirates can be found on Talus, Naboo, and Lok. Any of them may have documented his whereabouts, yes?
	stopConversation = "false",
	options = {}
}
corvetteBronellConvoTemplate:addScreen(quest_start);

which_planet = ConvoScreen:new {
	id = "which_planet",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_f9bdde1d", -- Bah! Fine. Talus, Naboo, or Lok... which planet, yes?
	stopConversation = "false",
	options = {}
}
corvetteBronellConvoTemplate:addScreen(which_planet);

first_location = ConvoScreen:new {
	id = "first_location",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_f7203ef1", -- On Talus resides the despicable gang of pirates called Binayre. Scum they are, yes? Well below our notice normally, but this CorSec officer owes them a small amount of money. Perhaps they have information on CorSec operations that would tell us his location, yes?
	stopConversation = "false",
	options = {}
}
corvetteBronellConvoTemplate:addScreen(first_location);

second_location = ConvoScreen:new {
	id = "second_location",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_469c9070", -- A ragtag bunch of pirates has a hideout there, yes? They are mostly known for kidnapping Naboo royalty, but they indulge in gambling from time to time as well. This CorSec officer owes them money, yes? He has quite a gambling problem, yes?
	stopConversation = "false",
	options = {	}
}
corvetteBronellConvoTemplate:addScreen(second_location);

third_location = ConvoScreen:new {
	id = "third_location",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_e1341a5c", -- I learned of a third option from an informant... well, a former informant. While his tongue was still attached, yes? The Canyon Corsairs on Lok have also dealt with this gambling maniac, yes? They might have the correct information as well, yes?
	stopConversation = "false",
	options = {	}
}
corvetteBronellConvoTemplate:addScreen(third_location);

go_get_intel = ConvoScreen:new {
	id = "go_get_intel",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_b1e7cb8c", -- Excellent! Now hurry my noble warrior, hurry for Bronell...I mean our magnificent Lord Hutt! Yes? Yes.
	stopConversation = "true",
	options = {}
}
corvetteBronellConvoTemplate:addScreen(go_get_intel);

hear_locations_quit = ConvoScreen:new {
	id = "hear_locations_quit",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_ecc1d177", -- Farewell, maybe I'll never see you again, yes?
	stopConversation = "true",
	options = {}
}
corvetteBronellConvoTemplate:addScreen(hear_locations_quit);

back_already = ConvoScreen:new {
	id = "back_already",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_491ecf2b", -- You are back already, yes? You have the documents, yes?
	stopConversation = "false",
	options = {}
}
corvetteBronellConvoTemplate:addScreen(back_already);

back_already_reset = ConvoScreen:new {
	id = "back_already_reset",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_88ef705e", -- Our bountiful Lord will be most disappointed by your response, yes? Also, I must take all documents from you that are connected to this business, yes? Yes.
	stopConversation = "true",
	options = {	}
}
corvetteBronellConvoTemplate:addScreen(back_already_reset);

decline_quest_reset = ConvoScreen:new {
	id = "decline_quest_reset",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_969790d9", -- Fine, get your smelly self out of here, yes?
	stopConversation = "true",
	options = {}
}
corvetteBronellConvoTemplate:addScreen(decline_quest_reset);

check_other_places = ConvoScreen:new {
	id = "check_other_places",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_502c2a8d", -- Splendid! but hurry, yes? Our magnificent Lord is not known for his patience, yes?
	stopConversation = "true",
	options = {}
}
corvetteBronellConvoTemplate:addScreen(check_other_places);

has_intel = ConvoScreen:new {
	id = "has_intel",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_6333f589", -- Let me see that, yes?
	stopConversation = "false",
	options = {	}
}
corvetteBronellConvoTemplate:addScreen(has_intel);

bad_intel_1 = ConvoScreen:new {
	id = "bad_intel_1",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_8c845e29", -- Hmm, yes, yes, completely useless. Here's some credits as compensation for you time. Anything else, yes?
	stopConversation = "false",
	options = {	}
}
corvetteBronellConvoTemplate:addScreen(bad_intel_1);

bad_intel_2 = ConvoScreen:new {
	id = "bad_intel_2",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_e9499aa6", -- Let me see. Hmm, yes, yes...No! Did you even read this? Oh well, guess I have to compensate you for your time, yes? Now check the other hideouts!
	stopConversation = "false",
	options = {	}
}
corvetteBronellConvoTemplate:addScreen(bad_intel_2);

other_documents = ConvoScreen:new {
	id = "other_documents",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_dcf8e793", -- Oh? Let me see that, yes?
	stopConversation = "false",
	options = {	}
}
corvetteBronellConvoTemplate:addScreen(other_documents);

good_intel = ConvoScreen:new {
	id = "good_intel",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_c79b5a4b", -- Splendid, let me see. Hmm, no, no...wait, yes! There he is! So that's where his ship is, yes? You must intercept this corvette and arrange his demise immediately, yes? If you succeed in this, Lord Jabba has allowed me to reward you generously, yes? Yes!
	stopConversation = "false",
	options = {}
}
corvetteBronellConvoTemplate:addScreen(good_intel);

go_to_corvette = ConvoScreen:new {
	id = "go_to_corvette",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_c1d18ea0", -- Go talk to Klaatu outside behind the palace and give him the travel authorization I provided you with, yes? He will make all the arrangements. If you succeed in your mission, return to me for your reward. Now hurry, who knows when the corvette will move on, yes?
	stopConversation = "true",
	options = {}
}
corvetteBronellConvoTemplate:addScreen(go_to_corvette);

launch_location = ConvoScreen:new {
	id = "launch_location",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_3ffc96c6", -- He's outside with the shuttle... back behind this building, Lord Jabba's palace! If you succeed in your mission, return to me for your reward, yes? Now hurry!
	stopConversation = "true",
	options = {}
}
corvetteBronellConvoTemplate:addScreen(launch_location);

still_here = ConvoScreen:new {
	id = "still_here",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_6f1692bf", -- Your still here? I thought I made clear time was not to be wasted looking at the dancers in the palace, yes?
	stopConversation = "false",
	options = {	}
}
corvetteBronellConvoTemplate:addScreen(still_here);

still_here_decline = ConvoScreen:new {
	id = "still_here_decline",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_f8c79456", -- Our bountiful Lord will be most disappointed by your attitude, maybe a bit too disappointed, yes? I'll be forced to take all documents from you that relate to this endeavor, yes?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_79855d10","decline_quest_reset"}, --I'm sorry, I just can't right now. Please erase all records of my progress.
		{"@conversation/corvette_bronell_neutral_assassin:s_bdde1d3a","changed_mind"}, -- You might be right. Fine, I'll get back to it.
	}
}
corvetteBronellConvoTemplate:addScreen(still_here_decline);

changed_mind = ConvoScreen:new {
	id = "changed_mind",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_ce8f15d7", -- Good, now hurry, yes?
	stopConversation = "true",
	options = {}
}
corvetteBronellConvoTemplate:addScreen(changed_mind);

reward = ConvoScreen:new {
	id = "reward",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_1779cf3b", -- Lord Jabba is pleased to hear that the CorSec officer has been eliminated. Let this be a lesson to all who fail to pay their debts to Lord Jabba the Hutt, yes? Are you here to receive your reward, yes?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bronell_neutral_assassin:s_b5022ce5","give_reward"}, -- I am, yes. Hand it over!
		{"@conversation/corvette_bronell_neutral_assassin:s_ffc988c3","ill_be_back"} --  No, not just yet. I'll be back.
	}
}
corvetteBronellConvoTemplate:addScreen(reward);

ill_be_back = ConvoScreen:new {
	id = "ill_be_back",
	leftDialog = "@conversation/corvette_bronell_neutral_assassin:s_44fa5eb9", --As you wish. Though I do not understand why you'd want to delay, yes?
	stopConversation = "true",
	options = {	}
}
corvetteBronellConvoTemplate:addScreen(ill_be_back);

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
