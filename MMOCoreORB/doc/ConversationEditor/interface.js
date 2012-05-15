function setString(stringChooserId, fileSelectId, keySelectId) {
	var stringChooser = document.getElementById(stringChooserId);
	var fileSelect = document.getElementById(fileSelectId);
	var keySelect = document.getElementById(keySelectId);

	if (stringChooser == null || fileSelect == null || keySelect == null)
		return;

	var editingElement = stringChooser.editingElement;

	if (editingElement == null)
		return;

	var selectedEntry = stringFiles[fileSelect.selectedIndex].entries[keySelect.options[keySelect.selectedIndex].value];

	if (selectedEntry == null || selectedEntry == "undefined")
		return alert("String entry could not be found.");

	editingElement.innerHTML = selectedEntry;

	stringChooser.style.display = "none";
}

function fillFiles(elementId, keyElementId) {
	var element = document.getElementById(elementId);

	if (element == null)
		return;

	for (var i = 0; i < stringFiles.length; ++i) {
		var stringFile = stringFiles[i];
		var option = document.createElement("option");
		option.text = stringFile.fileName;
		option.value = i;
		element.add(option);
	}

	fillKeys(element, keyElementId);
}

function fillKeys(fileSelect, elementId) {
	if (fileSelect == null)
		return;

	var element = document.getElementById(elementId);

	if (element == null)
		return;

	//Remove all elements
	while (element.options.length > 0)
		element.remove(0);

	var selectedFileIndex = fileSelect.options[fileSelect.selectedIndex].value;

	var stringFile = stringFiles[selectedFileIndex];

	for (entry in stringFile.entries) {
		var option = document.createElement("option");
		option.text = entry;
		option.value = entry;
		element.add(option);
	}

	//TODO: Fix
	var stringPreview = document.getElementById("stringPreview");
	stringPreview.innerHTML = stringFile.entries[element.options[element.selectedIndex].value];
}

function showStringChooser(editingElement, elementId, isOption) {
	var element = document.getElementById(elementId);

	if (element == null)
		return alert("Could not find element with id: " + elementId);

	element.editingElement = editingElement;

	//TODO: Fix
	var removeButton = document.getElementById("removeButton");

	if (removeButton != null)
		removeButton.style.visibility = (isOption ? "visible" : "hidden");

	//TODO: Add in the link form.

	element.style.display = "block";
}	

function setStringPreview(fileSelectId, stringPreviewId, keySelect) {
	var stringPreview = document.getElementById(stringPreviewId);
	var fileSelect = document.getElementById(fileSelectId);

	if (stringPreview == null || fileSelect == null)
		return;

	stringPreview.innerHTML = stringFiles[fileSelect.selectedIndex].entries[keySelect.options[keySelect.selectedIndex].value];
}

function hideStringChooser(stringChooserId) {
	var stringChooser = document.getElementById(stringChooserId);

	if (stringChooser == null)
		return;

	stringChooser.style.display = "none";
}

function addOption(optionCreate, stringChooserId, parentElementId) {
	var parentElement = document.getElementById(parentElementId);

	if (parentElement == null)
		return;

	var option = document.createElement("div");
	option.innerHTML = "undefined";

	option.onclick = function() {
		showStringChooser(this, stringChooserId, true);
	}

	showStringChooser(option, stringChooserId, true);

	parentElement.insertBefore(option, optionCreate);
}


function updateConversationScreen(screenName, elementId) {
	var convoScreen = conversationScreens[screenName];

	if (convoScreen == null)
		return alert("Conversation screen '" + screenName + "' does not exist.");

	
}


function findPos(obj) {
	var curLeft = curTop = 0;

	if (obj.offsetParent) {
		do {
			curLeft += obj.offsetLeft;
			curTop += obj.offsetTop;
		} while (obj = obj.offsetParent);

	}

	return [curTop, curLeft];
}
