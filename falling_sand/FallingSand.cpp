/* MARCO BOSSLE VILLANOVA (aka apecuca)
* to run this you'll need to have raylib
* I used vcpkg to install it globally, but if you want you can do it manually :)
*/

/* PLANS FOR THIS PROJECT
* 
* Add concrete/a cell that doesn't fall
* Make a class for the simulation and other for the brush
* 
*/

#include <raylib.h>
#include <iostream>
#include <math.h>

// Normally it's BAD to declare variables outside of a function, but
// Since all these variables are going to be created only once, I don't think it's a problem

// Screen data
const int screenWidth = 800;
const int screenHeight = 800;
const int targetFPS = 60;

// Grid preparation
const int rows = 100;
const int columns = 100;
const int cellSize_x = screenWidth / columns;
const int cellSize_y = screenHeight / rows;

// Grid and velocity grid, all cells are populated with 0
// Main grid is a char because it stores numbers up to 255, and it's exactly what I need :)
// also it's lighter hehe
char grid[rows][columns] = {};
float velocityGrid[columns][rows] = {};

// Additive force that applies every frame
// Just like gravity in real life :O
const float gravityForce = 0.5f;

// Sand placement and removal
const int brushSize = 5;
const int brushExtent = static_cast<int>(brushSize / 2);
Vector2 mousePosition;

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


// Funtion that returns if the coordinates are inside the grid
bool IsCellValid(int x, int y)
{
    if (x < 0 || x >= columns) return false;
    else if (y < 0 || y >= rows) return false;
    else return true;
}


// Method to handle Inputs from user, like reset, spawn and remove sand
void InputHandler()
{
    // Updates mouse position variable
    mousePosition = GetMousePosition();

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

    // Populate the entire grid
    if (IsKeyPressed(KEY_P))
    {
        for (int x = 0; x < columns; x++) {
            for (int y = 0; y < rows; y++) {
                grid[x][y] = static_cast<char>(rand() % 55 + 200);
                velocityGrid[x][y] = 1.0f;
            }
        }
    }

    // Click to spawn sand
    // Just aim and shoot (it's more like a pencil tho)
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 clickedCell = GetCellClicked(mousePosition);

        // Starts at the top left of the possible positions
        for (int x = -brushExtent; x <= brushExtent; x++) {
            for (int y = -brushExtent; y <= brushExtent; y++) {
                // This randomness makes the brush cooler
                if (std::rand() % 10 > 6) continue;
                if (!IsCellValid(clickedCell.x + x, clickedCell.y + y)) continue;

                // populates grid based on loop position and clicked cell
                grid[static_cast<int>(clickedCell.x) + x][static_cast<int>(clickedCell.y) + y] = static_cast<char>(rand() % 55 + 200);
                velocityGrid[static_cast<int>(clickedCell.x) + x][static_cast<int>(clickedCell.y) + y] = 1.0f;
            }
        }
    }

    // Click to remove sand
    // This one is basically the same thing as the above ^^^^, but 
    // de-populating grid, instead of populating it
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        Vector2 clickedCell = GetCellClicked(mousePosition);

        for (int x = -brushExtent; x <= brushExtent; x++) {
            for (int y = -brushExtent; y <= brushExtent; y++) {
                if (!IsCellValid(clickedCell.x + x, clickedCell.y + y)) continue;

                grid[static_cast<int>(clickedCell.x) + x][static_cast<int>(clickedCell.y) + y] = 0;
                velocityGrid[static_cast<int>(clickedCell.x) + x][static_cast<int>(clickedCell.y) + y] = 0;
            }
        }
    }
}


// Method that handles the whole simulation
void Simulate()
{
    // Nested loop to simulate the whole grid
    for (int x = columns - 1; x > -1; x--) {
        for (int y = rows - 1; y > -1; y--) {
            // Verificates if the cell is valid to simulate, skip if not
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
                // Starts with a random direction, and if it's not
                // available, try again next time
                // I liked this randomness in the simulation
                int _dir = (std::rand() % 2) < 1 ? -1 : 1;

                // Checks if the direction is available
                // If not, reset the velocity
                if (!IsCellValid(x + _dir, y + 1) ||
                    x + _dir >= columns || x + _dir < 0 ||
                    grid[x + _dir][y + 1] != 0)
                {
                    if (cellVelocity > 1.0f) velocityGrid[x][y] = 1.0f;
                    continue;
                }

                // Copies the cell from the two grids to the new and
                // resets the old cell
                grid[x + _dir][y + 1] = grid[x][y];
                velocityGrid[x + _dir][y + 1] = velocityGrid[x][y];
                grid[x][y] = 0;
                velocityGrid[x][y] = 0;
            }
            //
        }
    }
    // Nested loop ends here
}


// main function, everything happens HERE :)
int main(void)
{
    // Initiate THE WINDOW :O
    InitWindow(screenWidth, screenHeight, "Falling sand simulation");
    SetTargetFPS(targetFPS);

    // Main loop
    while (!WindowShouldClose())
    {
        // Order of action:
        // Input > Update/Simulate > Draw

        // Method that handles the Inputs from the user
        InputHandler();

        // Timer to reduce the number of times the simulation... Simulates
        simulateTimer += 1.0f * GetFrameTime() * simulationsPerSecond;
        if (simulateTimer >= 1.0f)
        {
            Simulate();
            simulateTimer = 0.0f;
        }

        // Begin drawing owo
        BeginDrawing();
        
        // clears background with the color black
        ClearBackground(BLACK);
        // Loop to draw the cells, from bottom to top
        for (int x = columns - 1; x > -1; x--) {
            for (int y = rows - 1; y > -1; y--) {
                // Draw empty rectangle or colored cell based on cell value
                if (grid[x][y] == 0) continue;

                // Again... 4 bytes...........
                // dang these (unsigned char) convertions are ugly
                Color colorVl = { (unsigned char)255, (unsigned char)grid[x][y],(unsigned char)0, (unsigned char)255 };
                DrawRectangle(cellSize_x * x, cellSize_y * y, cellSize_x, cellSize_y, colorVl);
            }
        }
        // Draw sand spawn preview
        DrawRectangleLines(mousePosition.x - ((brushSize * cellSize_x) / 2),
            mousePosition.y - ((brushSize * cellSize_y) / 2), brushSize * cellSize_x, brushSize * cellSize_y, GRAY);

        // Stop drawing uwu
        EndDrawing();
    }

    // Finalize the window :D
    CloseWindow();

    return 0;
}

// Just realized I typed a lot of comments haha sorry