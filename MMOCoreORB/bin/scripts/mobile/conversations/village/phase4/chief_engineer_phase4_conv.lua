villageChiefEngineerPhase4ConvoTemplate = ConvoTemplate:new {
  initialScreen = "",
  templateType = "Lua",
  luaClassHandler = "villageChiefEngineerPhase4ConvoHandler",
  screens = {}
}

intro_has_otherquest = ConvoScreen:new {
  id = "intro_has_otherquest",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_e77051e7", -- "I don't have time to speak. Too much to do. Too much to do and not enough time. Too frantic. Arrgh."
  stopConversation = "true",
  options = {}
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(intro_has_otherquest);

intro_begin_chief = ConvoScreen:new {
  id = "intro_begin_chief",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_cbc96768", -- "Arrrgh! It's too much! I'm only one person... and new to this position no less. How can I be expected to keep the village defenses working while we're under attack? It's too much!!"
  stopConversation = "false",
  options = {
    {"@conversation/fs_phase4_chief_engineer:s_59f5cee6", "choose_accept"}, -- "Is there anything I can do to help?"
    {"@conversation/fs_phase4_chief_engineer:s_5542b04b", "choose_decline"}, -- "Oh, my apologies. I'll let you get back to work."
  }
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(intro_begin_chief);

choose_decline = ConvoScreen:new {
  id = "choose_decline",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_df4917e", -- "Right. Well then I've wasted enough time talking. There's much for me to attend to."
  stopConversation = "true",
  options = {}
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(choose_decline);

choose_accept = ConvoScreen:new {
  id = "choose_accept",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_1a960799", -- "Yes. Yes there is. During the first of the recent attacks on the village, our primary computer was damaged, and the computer core has become unstable. A new core must be found as soon as possible. Thanks to all the damage being caused by the attacks, I am unable go find a replacement, but you could go get one in my place."
  stopConversation = "false",
  options = {
    {"@conversation/fs_phase4_chief_engineer:s_8e1d9e8a", "choose_certain"}, -- "I'll do it. Where can I find a replacement computer core?"
    {"@conversation/fs_phase4_chief_engineer:s_94925b50", "choose_pass"}, -- "Eh, no thanks. Sounds boring. I'll pass."
  }
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(choose_accept);

choose_certain = ConvoScreen:new {
  id = "choose_certain",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_bf01c6a4", -- "Well, I know some people who might be able to help you find one. You'd need to contact one of them and see what they have to say. From there, both they and I can advise you. In exchange for this service, I'd be happy to help you unlock the secrets that will lead you toward mastering the art of repair."
  stopConversation = "false",
  options = {
    {"@conversation/fs_phase4_chief_engineer:s_61fa9d29", "choose_wonder"}, -- "Hmm... what would that mean I'd have to do?"
    {"@conversation/fs_phase4_chief_engineer:s_94925b50", "choose_pass"}, -- "Eh, no thanks. Sounds boring. I'll pass."
  }
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(choose_certain);

choose_wonder = ConvoScreen:new {
  id = "choose_wonder",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_bf01c6a4", -- "Ah enthusiasm... I like that. Before getting started, you should know that in this village, you cannot work with more than one villager. So while you're working with me, you can't work with any other villagers."
  stopConversation = "false",
  options = {
    {"@conversation/fs_phase4_chief_engineer:s_7f1492c", "choose_affirm"}, -- "That's not a problem. How do I get started on this?"
    {"@conversation/fs_phase4_chief_engineer:s_85cf8e18", "choose_ponder"}, -- "Oh. Hmmm... maybe I should think about this a bit more."
  }
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(choose_wonder);

choose_pass = ConvoScreen:new {
  id = "choose_pass",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_96e10fe0", -- "I see. Thank you for coming by. If you'll excuse me, I've much to do."
  stopConversation = "true",
  options = {}
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(choose_pass);

choose_ponder = ConvoScreen:new {
  id = "choose_ponder",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_96e10fe0", -- "Fair enough. If you decide you'll be able to help, I'll be here. Now let's see... which emergency was I working on..."
  stopConversation = "true",
  options = {}
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(choose_ponder);

choose_affirm = ConvoScreen:new {
  id = "choose_affirm",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_b69a10cf", -- "I'd recommend speaking to a gadget specialist. I've done business with a gadget specialist in the past and know where you can find one. Actually, I know of three of them. One in Keren on Naboo, on in Mos Entha on Tatooine, and one in Coronet on Corellia. I can upload a waypoint to their location if you'd like?"
  stopConversation = "false",
  options = {
    {"@conversation/fs_phase4_chief_engineer:s_59f634d7", "choose_specialist"}, -- "I'd like a waypoint to the gadget specialist in Coronet."
    {"@conversation/fs_phase4_chief_engineer:s_7f1e8a0c", "choose_specialist"}, -- "I'd like a waypoint to the gadget specialist in Mos Entha."
    {"@conversation/fs_phase4_chief_engineer:s_f75c2f80", "choose_specialist"}, -- "I'd like a waypoint to the gadget specialist in Keren."
    {"@conversation/fs_phase4_chief_engineer:s_69b44245", "choose_no_waypoint"}, -- "No waypoint needed. I'll speak to them and get you a replacement computer core."
    {"@conversation/fs_phase4_chief_engineer:s_85cf8e18", "choose_ponder"}, -- " Oh. Hmmm... maybe I should think about this a bit more."
  }
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(choose_affirm);

choose_specialist = ConvoScreen:new {
  id = "choose_specialist",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_dd8b435", -- "My pleasure. Ask if they can supply a replacement core. Then return here and bring it to me. Thanks and may the Force guide you."
  stopConversation = "true",
  options = {}
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(choose_specialist);

choose_no_waypoint = ConvoScreen:new {
  id = "choose_no_waypoint",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_29e5661", -- "Right. Good. Come back if you find a replacement. Or if you have any questions."
  stopConversation = "true",
  options = {}
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(choose_no_waypoint);

back_for_questions = ConvoScreen:new {
  id = "back_for_questions",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_6c741657", -- "No, no, no... it'll have to wait. Sorry, sorry. Just trying to sort some things out. You're the one helping with the replacement core, right? If I can answer any questions, just ask. "
  stopConversation = "false",
  options = {
    {"@conversation/fs_phase4_chief_engineer:s_a2e520b8", "choose_affirm"}, -- "Can you remind me where I need to go to find a replacement computer core?"
    {"@conversation/fs_phase4_chief_engineer:s_c7baf80c", "choose_howdo_kit"}, -- "What do I do with this tracking device kit?"
    {"@conversation/fs_phase4_chief_engineer:s_bab2829b", "choose_howto_get"}, -- "How do I get tracking data for a fallen satellite?"
    {"@conversation/fs_phase4_chief_engineer:s_7496bddd", "choose_ontrack"}, -- "Do you know how this satellite tracking device works?"
    {"@conversation/fs_phase4_chief_engineer:s_174ddced", "choose_cease"}, -- "I've changed my mind. You're on your own. Good luck... I guess."
  }
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(back_for_questions);

choose_howdo_kit = ConvoScreen:new {
  id = "choose_howdo_kit",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_4bcdc402", -- "You need to collect or craft all of the required components and place them in the kit. Once you have all of the components, the kit's automated system will build the tracking device."
  stopConversation = "true",
  options = {}
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(choose_howdo_kit);

choose_howto_get = ConvoScreen:new {
  id = "choose_howto_get",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_65f76975", -- "Go to any ticket droid at a starport. They have access to the database with information about fallen and abandoned satellites around the galaxy. You can purchase the rights to one of them from the droid."
  stopConversation = "true",
  options = {}
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(choose_howto_get);

choose_ontrack = ConvoScreen:new {
  id = "choose_ontrack",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_f9732f00", -- "Simply use the device's menu and choose to activate the tracking device. If you're on the wrong planet, it will tell you which planet the satellite is on. Once you're on the correct planet, the device can then pinpoint the exact location of the satellite."
  stopConversation = "true",
  options = {}
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(choose_ontrack);

choose_cease = ConvoScreen:new {
  id = "choose_cease",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_9c2a9f48", -- "Oh. Okay. Thank you. I think. I suppose I'll manage, Somehow."
  stopConversation = "true",
  options = {}
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(choose_cease);

return_with_core = ConvoScreen:new {
  id = "return_with_core",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_64391455", -- "It's you... good. Did you find a replacement computer core? Have you configured it so that it will be compatible with our computers?"
  stopConversation = "false",
  options = {
    {"@conversation/fs_phase4_chief_engineer:s_e3e36f42", "incomplete_core"}, -- "I have a replacement computer core for the village."
    {"@conversation/fs_phase4_chief_engineer:s_e3e36f42", "core_noinv"}, -- "I have a replacement computer core for the village."
    {"@conversation/fs_phase4_chief_engineer:s_121666b3", "complete_core"}, -- "Success, the replacement computer core is ready!"
    {"@conversation/fs_phase4_chief_engineer:s_121666b3", "core_noinv"}, -- "Success, the replacement computer core is ready!"
    {"@conversation/fs_phase4_chief_engineer:s_4294034a", "core_notyet"}, -- "No, It's... um... not ready yet."
  }
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(return_with_core);

incomplete_core = ConvoScreen:new {
  id = "incomplete_core",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_8ef5f872", -- "Ah yes. The core's current interface will need to be modified so that it will be compatible with computers here in the village. There should be a simple menu you can access on the core itself that will allow you to attempt the modification. Be careful though... if you fail too often you could short out the core and render it useless."
  stopConversation = "true",
  options = {}
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(incomplete_core);

core_noinv = ConvoScreen:new {
 id = "core_noinv",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_50191de0", -- "Hmmm... you don't appear to have the computer core with you. Please return when you have it."
  stopConversation = "true",
  options = {}
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(core_noinv);

core_notyet = ConvoScreen:new {
  id = "core_notyet",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_742ff942", -- "Oh, that's not good. Please hurry. Our backup is not going to last much longer."
  stopConversation = "true",
  options = {}
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(core_notyet);

complete_core = ConvoScreen:new {
  id = "complete_core",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_860baf7e", -- "Yes! Thank you! This will work perfectly. In exchange for your services, I will happily get you started on the road to the Mastery of Crafting Repair."
  stopConversation = "false",
  options = {
    {"@conversation/fs_phase4_chief_engineer:s_4136c2df", "thank_get_reward"}, -- "Thank you very much."
    {"@conversation/fs_phase4_chief_engineer:s_4136c2df", "thank_get_reward_full"}, -- "Thank you very much."
  }
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(complete_core);

thank_get_reward = ConvoScreen:new {
  id = "thank_get_reward",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_8b482724", -- "As further token of the village's thanks, we would like to present to you this section of an Aurilian sculpture."
  stopConversation = "true",
  options = {}
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(thank_get_reward);

thank_get_reward_full = ConvoScreen:new {
  id = "thank_get_reward_full",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_bce29099", -- "We would also like to present you with this section of an Aurilian sculpture as further thanks for your help. But it seems that you do not have room in your inventory for it at the moment. Please make some room and then speak with me again."
  stopConversation = "true",
  options = {}
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(thank_get_reward_full);

back_clearedinv = ConvoScreen:new {
  id = "back_clearedinv",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_ec479e11", -- "Yes, hello. You've returned the rest of your reward?"
  stopConversation = "false",
  options = {
    {"@conversation/fs_phase4_chief_engineer:s_6516bd5a", "thank_get_reward"}, -- "Yes, I've made room and returned as you asked"
    {"@conversation/fs_phase4_chief_engineer:s_a69082f1", "back_no_reward_yet"}, -- "No thanks. Not this time."
  }
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(back_clearedinv);

back_no_reward_yet = ConvoScreen:new {
  id = "back_no_reward_yet",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_caa53683", -- "That's quite alright. Okay, first I need to... something. Maybe I'll start... no no. Obviously. Well. Something."
  stopConversation = "true",
  options = {}
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(back_no_reward_yet);

back_but_failed = ConvoScreen:new {
  id = "back_but_failed",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_acbab09c", -- "Those freaks are attacking. Everything is breaking. I can't believe I accepted this chief engineering post. What was I thinking. Ah well, there's nothing for it now but to muddle through."
  stopConversation = "false",
  options = {
    {"@conversation/fs_phase4_chief_engineer:s_59f5cee6", "accept_but_phase"}, -- "Is there anything I can do to help?"
    {"@conversation/fs_phase4_chief_engineer:s_5542b04b", "choose_decline"}, -- "Oh, my apologies. I'll let you get back to work."
  }
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(back_but_failed);

accept_but_lockout = ConvoScreen:new {
  id = "accept_but_lockout",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_9caa26f9", -- "Thank you, that's very kind. Normally I would gladly accept your help, but at the moment I'm already juggling more people and problems than I can handle. Please come back after some time has passed and I'll see if I can phase you in."
  stopConversation = "true",
  options = {}
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(accept_but_lockout);

new_chief_nextday = ConvoScreen:new {
  id = "new_chief_nextday",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_5062e892", -- "You worked with the last chief engineer, right? But weren't able to find a replacement in time. Would you like to try again? Continue from where you left off?"
  stopConversation = "false",
  options = {
    {"@conversation/fs_phase4_chief_engineer:s_ff872480", "choose_accept_newday"}, -- "Yes I would. Thank you for the second chance."
    {"@conversation/fs_phase4_chief_engineer:s_eac5593c", "choose_decline"}, -- "No, I'm doing just fine. I'll leave you to your work."
  }
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(new_chief_nextday);

choose_accept_newday = ConvoScreen:new {
  id = "choose_accept_newday",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_3031b4c9", -- "Excellent. Continue from where you left off. Come speak with me again if you have any questions."
  stopConversation = "true",
  options = {}
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(choose_accept_newday);

back_but_finished = ConvoScreen:new {
  id = "back_but_finished",
  leftDialog = "@conversation/fs_phase4_chief_engineer:s_48b1807b", -- "Ah, good to see you again. Have you had a chance to develop your mastery of crafting and repair? No wait... don't answer. I wish I had more time to speak, but I'm so very busy. I must get back to work."
  stopConversation = "true",
  options = {}
}

villageChiefEngineerPhase4ConvoTemplate:addScreen(back_but_finished);

addConversationTemplate("villageChiefEngineerPhase4ConvoTemplate", villageChiefEngineerPhase4ConvoTemplate);