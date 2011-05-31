//Conversation Editor
function ConversationEditor() {
	this.ui = document.createElement("div");
	this.ui.conversationEditor = this;
	this.ui.parentObject = this;
	this.scriptName = document.createElement("input");
	this.scriptWindow = document.createElement("pre");
	this.generateScriptButton = document.createElement("input");
	this.conversationScreenList = new ConversationScreenList(this);
	this.conversationStringSelectionDialog = new ConversationStringSelectionDialog(this);
	this.conversationScreen = this.conversationScreenList.createConversationScreen();

	this.appendToElement = function(elementId) {
		var parentObject = (this.parentObject != null) ? this.parentObject : this;
	
		var element = document.getElementById(elementId);

		if (element == null)
			return;

		element.appendChild(parentObject.ui);
	}

	this.changeScreen = function(conversationScreen) {
		var parentObject = (this.parentObject != null) ? this.parentObject : this;

		var parentNode = parentObject.conversationScreen.ui.parentNode;
		
		if (parentNode != null) {
			parentNode.replaceChild(conversationScreen.ui, parentObject.conversationScreen.ui);
		}
		
		parentObject.conversationScreen = conversationScreen;
	}

	this.writeToScript = function() {
		var parentObject = (this.parentObject != null) ? this.parentObject : this;

		if (parentObject.scriptName.value == "") {
			alert("Please specify a name for the script before generating it.");
			return parentObject.scriptName.focus();
		}

		var script = "";

		for (key in parentObject.conversationScreenList.conversationScreens) {
			if (key == "ui")
				continue;

			var convoScreen = parentObject.conversationScreenList.conversationScreens[key];

			script = convoScreen.writeToScript(script);

		}

		parentObject.scriptWindow.innerHTML = script;
	}

	//initialize
	this.ui.setAttribute("class", "conversationEditor");
	this.ui.setAttribute("className", "conversationEditor");

	var element = document.createElement("div");
	element.setAttribute("class", "conversationScriptName");
	element.setAttribute("className", "conversationScriptName");
	var label = document.createElement("label");
	this.scriptName.setAttribute("type", "text");
	this.scriptName.setAttribute("id", "scriptName");
	label.setAttribute("for", "scriptName");
	label.innerHTML = "Script Name: ";
	label.appendChild(this.scriptName);
	element.appendChild(label);
	this.ui.appendChild(element);

	var container = document.createElement("div");
	container.setAttribute("class", "conversationEditorContainer");
	container.setAttribute("className", "conversationEditorContainer");

	element = document.createElement("div");
	element.setAttribute("class", "conversationScriptWindow");
	element.setAttribute("className", "conversationScriptWindow");
	element.appendChild(this.scriptWindow);
	this.generateScriptButton.setAttribute("type", "button");
	this.generateScriptButton.setAttribute("value", "Generate Script");
	this.generateScriptButton.parentObject = this;
	this.generateScriptButton.onclick = this.writeToScript;
	element.appendChild(this.generateScriptButton);
	container.appendChild(element);

	container.appendChild(this.conversationScreenList.ui);
	container.appendChild(this.conversationScreen.ui);
	container.appendChild(this.conversationStringSelectionDialog.ui);

	this.ui.appendChild(container);
}

function ConversationScreenList(conversationEditor) {
	this.conversationEditor = conversationEditor;
	this.ui = document.createElement("div");
	this.ui.parentObject = this;
	this.conversationScreens = new Object();
	this.conversationScreens.ui = document.createElement("select");
	this.addButton = document.createElement("input");
	this.removeButton = document.createElement("input");
	this.totalScreens = 0;
	this.nextIndex = 0;

	this.createConversationScreen = function() {
		var parentObject = (this.parentObject != null) ? this.parentObject : this;

		++parentObject.totalScreens;
		++parentObject.nextIndex;

		var conversationScreen = new ConversationScreen("convoscreen" + parentObject.nextIndex, "Conversation Screen " + parentObject.nextIndex);
		conversationScreen.conversationScreenList = parentObject;
		parentObject.conversationScreens[conversationScreen.screenName] = conversationScreen;

		var option = document.createElement("option");
		option.text = conversationScreen.displayName;
		option.value = conversationScreen.screenName;
		
		try {
			parentObject.conversationScreens.ui.add(option, null);
		} catch (ex) {
			parentObject.conversationScreens.ui.add(option);
		}
		
		//Refresh the available screens.
		parentObject.conversationEditor.conversationStringSelectionDialog.fillScreens();

		return conversationScreen;
	}

	this.removeConversationScreen = function() {
		var parentObject = (this.parentObject != null) ? this.parentObject : this;

		if (parentObject.totalScreens == 1)
			return alert("You must have at least one conversation screen.");

		--parentObject.totalScreens;

		var selectedScreen = parentObject.conversationScreens[parentObject.conversationScreens.ui.options[parentObject.conversationScreens.ui.selectedIndex].value];

		delete parentObject.conversationScreens[parentObject.conversationScreens.ui.options[parentObject.conversationScreens.ui.selectedIndex].value];

		parentObject.conversationScreens.ui.remove(parentObject.conversationScreens.ui.selectedIndex);
		
		//Refresh the available screens.
		parentObject.conversationEditor.conversationStringSelectionDialog.fillScreens();
	}

	this.onselect = function() {
		var parentObject = (this.parentObject != null) ? this.parentObject : this;

		var selectedScreen = parentObject.conversationScreens[parentObject.conversationScreens.ui.options[parentObject.conversationScreens.ui.selectedIndex].value];

		parentObject.conversationEditor.changeScreen(selectedScreen);
	}

	//initialize
	this.ui.setAttribute("class", "conversationScreenList");
	this.ui.setAttribute("className", "conversationScreenList");

	this.conversationScreens.ui.setAttribute("multiple", "true");
	this.conversationScreens.ui.parentObject = this;
	this.conversationScreens.ui.onchange = this.onselect;
	this.ui.appendChild(this.conversationScreens.ui);

	var element = document.createElement("div");
	this.addButton.setAttribute("type", "button");
	this.addButton.setAttribute("value", "Add Screen");
	this.addButton.parentObject = this;
	this.addButton.onclick = this.createConversationScreen;

	this.removeButton.setAttribute("type", "button");
	this.removeButton.setAttribute("value", "Remove Screen");
	this.removeButton.parentObject = this;
	this.removeButton.onclick = this.removeConversationScreen;

	element.appendChild(this.addButton);
	element.appendChild(this.removeButton);

	this.ui.appendChild(element);
	
}

function ConversationScreen(screenName, displayName) {
	this.screenName = screenName;
	this.displayName = displayName;
	this.ui = document.createElement("div");
	this.ui.parentObject = this;
	this.title = document.createElement("div");
	this.conversationScreenList = null;
	this.conversationWindow = new ConversationWindow(this);

	this.writeToScript = function(script) {
		var parentObject = (this.parentObject != null) ? this.parentObject : this;

		script += parentObject.conversationScreenList.conversationEditor.scriptName.value + "_";

		script += parentObject.screenName + " = ConvoScreen:new {\r\n";
		script += "\tid = \"" + screenName + "\",\r\n";

		script = parentObject.conversationWindow.writeToScript(script);

		return script += "}\r\n\r\n";
	}

	//initialize
	this.ui.setAttribute("class", "conversationScreen");
	this.ui.setAttribute("className", "conversationScreen");

	this.title.setAttribute("class", "title");
	this.title.setAttribute("className", "title");
	this.title.innerHTML = this.displayName;
	this.ui.appendChild(this.title);
	this.ui.appendChild(this.conversationWindow.ui);
}

function ConversationWindow(conversationScreen) {
	this.conversationScreen = conversationScreen;
	this.ui = document.createElement("div");
	this.ui.parentObject = this;
	this.ui.conversationWindow = this;
	this.leftDialog = new ConversationDialog(this);
	this.conversationOptions = new ConversationOptions(this);

	this.writeToScript = function(script) {
		var parentObject = (this.parentObject != null) ? this.parentObject : this;

		script += "\tleftDialog = \"" + parentObject.leftDialog.stringPath + "\",\r\n";

		script += "\toptions = {\r\n";

		for (var i = 0; i < parentObject.conversationOptions.options.length; ++i) {
			var option = parentObject.conversationOptions.options[i];

			if (option != null)
				script = option.writeToScript(script);
		}

		script += "\t}\r\n";

		return script;
	}

	//initialize
	this.ui.setAttribute("class", "conversationWindow");
	this.ui.setAttribute("className", "conversationWindow");
	this.ui.appendChild(this.leftDialog.ui);

	var element = document.createElement("div");
	element.setAttribute("class", "divisor");
	element.setAttribute("className", "divisor");
	this.ui.appendChild(element);

	this.ui.appendChild(this.conversationOptions.ui);
}

function ConversationDialog(conversationWindow) {
	this.conversationWindow = conversationWindow;
	this.ui = document.createElement("div");
	this.ui.parentObject = this;
	this.stringPath = "undefined";

	this.onclick = function(event) {
		var parentObject = (this.parentObject != null) ? this.parentObject : this;

		var dialog = parentObject.conversationWindow.conversationScreen.conversationScreenList.conversationEditor.conversationStringSelectionDialog;
		
		if (dialog == null)
			return;

		dialog.show(event, parentObject, false);
	}

	this.setText = function(stringId, text, link) {
		var parentObject = (this.parentObject != null) ? this.parentObject : this;

		parentObject.stringPath = stringId;

		parentObject.ui.innerHTML = text;
	}

	//initialize
	this.ui.setAttribute("class", "conversationDialog");
	this.ui.setAttribute("className", "conversationDialog");
	this.ui.innerHTML = "&lt;Click here to set caption&gt;";
	this.ui.onclick = this.onclick;
}

function ConversationOptions(conversationWindow) {
	this.conversationWindow = conversationWindow;
	this.ui = document.createElement("div");
	this.ui.parentObject = this;
	this.ui.conversationOptions = this;
	this.createButton = document.createElement("div");
	this.options = new Array();

	this.createOption = function() {
		var parentObject = (this.parentObject != null) ? this.parentObject : this;

		var idx = parentObject.options.length;

		var option = new ConversationOption("undefined", "", idx);
		option.conversationOptions = parentObject;
		parentObject.options[idx] = option;

		parentObject.ui.conversationOptions.ui.insertBefore(option.ui, parentObject.createButton);
	}

	this.removeOption = function(idx) {
		delete this.options[idx];
	}

	//initialize
	this.ui.setAttribute("class", "conversationOptions");
	this.ui.setAttribute("className", "conversationOptions");
	this.createButton.setAttribute("class", "conversationOption");
	this.createButton.setAttribute("className", "conversationOption");
	this.createButton.innerHTML = "&lt;Click here to add an option&gt;";
	this.createButton.parentObject = this;
	this.createButton.onclick = this.createOption;
	this.createButton.conversationOptions = this;
	this.ui.appendChild(this.createButton);
}

function ConversationOption(stringPath, link, idx) {
	this.ui = document.createElement("div");
	this.ui.parentObject = this;
	this.conversationOptions = null;
	this.stringPath = stringPath;
	this.link = link;
	this.index = idx;

	this.setText = function(stringId, text, link) {
		var parentObject = (this.parentObject != null) ? this.parentObject : this;

		parentObject.stringPath = stringId;
		parentObject.link = link;

		parentObject.ui.innerHTML = text;
	}

	this.onclick = function(event) {
		var parentObject = (this.parentObject != null) ? this.parentObject : this;

		var dialog = parentObject.conversationOptions.conversationWindow.conversationScreen.conversationScreenList.conversationEditor.conversationStringSelectionDialog;
		
		if (dialog == null)
			return;

		dialog.show(event, parentObject, true);
	}

	this.writeToScript = function(script) {
		var parentObject = (this.parentObject != null) ? this.parentObject : this;

		script += "\t\t{\"" + parentObject.stringPath + "\", \"" + parentObject.link + "\"},\r\n"

		return script;
	}

	//initialize
	this.ui.innerHTML = stringPath;
	this.ui.onclick = this.onclick;
}

function ConversationStringSelectionDialog(conversationEditor) {
	this.conversationEditor = conversationEditor;
	this.ui = document.createElement("div");
	this.ui.conversationStringSelectionDialog = this;
	this.fileSelect = document.createElement("select");
	this.keySelect = document.createElement("select");
	this.screenLink = document.createElement("select");
	this.stringPreview = document.createElement("div");
	this.setButton = document.createElement("input");
	this.cancelButton = document.createElement("input");
	this.removeButton = document.createElement("input");
	this.editingObject = null;

	this.fillFiles = function() {
		var parentObject = (this.parentObject != null) ? this.parentObject : this;

		for (key in stringFiles) {
			var stringFile = stringFiles[key];
			var option = document.createElement("option");
			option.text = stringFile.fileName;
			option.value = key;
			try {
				parentObject.fileSelect.add(option, null);
			} catch (ex) {
				parentObject.fileSelect.add(option);
			}
		}
			
	}

	this.fillKeys = function() {
		var parentObject = (this.parentObject != null) ? this.parentObject : this;

		while (parentObject.keySelect.options.length > 0)
			parentObject.keySelect.remove(0);

		var stringFile = stringFiles[parentObject.fileSelect.selectedIndex];

		for (entry in stringFile.entries) {
			var option = document.createElement("option");
			option.text = entry;
			option.value = entry;
			try {
				parentObject.keySelect.add(option, null);
			} catch (ex) {
				parentObject.keySelect.add(option);
			}
		}

		parentObject.setPreviewString();
	}

	this.fillScreens = function() {
		var parentObject = (this.parentObject != null) ? this.parentObject : this;

		//Remove all options.
		while (parentObject.screenLink.options.length > 0)
			parentObject.screenLink.options.remove(0);

		var option = document.createElement("option");
		option.text = "None";
		option.value = "";
		parentObject.screenLink.options.add(option);

		var screens = parentObject.conversationEditor.conversationScreenList.conversationScreens;

		for (key in screens) {
			if (key == "ui")
				continue;

			var screen = screens[key];
			option = document.createElement("option");
			option.text = screen.displayName;
			option.value = screen.screenName;
			parentObject.screenLink.options.add(option);
		}
	}

	this.setPreviewString = function() {
		var parentObject = (this.parentObject != null) ? this.parentObject : this;

		parentObject.stringPreview.innerHTML = stringFiles[parentObject.fileSelect.selectedIndex].entries[parentObject.keySelect.options[parentObject.keySelect.selectedIndex].value];
	}

	this.show = function(event, object, showRemove) {
		if (!event) { event = window.event; }

		var pos = [0,0];

		if (event.pageX || event.pageY)
			pos = [event.pageX, event.pageY];
		else
			pos = [event.clientX, event.clientY];


		var parentObject = (this.parentObject != null) ? this.parentObject : this;

		parentObject.editingObject = object;
		parentObject.ui.style.display = "block";
		parentObject.ui.style.top = pos[1];
		parentObject.ui.style.left = pos[0];

		parentObject.removeButton.style.visibility = (showRemove ? "visible" : "hidden");
	}

	this.hide = function() {
		var parentObject = (this.parentObject != null) ? this.parentObject : this;

		parentObject.ui.style.display = "none";
	}

	this.setString = function() {
		var parentObject = (this.parentObject != null) ? this.parentObject : this;

		if (parentObject.editingObject != null) {
			var selectedFile = stringFiles[parentObject.fileSelect.selectedIndex];
			var stringId = "@" + selectedFile.fileName;
			stringId += ":" + parentObject.keySelect.options[parentObject.keySelect.selectedIndex].value;
			var link = parentObject.screenLink.options[parentObject.screenLink.selectedIndex].value;
			parentObject.editingObject.setText(stringId, parentObject.stringPreview.innerHTML, link);
		}

		parentObject.hide();	
	}

	this.removeElement = function() {
		var parentObject = (this.parentObject != null) ? this.parentObject : this;

		var key = parentObject.editingObject.screenName;
		var ui = parentObject.editingObject.ui;
		
		ui.parentNode.removeChild(ui);

		parentObject.editingObject.conversationOptions.removeOption(parentObject.editingObject.index);

		parentObject.hide();
	}
	
	//initialize
	this.ui.setAttribute("class", "conversationStringSelectionDialog");
	this.ui.setAttribute("className", "conversationStringSelectionDialog");

	var element = document.createElement("div");
	var label = document.createElement("label");
	label.innerHTML = "Select a file: ";
	label.setAttribute("for", "fileSelect");
	this.fileSelect.setAttribute("id", "fileSelect");
	this.fileSelect.onchange = this.fillKeys;
	this.fileSelect.parentObject = this;
	label.appendChild(this.fileSelect);
	element.appendChild(label);
	this.ui.appendChild(element);
	this.fillFiles();

	element = document.createElement("div");
	label = document.createElement("label");
	label.innerHTML = "Select a key: ";
	label.setAttribute("for", "keySelect");
	this.keySelect.setAttribute("id", "keySelect");
	this.keySelect.onchange = this.setPreviewString;
	this.keySelect.parentObject = this;
	label.appendChild(this.keySelect);
	element.appendChild(label);
	this.ui.appendChild(element);
	this.fillKeys();

	element = document.createElement("div");
	label = document.createElement("label");
	label.innerHTML = "Select a screen to link: ";
	this.screenLink.setAttribute("id", "screenLink");
	this.screenLink.parentObject = this;
	label.appendChild(this.screenLink);
	element.appendChild(label);
	this.ui.appendChild(element);
	this.fillScreens();
	
	this.stringPreview.setAttribute("class", "conversationStringPreview");
	this.stringPreview.setAttribute("className", "conversationStringPreview");
	this.stringPreview.innerHTML = "undefined";
	this.ui.appendChild(this.stringPreview);
	this.setPreviewString();

	//initialize buttons
	element = document.createElement("div");
	this.setButton.setAttribute("type", "button");
	this.setButton.setAttribute("value", "Set");	
	this.setButton.parentObject = this;
	this.setButton.onclick = this.setString;

	this.cancelButton.setAttribute("type", "button");
	this.cancelButton.setAttribute("value", "Cancel");
	this.cancelButton.parentObject = this;
	this.cancelButton.onclick = this.hide;

	this.removeButton.setAttribute("type", "button");
	this.removeButton.setAttribute("value", "Remove");
	this.removeButton.parentObject = this;
	this.removeButton.onclick = this.removeElement;

	element.appendChild(this.setButton);
	element.appendChild(this.cancelButton);
	element.appendChild(this.removeButton);

	this.ui.appendChild(element);
}
