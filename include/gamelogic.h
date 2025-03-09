#ifndef GAMELOG_H
#define GAMELOG_H

#include "../include/header.h"

#define TYPE_EMPTY           0
#define TYPE_BOMB            1
#define TYPE_EMPTY_NEAR_BOMB 2 

#define STATUS_OPEN          3
#define STATUS_MARK          4
#define STATUS_NORM          6

#define SIZE_BLOCK    43
#define OVER_BLOCKS   60
#define HEIGHT_BLOCKS 10
#define WIDTH_BLOCKS  6
#define TOTAL_BOMBS   12

#define INDENT_BLOCKS_X         11
#define INDENT_BLOCKS_Y         115

#define NEAR_BLOCKS  8

#define ERROR_ALLOC_MATRX  "Failed allocated memory for matrix!"

#define CHANGE_ONE_BLOCK  0
#define CHANGE_MANY_BLOCK 1
#define NOTHING_CHANGE    2
#define GAME_RESTART      3

#define TOTAL_NEAR_BLOCKS 8


struct PLAYFBLOCK			  
{
  INT8 type;
  INT8 status;
  INT8 count_bomb_near;
  BOOL highlight;
  RECT pos_block;

}; 
typedef struct PLAYFBLOCK PLAYFBLOCK;

extern PLAYFBLOCK** GameBlocksInitialization(void);

extern INT8 GameHandleGameBlocks(INT8 down_mouse_btn, INT8 iter_height, INT8 iter_width);

extern INT8 GameGetNumbersOfFlags(void);

extern BOOL GamePlayerIsLooser(void);

static void GameBombGeneration(void);

static POINT* RecalculateCurrentNearBlocks(INT8 iter_height, INT8 iter_width, POINT blocks[]);

static INT8 AllocateMatrix(void);

static void FreehighlightArray(void);

extern void FreeAlocatedMatrix(PLAYFBLOCK** matrix);

static void GenerateBombs(void);

static int GetCountNearBomb(INT8 iter_height, INT8 iter_width);

extern BOOL GetYouWinerFlag(void);

static void UpdateGame(void);

static void ParseEmptyBlocks(INT8 iter_height_start, INT8 iter_width_start);

#endif
