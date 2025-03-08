#ifndef GAMELOG_H
#define GAMELOG_H

#include "../include/header.h"

#define TYPE_EMPTY           0
#define TYPE_BOMB            1
#define TYPE_EMPTY_NEAR_BOMB 2 

#define STATUS_OPEN          3
#define STATUS_MARK          4
#define STATUS_BANG          5
#define STATUS_NORM          6

#define SIZE_BLOCK    43
#define OVER_BLOCKS   60
#define HEIGHT_BLOCKS 10
#define WIDTH_BLOCKS  6
#define COUNT_BOMB    12

#define INDENT_BLOCKS_X         11
#define INDENT_BLOCKS_Y         115

#define ERROR_ALLOC_MATRX  "Failed allocated memory for matrix!"


struct PLAYFBLOCK			  
{
  INT8 type;
  INT8 status;
  INT8 bomb_near;
  BOOL highlight;
  RECT pos_block;

}; 
typedef struct PLAYFBLOCK PLAYFBLOCK;

extern PLAYFBLOCK** GameBlocksInitialization(void);

extern void GameHandleGameBlocks(INT8 down_mouse_btn, INT8 iter_height, INT8 iter_width);

extern INT8 GameGetNumbersOfFlags(void);

extern BOOL GamePlayerIsLooser(void);

static void GameBombGeneration(void);

static void HighlightNearBlocks(PLAYFBLOCK* block);

static int AllocateMatrix(void);

extern void FreeAlocatedMatrix(PLAYFBLOCK** matrix);


#endif
