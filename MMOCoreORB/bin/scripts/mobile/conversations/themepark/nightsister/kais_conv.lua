nightsisterKaisConvoTemplate = ConvoTemplate:new {
  initialScreen = "",
  templateType = "Lua",
  luaClassHandler = "nightsisterKaisConvoHandler",
  screens = {}
}

intro_has_otherquest = ConvoScreen:new {
  id = "intro_has_otherquest",
  leftDialog = "@static_npc/dathomir/kais:cant_work", -- "You walk within my hearth, but yet you pridefully belong to another. I will not tolerate this. Begone with you."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(intro_has_otherquest);

intro_hasnt_progress = ConvoScreen:new {
  id = "intro_hasnt_progress",
  leftDialog = "@static_npc/dathomir/kais:notyet", -- "I look at you and see a bag of decaying flesh, one that lives only to die. Show yourself to the younger one, and ask her what she sees."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(intro_hasnt_progress);

intro_has_wrongfaction = ConvoScreen:new {
  id = "intro_has_wrongfaction",
  leftDialog = "@celebrity/kais:npc_1", -- "You are not one of us..."
  stopConversation = "false",
  options = {
    {"@celebrity/kais:player_1", "choose_leave"}, -- "Sorry, I'll go."
    {"@celebrity/kais:player_2", "choose_ask"}, -- "Who are you?"
  }
}

nightsisterKaisConvoTemplate:addScreen(intro_has_wrongfaction);

choose_leave = ConvoScreen:new {
  id = "choose_leave",
  leftDialog = "@celebrity/kais:npc_2", -- "Good!"
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(choose_leave);

choose_ask = ConvoScreen:new {
  id = "choose_ask",
  leftDialog = "@celebrity/kais:npc_3", -- "We are the Sisters of the Night!"
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(choose_ask);

tasknpc_but_nomission = ConvoScreen:new {
  id = "tasknpc_but_nomission",
  leftDialog = "@static_npc/dathomir/kais:dontknowyou_3", -- "Wait, you're not the guy who I'm supposed to meet. Get out of here before I have you arrested."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(tasknpc_but_nomission);

intro_firstmission = ConvoScreen:new {
  id = "intro_firstmission",
  leftDialog = "@static_npc/dathomir/kais:npc_1_1", -- "Sit and drink. You have been watched and deemed worthy to offer your services. You will venture into the dark of the forests and gaze upon the fangs of a Gaping Spider for me, correct? "
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/kais:player_3_1", "choose_helpwonder"}, -- "Why would I face such a trial?"
  }
}

nightsisterKaisConvoTemplate:addScreen(intro_firstmission);

choose_helpwonder = ConvoScreen:new {
  id = "choose_helpwonder",
  leftDialog = "@static_npc/dathomir/kais:npc_4_1", -- "The Clan Mother, Gethzerion, has wisely called upon my skills as a healer. I will heal any wounds that shall arise with the Imperials, but to do so, I need the power of the Gaping Spider within my hands. You will give me that power, will you not?"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/kais:player_1_1", "choose_help"}, -- "Yes, I will do so."
    {"@static_npc/dathomir/kais:player_2_1", "choose_decline"}, -- "Heck no I won't!!!"
  }
}

nightsisterKaisConvoTemplate:addScreen(choose_helpwonder);

choose_decline = ConvoScreen:new {
  id = "choose_decline",
  leftDialog = "@static_npc/dathomir/kais:npc_3_1", -- "Then your desire is to feel your insides cramp with discomfort until your intestines burst from your belly? If you deny my will, then that drink you consumed shall do just that."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(choose_decline);

choose_help = ConvoScreen:new {
  id = "choose_help",
  leftDialog = "@static_npc/dathomir/kais:npc_2_1", -- "Yes, you will. Arm yourself with your worthless weapons and defeat the eight-legged horror. Once you have quenched its life, reach inside its maw and rip out its poison glands. Only then will you return to me."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(choose_help);

return_notdone = ConvoScreen:new {
  id = "return_notdone",
  leftDialog = "@static_npc/dathomir/kais:npc_work_1", -- "Has fear become your enemy rather than your ally?"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/kais:player_sorry", "choose_helpstill"}, -- "What do you require of me again?"
    --{"@static_npc/dathomir/kais:player_sorry", "choose_helpstill_no_wp"}, -- "What do you require of me again?"
    {"@static_npc/dathomir/kais:player_reset", "choose_declinetoo"}, -- " I refuse to help any further, old woman!"
  }
}

nightsisterKaisConvoTemplate:addScreen(return_notdone);

choose_declinetoo = ConvoScreen:new {
  id = "choose_declinetoo",
  leftDialog = "@static_npc/dathomir/kais:npc_reset", -- "Then you are no longer useful to me. If you wish the cure to the poison within your system, prove your worth to me...."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(choose_declinetoo);

choose_helpstill = ConvoScreen:new {
  id = "choose_helpstill",
  leftDialog = "@static_npc/dathomir/kais:npc_backtowork_1", -- "You will venture into the forest and combat a Gaping Spider. Return with its poison sacs."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(choose_helpstill);

choose_helpstill_no_wp = ConvoScreen:new {
  id = "choose_helpstill_no_wp",
  leftDialog = "@static_npc/dathomir/kais:npc_noloc_1", -- "The time is not right for the Spiders to hunt. Ask again in a little while."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(choose_helpstill_no_wp);

return_failed = ConvoScreen:new {
  id = "return_failed",
  leftDialog = "@static_npc/dathomir/kais:npc_failure_1", -- "You have failed me, and in turn you have failed yourself. Your death will be slow, but needed."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(return_failed);

return_drag_item = ConvoScreen:new {
  id = "return_drag_item",
  leftDialog = "@static_npc/dathomir/kais:notit_1", -- "My eyes are old, but my mind is wise. This is not what I need of you. I am too old for games."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(return_drag_item);

return_success = ConvoScreen:new {
  id = "return_success",
  leftDialog = "@static_npc/dathomir/kais:npc_reward_1", -- "A pristine collection of succulent venom is held within this jar. You have done well, young one. Now, bite this leaf, for it will slow the poison within your gullet. After you have done so, speak with me again."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(return_success);

intro_secondmission = ConvoScreen:new {
  id = "intro_secondmission",
  leftDialog = "@static_npc/dathomir/kais:npc_1_2", -- "I hold the power of the spider within my hand, yet this will extinguish life within a few beats of the heart. I need of you to bring me the strength of time to couple with the strength of death. Bring me the heart of a cumbersome Malkloc."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/kais:player_3_2", "choose_helpwonder_two"}, -- "What does it's heart have to do with 'time'?"
    {"@static_npc/dathomir/kais:player_2_2", "choose_decline_two"}, -- "Those things are huge!! No!"
  }
}

nightsisterKaisConvoTemplate:addScreen(intro_secondmission);

choose_helpwonder_two = ConvoScreen:new {
  id = "choose_helpwonder_two",
  leftDialog = "@static_npc/dathomir/kais:npc_4_2", -- "The Malkloc is birthed and dies as does everything else. For every beat of its heart, many smaller creatures will see their whole cycle pass before them, making the Malkloc immortal in comparison. Within its heart is captured time, itself."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/kais:player_1_2", "choose_help_two"}, -- "I will do so."
  }
}

nightsisterKaisConvoTemplate:addScreen(choose_helpwonder_two);

choose_decline_two = ConvoScreen:new {
  id = "choose_decline_two",
  leftDialog = "@static_npc/dathomir/kais:npc_3_2", -- "Your lack of courage will couple with your lack of breath. You hold a poison within your system that only I can cure... you may think on what I said."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(choose_decline_two);

choose_help_two = ConvoScreen:new {
  id = "choose_help_two",
  leftDialog = "@static_npc/dathomir/kais:npc_2_2", -- "You will need to choose one that is in the prime of its life, for it still holds much time within its heart. Bring it to me and you will have pleased the Clan Mother."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(choose_help_two);

return_notdone_two = ConvoScreen:new {
  id = "return_notdone_two",
  leftDialog = "@static_npc/dathomir/kais:npc_work_2", -- "You hesitate?"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/kais:player_sorry", "choose_helpstill_two"}, -- "What do you require of me again?"
    --{"@static_npc/dathomir/kais:player_sorry", "choose_helpstill_two_no_wp"}, -- "What do you require of me again?"
    {"@static_npc/dathomir/kais:player_reset", "choose_declinetoo"}, -- "I refuse to help any further, old woman!"
  }
}

nightsisterKaisConvoTemplate:addScreen(return_notdone_two);

choose_helpstill_two = ConvoScreen:new {
  id = "choose_helpstill_two",
  leftDialog = "@static_npc/dathomir/kais:npc_backtowork_2", -- "You are to bring unto me the heart of a Malkloc. Do not tarry."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(choose_helpstill_two);

choose_helpstill_two_no_wp = ConvoScreen:new {
  id = "choose_helpstill_two_no_wp",
  leftDialog = "@static_npc/dathomir/kais:npc_noloc_2", -- "The Malkloc has not awakened from it's slumber. Speak to me when time has passed."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(choose_helpstill_two_no_wp);

return_failed_two = ConvoScreen:new {
  id = "return_failed_two",
  leftDialog = "@static_npc/dathomir/kais:npc_failure_2", -- "In the time you spent failing, the Malkloc's heart has not shuttered a beat. Your life is insignicant, therefore your failure is all the more worthless."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(return_failed_two);

return_drag_item_two = ConvoScreen:new {
  id = "return_drag_item_two",
  leftDialog = "@static_npc/dathomir/kais:notit_2", -- "Do not attempt foolery, for this is not a heart."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(return_drag_item_two);

return_success_two = ConvoScreen:new {
  id = "return_success_two",
  leftDialog = "@static_npc/dathomir/kais:npc_reward_2", -- "Together with both Spider and Malkloc combined, a toxin can be made to live forever within a person's blood. I will now draw these powers together with the mysteries of the Shadow. Speak with me when I am done."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(return_success_two);

intro_thirdmission = ConvoScreen:new {
  id = "intro_thirdmission",
  leftDialog = "@static_npc/dathomir/kais:npc_1_3", -- "The two reagents have been combined, and bring forth a glorious toxin. You will now fulfill the Clan Mother's request and bring this toxin to one who guards the prison of the Imperials."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/kais:player_3_3", "choose_helpwonder_three"}, -- "Who is this guard?"
    {"@static_npc/dathomir/kais:player_2_3", "choose_decline_three"}, -- "I'm not poisoning anyone! NO!"
  }
}

nightsisterKaisConvoTemplate:addScreen(intro_thirdmission);

choose_helpwonder_three = ConvoScreen:new {
  id = "choose_helpwonder_three",
  leftDialog = "@static_npc/dathomir/kais:npc_4_3", -- "He is one who has tasted a poison more deadly than anything I can create. Baritha's methods are quite... effective. Once this poison has been consumed by all of those that call themselves Imperials, it will stay within their system until activated. If the Mother asks of it, I will bring forth the agent that shall bring the toxin to life."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/kais:player_1_3", "choose_help_three"}, -- "I will do this, yes."
  }
}

nightsisterKaisConvoTemplate:addScreen(choose_helpwonder_three);

choose_decline_three = ConvoScreen:new {
  id = "choose_decline_three",
  leftDialog = "@static_npc/dathomir/kais:npc_3_3", -- "Then you will doom yourself, young one. A sad waste of such talent."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(choose_decline_three);

choose_help_three = ConvoScreen:new {
  id = "choose_help_three",
  leftDialog = "@static_npc/dathomir/kais:npc_2_3", -- "The guard is most willing to help condemn his brethren, and knows what to do. Take this powder to him, and he will ensure that all of the rest will taste of it."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(choose_help_three);

return_notdone_three = ConvoScreen:new {
  id = "return_notdone_three",
  leftDialog = "@static_npc/dathomir/kais:npc_work_3", -- "Have you brought the vial to the guard?"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/kais:player_sorry", "choose_helpstill_three"}, -- "What do you require of me again?"
    --{"@static_npc/dathomir/kais:player_sorry", "choose_helpstill_three_no_wp"}, -- "What do you require of me again?"
    {"@static_npc/dathomir/kais:player_reset", "choose_declinetoo"}, -- "I refuse to help any further, old woman!"
  }
}

nightsisterKaisConvoTemplate:addScreen(return_notdone_three);

choose_helpstill_three = ConvoScreen:new {
  id = "choose_helpstill_three",
  leftDialog = "@static_npc/dathomir/kais:npc_backtowork_3", -- "You are to give the guard the means in which we shall control the rest of them. Take the vial to the guard."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(choose_helpstill_three);

choose_helpstill_three_no_wp = ConvoScreen:new {
  id = "choose_helpstill_three_no_wp",
  leftDialog = "@static_npc/dathomir/kais:npc_noloc_3", -- "Wait until the time the Guard will be ready to accept our love. Check with me in a little while."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(choose_helpstill_three_no_wp);

return_failed_three = ConvoScreen:new {
  id = "return_failed_three",
  leftDialog = "@static_npc/dathomir/kais:npc_failure_3", -- "Make whatever excuses of your failure to whatever god you worship. The poison within your system will take effect soon enough, so you have scant time to do so."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(return_failed_three);

return_drag_item_three = ConvoScreen:new {
  id = "return_drag_item_three",
  leftDialog = "@static_npc/dathomir/kais:notit_3", -- "I have asked you for nothing."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(return_drag_item_three);

tasknpc_given_three = ConvoScreen:new {
  id = "tasknpc_given_three",
  leftDialog = "@static_npc/dathomir/kais:npc_smuggle_3", -- "Look, you tell Baritha that I'll put this in the water supply, okay? And then I'll come by tonight for my payment, got it?"
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(tasknpc_given_three);

return_success_three = ConvoScreen:new {
  id = "return_success_three",
  leftDialog = "@static_npc/dathomir/kais:npc_reward_3", -- "You have helped to bring the Clan Mother into a more desirable bargaining position, for which she should be most grateful. For now, the poison resides within the Imperials until it is time for it to be called upon. Drink this, and you shall be freed of the agents within your own system. You have done well."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(return_success_three);

tasknpc_found_three = ConvoScreen:new {
  id = "tasknpc_found_three",
  leftDialog = "@static_npc/dathomir/kais:npc_breech_3", -- "Do you have the stuff? Hurry up before by supervisor finds me gone."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(tasknpc_found_three);

return_all_done = ConvoScreen:new {
  id = "return_all_done",
  leftDialog = "@static_npc/dathomir/kais:next", -- "You have proven your worth. Perhaps the Clan Mother may find use of your willingness to assist."
  stopConversation = "true",
  options = {}
}

nightsisterKaisConvoTemplate:addScreen(return_all_done);

addConversationTemplate("nightsisterKaisConvoTemplate", nightsisterKaisConvoTemplate);