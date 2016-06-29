nightsisterBarithaConvoTemplate = ConvoTemplate:new {
  initialScreen = "",
  templateType = "Lua",
  luaClassHandler = "nightsisterBarithaConvoHandler",
  screens = {}
}

intro_has_otherquest = ConvoScreen:new {
  id = "intro_has_otherquest",
  leftDialog = "@static_npc/dathomir/baritha:cant_work", -- "Ah... your mind is preoccupied... Hahaha... you will be an easy one. You will remember to come back to me when you are not so distracted..."
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(intro_has_otherquest);

intro_has_wrongfaction = ConvoScreen:new {
  id = "intro_has_wrongfaction",
  leftDialog = "@static_npc/dathomir/baritha:dontknowyou_1", -- "Look at the mess you made! Get out of here before the reinforcements come."
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(intro_has_wrongfaction);

tasknpc_but_nomission = ConvoScreen:new {
  id = "tasknpc_but_nomission",
  leftDialog = "@static_npc/dathomir/baritha:dontknowyou_2", -- "Oh, you're not here to pick me up? Nevermind, then."
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(tasknpc_but_nomission);

intro_firstmission = ConvoScreen:new {
  id = "intro_firstmission",
  leftDialog = "@static_npc/dathomir/baritha:npc_1_1", -- "I have heard of your name spoken in whispers among the Sisters. You want to help me, don't you? You will feel more complete by offering your help, and want to give in to my every desire...."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/baritha:player_1_1", "choose_help"}, -- "What's going on he--.......... yesss... Yes, I want to help you."
  }
}

nightsisterBarithaConvoTemplate:addScreen(intro_firstmission);

choose_help = ConvoScreen:new {
  id = "choose_help",
  leftDialog = "@static_npc/dathomir/baritha:npc_2_1", -- "Yes, you are a good little one, aren't you. You will now go bring to me the newest arrival to the Imperial Prison. He is quite handsome, and I have not had a fun toy to play with for a while. Do not make me wait long..."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/baritha:player_2_1", "choose_helpwonder"}, -- "What's going on?! No! Get away from me!"
  }
}

nightsisterBarithaConvoTemplate:addScreen(choose_help);

choose_helpwonder = ConvoScreen:new {
  id = "choose_helpwonder",
  leftDialog = "@static_npc/dathomir/baritha:npc_3_1", -- "Oh... you are stronger than you look. Hmmm... I don't know whether to be angry or to view you as a challenge. I do so fear if I try any harder, I might shatter your little mind..."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/baritha:player_3_1", "choose_helpgo"}, -- "What are you doing to my head?"
  }
}

nightsisterBarithaConvoTemplate:addScreen(choose_helpwonder);

choose_helpgo = ConvoScreen:new {
  id = "choose_helpgo",
  leftDialog = "@static_npc/dathomir/baritha:npc_3_1", -- "I am helping you, little one. I am helping you to see that you cannot be happy unless you fulfill my whims... Anything I want, I deserve... I am helping you to see that. You like it when I help you, don't you? And now you want to help me."
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(choose_helpgo);

-- This screen below, 'tasknpc_anothers', should be used for the 1st & 3rd missions, but NOT for the 2nd.
tasknpc_anothers = ConvoScreen:new {
  id = "tasknpc_anothers",
  leftDialog = "@static_npc/dathomir/baritha:otherescort_1", -- "I am not the person you are looking for."
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(tasknpc_anothers);

-- This screen below, 'tasknpc_found', should be used for the 1st & 3rd missions, but NOT the 2nd.
tasknpc_found = ConvoScreen:new {
  id = "tasknpc_found",
  leftDialog = "@static_npc/dathomir/baritha:npc_breech_1", -- "What's going on here? Who are you? Guards, protect me!"
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(tasknpc_found);

-- This screen below, 'tasknpc_taken', should be used for 1st & 3rd missions, but NOT for the 2nd.
tasknpc_taken = ConvoScreen:new {
  id = "tasknpc_taken",
  leftDialog = "@static_npc/dathomir/baritha:npc_takeme_1", -- "Where are you taking me? I command you, Let me go at once. Oh... you have a weapon. Very well, lead on"
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(tasknpc_taken);

return_failed = ConvoScreen:new {
  id = "return_failed",
  leftDialog = "@static_npc/dathomir/baritha:npc_failure_1", -- "Bad, bad, bad pet!!! I told you to bring me a toy, and you have failed me. Perhaps I will tire of you and find a new pet."
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(return_failed);

return_reset = ConvoScreen:new {
  id = "return_reset",
  leftDialog = "@static_npc/dathomir/baritha:npc_work_1", -- "Yes, little pet?"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/baritha:player_reset_1", "return_resist"}, -- "I remember who I am now, Baritha. You have no power over me."
  }
}

nightsisterBarithaConvoTemplate:addScreen(return_reset);

return_resist = ConvoScreen:new {
  id = "return_resist",
  leftDialog = "@static_npc/dathomir/baritha:npc_reset_1", -- "Ahhh... a fiesty one.... well, this changes things, doesn't it? Now think carefully about what I am about to say. Either join me... or die."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/baritha:player_sorry_1", "return_notdone"}, -- "Mistress, what do you wish of me?"
    --{"@static_npc/dathomir/baritha:player_sorry_1", "return_notdone_no_wp"}, -- "Mistress, what do you wish of me?"
  }
}

nightsisterBarithaConvoTemplate:addScreen(return_resist);

return_notdone = ConvoScreen:new {
  id = "return_notdone",
  leftDialog = "@static_npc/dathomir/baritha:npc_backtowork_1", -- "You will be a good little pet and fetch me the Officer that has arrived at the prison so that I may... entertain myself."
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(return_notdone);

return_notdone_no_wp = ConvoScreen:new {
  id = "return_notdone_no_wp",
  leftDialog = "@static_npc/dathomir/baritha:npc_noloc_1", -- "Let us wait for him to emerge from his sanctuary, shall we? Come back to me in a little while."
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(return_notdone_no_wp);

return_drag_item = ConvoScreen:new {
  id = "return_drag_item",
  leftDialog = "@static_npc/dathomir/baritha:notit_1", -- "Oh, you are so cute, little one. You wish to shower me in gifts... no, you may keep that one for yourself."
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(return_drag_item);

-- This screen below, 'tasknpc_given', should be used for both the 1st & 3rd missions, but NOT the 2nd.
tasknpc_given = ConvoScreen:new {
  id = "tasknpc_given",
  leftDialog = "@static_npc/dathomir/baritha:npc_dropoff_1", -- "Who is this? Is this one of those Nightsisters? Whatever you want of me, you will not have it!"
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(tasknpc_given);

return_success = ConvoScreen:new {
  id = "return_success",
  leftDialog = "@static_npc/dathomir/baritha:npc_reward_1", -- "Oh, he is a strong looking one, isn't he? I hope this one will be more of a challenge this time.... you have done well, my precious pet. You may please me again in the future. For now, leave me."
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(return_success);

intro_secondmission = ConvoScreen:new {
  id = "intro_secondmission",
  leftDialog = "@static_npc/dathomir/baritha:npc_1_2", -- "I am sickened to hear what has recently happened. It seems the Singing Mountain Sisters know not how to leave well enough alone. Very well, I shall set my pet upon them, won't I?"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/baritha:player_1_2", "choose_helptwo"}, -- "Yes, my mistress, I will fulfill your wishes."
  }
}

nightsisterBarithaConvoTemplate:addScreen(intro_secondmission);

choose_helptwo = ConvoScreen:new {
  id = "choose_helptwo",
  leftDialog = "@static_npc/dathomir/baritha:npc_2_2", -- "Yes, it pleases you more than anything to do so. Go find the Nightsister who has fallen sway to the Singing Mountain's silly preachings, then bring her back to me. You may do as you please to the other Sisters there."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/baritha:player_2_2", "choose_wondertwo"}, -- "I... must... fight... this.... NOOOO!!!!"
  }
}

nightsisterBarithaConvoTemplate:addScreen(choose_helptwo);

choose_wondertwo = ConvoScreen:new {
  id = "choose_wondertwo",
  leftDialog = "@static_npc/dathomir/baritha:npc_3_2", -- "Oh, broken my compulsion, have you? You think you're clever, don't you? Hahaha... you are in the heart of our home, and you think you're going to walk out of here? Not so clever after all, are you?"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/baritha:player_3_2", "choose_helpgotwo"}, -- "What has the enemy done?"
  }
}

nightsisterBarithaConvoTemplate:addScreen(choose_wondertwo);

choose_helpgotwo = ConvoScreen:new {
  id = "choose_helpgotwo",
  leftDialog = "@static_npc/dathomir/baritha:npc_4_2", -- "The loathsome Singing Sisters have had the audacity to persuade one of our Sisters forsake the use of the Shadow Magics! This will not do. How dare they try to play with the mind of a Nightsister!! Who do they think they are?"
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(choose_helpgotwo);

tasknpc_anotherstwo = ConvoScreen:new {
  id = "tasknpc_anotherstwo",
  leftDialog = "@static_npc/dathomir/baritha:otherescort_2", -- "Nope, I'm not the one you're looking for. I think the other one's over there."
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(tasknpc_anotherstwo);

tasknpc_foundtwo = ConvoScreen:new {
  id = "tasknpc_foundtwo",
  leftDialog = "@static_npc/dathomir/baritha:npc_breech_2", -- "Oh no!!! I've been found out! Please, just let me go!"
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(tasknpc_foundtwo);

tasknpc_takentwo = ConvoScreen:new {
  id = "tasknpc_takentwo",
  leftDialog = "@static_npc/dathomir/baritha:npc_takeme_2", -- "No, please! You don't know what she'll do to me!! Please...please, I beg you... if you have any soul, please let me gooooo!!!!!!"
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(tasknpc_takentwo);

return_failedtwo = ConvoScreen:new {
  id = "return_failedtwo",
  leftDialog = "@static_npc/dathomir/baritha:npc_failure_2", -- "You didn't bring her here? This make me very angry... VERY angry. Do you know what I do to my pets when they make me angry?"
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(return_failedtwo);

return_resettwo = ConvoScreen:new {
  id = "return_resettwo",
  leftDialog = "@static_npc/dathomir/baritha:npc_work_2", -- "Yes, my precious pet?"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/baritha:player_reset_2", "return_resisttwo"}, -- "I remember who I am now, Baritha. You have no power over me."
  }
}

nightsisterBarithaConvoTemplate:addScreen(return_resettwo);

return_resisttwo = ConvoScreen:new {
  id = "return_resisttwo",
  leftDialog = "@static_npc/dathomir/baritha:npc_reset_2", -- "Ahhh... a fiesty one.... well, this changes things, doesn't it? Now think carefully about what I am about to say. Either join me... or die."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/baritha:player_sorry_2", "return_notdonetwo"}, -- "Mistress, what do you wish of me?"
    --{"@static_npc/dathomir/baritha:player_sorry_2", "return_notdonetwo_no_wp"}, -- "Mistress, what do you wish of me?"
  }
}

nightsisterBarithaConvoTemplate:addScreen(return_resisttwo);

return_notdonetwo = ConvoScreen:new {
  id = "return_notdonetwo",
  leftDialog = "@static_npc/dathomir/baritha:npc_backtowork_2", -- "You are to fetch that impudent little girl who now claims to be a Singing Sister... and then I will deal with her."
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(return_notdonetwo);

return_notdonetwo_no_wp = ConvoScreen:new {
  id = "return_notdonetwo_no_wp",
  leftDialog = "@static_npc/dathomir/baritha:npc_noloc_2", -- "She will be meeting with her co-conspirators soon. Come back to me and I will tell you when you will want to leave."
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(return_notdonetwo_no_wp);

return_drag_item_two = ConvoScreen:new {
  id = "return_drag_item_two",
  leftDialog = "@static_npc/dathomir/baritha:notit_2", -- "No, pet, I do not want this."
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(return_drag_item_two);

tasknpc_giventwo = ConvoScreen:new {
  id = "tasknpc_giventwo",
  leftDialog = "@static_npc/dathomir/baritha:npc_dropoff_2", -- "Baritha, I'm so sorry.... I'm so very sorry... I'm sorry.... please don't hurt me.... pleaaasee......"
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(tasknpc_giventwo);

return_success_two = ConvoScreen:new {
  id = "return_success_two",
  leftDialog = "@static_npc/dathomir/baritha:npc_reward_2", -- "Oh, you brought her back here. Here, let me pat you on the head, precious pet. You did good, didn't you? Yes, you did good... Now, as for you, Sister, you will learn the price of your mistake. Leave me, pet."
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(return_success_two);

intro_thirdmission = ConvoScreen:new {
  id = "intro_thirdmission",
  leftDialog = "@static_npc/dathomir/baritha:npc_1_3", -- "Oh, the Empire is quite effective indeed, aren't they? They have already sent someone to replace my 'toy'. Perhaps this one might know how to leave our beautiful planet this time. Pet! Go fetch this one for me!"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/baritha:player_1_3", "choose_helpthree"}, -- "Yes, my dark mistress."
  }
}

nightsisterBarithaConvoTemplate:addScreen(intro_thirdmission);

choose_helpthree = ConvoScreen:new {
  id = "choose_helpthree",
  leftDialog = "@static_npc/dathomir/baritha:npc_2_3", -- "So willing... you are such a good pet, aren't you? Now, go bring him here unharmed and maybe I'll give you a treat... you'd like that, wouldn't you?"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/baritha:player_2_3", "choose_wonderthree"}, -- "Get... out... of... my... head!!!! NO!!!"
  }
}

nightsisterBarithaConvoTemplate:addScreen(choose_helpthree);

choose_wonderthree = ConvoScreen:new {
  id = "choose_wonderthree",
  leftDialog = "@static_npc/dathomir/baritha:npc_3_3", -- "So. You could have remained happy being my pet, but instead you choose to have it this way... very well then... let me see how you plan on leaving our stronghold, little pet."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/baritha:player_3_3", "choose_helpgothree"}, -- "Why does my mistress wish to leave?"
  }
}

nightsisterBarithaConvoTemplate:addScreen(choose_wonderthree);

choose_helpgothree = ConvoScreen:new {
  id = "choose_helpgothree",
  leftDialog = "@static_npc/dathomir/baritha:npc_4_3", -- "There is a whole galaxy out there, little pet, which I think you very well know. The Sisters only wish to visit your people and bring them our culture. If they refuse... *sigh*... then we will have to kill them. I know they will be happy with us as their rulers."
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(choose_helpgothree);

return_failedthree = ConvoScreen:new {
  id = "return_failedthree",
  leftDialog = "@static_npc/dathomir/baritha:npc_failure_3", -- "You stupid little creature! I gave you a simple task, and you couldn't even do that!"
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(return_failedthree);

return_resetthree = ConvoScreen:new {
  id = "return_resetthree",
  leftDialog = "@static_npc/dathomir/baritha:npc_work_3", -- "Yes, my precious pet?"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/baritha:player_reset_3", "return_resistthree"}, -- "I remember who I am now, Baritha. You have no power over me."
  }
}

nightsisterBarithaConvoTemplate:addScreen(return_resetthree);

return_resistthree = ConvoScreen:new {
  id = "return_resistthree",
  leftDialog = "@static_npc/dathomir/baritha:npc_reset_3", -- "Ahhh... a fiesty one.... well, this changes things, doesn't it? Now think carefully about what I am about to say. Either join me... or die."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/baritha:player_sorry_3", "return_notdonethree"}, -- "Mistress, what do you wish of me?"
    --{"@static_npc/dathomir/baritha:player_sorry_2", "return_notdonethree_no_wp"}, -- "Mistress, what do you wish of me?"
  }
}

nightsisterBarithaConvoTemplate:addScreen(return_resistthree);

return_notdonethree = ConvoScreen:new {
  id = "return_notdonethree",
  leftDialog = "@static_npc/dathomir/baritha:npc_backtowork_3", -- "Go and fetch this new officer who is replacing the last one. Bring him back to me relatively unharmed."
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(return_notdonethree);

return_notdonethree_no_wp = ConvoScreen:new {
  id = "return_notdonethree_no_wp",
  leftDialog = "@static_npc/dathomir/baritha:npc_noloc_3", -- "You will wait until he is less guarded. Ask me again in a little while when you should leave to do so."
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(return_notdonethree_no_wp);

return_drag_item_three = ConvoScreen:new {
  id = "return_drag_item_three",
  leftDialog = "@static_npc/dathomir/baritha:notit_3", -- "I don't want this, you stupid little pet! Now go do what I said."
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(return_drag_item_three);

return_success_three = ConvoScreen:new {
  id = "return_success_three",
  leftDialog = "@static_npc/dathomir/baritha:npc_reward_3", -- "Ah... he has the look of someone important... very good, pet. Now, go to your corner and sit there until Ihave further need of you."
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(return_success_three);

return_all_done = ConvoScreen:new {
  id = "return_all_done",
  leftDialog = "@static_npc/dathomir/baritha:next", -- "My little pet, I am sad to see you go, yet the Clan Mother wishes to use you for her own ends. Oh... I could have treated you so much better... very well, I release you, and I will let you remember everything, as well.... hahaha.... Now, go see the Mother!"
  stopConversation = "true",
  options = {}
}

nightsisterBarithaConvoTemplate:addScreen(return_all_done);

addConversationTemplate("nightsisterBarithaConvoTemplate", nightsisterBarithaConvoTemplate);