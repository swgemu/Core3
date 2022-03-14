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

need_help = ConvoScreen:new {
    id = "need_help",
    leftDialog = "@conversation/c_ddroid_valance:s_1180", --I need a favor...for the good of the Empire, or its people, or whatever you believe in.  Either way, innocent people will get hurt if you can't help me.

    options = {
        {"@conversation/c_ddroid_valance:s_1182","what_favor"}, --What is the favor?
    }
}
valance_serth_convo_template:addScreen(need_help)

what_favor = ConvoScreen:new {
    id = "what_favor",
    leftDialog = "@conversation/c_ddroid_valance:s_1184", --What do you know about the Black Sun?

    options = {
        {"@conversation/c_ddroid_valance:s_1186","just_rumor"}, --Not all that much.  Just rumors really.
    }
}
valance_serth_convo_template:addScreen(what_favor)

just_rumor = ConvoScreen:new {
    id = "just_rumor",
    leftDialog = "@conversation/c_ddroid_valance:s_1188", --Well, the rumors are probably true.  They are vile, nasty criminals that live only for themselves and the control of anything that may make them money.  And destroy anything that could put that in jeopardy.

    options = {
        {"@conversation/c_ddroid_valance:s_1190","after_you"}, --Why were they going after you?
    }
}
valance_serth_convo_template:addScreen(just_rumor)

after_you = ConvoScreen:new {
    id = "after_you",
    leftDialog = "@conversation/c_ddroid_valance:s_1192", --I came across some information about one of their latest schemes.  They plan to taint a major shipment of medicinal spice.  I want to stop them, but I'm hurt.

    options = {
        {"@conversation/c_ddroid_valance:s_1194","tainted_spice"}, --Tainted medicinal spice?
        {"@conversation/c_ddroid_valance:s_1206","ill_help"}, --I will help.
        {"@conversation/c_ddroid_valance:s_1210","no_time"}, --I don't have time right now.
    }
}
valance_serth_convo_template:addScreen(after_you)

tainted_spice = ConvoScreen:new {
    id = "tainted_spice",
    leftDialog = "@conversation/c_ddroid_valance:s_1196", --Yes.  There's an outbreak of Ourim Flu on several planets.  People are dying.  The Sun will use the tainted spice to addict the sick people to their chemicals.

    options = {
        {"@conversation/c_ddroid_valance:s_1198","will_help"}, --I will help.
        {"@conversation/c_ddroid_valance:s_1202","not_now"}, --I don't have the time right now.
    }
}
valance_serth_convo_template:addScreen(tainted_spice)

ill_help = ConvoScreen:new {
    id = "ill_help",
    leftDialog = "@conversation/c_ddroid_valance:s_1208", --Oh thank you!  Here is the last known location of their base.  Here are coordinates of a spot near their base.  You should be able to see them from this spot.  Kill them if you must, but stop them.
    stopConversation = "true",
    options = {}
}
valance_serth_convo_template:addScreen(ill_help)

no_time = ConvoScreen:new {
    id = "no_time",
    leftDialog = "@conversation/c_ddroid_valance:s_1212", --I'm sorry to hear that.  I hope I'll be able to find someone that will help me resolve this dangerous situation.
    stopConversation = "true",
    options = {}
}
valance_serth_convo_template:addScreen(no_time)

will_help = ConvoScreen:new {
    id = "will_help",
    leftDialog = "@conversation/c_ddroid_valance:s_1200", --Oh thank you!  Here are coordinates of a spot near their base.  You should be able to see them from this spot.  Kill them if you must, but stop them.
    stopConversation = "true",
    options = {}
}
valance_serth_convo_template:addScreen(will_help)

not_now = ConvoScreen:new {
    id = "not_now",
    leftDialog = "@conversation/c_ddroid_valance:s_1204", --I'm sorry to hear that.  I hope I'll be able to find someone to help me resolve this dangerous situation.
    stopConversation = "true",
    options = {}
}
valance_serth_convo_template:addScreen(not_now)

on_part1 = ConvoScreen:new {
    id = "on_part1",
    leftDialog = "@conversation/c_ddroid_valance:s_1252", --Please go eliminate that staging camp.
    stopConversation = "true",
    options = {}
}
valance_serth_convo_template:addScreen(on_part1)

completed_part2 = ConvoScreen:new {
    id = "completed_part2",
    leftDialog = "@conversation/c_ddroid_valance:s_1214", --Welcome back.

    options = {
        {"@conversation/c_ddroid_valance:s_1216","camp_done"}, --I took care of the Black Sun Camp
        {"@conversation/c_ddroid_valance:s_1230","not_done_yet"}, --I'm not done yet.
    }
}
valance_serth_convo_template:addScreen(completed_part2)

camp_done = ConvoScreen:new {
    id = "camp_done",
    leftDialog = "@conversation/c_ddroid_valance:s_1220", --I'm afraid they must have had early warning! They launched their transport already.  The only hope left is to intercept the transport in space.

    options = {
        {"@conversation/c_ddroid_valance:s_1222","tell_more"}, --Ok, tell me more, I'm always ready for a trip into space.
        {"@conversation/c_ddroid_valance:s_1226","get_ready"}, --Give me a moment to get myself ready.
    }
}
valance_serth_convo_template:addScreen(camp_done)

not_done_yet = ConvoScreen:new {
    id = "not_done_yet",
    leftDialog = "@conversation/c_ddroid_valance:s_1232", --They are probably pretty tough.  Please hurry as much as you safely can.
    stopConversation = "true",
    options = {}
}
valance_serth_convo_template:addScreen(not_done_yet)

tell_more = ConvoScreen:new {
    id = "tell_more",
    leftDialog = "@conversation/c_ddroid_valance:s_1224", --What else can I tell you?  Get to a Starport and into space.  Go blow up that transport and anything that stands in the way.  I should be able to arrange for you to get some coordinates to help.
    stopConversation = "true",
    options = {}
}
valance_serth_convo_template:addScreen(tell_more)

get_ready = ConvoScreen:new {
    id = "get_ready",
    leftDialog = "@conversation/c_ddroid_valance:s_1228", --All right, but hurry.
    stopConversation = "true",
    options = {}
}
valance_serth_convo_template:addScreen(get_ready)

failed_space = ConvoScreen:new {
    id = "failed_space",
    leftDialog = "@conversation/c_ddroid_valance:s_1254", --Ouch, you don't look too good.  The first of the transports got away.  This isn't the end of the galaxy.  The majority still haven't gotten out of the system.  Are you ready to go after them again?

    options = {
        {"@conversation/c_ddroid_valance:s_1256","im_ready"}, --I'm ready!
        {"@conversation/c_ddroid_valance:s_1260","give_time"}, --Give me some time.
    }
}
valance_serth_convo_template:addScreen(failed_space)

im_ready = ConvoScreen:new {
    id = "im_ready",
    leftDialog = "@conversation/c_ddroid_valance:s_1258", --Good luck!
    stopConversation = "true",
    options = {}
}
valance_serth_convo_template:addScreen(im_ready)

give_time = ConvoScreen:new {
    id = "give_time",
    leftDialog = "@conversation/c_ddroid_valance:s_1262", --Please hurry.  It's still a trek back to the starport.
    stopConversation = "true",
    options = {}
}
valance_serth_convo_template:addScreen(give_time)

completed_space = ConvoScreen:new {
    id = "completed_space",
    leftDialog = "@conversation/c_ddroid_valance:s_1234", --Hello, my friend. Thank you for all your help so far.  I shouldn't ask, but...well...you recall the droid that sent you to me, C-3TC?

    options = {
        {"@conversation/c_ddroid_valance:s_1236","rather_difficult"}, --He's rather difficult to forget.
        {"@conversation/c_ddroid_valance:s_1248","oh_no"}, --Oh no!  I'm not going anywhere near that thing again!
    }
}
valance_serth_convo_template:addScreen(completed_space)

rather_difficult = ConvoScreen:new {
    id = "rather_difficult",
    leftDialog = "@conversation/c_ddroid_valance:s_1238", --Yes, well...he's also the one responsible for getting me into trouble in the first place and I'm tired of it.  If you head back to Moenia anytime soon, would you talk to him and have him run this program for me?  It will wipe his memory and I won't have to worry about Black Sun goons anymore.

    options = {
        {"@conversation/c_ddroid_valance:s_1240","do_that"}, --I can do that if you like.
        {"@conversation/c_ddroid_valance:s_1244","after_all"}, --What?!  After all that he did to help you...
    }
}
valance_serth_convo_template:addScreen(rather_difficult)

oh_no = ConvoScreen:new {
    id = "oh_no",
    leftDialog = "@conversation/c_ddroid_valance:s_1250", --Well, much as it saved my life, I can't say that I blame you.  If you change your mind, come back and talk to me.
    stopConversation = "true",
    options = {}
}
valance_serth_convo_template:addScreen(oh_no)

do_that = ConvoScreen:new {
    id = "do_that",
    leftDialog = "@conversation/c_ddroid_valance:s_1242", --I would appreciate it.  He's probably fretting his bolts off.
    stopConversation = "true",
    options = {}
}
valance_serth_convo_template:addScreen(do_that)

after_all = ConvoScreen:new {
    id = "after_all",
    leftDialog = "@conversation/c_ddroid_valance:s_1246", --Whoa!  Remember, he's a droid.  I'll just be doing both him and myself a favor.  If you don't want to do it, that's your business.  When you change your mind, talk to me.
    stopConversation = "true",
    options = {}
}
valance_serth_convo_template:addScreen(after_all)

completed_all = ConvoScreen:new {
    id = "completed_all",
    leftDialog = "@conversation/c_ddroid_valance:s_1264", --Hello my friend.  You saved many many innocent people.

    options = {
        {"@conversation/c_ddroid_valance:s_1266","doing_here"}, --What are you still doing here?
    }
}
valance_serth_convo_template:addScreen(completed_all)

doing_here = ConvoScreen:new {
    id = "doing_here",
    leftDialog = "@conversation/c_ddroid_valance:s_1268", --I like it here.  It's exciting!  Heh. Actually, I need to make sure that my stuff on this ship is taken care of.
    stopConversation = "true",
    options = {}
}
valance_serth_convo_template:addScreen(doing_here)

addConversationTemplate("valance_serth_convo_template", valance_serth_convo_template)