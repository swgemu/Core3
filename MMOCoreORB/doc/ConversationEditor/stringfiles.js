//StringFile class.
function StringFile(fileName) {
	this.fileName = fileName;
	this.entries = new Object();

	this.addEntry = function(key, value) {
		this.entries[key] = value;
	}
}

var stringFiles = new Array();
stringFiles[0] = new StringFile("newbie_tutorial/newbie_convo");
stringFiles[0].addEntry("banker_1_start", "Well it seems your ship wasn't carrying contraband after all. Pity we didn't discover that sooner...");
stringFiles[0].addEntry("banker_2_start", "Well we suspected you were smuggling, so we boarded the transport you were travelling aboard, of course. Don't worry, we've cleared you of all charges.");
stringFiles[0].addEntry("banker_1_reply_1", "What did you do to my ship?");
stringFiles[0].addEntry("convo_1_start", "That's more like it. Well, I'm your supply disbursement officer. I don't see why we should waste good supplies on refugees like you.");
stringFiles[0].addEntry("convo_1_more", "You people, you're all the same. Look, you were on a ship with dubious credentials. The Star Destroyer hailed you, and you didn't stop fast enough. So they boarded, and brought the survivors over here.");
stringFiles[0].addEntry("convo_1_reply_1", "What happened?");
stringFiles[0].addEntry("convo_1_explain", "They weren't civilians. They were dissidents. Officially, anyway. Now, go get your free supplies from this drum right here, courtesy of the generosity of the Empire.");
stringFiles[0].addEntry("convo_1_reply_2", "What supplies?");
stringFiles[0].addEntry("convo_1_stuff", "There's some stuff left that the other refugees didn't take. Not much though. In the drum right here.");
stringFiles[0].addEntry("convo_1_reply_3", "The survivors? You mean the Empire killed civilian passengers?");

stringFiles[1] = new StringFile("hireling/hireling_military");
stringFiles[1].addEntry("start_convo_1", "Sir?");
