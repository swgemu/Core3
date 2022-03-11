valance_serth_convo_template = ConvoTemplate:new {
    initialScreen = "first_screen",
    templateType = "Lua",
    luaClassHandler = "valance_serth_convo_handler",
    screens = {}
}

first_screen = ConvoScreen:new {
    id = "first_screen",
    leftDialog = "@conversation/c_ddroid_valance:s_1170", --Thank you!  Once those pirates get roused, there's nothing to stop them.

    options = {
        {"@conversation/c_ddroid_valance:s_1172","happy_help"}, --I'm happy I could help.
        {"@conversation/c_ddroid_valance:s_1176","expect_return"}, --I'm expecting a little in return.
    }
}
valance_serth_convo_template:addScreen(first_screen)

happy_help = ConvoScreen:new {
    id = "happy_help",
    leftDialog = "@conversation/c_ddroid_valance:s_1174", --I owe you my life, but this is all that I have been able to salvage from the flight. I hope it will help you out. I have one more favor to ask, if possible.
    stopConversation = "true",
    options = {}
}
valance_serth_convo_template:addScreen(happy_help)

expect_return = ConvoScreen:new {
    id = "expect_return",
    leftDialog = "@conversation/c_ddroid_valance:s_1178", --Of course you are!  Unfortunately, this is all that I have been able to salvage from the flight.  I know that I shouldn't be asking, but I need another favor.
    stopConversation = "true",
    options = {}
}
valance_serth_convo_template:addScreen(expect_return)

not_ready = ConvoScreen:new {
    id = "not_ready",
    leftDialog = "@conversation/c_ddroid_valance:s_1269", --It's going to take me forever to fix this ship!
    stopConversation = "true",
    options = {}
}
valance_serth_convo_template:addScreen(not_ready)

inventory_full = ConvoScreen:new {
    id = "inventory_full",
    leftDialog = "@conversation/crafting_contractor:s_82c3e20a", --It looks like your inventory is full. Talk to me again when you free up some space.
    stopConversation = "true",
    options = {}
}
valance_serth_convo_template:addScreen(inventory_full)

addConversationTemplate("valance_serth_convo_template", valance_serth_convo_template)