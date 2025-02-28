#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// GLOBAL VARIABLES
int ROWS = 0;         
int COLUMNS = 0;      
bool **GRID = nullptr;

// This function reads the input file for subsequent processing
void populateWorld(const char *file) {
    ifstream inFile(file);
    if (!inFile) {
        cerr << "Unable to open file " << file << endl;
        exit(1);
    }

    string line;
    while (getline(inFile, line)) {
        if (COLUMNS == 0) {
            COLUMNS = line.length(); // Get the length of the line
        }
        ROWS++;
    }

    // Allocate memory for the grid
    GRID = new bool *[ROWS];
    for (int i = 0; i < ROWS; i++) {
        GRID[i] = new bool[COLUMNS];
    }

    // Reset file pointer to the beginning
    inFile.clear();
    inFile.seekg(0, ios::beg);

    // Populate the grid
    for (int i = 0; i < ROWS; i++) {
        getline(inFile, line);
        for (int j = 0; j < COLUMNS; j++) {
            GRID[i][j] = (line[j] == '1');
        }
    }

    inFile.close();
}

// This function counts the number of live neighbors for a given cell
int countLiveNeighbors(bool **grid, int ROWS, int COLUMNS, int i, int j) {
    int count_alive = 0;

    if ((i > 0 && i < ROWS - 1) && (j > 0 && j < COLUMNS - 1)) { // Interior cells
        if (grid[i + 1][j + 1]) count_alive++; // Bottom right
        if (grid[i - 1][j - 1]) count_alive++; // Top left
        if (grid[i][j + 1]) count_alive++; // Right
        if (grid[i][j - 1]) count_alive++; // Left
        if (grid[i + 1][j]) count_alive++; // Bottom
        if (grid[i - 1][j]) count_alive++; // Top
        if (grid[i + 1][j - 1]) count_alive++; // Bottom left
        if (grid[i - 1][j + 1]) count_alive++; // Top right
    } else if (i == 0 || j == 0 || i == ROWS - 1 || j == COLUMNS - 1) { // Edge cells
        if (j < COLUMNS - 1 && grid[i][j + 1]) count_alive++; // Right
        if (j > 0 && grid[i][j - 1]) count_alive++; // Left
        if (i < ROWS - 1 && grid[i + 1][j]) count_alive++; // Bottom
        if (i > 0 && grid[i - 1][j]) count_alive++; // Top

        if (i < ROWS - 1 && j < COLUMNS - 1 && grid[i + 1][j + 1]) count_alive++; // Bottom-right
        if (i > 0 && j > 0 && grid[i - 1][j - 1]) count_alive++; // Top-left
        if (i < ROWS - 1 && j > 0 && grid[i + 1][j - 1]) count_alive++; // Bottom-left
        if (i > 0 && j < COLUMNS - 1 && grid[i - 1][j + 1]) count_alive++; // Top-right
    }

    return count_alive;
}

// This function outputs the grid for the current generation
void showWorld() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            cout << (GRID[i][j] ? '1' : '0');
        }
        cout << endl;
    }
}

// This function creates a new generation grid from the old generation grid
void iterateGeneration(bool **grid, int ROWS, int COLUMNS) {
    bool **newGrid = new bool *[ROWS];
    for (int i = 0; i < ROWS; i++) {
        newGrid[i] = new bool[COLUMNS];
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            int liveNeighbors = countLiveNeighbors(grid, ROWS, COLUMNS, i, j);

            // Apply Conway's Game of Life rules
            if (grid[i][j] && (liveNeighbors < 2 || liveNeighbors > 3)) {
                newGrid[i][j] = false; // Cell dies
            } else if (!grid[i][j] && liveNeighbors == 3) {
                newGrid[i][j] = true; // Cell is born
            } else {
                newGrid[i][j] = grid[i][j]; // Cell remains the same
            }
        }
    }

    // Copy the new grid back to the original grid
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            grid[i][j] = newGrid[i][j];
        }
    }

    // Free memory allocated for newGrid
    for (int i = 0; i < ROWS; i++) {
        delete[] newGrid[i];
    }
    delete[] newGrid;
}

int main() {
    populateWorld("glider_gun_fight.txt");

    cout << "Initial Generation:" << endl;
    showWorld();

    for (int generation = 1; generation <= 10; generation++) {
        iterateGeneration(GRID, ROWS, COLUMNS);
        cout << "Generation " << generation << ":" << endl;
        showWorld();
    }

    // Free memory allocated for GRID
    for (int i = 0; i < ROWS; i++) {
        delete[] GRID[i];
    }
    delete[] GRID;

    return 0;
}
