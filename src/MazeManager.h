#include <QWidget>
#include <QPoint>
#include <QRect>
#include <QVector>

class MazeManager {

public:
	MazeManager(int maze_width, int maze_height, int tile_width, int tile_height);
	~MazeManager();

	QVector<QPoint> getEmptyTiles(QWidget* mainWindow, int length, bool vertical);
	bool isTileEmpty(QWidget* mainWindow, int x, int y, int length=1, bool horizontal=true);

private:
	int m_iTileWidth;
	int m_iTileHeight;
	int m_iMazeWidth;
	int m_iMazeHeight;	
};