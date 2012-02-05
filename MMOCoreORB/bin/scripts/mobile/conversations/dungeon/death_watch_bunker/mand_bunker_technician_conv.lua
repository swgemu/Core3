mand_bunker_technician_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Normal",
	--luaClassHandler = "death_watch_mand_bunker_technician_handler",
	screens = {}
}


mand_bunker_technician_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@conversation/death_watch_technician:s_ebfed4db",
	stopConversation = "true",
	options = {
		--{"@conversation/death_watch_technician:s_3fb7180e", "convoscreen2"},
	}
}

mand_bunker_technician_convotemplate:addScreen(mand_bunker_technician_convoscreen1);

addConversationTemplate("mand_bunker_technician_convotemplate", mand_bunker_technician_convotemplate);

--[[
option s_17aa7854	I can do that. Send in the droid and I will take care of the Mandalorians.
option s_1a05844b	Hmmm, I am not going to do that. Those Mandalorians are nasty.
option s_1cc2ceff	I see. So.... what sort of work do you do here?
response s_1fb416ce	Give me a few minutes. I just sent out one of my droids on a dangerous mission with an escort. I am hoping that this works.
response s_25e933d3	I am an exhaust ventilation technician for the mines. It is my job to make sure that the mine's exhaust system is working correctly. Of course, that is when the Mandalorians let me do my job.
response s_32b29b58	You are going to have to give me a little while to get another droid put together. Come back and talk to me later. If I still need the help, I will be more than willing to take it.
response s_33381eda	I can't thank you enough for helping me out back there. The exhaust fans are back online and the miners should be safe for a while at least. That exhaust system is pretty iffy and shorts out alot. I think the Mandalorians are breaking it on purpose just so they can have their fun.
option s_373533eb	You know it. I will protect that droid.
option s_3bc0260c	Those Mandalorians are to much for me.
response s_3cab69e3	Hey, you don't know how happy I am to see you again. The exhaust system went offline again and...that's right...you guessed it...those Mandalorians are at it again. You willing to give me a hand again?
option s_3f1a842c	Yeah, yeah.
option s_406a4ae2	Sounds like you do have it rough.
response s_45ae332c	The mines fill up with allum gas. That stuff can really mess up the men working inside the mines. So all the miners have to wear the rebreather gear in order to work down there, but those things are not always reliable.
?? s_72f8ec3a	Okay, well, good luck with that.
option s_7d875e15	Give me another chance. I know I can keep that droid alive.
response s_89b80057	Can't say I blame you.
response s_8b67f49d	Hmm, who are you? Actually, nevermind. I don't want to know. If the Mandalorians don't want you here, they can take care of you themselves. It's not like they ever help me. No, not them. They tell me to get a job done and then don't let me do it.
response s_9a8c12bc	I knew I could count on you. Okay, I am going to unleash the droid now. Good luck to you.
option s_a0c1a32f	What are the Mandalorians doing to stop you from working?
response s_a8fb8b64	The main exhaust ports are offline and I need to send in a droid to fix it. But everytime I send in one of my droids, these dumb Mandalorians shoot it to pieces. Then, they laugh about it all the while yelling at me for not having the ports back online.
response s_aad4d52	Oh, well, I am sure I will figure something else out. Thanks anyways.
?? s_bb1676fc	Having problems with the Mandalorians?
response s_bb18b90f	Ain't that the truth. Now, if there isn't anything else, I really need to get back to trying to figure out a way to get those dumb Mandalorians not to trash another one of my droids.
response s_bd52a08a	Blast it! Lost another droid. I swear those Mandalorians are just relentless when they feel the need to torment someone.
option s_bd5476c4	Maybe I can help you out?
option s_c4446dd7	What happens if the mine's exhaust system isn't working?
response s_c74f6e65	The only thing that I can think of to help me out is if you go in with the droid and don't let the Mandalorians blow it up. If you are willing to do that, you have way more guts than I would ever have.
response s_cba682eb	What are you doing back here? You are supposed to be protecting that droid. Without your protection, those Mandalorians will blow him to bits.
option s_cbf95857	I am sorry, but I can't right now.
option s_d7a232dc	What sort of job do you do?
response s_ebfed4db	I am sorry, but I really don't have much time to chat right now. Always too much work to do in to little time. Maybe later I will have a spare moment.
response s_f7d4b8be	Now that might be a little bit of an understatement. I always have problems with the Mandalorians. They just don't deal well with others... I am thinking that they probably weren't hugged enough when they were children.
response s_fc578c95	You are not the first person to say those words.
response s_fe84832a	Alright, I am going to release the droid. It has to make a stop over at the tool chest to get some extra tools before it can make the repairs. Keep those Mandalorians off it until it can finish the repairs and these air vents will kick on and clear out the allum gases.
]]