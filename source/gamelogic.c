#include "../include/gamelogic.h"



static INT8         flags         = TOTAL_BOMBS;
static PLAYFBLOCK** playfblocks   = NULL;
static BOOL         FlagYouLooser = FALSE;
static BOOL         FlagYouWiner  = FALSE;
static POINT        CurrentNearBlocks[TOTAL_NEAR_BLOCKS] = {0};
static POINT        BombPos[TOTAL_BOMBS]                 = {0};


extern PLAYFBLOCK** GameBlocksInitialization()
{   
	
	if(AllocateMatrix() == 1)
		GetMessageErrorAndExit(ERROR_ALLOC_MATRX);

	flags = TOTAL_BOMBS;
	FlagYouLooser  = FALSE;
	
	for(size_t i = 0; i < HEIGHT_BLOCKS; i++){
		for(size_t f = 0; f < WIDTH_BLOCKS; f++){
			PLAYFBLOCK block;
			block.pos_block.left   = f * SIZE_BLOCK + 1;
			block.pos_block.top    = i * SIZE_BLOCK + 1;
			block.pos_block.right  = (f * SIZE_BLOCK) + SIZE_BLOCK;
			block.pos_block.bottom = (i * SIZE_BLOCK) + SIZE_BLOCK;

			block.pos_block.left   += INDENT_BLOCKS_X;
			block.pos_block.top    += INDENT_BLOCKS_Y;
			block.pos_block.right  += INDENT_BLOCKS_X;
			block.pos_block.bottom += INDENT_BLOCKS_Y;


			block.status = STATUS_NORM;
			block.type = TYPE_EMPTY;
			block.highlight = FALSE;
			block.count_bomb_near = -1;

			playfblocks[i][f] = block;

		}
	}
	
	GenerateBombs();

	return playfblocks;
}


extern INT8 GameHandleGameBlocks(INT8 down_mouse_btn, INT8 iter_height, INT8 iter_width)
{
	PLAYFBLOCK *block = &playfblocks[iter_height][iter_width];

	if(MOUSE_R_BTN == down_mouse_btn){
		if(flags > 0 && block->status == STATUS_NORM){
			block->status = STATUS_MARK;
			flags --;
			CheckWin();
			return CHANGE_ONE_BLOCK;
		}
	}

		if(MOUSE_L_BTN  == down_mouse_btn){
			if(block->status == STATUS_OPEN){
				FreehighlightArray();
				RecalculateCurrentNearBlocks(iter_height, iter_width);
				for(size_t i = 0; i < TOTAL_NEAR_BLOCKS; i++){
					if(CurrentNearBlocks[i].x >= 0)
						playfblocks[CurrentNearBlocks[i].x][CurrentNearBlocks[i].y].highlight = TRUE;
				}

				return CHANGE_MANY_BLOCK;
			}

			if(block->status == STATUS_NORM){
				if(block->type != TYPE_BOMB){
					block->status = STATUS_OPEN;
					block->count_bomb_near = GetCountNearBomb(iter_height, iter_width);
					return CHANGE_ONE_BLOCK;
				}
				else{
					FlagYouLooser = TRUE;
					return CHANGE_MANY_BLOCK;
				}
			}


			if(block->status == STATUS_MARK){
				block->status = STATUS_NORM;
				flags ++;
			}

		
		}

		if(MOUSE_L_BTN_UP){
			FreehighlightArray();

			return CHANGE_MANY_BLOCK;
		}
	


	return NOTHING_CHANGE;
}


extern INT8 GameGetNumbersOfFlags(void)
{
    return flags;
}


extern BOOL GamePlayerIsLooser(void)
{
	return FlagYouLooser;
}



static void RecalculateCurrentNearBlocks(INT8 iter_height, INT8 iter_width)
{
	POINT operation[TOTAL_NEAR_BLOCKS];
	operation[0].x = -1, operation[0].y = 0;  operation[1].x = -1, operation[1].y = 1; 
	operation[3].x = 1, operation[3].y = 1; operation[4].x = -1, operation[4].y = -1; 
	operation[6].x = 0, operation[6].y = -1;   operation[7].x = 1, operation[7].y = -1; 
    operation[2].x = 0, operation[2].y = 1;   operation[5].x = 1, operation[5].y = 0;

	for(size_t i = 0; i < TOTAL_NEAR_BLOCKS; i++){
		INT8 offset_x = (iter_height + operation[i].x), offset_y = (iter_width + operation[i].y);
		if(offset_x > HEIGHT_BLOCKS-1 || offset_x < -1 || offset_y > WIDTH_BLOCKS-1 || offset_y < -1){
			CurrentNearBlocks[i].x = -1;
			continue;
		}

		CurrentNearBlocks[i].x = offset_x; CurrentNearBlocks[i].y = offset_y;
	}
	
} 


static INT8 AllocateMatrix(void)
{
	playfblocks = (PLAYFBLOCK**)calloc(HEIGHT_BLOCKS, sizeof(PLAYFBLOCK*) * HEIGHT_BLOCKS);
	if(NULL == playfblocks)
		return 1;

	for (size_t i = 0; i < HEIGHT_BLOCKS; i++){
		playfblocks[i] = (PLAYFBLOCK*)calloc(WIDTH_BLOCKS, sizeof(PLAYFBLOCK) * WIDTH_BLOCKS);
		if(NULL == playfblocks[i])
			return 1;
	}

	return 0;
}


static void FreehighlightArray(void)
{
	for(size_t i = 0; i < TOTAL_NEAR_BLOCKS; i++){
		if(CurrentNearBlocks[i].x >= 0)
			playfblocks[CurrentNearBlocks[i].x][CurrentNearBlocks[i].y].highlight = FALSE;
		CurrentNearBlocks[i].x = 0; CurrentNearBlocks[i].y = 0;
	}
}


extern void FreeAlocatedMatrix(PLAYFBLOCK** matrix)
{
 	for(size_t i = 0; i < HEIGHT_BLOCKS; i++)
 		free(playfblocks[i]);
	
 	free(playfblocks);
 }


 static void GenerateBombs(void)
 {	
	srand(time(0));
	INT8 h, w;
	for (size_t i = 0; i < TOTAL_BOMBS; i++){
		h = rand() % (HEIGHT_BLOCKS - 0) + 0;
		w = rand() % (WIDTH_BLOCKS - 0) + 0;
		BombPos[i].x = h; BombPos[i].y = w;

		for(int j = i-1; j > -1; j--){
			if(BombPos[j].x == h && BombPos[j].y == w){
				i--;
				continue;
			}
		}

		playfblocks[h][w].type = TYPE_BOMB;
	}
	
 }

 static int GetCountNearBomb(INT8 iter_height, INT8 iter_width)
 {
	INT8 count = 0;
	RecalculateCurrentNearBlocks(iter_height, iter_width);
	for (size_t i = 0; i < TOTAL_NEAR_BLOCKS; i++)
	{
		if(CurrentNearBlocks[i].x >= 0)
			if(playfblocks[CurrentNearBlocks[i].x][CurrentNearBlocks[i].y].type == TYPE_BOMB)
				count ++;
	}
	
	for(size_t i = 0; i < TOTAL_NEAR_BLOCKS; i++){
		CurrentNearBlocks[i].x = 0; CurrentNearBlocks[i].y = 0;
	}
	return count;
 }


 void CheckWin()
 {
	for (size_t i = 0; i < TOTAL_BOMBS; i++)
	{	
		if(playfblocks[BombPos[i].x][BombPos[i].y].status != STATUS_MARK)
			return;
	}
	
	FlagYouWiner = TRUE;
	GetMsg("YOU WIN!!!");
 }

 extern BOOL GetYouWinerFlag(void)
 {
	return FlagYouWiner;
 }