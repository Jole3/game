#pragma once
#include "box.h"

bool getUserInfo(useInfo &user);

bool getLevelInfo(levelInfo &level, int level_id);

bool loadLevel(levelInfo &level,int map[MAP_LINE][MAP_COLUMN]);

bool updateUserLevel(int nextLevel, useInfo &user);