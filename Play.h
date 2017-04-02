int32_t vel;										// Velocity of bird (positive is upward, negative is downward)
const unsigned char bird[];			// Image of flappy bird
const unsigned char stage[];		// Image of stage

// Progress the stage 
void advance_stage(void);

// Make flappy bird fall due to gravity
void fall(void);

// Make flappy bird jump if screen is touched
void jump(void);

// Check to see if flappy bird collided with obstacle
uint16_t collision(void);