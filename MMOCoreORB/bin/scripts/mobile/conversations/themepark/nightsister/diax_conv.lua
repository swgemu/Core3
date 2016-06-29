nightsisterDiaxConvoTemplate = ConvoTemplate:new {
  initialScreen = "",
  templateType = "Lua",
  luaClassHandler = "nightsisterDiaxConvoHandler",
  screens = {}
}

intro_has_otherquest = ConvoScreen:new {
  id = "intro_has_otherquest",
  leftDialog = "@static_npc/dathomir/diax:cant_work", -- "You look a bit preoccupied. Why don't you take care of whatever it is you're doing now and come back. I may have work for you."
  stopConversation = "true",
  options = {}
}

nightsisterDiaxConvoTemplate:addScreen(intro_has_otherquest);

intro_hasnt_progress = ConvoScreen:new {
  id = "intro_hasnt_progress",
  leftDialog = "@static_npc/dathomir/diax:notyet", -- "You may have potential, but I do not know if you are ready to serve. Come back after you have helped us more."
  stopConversation = "true",
  options = {}
}

nightsisterDiaxConvoTemplate:addScreen(intro_hasnt_progress);

intro_has_wrongfaction = ConvoScreen:new {
  id = "intro_has_wrongfaction",
  leftDialog = "@celebrity/diax:npc_1", -- "You are not one of us..."
  stopConversation = "false",
  options = {
    {"@celebrity/diax:player_1", "choose_leave"}, -- "Sorry, I'll go."
    {"@celebrity/diax:player_2", "choose_ask"}, -- "Who are you?"
  }
}

nightsisterDiaxConvoTemplate:addScreen(intro_has_wrongfaction);

choose_leave = ConvoScreen:new {
  id = "choose_leave",
  leftDialog = "@celebrity/diax:npc_2", -- "Good!"
  stopConversation = "true",
  options = {}
}

nightsisterDiaxConvoTemplate:addScreen(choose_leave);

choose_ask = ConvoScreen:new {
  id = "choose_ask",
  leftDialog = "@celebrity/diax:npc_3", -- "We are the Sisters of the Night!"
  stopConversation = "true",
  options = {}
}

nightsisterDiaxConvoTemplate:addScreen(choose_ask);

intro_firstmission = ConvoScreen:new {
  id = "intro_firstmission",
  leftDialog = "@static_npc/dathomir/diax:npc_1_1", -- "Yes? Come closer. You'll do nicely, outsider. I'm struggling with a dilemma. I'm an apprentice healer in the service of Kais. I find myself constantly competing for her favor with another apprentice. Would you object to making sure she never hinders me again?"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/diax:player_3_1", "choose_helpwonder"}, -- "Why?"
    {"@static_npc/dathomir/diax:player_2_1", "choose_decline"}, -- "Kill her? No way!"
  }
}

nightsisterDiaxConvoTemplate:addScreen(intro_firstmission);

choose_helpwonder = ConvoScreen:new {
  id = "choose_helpwonder",
  leftDialog = "@static_npc/dathomir/diax:npc_4_1", -- "I'd take care of this myself, but it would reflect poorly on the healers if I did. The rest of the clan shouldn't see us as political schemers. The last thing I need is Kais to see me as overly ambitious. If you help me with this dilemma I'll be sure to reward you well."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/diax:player_1_1", "choose_help"}, -- "I will do it."
  }
}

nightsisterDiaxConvoTemplate:addScreen(choose_helpwonder);

choose_decline = ConvoScreen:new {
  id = "choose_decline",
  leftDialog = "@static_npc/dathomir/diax:npc_3_1", -- "Hah, timid mouse. Very well then, there is more than one way to skin a brackaset."
  stopConversation = "true",
  options = {}
}

nightsisterDiaxConvoTemplate:addScreen(choose_decline);

choose_help = ConvoScreen:new {
  id = "choose_help",
  leftDialog = "@static_npc/dathomir/diax:npc_2_1", -- "That's fine. Daverda is currently gathering herbs near the location I've marked on this map. Go there, kill her, and return quickly."
  stopConversation = "true",
  options = {}
}

nightsisterDiaxConvoTemplate:addScreen(choose_help);

return_notdone = ConvoScreen:new {
  id = "return_notdone",
  leftDialog = "@static_npc/dathomir/diax:npc_work_1", -- "You're not scared are you? Look, she's not all that tough. I'd do it myself if it weren't for certain political entanglements."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/diax:player_sorry", "choose_helpstill"}, -- "Where did you say she was again?"
    --{"@static_npc/dathomir/diax:player_sorry", "choose_helpstill_no_wp"}, -- "Where did you say she was again?"
    {"@static_npc/dathomir/diax:player_reset", "choose_declinetoo"}, -- "I'm not ready for this."
  }
}

nightsisterDiaxConvoTemplate:addScreen(return_notdone);

choose_declinetoo = ConvoScreen:new {
  id = "choose_declinetoo",
  leftDialog = "@static_npc/dathomir/diax:npc_reset", -- "Well, perhaps you are correct. Come back when you feel up to the challenge."
  stopConversation = "true",
  options = {}
}

nightsisterDiaxConvoTemplate:addScreen(choose_declinetoo);

choose_helpstill = ConvoScreen:new {
  id = "choose_helpstill",
  leftDialog = "@static_npc/dathomir/diax:npc_backtowork_1", -- "She's out gathering herbs for Kais. Look at this map I made. Right here. Now hurry."
  stopConversation = "true",
  options = {}
}

nightsisterDiaxConvoTemplate:addScreen(choose_helpstill);

choose_helpstill_no_wp = ConvoScreen:new {
  id = "choose_helpstill_no_wp",
  leftDialog = "@static_npc/dathomir/diax:npc_noloc_1", -- "Something is not right here. Come back later, I may have work for you then."
  stopConversation = "true",
  options = {}
}

nightsisterDiaxConvoTemplate:addScreen(choose_helpstill_no_wp);

tasknpc_found = ConvoScreen:new {
  id = "tasknpc_found",
  leftDialog = "@static_npc/dathomir/diax:npc_breech_1", -- "What are you doing here?"
  stopConversation = "true",
  options = {}
}

nightsisterDiaxConvoTemplate:addScreen(tasknpc_found);

return_failed = ConvoScreen:new {
  id = "return_failed",
  leftDialog = "@static_npc/dathomir/diax:npc_failure_1", -- "By the book of shadows, these outworlders are inept."
  stopConversation = "true",
  options = {}
}

nightsisterDiaxConvoTemplate:addScreen(return_failed);

return_drag_item = ConvoScreen:new {
  id = "return_drag_item",
  leftDialog = "@static_npc/dathomir/diax:notit_1", -- "You realize this is not what I asked for at all? What made you think this is what I wanted? By the book of shadows, these outworlders are inept."
  stopConversation = "true",
  options = {}
}

nightsisterDiaxConvoTemplate:addScreen(return_drag_item);

return_success = ConvoScreen:new {
  id = "return_success",
  leftDialog = "@static_npc/dathomir/diax:npc_reward_1", -- "Ah, she is... dead? Oh lovely. I'm glad you are working for me. Yes, you are such a wonderful little pet. As promised - here is your treat, pet."
  stopConversation = "true",
  options = {}
}

nightsisterDiaxConvoTemplate:addScreen(return_success);

intro_secondmission = ConvoScreen:new {
  id = "intro_secondmission",
  leftDialog = "@static_npc/dathomir/diax:npc_1_2", -- "You have done well so far. I have another task for you. Our spies report having seen a certain singing mountain clan healer using an incredibly effective salve. From what I am told the salve sounds like something I read about once, I believe it was called bac-ta. Are you willing to find this healer and bring me her salve to study?"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/diax:player_3_2", "choose_helpwonder_two"}, -- "Why should I?"
    {"@static_npc/dathomir/diax:player_2_2", "choose_declinetwo"}, -- "No, I will not."
  }
}

nightsisterDiaxConvoTemplate:addScreen(intro_secondmission);

choose_helpwonder_two = ConvoScreen:new {
  id = "choose_helpwonder_two",
  leftDialog = "@static_npc/dathomir/diax:npc_4_2", -- "Do this for me and I will let Kais know you can be trusted. Also I will reward you with a kit of healing herbs and poultices."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/diax:player_1_2", "choose_helptwo"}, -- "Yes, I will."
  }
}

nightsisterDiaxConvoTemplate:addScreen(choose_helpwonder_two);

choose_declinetwo = ConvoScreen:new {
  id = "choose_declinetwo",
  leftDialog = "@static_npc/dathomir/diax:npc_3_2", -- "Outworlder, you try my patience."
  stopConversation = "true",
  options = {}
}

nightsisterDiaxConvoTemplate:addScreen(choose_declinetwo);

choose_helptwo = ConvoScreen:new {
  id = "choose_helptwo",
  leftDialog = "@static_npc/dathomir/diax:npc_2_2", -- "Good. The scouts report her location over that way. Don't try to negotiate with her. Just eliminate her as quickly and efficiently as possible. I do not want the Singing Mountain Clan to know we have stolen their secret. Once you have the salve, return it to me."
  stopConversation = "true",
  options = {}
}

nightsisterDiaxConvoTemplate:addScreen(choose_helptwo);

return_notdonetwo = ConvoScreen:new {
  id = "return_notdonetwo",
  leftDialog = "@static_npc/dathomir/diax:npc_work_2", -- "I suggest you start out immediately."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/diax:player_sorry", "choose_helpstill_two"}, -- "Where did you say she was again?"
    --{"@static_npc/dathomir/diax:player_sorry", "choose_helpstill_two_no_wp"}, -- "Where did you say she was again?"
    {"@static_npc/dathomir/diax:player_reset", "choose_declinetoo"}, -- "I'm not ready for this."
  }
}

nightsisterDiaxConvoTemplate:addScreen(return_notdonetwo);

choose_helpstill_two = ConvoScreen:new {
  id = "choose_helpstill_two",
  leftDialog = "@static_npc/dathomir/diax:npc_backtowork_2", -- "Look, here is my map. Study it carefully. The healer was spotted in this area. Now get going!"
  stopConversation = "true",
  options = {}
}

nightsisterDiaxConvoTemplate:addScreen(choose_helpstill_two);

choose_helpstill_two_no_wp = ConvoScreen:new {
  id = "choose_helpstill_two_no_wp",
  leftDialog = "@static_npc/dathomir/diax:npc_noloc_2", -- "Something is not right here. Come back later, I may have work for you then."
  stopConversation = "true",
  options = {}
}

nightsisterDiaxConvoTemplate:addScreen(choose_helpstill_two_no_wp);

tasknpc_found_two = ConvoScreen:new {
  id = "tasknpc_found_two",
  leftDialog = "@static_npc/dathomir/diax:npc_breech_2", -- "I'm not looking for company. Go away."
  stopConversation = "true",
  options = {}
}

nightsisterDiaxConvoTemplate:addScreen(tasknpc_found_two);

return_failed_two = ConvoScreen:new {
  id = "return_failed_two",
  leftDialog = "@static_npc/dathomir/diax:npc_failure_2", -- "By the book of shadows, these outworlders are inept."
  stopConversation = "true",
  options = {}
}

nightsisterDiaxConvoTemplate:addScreen(return_failed_two);

return_drag_item_two = ConvoScreen:new {
  id = "return_drag_item_two",
  leftDialog = "@static_npc/dathomir/diax:notit_2", -- "You realize this is not what I asked for at all? What made you think this is what I wanted? By the book of shadows, these outworlders are inept."
  stopConversation = "true",
  options = {}
}

nightsisterDiaxConvoTemplate:addScreen(return_drag_item_two);

return_success_two = ConvoScreen:new {
  id = "return_success_two",
  leftDialog = "@static_npc/dathomir/diax:npc_reward_2", -- "You have the salve? Give it to me at once. Hmm, what an odd smell. Familiar, but I just can't place it. Very well, here is your reward. Kais should be waiting for you. I must study the salve. Leave."
  stopConversation = "true",
  options = {}
}

nightsisterDiaxConvoTemplate:addScreen(return_success_two);

return_all_done = ConvoScreen:new {
  id = "return_all_done",
  leftDialog = "@static_npc/dathomir/diax:next", -- "You are worthy of the honor of helping my mistress Kais. Go speak with her now."
  stopConversation = "true",
  options = {}
}

nightsisterDiaxConvoTemplate:addScreen(return_all_done);

addConversationTemplate("nightsisterDiaxConvoTemplate", nightsisterDiaxConvoTemplate);