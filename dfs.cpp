#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include <iostream>

// Constants for grid size and window
const int WIDTH = 600;
const int HEIGHT = 600;
const int ROWS = 20;
const int COLS = 20;
const int CELL_SIZE = WIDTH / COLS;

// Colors
sf::Color WHITE = sf::Color::White;
sf::Color BLACK = sf::Color::Black;
sf::Color GRAY = sf::Color(200, 200, 200);
sf::Color BLUE = sf::Color::Blue;
sf::Color GREEN = sf::Color::Green;
sf::Color RED = sf::Color::Red;
sf::Color YELLOW = sf::Color::Yellow;

// Directions for DFS (Right, Down, Left, Up)
const std::vector<std::pair<int, int>> DIRECTIONS = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

// Node structure
struct Node {
    int row, col;
    Node(int r, int c) : row(r), col(c) {}
};

// Global grid and state
sf::RectangleShape grid[ROWS][COLS];
bool visited[ROWS][COLS] = { false };
sf::Vector2i start(-1, -1);
sf::Vector2i end(-1, -1);

// Function to initialize the grid
void initializeGrid() {
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            grid[row][col].setSize(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1)); // Cell size with margin
            grid[row][col].setPosition(col * CELL_SIZE, row * CELL_SIZE);      // Position in window
            grid[row][col].setFillColor(WHITE);                                // Default color
        }
    }
}

// Function to visualize DFS
void dfs(sf::RenderWindow& window) {
    if (start.x == -1 || end.x == -1) return; // Ensure start and end are set

    std::stack<Node> stack;
    stack.push(Node(start.x, start.y));
    visited[start.x][start.y] = true;

    bool pathFound = false;

    while (!stack.empty() && !pathFound) {
        Node current = stack.top();
        stack.pop();

        // Color the current cell as part of the path
        if (current.row != start.x || current.col != start.y) {
            grid[current.row][current.col].setFillColor(BLUE);
        }

        // Check if we've reached the end
        if (current.row == end.x && current.col == end.y) {
            pathFound = true;
            break;
        }

        // Explore neighbors
        for (auto dir : DIRECTIONS) {
            int newRow = current.row + dir.first;
            int newCol = current.col + dir.second;

            // Check bounds and if the cell is unvisited and not an obstacle
            if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS &&
                !visited[newRow][newCol] && grid[newRow][newCol].getFillColor() != BLACK) {
                stack.push(Node(newRow, newCol));
                visited[newRow][newCol] = true;

                // Mark the cell as part of the current path
                if (sf::Vector2i(newRow, newCol) != end) {
                    grid[newRow][newCol].setFillColor(YELLOW);
                }
            }
        }

        // Render the grid
        window.clear(WHITE);
        for (int row = 0; row < ROWS; ++row) {
            for (int col = 0; col < COLS; ++col) {
                window.draw(grid[row][col]);
            }
        }
        window.display();
        sf::sleep(sf::milliseconds(50)); // Slow down visualization
    }

    // Highlight the final path if found
    if (pathFound) {
        while (!stack.empty()) stack.pop(); // Clear stack
        std::cout << "Path found!\n";
    }
    else {
        std::cout << "No path found!\n";
    }
}

// Main function
int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "DFS Visualizer");

    initializeGrid();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Left mouse button: Set start, end, or obstacles
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int row = mousePos.y / CELL_SIZE;
                int col = mousePos.x / CELL_SIZE;

                if (start.x == -1) {
                    start = sf::Vector2i(row, col);
                    grid[row][col].setFillColor(GREEN); // Start point
                }
                else if (end.x == -1 && sf::Vector2i(row, col) != start) {
                    end = sf::Vector2i(row, col);
                    grid[row][col].setFillColor(RED); // End point
                }
                else if (sf::Vector2i(row, col) != start && sf::Vector2i(row, col) != end) {
                    grid[row][col].setFillColor(BLACK); // Obstacle
                }
            }

            // Right mouse button: Clear cells
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int row = mousePos.y / CELL_SIZE;
                int col = mousePos.x / CELL_SIZE;

                if (sf::Vector2i(row, col) == start) {
                    start = sf::Vector2i(-1, -1);
                }
                else if (sf::Vector2i(row, col) == end) {
                    end = sf::Vector2i(-1, -1);
                }
                grid[row][col].setFillColor(WHITE); // Reset to default
            }

            // Press Enter to start DFS
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                dfs(window); // Start DFS visualization
            }
        }

        // Render the grid
        window.clear(WHITE);
        for (int row = 0; row < ROWS; ++row) {
            for (int col = 0; col < COLS; ++col) {
                window.draw(grid[row][col]);
            }
        }
        window.display();
    }

    return 0;
}