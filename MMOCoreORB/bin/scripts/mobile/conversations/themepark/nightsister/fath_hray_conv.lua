nightsisterFathHrayConvoTemplate = ConvoTemplate:new {
  initialScreen = "",
  templateType = "Lua",
  luaClassHandler = "nightsisterFathHrayConvoHandler",
  screens = {}
}

intro_has_otherquest = ConvoScreen:new {
  id = "intro_has_otherquest",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:cant_work", -- "I need someone who will dedicate themselves to my assignments. Come back when you are not as occupied."
  stopConversation = "true",
  options = {}
}

nightsisterFathHrayConvoTemplate:addScreen(intro_has_otherquest);

intro_has_wrongfaction = ConvoScreen:new {
  id = "intro_has_wrongfaction",
  leftDialog = "@celebrity/fath_hray:npc_1", -- "You are not one of us..."
  stopConversation = "false",
  options = {
    {"@celebrity/fath_hray:player_1", "choose_leave"}, -- "Sorry, I'll go."
    {"@celebrity/fath_hray:player_2", "choose_ask"}, -- "Who are you?"
  }
}

nightsisterFathHrayConvoTemplate:addScreen(intro_has_wrongfaction);

choose_leave = ConvoScreen:new {
  id = "choose_leave",
  leftDialog = "@celebrity/fath_hray:npc_2", -- "Good!"
  stopConversation = "true",
  options = {}
}

nightsisterFathHrayConvoTemplate:addScreen(choose_leave);

choose_ask = ConvoScreen:new {
  id = "choose_ask",
  leftDialog = "@celebrity/fath_hray:npc_3", -- "We are the Sisters of the Night!"
  stopConversation = "true",
  options = {}
}

nightsisterFathHrayConvoTemplate:addScreen(choose_ask);

tasknpc_but_nomission = ConvoScreen:new {
  id = "tasknpc_but_nomission",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:dontknowyou_2", -- "Away with you. I am on a mission from my clan."
  stopConversation = "true",
  options = {}
}

nightsisterFathHrayConvoTemplate:addScreen(tasknpc_but_nomission);

intro_firstmission = ConvoScreen:new {
  id = "intro_firstmission",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:npc_1_1", -- "Are you here to help, offworlder? I have little time for you if you're not. One of my rancors has escaped from its pen. These creatures take years to train and I don't want to lose all the work that went into this one. Could you help me get it back?"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:player_1_1", "choose_help"}, -- "Yes."
    {"@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:player_2_1", "choose_decline"}, -- "No."
    {"@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:player_3_1", "choose_helpwonder"}, -- "Wouldn't the rancor eat me if I approached it?"
  }
}

nightsisterFathHrayConvoTemplate:addScreen(intro_firstmission);

choose_decline = ConvoScreen:new {
  id = "choose_decline",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:npc_3_1", -- "Why do you waste my time then? Away with you."
  stopConversation = "true",
  options = {}
}

nightsisterFathHrayConvoTemplate:addScreen(choose_decline);

choose_help = ConvoScreen:new {
  id = "choose_help",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:npc_2_1", -- "My scouts reported unusual rancor activity in this area. Go and check it out. If you find my rancor, bring it back here."
  stopConversation = "true",
  options = {}
}

nightsisterFathHrayConvoTemplate:addScreen(choose_help);

choose_helpwonder = ConvoScreen:new {
  id = "choose_helpwonder",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:npc_4_1", -- "Normally yes, but I've sprayed you with a musk that the rancor will recognize. You will be safe and it will follow you back here. Will you do it?"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:player_1_1", "choose_help"}, -- "Yes."
    {"@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:player_2_1", "choose_decline"}, -- "No."
  }
}

nightsisterFathHrayConvoTemplate:addScreen(choose_helpwonder);

return_notdone = ConvoScreen:new {
  id = "return_notdone",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:npc_work_1", -- "Have you found my rancor? I do not wish our rivals to claim this beast."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:player_2_1", "choose_continue"}, -- "No."
  }
}

nightsisterFathHrayConvoTemplate:addScreen(return_notdone);

choose_continue = ConvoScreen:new {
  id = "choose_continue",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:npc_reset_1", -- "I do not have time for those who cannot finish what they begin. If that changes, you may see me again."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:player_sorry", "choose_helpstill"}, -- "I'll keep working on the mission."
    --{"@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:player_sorry", "choose_helpstill_no_wp"}, -- "I'll keep working on the mission."
    {"@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:player_reset", "choose_decline"}, -- "I don't want this mission right now."
  }
}

nightsisterFathHrayConvoTemplate:addScreen(choose_continue);

choose_helpstill = ConvoScreen:new {
  id = "choose_helpstill",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:npc_backtowork_1", -- "Why are you just standing around?"
  stopConversation = "true",
  options = {}
}

nightsisterFathHrayConvoTemplate:addScreen(choose_helpstill);

choose_helpstill_no_wp = ConvoScreen:new {
  id = "choose_helpstill_no_wp",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:npc_noloc_1", -- "Let me verify these coordinates with my scouts. Return in a few moments."
  stopConversation = "true",
  options = {}
}

nightsisterFathHrayConvoTemplate:addScreen(choose_helpstill_no_wp);

return_failed = ConvoScreen:new {
  id = "return_failed",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:npc_failure_1", -- "I've just lost years of hard work and training. I must investigate how this rancor escaped from its pen."
  stopConversation = "true",
  options = {}
}

nightsisterFathHrayConvoTemplate:addScreen(return_failed);

return_success = ConvoScreen:new {
  id = "return_success",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:npc_reward_1", -- "You have done well. Take this as compensation for your efforts."
  stopConversation = "true",
  options = {}
}

nightsisterFathHrayConvoTemplate:addScreen(return_success);

intro_secondmission = ConvoScreen:new {
  id = "intro_secondmission",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:npc_1_2", -- "It appears that Singing Mountain Clan has been raiding our territory looking for rancor nests. They are probably also responsible for freeing the rancors from their pens. I need someone to wipe this raiding party out. Could you handle that?"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:player_1_2", "choose_helptwo"}, -- "Yes."
    {"@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:player_2_2", "choose_declinetwo"}, -- "No."
  }
}

nightsisterFathHrayConvoTemplate:addScreen(intro_secondmission);

choose_declinetwo = ConvoScreen:new {
  id = "choose_declinetwo",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:npc_3_2", -- "I believe you are correct. You probably can't handle a Singing Mountain Clan raiding party."
  stopConversation = "true",
  options = {}
}

nightsisterFathHrayConvoTemplate:addScreen(choose_declinetwo);

choose_helptwo = ConvoScreen:new {
  id = "choose_helptwo",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:npc_2_2", -- "Head to these coordinates. The Singing Mountain Clan's raiding party should be there. Wipe them all out. This will not be easy so you might wish to bring allies."
  stopConversation = "true",
  options = {}
}

nightsisterFathHrayConvoTemplate:addScreen(choose_helptwo);

return_notdone_two = ConvoScreen:new {
  id = "return_notdone_two",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:npc_work_2", -- "Have you destroyed that raiding party? They must be stopped."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:player_2_2", "choose_continuetwo"}, -- "No."
  }
}

nightsisterFathHrayConvoTemplate:addScreen(return_notdone_two);

choose_continuetwo = ConvoScreen:new {
  id = "choose_continuetwo",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:npc_reset_2", -- "I do not have time for those who cannot finish what they begin. If that changes, you may see me again."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:player_sorry", "choose_helpstill_two"}, -- "I'll keep working on the mission."
    --{"@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:player_sorry", "choose_helpstill_two_no_wp"}, -- "I'll keep working on the mission."
    {"@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:player_reset", "choose_declinetwo"}, -- "I don't want this mission right now."
  }
}

nightsisterFathHrayConvoTemplate:addScreen(choose_continuetwo);

choose_helpstill_two = ConvoScreen:new {
  id = "choose_helpstill_two",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:npc_backtowork_2", -- "Ogling me won't help you accomplish this goal."
  stopConversation = "true",
  options = {}
}

nightsisterFathHrayConvoTemplate:addScreen(choose_helpstill_two);

choose_helpstill_two_no_wp = ConvoScreen:new {
  id = "choose_helpstill_two_no_wp",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:npc_noloc_2", -- "I must verify the coordinates with my scouts. Come back in a few moments."
  stopConversation = "true",
  options = {}
}

nightsisterFathHrayConvoTemplate:addScreen(choose_helpstill_two_no_wp);

tasknpc_found_two = ConvoScreen:new {
  id = "tasknpc_found_two",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray::npc_breech_2", -- "A stranger approaches, sisters! Be on your guard!"
  stopConversation = "true",
  options = {}
}

nightsisterFathHrayConvoTemplate:addScreen(tasknpc_found_two);


return_failedtwo = ConvoScreen:new {
  id = "return_failedtwo",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:npc_failure_2", -- "I must find a way to dispose of this raiding party. Perhaps I will go personally."
  stopConversation = "true",
  options = {}
}

nightsisterFathHrayConvoTemplate:addScreen(return_failedtwo);

return_successtwo = ConvoScreen:new {
  id = "return_successtwo",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:npc_reward_2", -- "Well done. You are efficient, for an offworlder. Claim your reward."
  stopConversation = "true",
  options = {}
}

nightsisterFathHrayConvoTemplate:addScreen(return_successtwo);

return_all_done = ConvoScreen:new {
  id = "return_all_done",
  leftDialog = "@static_npc/dathomir/dathomir_nightsisterstronghold_fath_hray:next", -- "I have nothing further for you at present."
  stopConversation = "true",
  options = {}
}

nightsisterFathHrayConvoTemplate:addScreen(return_all_done);

addConversationTemplate("nightsisterFathHrayConvoTemplate", nightsisterFathHrayConvoTemplate);