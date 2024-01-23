/* MARCO BOSSLE VILLANOVA (aka apecuca)
* to run this you'll need to have raylib
* I used vcpkg to install it globally, but if you want you can do it manually :)
*/

#include <raylib.h>
#include <iostream>
#include <math.h>

// Normally it's BAD to declare variables outside of a function, but
// Since all these variables are going to be created only once, I don't think it's a problem

// Screen data
const int screenWidth = 800;
const int screenHeight = 800;

// Grid preparation
const int rows = 50;
const int columns = 50;
const int cellSize_x = screenWidth / columns;
const int cellSize_y = screenHeight / rows;

// Grid and velocity grid, all cells are populated with 0
int grid[rows][columns] = {};
float velocityGrid[columns][rows] = {};

// the force of gravity
// very stronk
const float gravityForce = 0.25f;

// Simulation constraints
float simulateTimer = 0.0f;
const int simulationsPerSecond = 15;

// The name if pretty self-explanatory
Vector2 GetCellClicked(Vector2 _mousePos)
{
    Vector2 clickedCell;
    // trunc() removes the decimals
    clickedCell.x = trunc((_mousePos.x / (screenWidth / columns)));
    clickedCell.y = trunc((_mousePos.y / (screenHeight / rows)));

    return clickedCell;
}

// main function :)
int main(void)
{
    // Initiate THE WINDOW :O
    InitWindow(screenWidth, screenHeight, "Falling sand simulation");
    SetTargetFPS(60);

    // Main loop
    while (!WindowShouldClose())
    {
        // RESET EVERYTHING OH MAH GAHH
        if (IsKeyPressed(KEY_R))
        {
            for (int x = 0; x < columns; x++) {
                for (int y = 0; y < rows; y++) {
                    grid[x][y] = 0;
                    velocityGrid[x][y] = 0;
                }
            }
        }

        // Timer to reduce the number of times the simulation... Simulates
        simulateTimer += 1.0f * GetFrameTime() * simulationsPerSecond;
        if (simulateTimer >= 1.0f)
        {
            // Nested loop to simulate the whole grid
            for (int x = columns - 1; x > -1; x--) {
                for (int y = rows - 1; y > -1; y--) {
                    // Verificates if the cell is valid to simulate, continues the loop if not
                    if (y == rows - 1) continue;
                    if (grid[x][y] == 0) continue;

                    // I COULD not create this variable to save on 4 bytes of memory...
                    // But it makes my life easier and it makes the code more readable
                    int cellVelocity = static_cast<int>(velocityGrid[x][y]);
                    
                    // Checks if the cell below is empty
                    if (grid[x][y + 1] == 0)
                    {
                        // Loops between the next grid and the current
                        // Because of the speed, the sand can skip some cells, so
                        // this loop is to find the next available cell
                        for (int i = y + cellVelocity; i >= y; i--)
                        {
                            // If the target cell is not available, try the next one
                            if (i >= rows) continue;
                            if (grid[x][i] != 0) continue;

                            // Copies the cell from the two grids and
                            // resets the old cell
                            grid[x][i] = grid[x][y];
                            velocityGrid[x][i] = velocityGrid[x][y] + gravityForce;
                            grid[x][y] = 0;
                            velocityGrid[x][y] = 0;
                        }
                    }
                    else
                    {
                        // It's 4am and I don't want to fix this
                        // It starts with a random direction to fall and
                        // EVENTUALLY it falls in the right direction hehe
                        int _dir = (std::rand() % 2) < 1 ? -1 : 1;
                        if (x + _dir >= columns || x + _dir < 0) continue;
                        if (grid[x + _dir][y + 1] != 0) continue;

                        // Copies the cell from the two grids and
                        // resets the old cell
                        grid[x + _dir][y + 1] = grid[x][y];
                        velocityGrid[x + _dir][y + 1] = 1.0f;
                        grid[x][y] = 0;
                        velocityGrid[x][y] = 0;
                    }
                }
            }

            simulateTimer = 0.0f;
        }

        // Click to spawn sand
        // Just aim and shoot (it's more like a pencil tho)
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 clickedCell = GetCellClicked(GetMousePosition());

            // Verify if cell is valid
            if (clickedCell.x > -1 && clickedCell.x < rows &&
                clickedCell.y > -1 && clickedCell.y < columns)
            {
                // Populate cell in both grids
                // Integer convertion because Vector2 stores floats, not integers
                // populated with a random number between 200 and 255, to determine color
                grid[static_cast<int>(clickedCell.x)][static_cast<int>(clickedCell.y)] = rand() % 55 + 200;
                velocityGrid[static_cast<int>(clickedCell.x)][static_cast<int>(clickedCell.y)] = 1.0f;
            }
        }

        // Click to remove sand
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            Vector2 clickedCell = GetCellClicked(GetMousePosition());

            if (clickedCell.x > -1 && clickedCell.x < rows &&
                clickedCell.y > -1 && clickedCell.y < columns)
            {
                // Populate cells with 0
                grid[static_cast<int>(clickedCell.x)][static_cast<int>(clickedCell.y)] = 0;
                velocityGrid[static_cast<int>(clickedCell.x)][static_cast<int>(clickedCell.y)] = 0;
            }
        }

        // Begin drawing owo
        BeginDrawing();
        
        // clears background with the color black
        ClearBackground(BLACK);
        // Loop to draw the cells, from bottom to top
        for (int x = columns - 1; x > -1; x--) {
            for (int y = rows - 1; y > -1; y--) {
                // Draw empty rectangle or colored cell based on cell value
                if (grid[x][y] == 0)
                {
                    DrawRectangleLines(cellSize_x * x, cellSize_y * y, cellSize_x, cellSize_y, DARKGRAY);
                }
                else
                {
                    // Again... 4 bytes........... Or more, I really don't know :P
                    // dang these (unsigned char) convertions are ugly
                    Color colorVl = { (unsigned char)255, (unsigned char)grid[x][y],(unsigned char)0, (unsigned char)255};
                    DrawRectangle(cellSize_x * x, cellSize_y * y, cellSize_x, cellSize_y, colorVl);
                } 
            }
        }

        // Stop drawing uwu
        EndDrawing();
    }

    // Finalize the window :D
    CloseWindow();

    return 0;
}