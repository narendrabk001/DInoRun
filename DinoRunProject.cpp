#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <time.h>

struct Cactus {
    int x;
    int height;
    bool active;
    int type; 
};

struct Cloud {
    int x;
    int y;
    int speed;
};

// Function to draw mountains in background
void drawMountains(int groundY) {
    // Mountain 1 - Left side (large)
    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, DARKGRAY);
    int mountain1[] = {0, groundY, 120, 200, 240, groundY, 0, groundY};
    fillpoly(4, mountain1);
    
    // Mountain 2 - Right side
    setcolor(LIGHTGRAY);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    int mountain2[] = {400, groundY, 520, 220, 640, groundY, 400, groundY};
    fillpoly(4, mountain2);
    
    // Mountain 3 - Center background
    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, DARKGRAY);
    int mountain3[] = {250, groundY, 380, 250, 510, groundY, 250, groundY};
    fillpoly(4, mountain3);
    
    // Small mountain in front
    setcolor(LIGHTGRAY);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    int mountain4[] = {150, groundY, 220, 290, 290, groundY, 150, groundY};
    fillpoly(4, mountain4);
}

// Function to draw a single cloud
void drawCloud(int x, int y) {
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    
    // Draw cloud using multiple circles
    fillellipse(x, y, 25, 12);
    fillellipse(x + 20, y, 25, 12);
    fillellipse(x + 10, y - 10, 20, 10);
}

// Function to update and draw moving clouds
void updateClouds(Cloud clouds[], int numClouds) {
    for (int i = 0; i < numClouds; i++) {
        // Move cloud from right to left
        clouds[i].x -= clouds[i].speed;
        
        // If cloud goes off screen, reset it to the right
        if (clouds[i].x < -50) {
            clouds[i].x = 640 + rand() % 100;
            clouds[i].y = 50 + rand() % 100;
            clouds[i].speed = 1 + rand() % 3;
        }
        
        // Draw the cloud
        drawCloud(clouds[i].x, clouds[i].y);
    }
}

// Function to draw improved red dinosaur shape
void drawDino(int x, int y, bool isJumping, int groundY) {
    // Set dino color to RED
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    
    // Main body (oval shape)
    fillellipse(x + 20, y + 20, 18, 12);
    
    // Neck and head
    bar(x + 30, y - 5, x + 45, y + 10);
    
    // Head (rounded)
    fillellipse(x + 50, y, 8, 6);
    
    // Thighs
    bar(x + 10, y + 15, x + 20, y + 25);
    bar(x + 30, y + 15, x + 40, y + 25);
    
    // Legs - different when jumping vs on ground
    if (!isJumping) {
        // Running legs (on ground) - alternating animation
        static int legFrame = 0;
        if (legFrame == 0) {
            // Front leg back, back leg forward
            bar(x + 12, y + 25, x + 16, groundY);
            bar(x + 32, y + 25, x + 36, groundY - 8);
        } else {
            // Front leg forward, back leg back
            bar(x + 12, y + 25, x + 16, groundY - 8);
            bar(x + 32, y + 25, x + 36, groundY);
        }
        legFrame = 1 - legFrame;
    } else {
        // Jumping legs (tucked up)
        bar(x + 12, y + 22, x + 16, y + 28);
        bar(x + 32, y + 22, x + 36, y + 28);
    }
    
    // Tail (curved appearance)
    int tailPoints[] = {x - 15, y + 15, x - 5, y + 10, x, y + 18, x - 15, y + 15};
    fillpoly(4, tailPoints);
    
    // Eye
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x + 47, y - 2, 2, 2);
    
    // Eye pupil
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x + 48, y - 2, 1, 1);
    
    // Mouth (smile)
    setcolor(BLACK);
    arc(x + 45, y + 3, 0, 180, 4);
    
    // Spikes on back
    setcolor(RED);
    line(x + 5, y + 5, x + 10, y);
    line(x + 15, y + 3, x + 20, y - 2);
    line(x + 25, y + 5, x + 30, y);
}

// Function to draw improved cactus shapes
void drawCactus(int x, int height, int type, int groundY) {
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    
    switch(type) {
        case 0: // Single tall cactus
            // Main stem
            bar(x, groundY - height, x + 12, groundY);
            // Left arm
            bar(x - 8, groundY - height + 15, x, groundY - height + 25);
            // Right arm
            bar(x + 12, groundY - height + 20, x + 20, groundY - height + 30);
            break;
            
        case 1: // Double cactus (medium)
            // Left stem
            bar(x - 5, groundY - (height - 10), x, groundY);
            // Right stem (taller)
            bar(x + 5, groundY - height, x + 15, groundY);
            // Arm on right stem
            bar(x + 15, groundY - height + 25, x + 22, groundY - height + 35);
            break;
            
        case 2: // Triple cactus (small group)
            // Left small cactus
            bar(x - 8, groundY - (height - 15), x - 3, groundY);
            // Middle main cactus
            bar(x + 2, groundY - height, x + 10, groundY);
            // Right small cactus
            bar(x + 13, groundY - (height - 20), x + 18, groundY);
            // Arm on middle cactus
            bar(x + 10, groundY - height + 18, x + 15, groundY - height + 25);
            break;
    }
    
    // Add cactus segments/details
    setcolor(DARKGRAY);
    switch(type) {
        case 0:
            for (int j = 8; j < height; j += 10) {
                line(x, groundY - j, x + 12, groundY - j);
            }
            // Arm segments
            line(x - 8, groundY - height + 20, x, groundY - height + 20);
            line(x + 12, groundY - height + 25, x + 20, groundY - height + 25);
            break;
            
        case 1:
            for (int j = 8; j < height; j += 10) {
                line(x + 5, groundY - j, x + 15, groundY - j);
            }
            for (int j = 8; j < (height - 10); j += 10) {
                line(x - 5, groundY - j, x, groundY - j);
            }
            break;
            
        case 2:
            for (int j = 8; j < height; j += 10) {
                line(x + 2, groundY - j, x + 10, groundY - j);
            }
            for (int j = 8; j < (height - 15); j += 10) {
                line(x - 8, groundY - j, x - 3, groundY - j);
            }
            for (int j = 8; j < (height - 20); j += 10) {
                line(x + 13, groundY - j, x + 18, groundY - j);
            }
            break;
    }
}

// Function to initialize game state
void initializeGame(int &dinoY, bool &isJumping, int &jumpVelocity, Cactus cacti[], int &cactusTimer, int &score, Cloud clouds[], int numClouds) {
    dinoY = 310; // groundY - 40
    isJumping = false;
    jumpVelocity = 0;
    score = 0;
    cactusTimer = 0;
    
    // Reset all cacti
    for (int i = 0; i < 3; i++) {
        cacti[i].active = false;
    }
    
    // Reinitialize clouds with random positions
    for (int i = 0; i < numClouds; i++) {
        clouds[i].x = rand() % 640;
        clouds[i].y = 30 + rand() % 120;
        clouds[i].speed = 1 + rand() % 3;
    }
}

// Function to draw game over screen with replay option
bool drawGameOverScreen(int score) {
    cleardevice();
    
    // Draw background
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    bar(0, 0, 640, 350);
    
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    bar(0, 350, 640, 480);
    
    // Game Over text
    setcolor(RED);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    outtextxy(220, 120, "GAME OVER");
    
    // Score display
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    char scoreStr[50];
    sprintf(scoreStr, "Final Score: %d", score);
    outtextxy(240, 180, scoreStr);
    
    // Replay instructions
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(200, 230, "Press 'R' to Play Again");
    outtextxy(220, 260, "Press 'ESC' to Exit");
    
    // Wait for player input
    while (true) {
        if (kbhit()) {
            char key = getch();
            if (key == 'r' || key == 'R') {
                return true; // Replay
            }
            else if (key == 27) { // ESC
                return false; // Exit
            }
        }
        delay(40);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    
    srand(time(NULL));
    
    int groundY = 350;
    int dinoX = 100;  // Fixed dinosaur position
    int dinoY = groundY - 40;  // Starting position
    
    // Dinosaur variables
    bool isJumping = false;
    int jumpVelocity = 0;
    const int gravity = 1;
    const int jumpStrength = -15;
    
    // Cactus variables
    Cactus cacti[3];
    for (int i = 0; i < 3; i++) {
        cacti[i].active = false;
        cacti[i].type = 0;
    }
    int cactusTimer = 0;
    int score = 0;
    bool gameRunning = true;
    bool replay = true;
    
    // Cloud variables
    const int NUM_CLOUDS = 4;
    Cloud clouds[NUM_CLOUDS];
    
    // Main game loop with replay capability
    while (replay) {
        // Initialize game state
        initializeGame(dinoY, isJumping, jumpVelocity, cacti, cactusTimer, score, clouds, NUM_CLOUDS);
        gameRunning = true;
        
        // Set background color to BLUE for sky
        setbkcolor(BLUE);

        while (gameRunning) {
            cleardevice();
            
            // Draw sky background - BLUE
            setcolor(BLUE);
            setfillstyle(SOLID_FILL, BLUE);
            bar(0, 0, 640, groundY);
            
            // Draw mountains in background (attached to ground)
            drawMountains(groundY);
            
            // Update and draw moving clouds
            updateClouds(clouds, NUM_CLOUDS);
            
            // Draw horizontal ground line (white for contrast)
            setcolor(WHITE);
            line(0, groundY, 640, groundY);
            
            // Fill ground area with GREEN color
            setcolor(GREEN);
            setfillstyle(SOLID_FILL, GREEN);
            bar(0, groundY + 1, 640, 480);
            
            // Handle keyboard input
            if (kbhit()) {
                char key = getch();
                if (key == ' ' && !isJumping) {
                    // Start jump
                    jumpVelocity = jumpStrength;
                    isJumping = true;
                }
                else if (key == 27) {  // ESC key to exit
                    gameRunning = false;
                    replay = false;
                }
            }
            
            // Update jumping physics
            if (isJumping) {
                dinoY += jumpVelocity;
                jumpVelocity += gravity;
                
                // Check if landed back on ground
                if (dinoY >= groundY - 40) {
                    dinoY = groundY - 40;
                    isJumping = false;
                    jumpVelocity = 0;
                }
            }
            
            // Spawn moving cacti
            cactusTimer++;
            if (cactusTimer > 60) {
                for (int i = 0; i < 3; i++) {
                    if (!cacti[i].active) {
                        cacti[i].active = true;
                        cacti[i].x = 640;
                        cacti[i].height = 25 + rand() % 35;
                        cacti[i].type = rand() % 3;
                        break;
                    }
                }
                cactusTimer = 0;
            }
            
            // Update and draw moving cacti
            for (int i = 0; i < 3; i++) {
                if (cacti[i].active) {
                    // Move cactus from right to left
                    cacti[i].x -= 6;
                    
                    // Draw improved cactus
                    drawCactus(cacti[i].x, cacti[i].height, cacti[i].type, groundY);
                    
                    // Remove cactus when off screen and add to score
                    if (cacti[i].x < -30) {
                        cacti[i].active = false;
                        score += 1;
                    }
                    
                    // Check collision with dinosaur
                    if (cacti[i].active) {
                        // Different collision boxes based on cactus type
                        int cactusLeft, cactusRight;
                        
                        switch(cacti[i].type) {
                            case 0: // Single cactus
                                cactusLeft = cacti[i].x - 8;
                                cactusRight = cacti[i].x + 20;
                                break;
                            case 1: // Double cactus
                                cactusLeft = cacti[i].x - 5;
                                cactusRight = cacti[i].x + 22;
                                break;
                            case 2: // Triple cactus
                                cactusLeft = cacti[i].x - 8;
                                cactusRight = cacti[i].x + 18;
                                break;
                        }
                        
                        // Only check collision if dinosaur is not high enough to jump over
                        if (cactusLeft < dinoX + 40 && cactusRight > dinoX) {
                            // Check if dinosaur is jumping high enough to clear the cactus
                            if (!isJumping || dinoY > groundY - cacti[i].height - 40) {
                                // Collision detected - end this game session
                                gameRunning = false;
                            }
                        }
                    }
                }
            }
            
            // Draw single red dinosaur
            drawDino(dinoX, dinoY, isJumping, groundY);
            
            // Ground details (dark green lines on green ground for contrast)
            setcolor(DARKGRAY);
            for (int i = 0; i < 640; i += 50) {
                line(i, groundY + 3, i + 25, groundY + 3);
            }
            
            // Display score and info
            setcolor(WHITE);
            char scoreStr[30];
            sprintf(scoreStr, "Score: %d", score);
            outtextxy(500, 20, scoreStr);
            
            // Jump status
            if (isJumping) {
                outtextxy(500, 40, "Status: JUMPING");
            } else {
                outtextxy(500, 40, "Status: Running");
            }
            
         
            
            // Instructions
            setcolor(WHITE);
            outtextxy(10, 10, "Press SPACE to jump over Cactus");
            outtextxy(10, 30, "Press ESC to exit");
            
            delay(40);
        }
        
        // Show game over screen and check for replay
        if (replay) {
            replay = drawGameOverScreen(score);
        }
    }
    
    closegraph();
    return 0;
}
