#include <QMessageBox>

int getMultiCharacterByteSize(const char * mbchar) {
	wchar_t dest;
  	mbtowc (NULL, NULL, 0);  // reset mbtowc
    return mbtowc(&dest,mbchar,4);
}

int getUTF8StringLength(std::string s) {

	int characters = 0;
	int sizeRequired = 1;

	for (unsigned int i=0;i<s.length();i+=sizeRequired) {
		sizeRequired = getMultiCharacterByteSize(&s.c_str()[i]);
		characters+=1;
	}

	return characters;
}

std::string getRandomCharacter(std::string character_set) {

	// TODO: Split into array to skip the -1 check...

	int sizeRequired = -1;
	int nextCharacter = 0;
	while(sizeRequired == -1) {
		nextCharacter = rand() %character_set.length();
		sizeRequired = getMultiCharacterByteSize(&character_set.c_str()[nextCharacter]);
	}

	return character_set.substr(nextCharacter, sizeRequired);
}

void err(const char * pMessage) {
	QMessageBox Msgbox;
    Msgbox.setText(pMessage);
    Msgbox.exec();
}

std::vector<std::string> loadWordList(const char* path) {

	std::vector<std::string> wordList;

	std::string line;
	std::ifstream myfile (path);
	if (myfile.is_open()) {
		while ( getline (myfile,line) ) {
	      wordList.push_back( line );
	    }
	    myfile.close();
	  }

	  return wordList;
}