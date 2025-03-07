#include "../include/gamelogic.h"

static INT8       flags                                    = COUNT_BOMB;
static PLAYFBLOCK **playfblocks;
static BOOL       FlagYouLooser                            = FALSE;

extern PLAYFBLOCK** GameBlocksInitialization()
{   
	
	if(AllocateMatrix() == 1)
		GetMessageErrorAndExit(ERROR_ALLOC_MATRX);

	flags = COUNT_BOMB;
	FlagYouLooser  = FALSE;
	
	INT8 count = 0; 
	for(INT8 i = 0; i < HEIGHT_BLOCKS; i++){
		for(INT8 f = 0; f < WIDTH_BLOCKS; f++){
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

			playfblocks[i][f] = block;
			count++;
		}
	}
	
	return playfblocks;
}


extern void GameHandleGameBlocks(INT8 down_mouse_btn, INT8 iter_height, INT8 iter_width)
{	
	PLAYFBLOCK *block = &playfblocks[iter_height][iter_width];
	if(block->status != STATUS_OPEN){
		if(MOUSE_R_BTN == down_mouse_btn){
			if(flags > 0 && block->status == STATUS_NORM){
				block->status = STATUS_MARK;
				flags --;
			}
		}
		if(MOUSE_L_BTN  == down_mouse_btn){

			if(block->status == STATUS_NORM){
				if(block->type != TYPE_BOMB){
					block->status = STATUS_OPEN;
				}
				else{
					FlagYouLooser = TRUE;
					return;
				}
			}


			if(block->status == STATUS_MARK){
				block->status = STATUS_NORM;
				flags ++;
			}

			if(block->status == STATUS_OPEN){
				HighlightNearBlocks(&block->pos_block);
			}
		}
	}

	return;
}


extern INT8 GameGetNumbersOfFlags(void)
{
    return flags;
}


extern BOOL GamePlayerIsLooser(void)
{
	return FlagYouLooser;
}


void HighlightNearBlocks(RECT *rblock)
{
	return;
}


int AllocateMatrix(void)
{
	playfblocks = (PLAYFBLOCK**)calloc(HEIGHT_BLOCKS, sizeof(PLAYFBLOCK*)*HEIGHT_BLOCKS*WIDTH_BLOCKS);
	if(NULL == playfblocks)
		return 1;

	for (size_t i = 0; i < HEIGHT_BLOCKS; i++){
		playfblocks[i] = (PLAYFBLOCK*)calloc(WIDTH_BLOCKS, sizeof(PLAYFBLOCK)*WIDTH_BLOCKS);
		if(NULL == playfblocks[i])
			return 1;
	}

	return 0;
}
