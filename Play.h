#include <stdint.h>

// Generates a random height for an up pipe
int16_t randUp(void);

// Generates a random height for an down pipe
int16_t randDown(void);

// Initialize game
void gameInit(void);

// Clear the pipes
void clearPipes(void);

// Draw the pipes
void drawPipes(void);

// Progress the stage 
void advanceStage(void);

// Clear Bird
void clearBird(void);

// Draw Bird
void drawBird(void);

// Make flappy bird fall due to gravity
void fall(void);

// Make flappy bird jump if screen is touched
void jump(void);

// Check to see if flappy bird collided with obstacle
void collision(void);

// Game over state
void gameOver(void);
