#ifndef GAMELOG_H
#define GAMELOG_H

#include "../include/header.h"

#define TYPE_EMPTY           0
#define TYPE_BOMB            1

#define STATUS_OPEN          3
#define STATUS_MARK          4
#define STATUS_NORM          6

#define SIZE_BLOCK    43

#define HEIGHT_BLOCKS 10
#define WIDTH_BLOCKS  6
#define TOTAL_BOMBS   12

#define INDENT_BLOCKS_X         11
#define INDENT_BLOCKS_Y         115

#define ERROR_ALLOC_MATRX  "Failed allocated memory for matrix!"

#define CHANGE_MANY_BLOCK 1

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

extern INT8 GameHandleGameBlocks(INT8 down_mouse_btn, INT8 iter_height, INT8 iter_width, RECT array_redraw_objects[]);

extern INT8 GameGetNumbersOfFlags(void);

extern BOOL GamePlayerIsLooser(void);
extern BOOL GamePlayerIsWiner(void);

static void GenerateBombs(void);

static POINT* RecalculateCurrentNearBlocks(INT8 iter_height, INT8 iter_width, POINT blocks[]);

static INT8 AllocateMatrix(void);

extern void FreeAlocatedMatrix(PLAYFBLOCK** matrix);

static void GenerateBombs(void);

static int GetCountNearBomb(INT8 iter_height, INT8 iter_width);

static void UpdateGame(void);


#endif
