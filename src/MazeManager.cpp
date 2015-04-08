#include "MazeManager.h"

MazeManager::MazeManager(int maze_width, int maze_height, int tile_width, int tile_height) {
	m_iMazeWidth	= maze_width;
	m_iMazeHeight 	= maze_height;		
	m_iTileWidth	= tile_width;
	m_iTileHeight 	= tile_height;
}

MazeManager::~MazeManager() {

}

QVector<QPoint> MazeManager::getEmptyTiles(QWidget* mainWindow, int length, bool vertical) {

	QVector<QPoint> vEmptyTiles;
	bool bFound=false;
	if(!vertical) {

		for(int y=1;y<m_iMazeHeight;y++) {
			for(int x=0;x<m_iMazeWidth-length;x++) {
				for(int i=0;i<length;i++) {
					bFound = isTileEmpty(mainWindow, x+i, y, 1, true);					
					if(!bFound) {
						break;
					}
				}

				if(bFound) {
					vEmptyTiles.push_back( QPoint(x,y) );
				}

			}
		}		

		return vEmptyTiles;
	}

	for(int x=1;x<m_iMazeWidth;x++) {
		for(int y=0;y<m_iMazeHeight-length;y++) {
			for(int i=0;i<length;i++) {
				bFound = isTileEmpty(mainWindow, x, y+i, 1, false);	
				if(!bFound) {
					break;
				}
			}

			if(bFound) {
				vEmptyTiles.push_back( QPoint(x,y) );
			}
		}
	}
	

	return vEmptyTiles;
}

bool MazeManager::isTileEmpty(QWidget* mainWindow, int x, int y, int length, bool horizontal) {
	QRect pos = QRect(x*m_iTileWidth, y*m_iTileHeight, m_iTileWidth, m_iTileHeight);

	return !mainWindow->childrenRegion().contains(pos);
}