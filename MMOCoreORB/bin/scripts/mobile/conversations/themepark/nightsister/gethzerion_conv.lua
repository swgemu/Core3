nightsisterGethzerionConvoTemplate = ConvoTemplate:new {
  initialScreen = "",
  templateType = "Lua",
  luaClassHandler = "nightsisterGethzerionConvoHandler",
  screens = {}
}

intro_has_otherquest = ConvoScreen:new {
  id = "intro_has_otherquest",
  leftDialog = "@static_npc/dathomir/gethzerion:cant_work", -- "How dare you? I ordered you released from Baritha's compulsion, and you run off to someone else? If you value your life, you will direct all of you attentions to your ruler... myself."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(intro_has_otherquest);

intro_hasnt_progress = ConvoScreen:new {
  id = "intro_hasnt_progress",
  leftDialog = "@static_npc/dathomir/gethzerion:notyet", -- "How dare you disturb me? Since I am in a good mood, you will be allowed to leave my chamber alive. Do no make the same mistake again."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(intro_hasnt_progress);

intro_has_wrongfaction = ConvoScreen:new {
  id = "intro_has_wrongfaction",
  leftDialog = "@celebrity/gethzerion:npc_1", -- "I am the ruler of the Nightsisters. You have no place here..."
  stopConversation = "false",
  options = {
    {"@celebrity/gethzerion:player_1", "choose_leave"}, -- "Sorry, I'll go."
    {"@celebrity/gethzerion:player_2", "choose_say"}, -- "I like it here."
  }
}

nightsisterGethzerionConvoTemplate:addScreen(intro_has_wrongfaction);

choose_leave = ConvoScreen:new {
  id = "choose_leave",
  leftDialog = "@celebrity/gethzerion:npc_2", -- "Good!"
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(choose_leave);

choose_say = ConvoScreen:new {
  id = "choose_say",
  leftDialog = "@celebrity/gethzerion:npc_3", -- "Fool!"
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(choose_say);

tasknpc_but_nomission = ConvoScreen:new {
  id = "tasknpc_but_nomission",
  leftDialog = "@static_npc/dathomir/gethzerion:dontknowyou_1", -- "Nevermind, I don't know you."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(tasknpc_but_nomission);

tasknpc_found = ConvoScreen:new {
  id = "tasknpc_found",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_breech_1", -- "No, please... you don't know what kind of nightmare I was fleeing! LET ME GO!!!"
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(tasknpc_found);

intro_firstmission = ConvoScreen:new {
  id = "intro_firstmission",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_1_1", -- "So, you are the one that Baritha has been mooning over. Considering I am recently missing a slave, I will have to take you from her. Your first act as my slave will be to take care of your predecessor. Do you understand?"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/gethzerion:player_3_1", "choose_helpwonder"}, -- "What do you mean by predecessor?"
    {"@static_npc/dathomir/gethzerion:player_2_1", "choose_decline"}, -- "I understand that I'm leaving. Bye!"
  }
}

nightsisterGethzerionConvoTemplate:addScreen(intro_firstmission);

choose_helpwonder = ConvoScreen:new {
  id = "choose_helpwonder",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_4_1", -- "My first and foremost among slaves was a cunning man by the name of Dal Zeybuub. Unfortunately for him, My Prime Slave thinks too highly of himself. Rather than betraying me, as he plans, he will now be a victim of his own thoughts betraying him."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/gethzerion:player_1_1", "choose_help"}, -- "Yes, Clan Mother. I shall do so."
    
  }
}

nightsisterGethzerionConvoTemplate:addScreen(choose_helpwonder);

choose_decline = ConvoScreen:new {
  id = "choose_decline",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_3_1", -- "Oh, really? You believe that you will leave our stronghold just like that? You presume too much, fool. I will give you one more chance to change your mind."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(choose_decline);

choose_help = ConvoScreen:new {
  id = "choose_help",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_2_1", -- "Very good... quick to respond, and very clear... I shall see if there may be more than slavery for you. For now, go find my slave, then kill him in a most painful manner. Once the punishment has been exacted, bring his heart back to me."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(choose_help);

return_notdone = ConvoScreen:new {
  id = "return_notdone",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_work_1", -- "Why do you disturb me? I have already spoken!"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/gethzerion:player_sorry", "choose_helpstill"}, -- "I am sorry, Mother. What was I to do again?"
    --{"@static_npc/dathomir/gethzerion:player_sorry", "choose_helpstill_no_wp"}, -- "I am sorry, Mother. What was I to do again?"
    {"@static_npc/dathomir/gethzerion:player_reset", "choose_declinetoo"}, -- "I am too lowly to serve you any more, Clan Mother."
  }
}

nightsisterGethzerionConvoTemplate:addScreen(return_notdone);

choose_declinetoo = ConvoScreen:new {
  id = "choose_declinetoo",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_reset", -- "Yes you are, come to think of it. You would assist me better were you to help me... test... my spells."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(choose_declinetoo);

choose_helpstill = ConvoScreen:new {
  id = "choose_helpstill",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_backtowork_1", -- "You will find my Prime Slave and kill him. Once done, bring me back his heart... and I will know if it is his."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(choose_helpstill);

choose_helpstill_no_wp = ConvoScreen:new {
  id = "choose_helpstill_no_wp",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_noloc_1", -- "The time is not right to track him down. Come back to me in a while and I will send you out against him."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(choose_helpstill_no_wp);

return_failed = ConvoScreen:new {
  id = "return_failed",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_failure_1", -- "What? You failed me? HOW DARE YOU!!!"
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(return_failed);

return_drag_item = ConvoScreen:new {
  id = "return_drag_item",
  leftDialog = "@static_npc/dathomir/gethzerion:notit_1", -- "What is this? You waste my time!"
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(return_drag_item);

return_success = ConvoScreen:new {
  id = "return_success",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_reward_1", -- "Ahhhh... Dal's heart... Once it has been chilled, it will make for a most pleasant dinner. I have found that it is true that vengeance is best served cold. As for you... I sense I am not using you to the fullest.. Come back to me after I have thought this matter over."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(return_success);

tasknpc_but_nomission_two = ConvoScreen:new {
  id = "tasknpc_but_nomission_two",
  leftDialog = "@static_npc/dathomir/gethzerion:dontknowyou_2", -- "You didn't see anything, right? Good."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(tasknpc_but_nomission_two);

tasknpc_found_two = ConvoScreen:new {
  id = "tasknpc_found_two",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_breech_2", -- "Sisters, we have been found! Leave no witnesses!"
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(tasknpc_found_two);

intro_secondmission = ConvoScreen:new {
  id = "intro_secondmission",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_1_2", -- "I have decided that you may serve me better were you not under the yoke of slavery. Go show me your effectiveness at destroying those weak Singing Mountain sisters, and I will consider the prospect further."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/gethzerion:player_3_2", "choose_helpwonder_two"}, -- "If I do so, will I retain my freedom?"
  }
}

nightsisterGethzerionConvoTemplate:addScreen(intro_secondmission);

choose_helpwonder_two = ConvoScreen:new {
  id = "choose_helpwonder_two",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_4_2", -- "Perhaps. Perhaps not. Depending on how well you do, I may decide to grant you that boon, for I am a gracious Mother. Now go!"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/gethzerion:player_1_2", "choose_help_two"}, -- "I will not fail you, Mother."
    {"@static_npc/dathomir/gethzerion:player_2_2", "choose_decline_two"}, -- "I cannot handle them alone. No."
  }
}

nightsisterGethzerionConvoTemplate:addScreen(choose_helpwonder_two);

choose_decline_two = ConvoScreen:new {
  id = "choose_decline_two",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_3_2", -- "You will deal with what I tell you to deal with. I will not tolerate this insolence!"
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(choose_decline_two);

choose_help_two = ConvoScreen:new {
  id = "choose_help_two",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_2_2", -- "Baritha has brought to my attention that a few of the Singing Mountain sisters have had the audacity to enter our territory. Silence their spells and lead them to the carrion-feeders."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(choose_help_two);

return_notdone_two = ConvoScreen:new {
  id = "return_notdone_two",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_work_2", -- "Why do you hesitate, fool?"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/gethzerion:player_sorry", "choose_helpstill_two"}, -- "I am sorry, Mother. What was I to do again?"
    --{"@static_npc/dathomir/gethzerion:player_sorry", "choose_helpstill_two_no_wp"}, -- "I am sorry, Mother. What was I to do again?"
    {"@static_npc/dathomir/gethzerion:player_reset", "choose_declinetoo"}, -- "I am too lowly to serve you any more, Clan Mother."
  }
}

nightsisterGethzerionConvoTemplate:addScreen(return_notdone_two);

choose_helpstill_two = ConvoScreen:new {
  id = "choose_helpstill_two",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_backtowork_2", -- "Go find these impudent sisters of Augwynne and render their lives from their bodies."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(choose_helpstill_two);

choose_helpstill_two_no_wp = ConvoScreen:new {
  id = "choose_helpstill_two_no_wp",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_noloc_2", -- "When Baritha returns, I will know where these sisters can be found. Come back to me in a short while."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(choose_helpstill_two_no_wp);

return_failed_two = ConvoScreen:new {
  id = "return_failed_two",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_failure_2", -- "How dare you come back and face me after you have failed. It shall be the slave's collar for you, then."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(return_failed_two);

return_drag_item_two = ConvoScreen:new {
  id = "return_drag_item_two",
  leftDialog = "@static_npc/dathomir/gethzerion:notit_2", -- "I asked you for nothing!"
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(return_drag_item_two);

return_success_two = ConvoScreen:new {
  id = "return_success_two",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_reward_2", -- "So you handled yourself better than some of these pathetic women who call themselves Witches? Very well then - your freedom is granted... for now. I will have a more important purpose for you, so stay close."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(return_success_two);

tasknpc_but_nomission_three = ConvoScreen:new {
  id = "tasknpc_but_nomission_three",
  leftDialog = "@static_npc/dathomir/gethzerion:dontknowyou_3", -- "Actually, I changed my mind."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(tasknpc_but_nomission_three);

tasknpc_found_three = ConvoScreen:new {
  id = "tasknpc_found_three",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_breech_3", -- "You were sent by Gethzerion? But you're not a Nightsister... oh well... you will still die."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(tasknpc_found_three);

intro_thirdmission = ConvoScreen:new {
  id = "intro_thirdmission",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_1_3", -- "You have proven yourself adequate to my uses. I hereby name you my Dagger... and from now on you will be my personal assassin. I now need you to target your first victim."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/gethzerion:player_3_3", "choose_helpwonder_three"}, -- "Who shall I dispatch now?"
  }
}

nightsisterGethzerionConvoTemplate:addScreen(intro_thirdmission);

choose_helpwonder_three = ConvoScreen:new {
  id = "choose_helpwonder_three",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_4_3", -- "You will be ending the short life of Sister Aelta, one of the Singing Mountain Sisters. Ever since Augwynne, Clan Mother of the Singers, has lost both of her daughters she has 'adopted' two more. You will show that old crone that I will not accept this."
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/gethzerion:player_1_3", "choose_help_three"}, -- "Yes, Clan Mother, I will do so."
    {"@static_npc/dathomir/gethzerion:player_2_3", "choose_decline_three"}, -- "I will not kill people for a living! No!"
  }
}

nightsisterGethzerionConvoTemplate:addScreen(choose_helpwonder_three);

choose_decline_three = ConvoScreen:new {
  id = "choose_decline_three",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_3_3", -- "That may well be the least wise thing you have ever done. Perhaps you believed this was a request? Or perhaps you think yourself on an equal level as myself that you may speak so openly? Not smart...."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(choose_decline_three);

choose_help_three = ConvoScreen:new {
  id = "choose_help_three",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_2_3", -- "Your willingness is pleasing to me. You will locate and kill Sister Aelta, getting her out of my hair once and for all. Do the deed, then return to let me know."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(choose_help_three);

return_notdone_three = ConvoScreen:new {
  id = "return_notdone_three",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_work_3", -- "Why do you bother me?"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/gethzerion:player_sorry", "choose_helpstill_three"}, -- "I am sorry, Mother. What was I to do again?"
    --{"@static_npc/dathomir/gethzerion:player_sorry", "choose_helpstill_three_no_wp"}, -- "I am sorry, Mother. What was I to do again?"
    {"@static_npc/dathomir/gethzerion:player_reset", "choose_declinetoo"}, -- "I am too lowly to serve you any more, Clan Mother."
  }
}

nightsisterGethzerionConvoTemplate:addScreen(return_notdone_three);

choose_helpstill_three = ConvoScreen:new {
  id = "choose_helpstill_three",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_backtowork_3", -- "You will find that bold harlot that calls herself a sister, Aelta. Once you have done so, kill her.... painfully."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(choose_helpstill_three);

choose_helpstill_three_no_wp = ConvoScreen:new {
  id = "choose_helpstill_three_no_wp",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_noloc_3", -- "I will send a scout to find where Sister Aelta can be found. Return to me in a short while."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(choose_helpstill_three_no_wp);

return_failed_three = ConvoScreen:new {
  id = "return_failed_three",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_failure_3", -- "You were unable to accomplish a simple task as this? Very well... it shall be the slave's collar for you."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(return_failed_three);

return_drag_item_three = ConvoScreen:new {
  id = "return_drag_item_three",
  leftDialog = "@static_npc/dathomir/gethzerion:notit_3", -- "I did not ask for this. Take it away from me."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(return_drag_item_three);

return_success_three = ConvoScreen:new {
  id = "return_success_three",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_reward_3", -- "You have done well on your first assignment for me. My left breast is warmed at the thought of the pain she felt as she died. Any of those foolish Singing sisters will do well to heed this warning : Augwynne's daughters are dead, and they will not be 'replaced'!"
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(return_success_three);

intro_fourthmission = ConvoScreen:new {
  id = "intro_fourthmission",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_1_4", -- "That... that.... that WITCH!!! How dare she!? When I find her, I will tear her soul apart!! Ahhh... yessss... and that's exactly what she expects, isn't it? What a clever little trap... but she didn't expect you, did she, my little Dagger? You will go and kill Sister Chastina for her impudence!"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/gethzerion:player_3_4", "choose_helpwonder_four"}, -- "If I might ask, what troubles you so?"
  }
}

nightsisterGethzerionConvoTemplate:addScreen(intro_fourthmission);

choose_helpwonder_four = ConvoScreen:new {
  id = "choose_helpwonder_four",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_4_4", -- "How DARE she? That withered hag, Augwynne, has chosen another 'daughter', my former friend Chastina. She has gone so far as to give to Chastina her necklace! That is MY necklace!!! As Augwynne's real daughter, I DESERVE IT!!! ... -er-.... Why am I telling you this?"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/gethzerion:player_1_4", "choose_help_four"}, -- "I shall do so at once, gracious Mother!"
    {"@static_npc/dathomir/gethzerion:player_2_4", "choose_decline_four"}, -- "You're too emotional right now. No."
  }
}

nightsisterGethzerionConvoTemplate:addScreen(choose_helpwonder_four);

choose_decline_four = ConvoScreen:new {
  id = "choose_decline_four",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_3_4", -- "Were I not so distraught, I enjoy watching you as I choke the very breath out of your lungs. Please.... stay close so that I may calm down enough to do so."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(choose_decline_four);

choose_help_four = ConvoScreen:new {
  id = "choose_help_four",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_2_4", -- "Track that filthy, brazen witch down... when you find her, rip her heart out and show it to her! Afterwards, remove that necklace she wrongfully wears around her neck and bring it back to me."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(choose_help_four);

return_notdone_four = ConvoScreen:new {
  id = "return_notdone_four",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_work_4", -- "What?"
  stopConversation = "false",
  options = {
    {"@static_npc/dathomir/gethzerion:player_sorry", "choose_helpstill_four"}, -- "I am sorry, Mother. What was I to do again?"
    --{"@static_npc/dathomir/gethzerion:player_sorry", "choose_helpstill_four_no_wp"}, -- "I am sorry, Mother. What was I to do again?"
    {"@static_npc/dathomir/gethzerion:player_reset", "choose_declinetoo"}, -- "I am too lowly to serve you any more, Clan Mother."
  }
}

nightsisterGethzerionConvoTemplate:addScreen(return_notdone_four);

choose_helpstill_four = ConvoScreen:new {
  id = "choose_helpstill_four",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_backtowork_4", -- "Go kill that impudent failure of a witch and bring me the necklace she wears around her neck."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(choose_helpstill_four);

choose_helpstill_four_no_wp = ConvoScreen:new {
  id = "choose_helpstill_four_no_wp",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_noloc_4", -- "I do not know where Chastina can be found. Come back to me in a while and I will assist you in finding her."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(choose_helpstill_four_no_wp);

return_failed_four = ConvoScreen:new {
  id = "return_failed_four",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_failure_4", -- "How dare you return after you have failed me?"
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(return_failed_four);

return_drag_item_four = ConvoScreen:new {
  id = "return_drag_item_four",
  leftDialog = "@static_npc/dathomir/gethzerion:notit_4", -- "This is not the necklace! BRING ME THE NECKLACE!"
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(return_drag_item_four);

return_success_four = ConvoScreen:new {
  id = "return_success_four",
  leftDialog = "@static_npc/dathomir/gethzerion:npc_reward_4", -- " Yes... my necklace! Were I able to have succeeded in beheading my moth... I mean to say, beheading that Clan Mother.... well, either way, it is mine now, where it should have been for many years now. My Dagger, you have pleased my very, very much."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(return_success_four);

return_all_done = ConvoScreen:new {
  id = "return_all_done",
  leftDialog = "@static_npc/dathomir/gethzerion:next", -- "You have pleased me, but do not try my patience. If I have need of you in the future, I shall call upon you."
  stopConversation = "true",
  options = {}
}

nightsisterGethzerionConvoTemplate:addScreen(return_all_done);

addConversationTemplate("nightsisterGethzerionConvoTemplate", nightsisterGethzerionConvoTemplate);