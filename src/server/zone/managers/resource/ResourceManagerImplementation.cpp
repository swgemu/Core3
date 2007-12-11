/*
 *	ResourceManagerImplementationStub
 */

#include "../../ZoneServer.h"

#include "ResourceManager.h"
#include "ResourceManagerImplementation.h"

ResourceManagerImplementation::ResourceManagerImplementation(ZoneServer* server) :
	ResourceManagerServant(), Mutex("ResourceMananger") {
}

void ResourceManagerImplementation::shiftOutResources() {
}

void ResourceManagerImplementation::shiftInResources() {
}

void ResourceManagerImplementation::makeResourceName(string& resname, bool isOrganic) {
	cout << "Making name" << endl;

	nameLength = 4 + System::random(5);

	char name[nameLength];
	int x = 0;

	if (System::random(2) == 1 && nameLength > 5) {
		x = addPrefix(name);
	} else {
		name[0] = chooseNextLetter(' ', ' ');
		name[1] = chooseNextLetter(name[0], ' ');

		x = 2;
	}

	for (; x < nameLength + 1; x++) {
		if (x < nameLength) {
			//cout << "Name Progress = " << name << endl;
			name[x] = chooseNextLetter(name[x-1], name[x-2]);
		} else {
			if (System::random(1) == 1 && !isOrganic && !isVowel(name[x-1])	&& name[x-1] != 'q')
				addSuffix(name, x);
			else
				name[x] = '\0';

			break;
		}
	}

	name[0] = toupper(name[0]);

	resname = name;
}

char ResourceManagerImplementation::chooseNextLetter(const char lastLetter,	const char letterBeforeLast) {
	//int nextLetter;

	cout << "Last Letter = " << lastLetter << "  is vowel = "
			<< isVowel(lastLetter) << endl;
	//cout << "Letter before Last = " << letterBeforeLast << "  is vowel = " << isVowel(letterBeforeLast) << endl;

	if (letterBeforeLast == ' ' && lastLetter == ' ')
		return 97 + System::random(25);

	if ((!isVowel(lastLetter) && !isVowel(letterBeforeLast) && letterBeforeLast
			!= ' ') || (lastLetter == 'u' && letterBeforeLast == 'q')) {
		char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'u', 
				'v', 'w', 'x', 'y', 'z', '\0' };

		return chooseLetterExcluding(exclusion);
	}

	if ((isVowel(lastLetter) && isVowel(letterBeforeLast) && letterBeforeLast != ' ')) {
		char exclusion[] = { 'a', 'e', 'i', 'o', 'u', 'y', '\0' };

		return chooseLetterExcluding(exclusion);
	} else {
		switch (lastLetter) {
		case 'a': 
		{
			char exclusion[] = { 'a', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'b': 
		{
			char exclusion[] = { 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'j', 'k',
					'm', 'n', 'p', 'q', 's', 't', 'v', 'w', 'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'c': 
		{
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'j', 'k', 'm', 'n',
					'p', 'q', 's', 't', 'v', 'w', 'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'd': 
		{
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'm',
					'n', 'p', 'q', 's', 't', 'v', 'x', 'y', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'f': 
		{
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'm',
					'n', 'p', 'q', 's', 't', 'v', 'w', 'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'g':
		{
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'j', 'k', 'm', 'n',
					'p', 'q', 's', 't', 'v', 'w', 'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'h':
		{
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 
					's', 't', 'v', 'w',	'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'i':
		{
			char exclusion[] = { 'i', 'j', 'u', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'j':
		{
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 
					's', 't', 'v', 'w', 'x', 'y', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'k':
		{
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'm',
					'n', 'p', 'q', 's', 't', 'v', 'w', 'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'l':
		{
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 
					's', 't', 'v', 'w',	'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'm':
		{
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 
					's', 't', 'v', 'w', 'x', 'y', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'n':
		{
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 
					's', 't', 'v', 'w', 'x', 'y', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'p':
		{
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'j', 'k', 'm', 'n', 'p', 'q', 's', 't', 'v', 
					'w', 'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'q':
			return 'u';
		case 'r':
		{
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 
					's', 't', 'v', 'w',	'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 's':
		{
			char exclusion[] = { 'b', 'd', 'f', 'g', 'j', 'v', 'x', 'y', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 't':
		{
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'j', 'k', 'l', 'm',
					'n', 'p', 'q', 't', 'v', 'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'u':
		{
			char exclusion[] = { 'a', 'b', 'd', 'e', 'h', 'i', 'm', 'o', 'r',
					'u', 'v', 'x', 'y', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'v':
		{
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 
					's', 't', 'v', 'w',	'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'w':
		{
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'j', 'k', 'l', 'm',
					'n', 'p', 'q', 's', 't', 'v', 'w', 'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'x':
		{
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 
					's', 't', 'v', 'w',	'x', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'y':
		{
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 
					's', 't', 'v', 'w', 'x', 'y', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		case 'z':
		{
			char exclusion[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 
					's', 't', 'v', 'w', 'x', 'y', 'z', '\0' };
			return chooseLetterExcluding(exclusion);
		}
		default:
			return 97 + System::random(25);
		}
	}
}

bool ResourceManagerImplementation::isVowel(const char inChar) {
	if (inChar == 'a' || inChar == 'e' || inChar == 'i' || inChar == 'o' || inChar == 'u')
		return true;
	else
		return false;
}

char ResourceManagerImplementation::chooseLetterExcluding(const char exclude[]) {
	char x = 97 + System::random(25);

	//cout << "Exclude = " << exclude << endl;
	
	for (int i = 0; i < 25; i++) {
		//if (std::char_traits<char>::compare(&x, &exclude[x], 1) != 0 ){
		
		if (x == exclude[i]) {
			//cout <<"Can't be: " << exclude[i] << endl;
			x = 97 + System::random(25);
			
			i = -1;
		}
	}
	
	//cout << "Can be = " << x  << endl << "**************************************" << endl;
	
	return x;
}

int ResourceManagerImplementation::addPrefix(char* name) {
	int x = 1 + System::random(4);
	
	switch (x) {
	case 1:
		name[0] = 'c';
		name[1] = 'a';
		name[2] = 'r';
		name[3] = 'b';
		return 4;
	case 2:
		name[0] = 'd';
		name[1] = 'u';
		name[2] = 'r';
		return 3;
	case 3:
		name[0] = 'o';
		name[1] = 'm';
		name[2] = 'n';
		name[3] = 'i';
		return 4;
	case 4:
		name[0] = 'q';
		name[1] = 'u';
		name[2] = 'a';
		name[3] = 'd';
		return 4;
	case 5:
		name[0] = 't';
		name[1] = 'r';
		name[2] = 'i';
		return 3;
	default:
		return 0;
	}
}

void ResourceManagerImplementation::addSuffix(char* name, int location) {
	int x = 1 + System::random(7);
	
	switch (x) {
	case 1:
		name[location] = 'i';
		name[location+1] = 'u';
		name[location+2] = 'm';
		name[location+3] = '\0';
		break;
	case 2:
		name[location] = 'i';
		name[location+1] = 'a';
		name[location+2] = 'n';
		name[location+3] = '\0';
		break;
	case 3:
		name[location] = 'i';
		name[location+1] = 's';
		name[location+2] = 'm';
		name[location+3] = '\0';
		break;
	case 4:
		name[location] = 'i';
		name[location+1] = 't';
		name[location+2] = 'e';
		name[location+3] = '\0';
		break;
	case 5:
		name[location] = 's';
		name[location+1] = 'i';
		name[location+2] = 's';
		name[location+3] = '\0';
		break;
	case 6:
		name[location] = 'i';
		name[location+1] = 'n';
		name[location+2] = 'e';
		name[location+3] = '\0';
		break;
	case 7:
		name[location] = 'i';
		name[location+1] = 'c';
		name[location+2] = '\0';
		break;
	case 8:
		name[location] = 'i';
		name[location+1] = 'd';
		name[location+2] = 'e';
		name[location+3] = '\0';
		break;
	default:
		break;
	}
}

string ResourceManagerImplementation::stringify(const int x) {
	ostringstream o;

	if (!(o << x))
		return "";
	else
		return o.str();
}

