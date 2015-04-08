#include <QApplication> //For Qt5
#include <QMainWindow>
#include <QWindow> //For Qt5
#include <QWidget> //For Qt5
#include <QLabel>
#include <QDebug> // only needed for debug
#include <QString>
#include <QPoint>
#include <QVector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#ifdef LINUX
#include <unistd.h>
#endif
#ifdef WINDOWS
#include <windows.h>
#endif

#include "ConfigParser.h"
#include "MazeManager.h"
#include "utils.h"

int main(int argc, char *argv[])
{
	/* definitions */
	bool vertical = false;

	/* load settings */
	ConfigParser* config = new ConfigParser("config.ini");
	std::string str_character_set = config->getVariable("characters", "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	std::string str_wordlist_path = config->getVariable("wordlist", "wordlist.txt");
	int MAZE_HEIGHT = config->getVariable("maze_height", 20);	
	int MAZE_WIDTH = config->getVariable("maze_width", 20);			
	int TILE_HEIGHT = config->getVariable("tile_height", 22);	
	int TILE_WIDTH = config->getVariable("tile_width", 22);	

	/* load wordlist */
	std::vector<std::string> wordList = loadWordList(str_wordlist_path.c_str());

	srand (time(NULL));

    QApplication app(argc, argv);
    QMainWindow mainWindow;

	MazeManager* pMaze = new MazeManager(MAZE_WIDTH, MAZE_HEIGHT, TILE_WIDTH, TILE_HEIGHT); // TODO: Clean memory

	mainWindow.resize((MAZE_WIDTH+1)*TILE_WIDTH, (MAZE_HEIGHT+1)*TILE_HEIGHT);
	mainWindow.show();
		
    // draw the words
    QRect box = QRect(0,0,0,0);

	for (std::vector<std::string>::iterator it = wordList.begin() ; it != wordList.end(); ++it) {
		vertical = (rand() %2);

		std::string str = *it;		

		int characters = getUTF8StringLength(str); // str.length()

		QVector<QPoint> vEmptyTiles = pMaze->getEmptyTiles(&mainWindow, characters, vertical);
		if(vEmptyTiles.length()==0) {
			vEmptyTiles = pMaze->getEmptyTiles(&mainWindow, characters, !vertical);

			if(vEmptyTiles.length()==0) {
				continue;  //qDebug() << "SKIPPED" << QString::fromStdString(str);	
			}
		}

		// Now get a random position from the list of available spots
		QPoint pos = vEmptyTiles[rand() %vEmptyTiles.length()];

		unsigned int nextCharacter = 0;
		for (unsigned int i=0;i<str.length();i++) {

			if(nextCharacter>=str.length())
				break;

			if(vertical)
				box = QRect(pos.x()*TILE_WIDTH,(pos.y()*TILE_HEIGHT)+(i*TILE_HEIGHT),TILE_HEIGHT,TILE_WIDTH);
			else
				box = QRect((pos.x()*TILE_WIDTH)+(i*TILE_WIDTH), pos.y()*TILE_HEIGHT,TILE_HEIGHT,TILE_WIDTH);
			
			// Get number of BYTE's required for the current character to preserve encoding
			int sizeRequired = getMultiCharacterByteSize(&str.c_str()[nextCharacter]);

    		QLabel *word = new QLabel(QString::fromStdString(str.substr(nextCharacter,sizeRequired)), &mainWindow);

			nextCharacter+=	sizeRequired;

			if(vertical)
				word->setGeometry(box);
			else
				word->setGeometry(box);

			word->setStyleSheet("border: 2px solid");
			word->setAlignment(Qt::AlignCenter);
			word->show();
			mainWindow.update();
		}

	}
	
	// now fill the blanks
	for(int y=0;y<=MAZE_HEIGHT;y++) {
		for(int x=0;x<=MAZE_WIDTH;x++) {
			if(pMaze->isTileEmpty(&mainWindow, x,y)) {
				QLabel *word = new QLabel(QString::fromStdString(getRandomCharacter(str_character_set)), &mainWindow);
				word->setGeometry(x*TILE_WIDTH, y*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
				word->setStyleSheet("border: 1px solid");
				word->setAlignment(Qt::AlignCenter);
				word->show();
			}
		}
	}
	
	mainWindow.update();

	if(config)
		delete config;

	if(pMaze)
		delete pMaze;
	
    return app.exec();
}