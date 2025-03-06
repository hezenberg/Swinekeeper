#include "gamelogic.h"

static INT8       flags                    = COUNT_BOMB;
static PLAYFBLOCK playfblocks[OVER_BLOCKS] = {};
static BOOL       FlagYouLooser            = FALSE;

extern PLAYFBLOCK* GameBlocksInitialization()
{   
	flags = COUNT_BOMB;
	FlagYouLooser  = FALSE;
	
	INT8 count = 0; 
	for(INT8 i = 0; i < 10; i++){
		for(INT8 f = 0; f < 6; f++){
			playfblocks[count].pos_block.left   = f * SIZE_BLOCK + 1;
			playfblocks[count].pos_block.top    = i * SIZE_BLOCK + 1;
			playfblocks[count].pos_block.right  = (f * SIZE_BLOCK) + SIZE_BLOCK;
			playfblocks[count].pos_block.bottom = (i * SIZE_BLOCK) + SIZE_BLOCK;

			playfblocks[count].pos_block.left   += INDENT_BLOCKS_X;
			playfblocks[count].pos_block.top    += INDENT_BLOCKS_Y;
			playfblocks[count].pos_block.right  += INDENT_BLOCKS_X;
			playfblocks[count].pos_block.bottom += INDENT_BLOCKS_Y;


			playfblocks[count].status = STATUS_NORM;

			count++;
		}
	}
	
	return playfblocks;
}


extern void GameHandleGameBlocks(INT8 down_mouse_btn, INT8 iterator_blocks)
{
	if(playfblocks[iterator_blocks].status != STATUS_OPEN){
		if(MOUSE_R_BTN == down_mouse_btn){
			if(flags > 0 && playfblocks[iterator_blocks].status == STATUS_NORM){
				playfblocks[iterator_blocks].status = STATUS_MARK;
				flags --;
			}
		}
		if(MOUSE_L_BTN  == down_mouse_btn){

			if(playfblocks[iterator_blocks].status == STATUS_NORM){
				if(playfblocks[iterator_blocks].type != TYPE_BOMB){
					playfblocks[iterator_blocks].status = STATUS_OPEN;
				}
				else{
					FlagYouLooser = TRUE;
					return;
				}
			}


			if(playfblocks[iterator_blocks].status == STATUS_MARK){
				playfblocks[iterator_blocks].status = STATUS_NORM;
				flags ++;
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
