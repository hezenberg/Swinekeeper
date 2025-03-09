#include "../include/gamelogic.h"

static INT8         flags         = TOTAL_BOMBS;
static PLAYFBLOCK** playfblocks   = NULL;
static BOOL         FlagYouLooser = FALSE;
static BOOL         FlagYouWiner  = FALSE;
static RECT       BufferDeleteHigl[TOTAL_NEAR_BLOCKS];
static BOOL       BufferIsEmpty = TRUE;
extern PLAYFBLOCK** GameBlocksInitialization()
{   
	
	if(AllocateMatrix() == 1)
		GetMessageErrorAndExit(ERROR_ALLOC_MATRX);

	flags = TOTAL_BOMBS;
	FlagYouLooser  = FALSE;
	PLAYFBLOCK block;
	for(size_t i = 0; i < HEIGHT_BLOCKS; i++){
		for(size_t f = 0; f < WIDTH_BLOCKS; f++){
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



extern INT8 GameHandleGameBlocks(INT8 down_mouse_btn, INT8 iter_height, INT8 iter_width, RECT redraw_objects[])
{	
	PLAYFBLOCK *block = &playfblocks[iter_height][iter_width];
	INT8 iterator_redraw_obj = 0;

	if(MOUSE_R_BTN == down_mouse_btn){
		if(flags > 0 && block->status == STATUS_NORM){
			block->status = STATUS_MARK;
			flags --;
			redraw_objects[iterator_redraw_obj] = block->pos_block;
			return iterator_redraw_obj;
		}
	}

		if(MOUSE_L_BTN  == down_mouse_btn){
			if(block->status == STATUS_OPEN){

				POINT CurrentNearBlocks[TOTAL_NEAR_BLOCKS];
				RecalculateCurrentNearBlocks(iter_height, iter_width, CurrentNearBlocks);
				for(size_t i = 0; i < TOTAL_NEAR_BLOCKS; i++){
					if(CurrentNearBlocks[i].x >= 0){
						playfblocks[CurrentNearBlocks[i].x][CurrentNearBlocks[i].y].highlight = TRUE;
						redraw_objects[iterator_redraw_obj] = playfblocks[CurrentNearBlocks[i].x][CurrentNearBlocks[i].y].pos_block;
						iterator_redraw_obj++;
					}
				}

				memcpy(BufferDeleteHigl, redraw_objects, sizeof(RECT) * iterator_redraw_obj);
				BufferIsEmpty = FALSE;
				return iterator_redraw_obj;
			}

			if(block->status == STATUS_NORM){
				if(block->type != TYPE_BOMB){
					block->status = STATUS_OPEN;
					redraw_objects[iterator_redraw_obj] = block->pos_block;
					iterator_redraw_obj++;
					block->count_bomb_near = GetCountNearBomb(iter_height, iter_width);
					if(block->count_bomb_near == 0){
						POINT CurrentNearBlocks[TOTAL_NEAR_BLOCKS];
    					RecalculateCurrentNearBlocks(iter_height, iter_width, CurrentNearBlocks);
						for (size_t i = 0; i < TOTAL_NEAR_BLOCKS; i++)
						{	
							if(CurrentNearBlocks[i].x > -1){
								if(playfblocks[CurrentNearBlocks[i].x][CurrentNearBlocks[i].y].type != TYPE_BOMB){
									redraw_objects[iterator_redraw_obj] = playfblocks[CurrentNearBlocks[i].x][CurrentNearBlocks[i].y].pos_block;
									iterator_redraw_obj++;
									playfblocks[CurrentNearBlocks[i].x][CurrentNearBlocks[i].y].status = STATUS_OPEN;
									playfblocks[CurrentNearBlocks[i].x][CurrentNearBlocks[i].y].count_bomb_near = GetCountNearBomb(CurrentNearBlocks[i].x, CurrentNearBlocks[i].y);
								}
							}
						}
					}
		
					return iterator_redraw_obj;
				}
				else{
					FlagYouLooser = TRUE;
					return GAME_RESTART;
				}
			}


			if(block->status == STATUS_MARK){
				block->status = STATUS_NORM;
				flags ++;
				redraw_objects[iterator_redraw_obj] = block->pos_block;
				return iterator_redraw_obj;
			}

		
		}

		if(MOUSE_L_BTN_UP){
			UpdateGame();
			if(!BufferIsEmpty){
				memcpy(redraw_objects, BufferDeleteHigl, sizeof(RECT) * TOTAL_NEAR_BLOCKS);
				iterator_redraw_obj = TOTAL_NEAR_BLOCKS;
				BufferIsEmpty = TRUE;
				return iterator_redraw_obj;
			}else{
				return -1;
			}
		}

}


extern INT8 GameGetNumbersOfFlags(void)
{
    return flags;
}


extern BOOL GamePlayerIsLooser(void)
{
	return FlagYouLooser;
}


static POINT* RecalculateCurrentNearBlocks(INT8 iter_height, INT8 iter_width, POINT CurrentNearBlocks[])
{	
	POINT operation[TOTAL_NEAR_BLOCKS];
	operation[0].x = -1, operation[0].y = 0;   operation[1].x = -1, operation[1].y = 1; 
	operation[3].x = 1,  operation[3].y = 1;   operation[4].x = -1, operation[4].y = -1; 
	operation[6].x = 0,  operation[6].y = -1;  operation[7].x = 1,  operation[7].y = -1; 
    operation[2].x = 0,  operation[2].y = 1;   operation[5].x = 1,  operation[5].y = 0;
 
	for(size_t i = 0; i < TOTAL_NEAR_BLOCKS; i++){
		INT8 offset_x = (iter_height + operation[i].x), offset_y = (iter_width + operation[i].y);
		if(offset_x > HEIGHT_BLOCKS-1 || offset_x < -1 || offset_y > WIDTH_BLOCKS-1 || offset_y < -1){
			CurrentNearBlocks[i].x = -1;
			continue;
		}

		CurrentNearBlocks[i].x = offset_x; CurrentNearBlocks[i].y = offset_y;
	}

	return CurrentNearBlocks;
	
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
	POINT BombPos[TOTAL_BOMBS] = {0};

	for (size_t i = 0; i < TOTAL_BOMBS; i++){
		h = rand() % (HEIGHT_BLOCKS - 0) + 0;
		w = rand() % (WIDTH_BLOCKS - 0) + 0;
		BombPos[i].x = h;
		BombPos[i].y = w;
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
	POINT CurrentNearBlocks[TOTAL_NEAR_BLOCKS];
    RecalculateCurrentNearBlocks(iter_height, iter_width, CurrentNearBlocks);
	for (size_t i = 0; i < TOTAL_NEAR_BLOCKS; i++)
	{
		if(CurrentNearBlocks[i].x >= 0)
			if(playfblocks[CurrentNearBlocks[i].x][CurrentNearBlocks[i].y].type == TYPE_BOMB)
				count ++;
	}
	
	return count;
 }


 void UpdateGame(void)
 {
	FlagYouWiner = TRUE;
	for(size_t i = 0; i < HEIGHT_BLOCKS; i++){
		for(size_t f = 0; f < WIDTH_BLOCKS; f++){
			playfblocks[i][f].highlight = FALSE;
			if(playfblocks[i][f].type == TYPE_BOMB){
				if(playfblocks[i][f].status != STATUS_MARK){
					FlagYouWiner = FALSE;
				}
			}
		}
	}


	if(FlagYouWiner)
		GetMsg("WIN");
	
 }


 extern BOOL GetYouWinerFlag(void)
 {
	return FlagYouWiner;
 }


 static void ParseEmptyBlocks(INT8 iter_height_start, INT8 iter_width_start)
 {	
	//const INT8 possible_empty_block = (HEIGHT_BLOCKS * WIDTH_BLOCKS) - TOTAL_BOMBS;
	//POINT buffer_blocks[TOTAL_BOMBS] = {0};
	//POINT empty_blocks[possible_empty_block];
	
	POINT CurrentNearBlocks[TOTAL_NEAR_BLOCKS];
    RecalculateCurrentNearBlocks(iter_height_start, iter_width_start, CurrentNearBlocks);
	for (size_t i = 0; i < TOTAL_NEAR_BLOCKS; i++)
	{	
		if(CurrentNearBlocks[i].x > -1){
			if(playfblocks[CurrentNearBlocks[i].x][CurrentNearBlocks[i].y].type != TYPE_BOMB){
				playfblocks[CurrentNearBlocks[i].x][CurrentNearBlocks[i].y].status = STATUS_OPEN;
				playfblocks[CurrentNearBlocks[i].x][CurrentNearBlocks[i].y].count_bomb_near = GetCountNearBomb(CurrentNearBlocks[i].x, CurrentNearBlocks[i].y);
			}
	
		}
	}
		
	
 }