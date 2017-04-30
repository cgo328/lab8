#include "Play.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../inc/tm4c123gh6pm.h"
#include "SSD2119.h"

const extern unsigned short Background[];
const extern unsigned short pipeup[];
const extern unsigned short pipedown[];
const extern unsigned short bird[];

// Any pos variables refer to the location of the top left corner of corresponding image (except bottom left for 

const int16_t gravity = 1;							// How much velocity changes when the bird falls
const int16_t jump_vel = -7;						// Upward velocity of bird when it jumps
const int16_t x_pos = 20;								// X position of left edge of bird (stays constant)
const int16_t start = 120;							// Starting y_pos of bird

const int16_t background_len = 320;			// Length of background (screen)
const int16_t background_height = 240;	// Height of background (screen)

const int16_t bird_len = 19;						// Length of bird 
const int16_t bird_height = 15;					// Height of bird

int16_t vel;														// Velocity of bird (negative is upward, positive is downward)
int16_t y_pos;													// Y position of top of bird (0 is top of screen)

int16_t pipe_pos[3];											// Position of pipes
int16_t pipe_height[3];										// Height of pipes
int16_t pipe_pot_height;
int16_t pipe_range;

const int16_t pipe_len = 27;
const int16_t pipe_max_range = 120;
const int16_t pipe_max_height = 158;
const int16_t pipe_gap = 60;
const int16_t pipe_dist = 115;
const int16_t pipe_start = 120;
const int16_t pipe_reset = -30;					// The point at which pipe1 is removed and a new pipe is created
const int16_t pipe_start_range = 30;
const int16_t pipe_start_height = 75;
const int16_t pipe_inc = 3;
const int16_t new_diff = 40;

int16_t score;

// Generates a random height for a pipe
int16_t randHeight(void) {
	return (rand() % pipe_range) + pipe_pot_height;
}

// Initialize game
void gameInit(void) {
	LCD_DrawBMP(0, 0, Background, 320, 240);		// Draw the background 
	vel = 0;
	y_pos = start;
	pipe_range = pipe_start_range;
	pipe_pot_height = pipe_start_height;
	pipe_pos[0] = pipe_start;
	pipe_height[0] = randHeight();
	pipe_pos[1] = pipe_pos[0] + pipe_dist;
	pipe_height[1] = randHeight();
	pipe_pos[2] = pipe_pos[1] + pipe_dist;
	pipe_height[2] = randHeight();
	score = 0;
}

// Clear the pipes
void clearPipes(void) {
	int x, y;
	for (int i = 0; i < 3; i++) {
		for (int j = pipe_len - pipe_inc; j < pipe_len; j++) {
			
			for (int k = 0; k < pipe_height[i]; k++) {
				x = pipe_pos[i] + j;
				y = pipe_height[i] - k - 1;
				LCD_DrawPixel(x, y, Background[(background_len * y) + x]);
			}
			
			for (int k = pipe_height[i] + pipe_gap; k < background_height; k++) {
				x = pipe_pos[i] + j;
				y = k;
				LCD_DrawPixel(x, y, Background[(background_len * y) + x]);
			}
			
		}
	}
}

// Draw the pipes
void drawPipes(void) {
	int x, y;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < pipe_len; j++) {
			for (int k = 0; k < pipe_height[i]; k++) {
				x = pipe_pos[i] + j;
				y = pipe_height[i] - k - 1;
				if (pipedown[((pipe_max_height - k) * pipe_len) + j] != 0xFFFF) {
					LCD_DrawPixel(x, y, pipedown[((pipe_max_height - k) * pipe_len) + j]);
				}
				else {
					LCD_DrawPixel(x, y, Background[(background_len * y) + x]);
				}
			}
			for (int k = 0; k < background_height - (pipe_height[i] + pipe_gap); k++) {
				x = pipe_pos[i] + j;
				y = pipe_height[i] + pipe_gap + k;
				if (pipeup[(k * pipe_len) + j] != 0xFFFF) {
					LCD_DrawPixel(x, y, pipeup[(k * pipe_len) + j]);
				}
				else {
					LCD_DrawPixel(x, y, Background[(background_len * y) + x]);
				}
			}
			
		}
	}
}

// Progress the stage 
void advanceStage(void){
	clearPipes();
	pipe_pos[0]-= pipe_inc;
	pipe_pos[1]-= pipe_inc;
	pipe_pos[2]-= pipe_inc;
	if (pipe_pos[0] <= pipe_reset) {
		pipe_pos[0] = pipe_pos[1];
		pipe_height[0] = pipe_height[1];
		pipe_pos[1] = pipe_pos[2];
		pipe_height[1] = pipe_height[2];
		pipe_pos[2] = pipe_pos[1] + pipe_dist;
		pipe_height[2] = randHeight();
	}
	drawPipes();
	score++;
	LCD_SetCursor(0,0);
	LCD_PrintInteger(score);
	if (score % new_diff == 0) {
		if (pipe_range < pipe_max_range) {
			pipe_range += 2;
			pipe_pot_height--;
		}
	}
}

// Clear Bird
void clearBird(void) {
	int x, y;
	for (int i = 0; i < bird_len; i ++) {
		for (int j = 0; j < bird_height; j++) {
			x = x_pos + i;
			y = y_pos + j;
			LCD_DrawPixel(x, y, Background[((background_len * y) + x) % 76800]);
		}
	}
}

// Draw Bird
void drawBird(void) {
	int x, y;
	for (int i = 0; i < bird_len; i ++) {
		for (int j = 0; j < bird_height; j++) {
			x = x_pos + i;
			y = y_pos + j;
			if (bird[(bird_len * j) + i] != 0) {
				LCD_DrawPixel(x, y, bird[(bird_len * j) + i]);
			}
		}
	}
}

// Make flappy bird fall due to gravity
void fall(void) {
	clearBird();
	vel += gravity;			
	y_pos += vel;
	drawBird();
}

// Make flappy bird jump if screen is touched
void jump(void) {
	clearBird();
	vel = jump_vel;
	y_pos += vel;
	drawBird();
}

// Check to see if flappy bird collided with obstacle
void collision(void) {
	if (y_pos < 0 || y_pos > background_height - bird_height) {
		gameOver();
	}
	if ((pipe_pos[0] < x_pos + bird_len) && (pipe_pos[0] + pipe_len > x_pos)) {
		if ((y_pos < pipe_height[0]) || (y_pos + bird_height > pipe_height[0] + pipe_gap)) {
			gameOver();
		}
	}
	return;
}

// Game over state
void gameOver(void) {
	gameInit();
}
