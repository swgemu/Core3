//Conversation Editor
function ConversationEditor() {
	this.ui = document.createElement("div");
	this.conversationScreenList = new ConversationScreenList(this);
	this.conversationScreen = new ConversationScreen(this, "convoscreen1", "Conversation Screen 1");
	this.conversationStringSelectionDialog = new ConversationStringSelectionDialog(this);

	//initialize
	this.ui.appendChild(this.conversationScreen.ui);
	this.ui.appendChild(this.conversationScreenList.ui);
}

function ConversationScreenList(conversationEditor) {
	this.conversationEditor = conversationEditor;
	this.ui = document.createElement("div");
	this.conversationScreens = new Object();
	this.conversationScreen.ui = document.createElement("select");
	this.totalScreens = 0;

	this.addConversationScreen = function(conversationScreen) {
		conversationScreen.conversationScreenList = this;
		this.conversationScreens[conversationScreen.screenName] = conversationScreen;

		var option = document.createElement("option");
	}

	//initialize
}

function ConversationScreen(screenName, displayName) {
	this.screenName = screenName;
	this.displayName = displayName;
	this.ui = document.createElement("div");
	this.conversationScreenList = null;
	this.option.ui = null;

	this.conversationWindow = null;


	//initialize
}

function ConversationWindow(conversationScreen) {
	this.conversationScreen = conversationScreen;
	this.ui = document.createElement("div");
	this.leftDialog = new ConversationDialog(this);
	this.conversationOptions = new ConversationOptions(this);

	//initialize
	//this.leftDialog.onclick = showStringDialog();
}

function ConversationDialog(conversationWindow) {
	this.conversationWindow = conversationWindow;
	this.ui = document.createElement("div");

	//initialize
	this.ui.innerHTML = "&lt;Add Caption&gt;";
	this.conversationWindow.ui.appendChild(this.ui);
}

function ConversationOptions(conversationWindow) {
	this.conversationWindow = conversationWindow;
	this.ui = document.createElement("div");
	this.addButton = document.createElement("div");
	this.options = new Object();

	this.addOption = function(key, conversationOption) {
		this.options[key] = conversationOption;
	}

	this.removeOption = function(key) {
		delete this.options[key];
	}

	this.containsOption = function(key) {
		return (this.options[key] != null);
	}

	//initialize
	//this.addButton.onclick = this.addOption();
}

function ConversationOption(stringPath, link) {
	this.ui = document.createElement("div");
	this.stringPath = stringPath;
	this.link = link;

	this.onclick = function() {
	}

	//initialize
	this.ui.innerHTML = stringPath;
	this.ui.onclick = this.onclick;
}

function ConversationStringSelectionDialog(conversationEditor) {
	this.conversationEditor = conversationEditor;
	this.ui = document.createElement("div");
	this.fileSelect = document.createElement("select");
	this.keySelect = document.createElement("select");
	this.stringPreview = document.createElement("p");

	this.fillKeys = function() {
	}

	this.show = function() {
		this.ui.style.display = "block";
	}

	this.hide = function() {
		this.ui.style.display = "none";
	}
	
	//initialize fileselect
	var element = document.createElement("div");
	var label = document.createElement("label");	
	label.setAttribute("for", "fileSelect");
	this.fileSelect.setAttribute("id", "fileSelect");
	this.fileSelect.onchange = this.fillKeys;
	label.appendChild(this.fileSelect);
	element.appendChild(label);
	this.ui.appendChild(element);

	//initialize keyselect
	element = document.createElement("div");
	label = document.createElement("label");
	label.setAttribute("for", "keySelect");
	this.keySelect.setAttribute("id", "keySelect");
	this.keySelect.onchange = this.setPreviewString;
	label.appendChild(this.keySelect);
	element.appendChild(label);
	this.ui.appendChild(element);

	//initialize stringpreview	
	element = document.createElement("div");
	this.stringPreview.innerHTML = "undefined";
	element.appendChild(this.stringPreview);
	this.ui.appendChild(element);

	//initialize buttons
	//this.
}

/*
<div id="stringChooser">
	<div>
		<input type="button" value="Set String" onclick="setString('stringChooser', 'fileSelect', 'keySelect');" />
		<input type="button" value="Cancel" onclick="hideStringChooser('stringChooser');" />
		<input type="button" id="removeButton" value="Remove Option" onclick="removeOption();" />
	</div>
</div>
*/


/*
<div id="conversationWindow">
	<div id="leftDialog" onclick="showStringChooser(this, 'stringChooser', false);">
		&lt;Add Caption&gt;
	</div>
	<div class="divisor"></div>
	<div id="conversationOptions">
		<div id="optionCreate" onclick="addOption(this, 'stringChooser', 'conversationOptions');">&lt;Add Option&gt;</div>
	</div>
</div>
*/
