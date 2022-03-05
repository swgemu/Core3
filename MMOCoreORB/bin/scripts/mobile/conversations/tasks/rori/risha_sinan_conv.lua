risha_sinan_convo_template = ConvoTemplate:new {
    initialScreen = "first_screen",
    templateType = "Lua",
    luaClassHandler = "risha_sinan_convo_handler",
    screens = {}
}

first_screen = ConvoScreen:new {
    id = "first_screen",
    leftDialog = "@conversation/lf_killmite:s_159", --Hello!  Sorry to bother you, but do you have some time to check out a mite nest?

    options = {
        {"@conversation/lf_killmite:s_161","i_suppose"}, --I suppose I have the time.
        {"@conversation/lf_killmite:s_183","maybe"}, --Maybe.  Would you tell me more about it?".
        {"@conversation/lf_killmite:s_177","not_now"}, --Not right now.
    }
}
risha_sinan_convo_template:addScreen(first_screen)

i_suppose = ConvoScreen:new {
    id = "i_suppose",
    leftDialog = "@conversation/lf_killmite:s_164", --Thank you.  To the west is a giant bark mite cave.  I can show you where.  I need specimens.  Once you get there, I'll transmit the specimens that I need and how many of each.

    options = {
        {"@conversation/lf_killmite:s_167", "happy_to_help"}, --I would be happy to help you out.
        {"@conversation/lf_killmite:s_172", "get_paid"}, --And I'll get paid for this, I assume?
    }
}
risha_sinan_convo_template:addScreen(i_suppose)

maybe = ConvoScreen:new {
    id = "maybe",
    leftDialog = "@conversation/lf_killmite:s_185", --Bark mites!  Fascinating little creatures, but they absolutely destroy the greenery!  I recently found a mutant variant that may yield information that may lead to a chemical that will repel these insects.

    options = {
        {"@conversation/lf_killmite:s_161","i_suppose"}, --I suppose I have the time.
        {"@conversation/lf_killmite:s_177","not_now"}, --Not right now.
    }
}
risha_sinan_convo_template:addScreen(maybe)

not_now = ConvoScreen:new {
    id = "not_now",
    leftDialog = "@conversation/lf_killmite:s_180", --That's a shame.  Come back to me if you change your mind.
    stopConversation = "true",
    options = {}
}
risha_sinan_convo_template:addScreen(not_now)

happy_to_help = ConvoScreen:new {
    id = "happy_to_help",
    leftDialog = "@conversation/lf_killmite:s_169", --Excellent.  I am glad to see that someone supports science around here.  I'll transfer credits into your bank account as I get usable readings.  Hopefully I can get my hands on something extra special by the time you get back.
    stopConversation = "true",
    options = {}
}
risha_sinan_convo_template:addScreen(happy_to_help)

get_paid = ConvoScreen:new {
    id = "get_paid",
    leftDialog = "@conversation/lf_killmite:s_175", --Of course.  I cannot expect others to love science the way I do.  I'll transfer credits into your bank account as I get usable readings.  Perhaps I will get my hands on something extra special by the time you get back.

    options = {
        {"@conversation/lf_killmite:s_167", "happy_to_help"}, --I would be happy to help you out.
        {"@conversation/lf_killmite:s_177","not_now"}, --Not right now.
    }
}
risha_sinan_convo_template:addScreen(get_paid)

how_goes = ConvoScreen:new {
    id = "how_goes",
    leftDialog = "@conversation/lf_killmite:s_188", --How did you fare?

    options = {}
}
risha_sinan_convo_template:addScreen(how_goes)

got_lost = ConvoScreen:new {
    id = "got_lost",
    leftDialog = "@conversation/lf_killmite:s_215", --Certainly!  I know what you mean.  If I don't keep things perfectly organized, I can't find a darn thing.
    stopConversation = "true",
    options = {}
}
risha_sinan_convo_template:addScreen(got_lost)

not_done = ConvoScreen:new {
    id = "not_done",
    leftDialog = "@conversation/lf_killmite:s_209", --Of course not.  I should know that by my notes.  Good luck with the rest of your hunting!
    stopConversation = "true",
    options = {}
}
risha_sinan_convo_template:addScreen(not_done)

tasks_complete = ConvoScreen:new {
    id = "tasks_complete",
    leftDialog = "@conversation/lf_killmite:s_193", --Oh goodness.  Of course I did.  I'm a little scatterbrained these days.  Fantastic work.  Are you interested in science and engineering?

    options = {
        {"@conversation/lf_killmite:s_196", "give_schematic"}, --Yes!  I love creating things.
        {"@conversation/lf_killmite:s_201","give_stim"}, --Actually, I prefer hunting.
    }
}
risha_sinan_convo_template:addScreen(tasks_complete)

give_schematic = ConvoScreen:new {
    id = "give_schematic",
    leftDialog = "@conversation/lf_killmite:s_199", --Wonderful!  I have this schematic for you then.  I'm not sure if it's your particular field, but it should be worth something.
    stopConversation = "true",
    options = {}
}
risha_sinan_convo_template:addScreen(give_schematic)

give_stim = ConvoScreen:new {
    id = "give_stim",
    leftDialog = "@conversation/lf_killmite:s_204", --Well, we all have our paths to walk, don't we?  This should help you out while you hunt!
    stopConversation = "true",
    options = {}
}
risha_sinan_convo_template:addScreen(give_stim)

nice_to_see_you = ConvoScreen:new {
    id = "nice_to_see_you",
    leftDialog = "@conversation/lf_killmite:s_217", --Hello!  It's good to see you again.
    stopConversation = "true",
    options = {}
}
risha_sinan_convo_template:addScreen(nice_to_see_you)

addConversationTemplate("risha_sinan_convo_template", risha_sinan_convo_template)