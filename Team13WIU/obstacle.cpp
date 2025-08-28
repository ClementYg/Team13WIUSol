#include "obstacle.h"
obstacle::obstacle(int x, int y) {
	pos.x = x;
	pos.y = y;
	symbol = '#';
	IsActive = true;
}
void obstacle::move(int xchange, int ychange)
{
	pos.x += xchange;
	pos.y += ychange;
}
;
//void obstacle::move(Entity* player, int thing)
//{
//	if (pos.x == player->getX() && pos.y == player->getY())
//	{
//		pos.x = player->getX()-playerOldX
//	}
//	playerOldX = player->getX();
//	playerOldY = player->getY();
//}
void obstacle::move(Entity* gameObjects[], int entityCount) {
	// Not used in this implementation
}