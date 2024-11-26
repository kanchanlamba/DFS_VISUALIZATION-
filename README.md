# DFS_VISUALIZATION-
# **DFS Visualizer**

This project is a **Depth-First Search (DFS) Visualizer** built using the **SFML (Simple and Fast Multimedia Library)**. It provides an interactive and visually engaging way to learn and understand how the DFS algorithm works in a grid-based environment.

---

## **Features**

### 🎨 **Interactive Grid Setup**
- **Left Click**:  
  - Set the **start point** (green), **end point** (red), and add **obstacles** (black).  
- **Right Click**:  
  - Clear any cell, resetting it to its default state (white).  
- Experiment with different grid configurations to test a variety of scenarios.

### 🔍 **Real-Time DFS Visualization**
- **Press Enter** to start the DFS traversal:
  - Cells being explored are marked in **yellow**.
  - Confirmed parts of the path are marked in **blue**.
- The algorithm halts when the **end point** is found, highlighting the successful path.
- If no path exists, a **message is displayed**.

### 💡 **Dynamic Feedback**
- The program **slows the traversal** using small delays for a step-by-step view of how DFS works.
- Instantly reflects changes in the grid, providing an **interactive learning experience**.

---

## **How It Works**

### **DFS Implementation**
- The algorithm is implemented using a **stack-based approach**.
- Starting at the user-defined **start point**, it explores neighboring cells in a fixed order:
  - **Right, Down, Left, Up**.
- It avoids obstacles and cells that have already been visited.

### **Grid Visualization**
- The grid updates dynamically during the algorithm’s execution.
- **Visual cues** help users follow the algorithm's progression:
  - **Yellow**: Cells currently being explored.
  - **Blue**: Confirmed cells in the path.
  - **Green**: Start point.
  - **Red**: End point.
  - **Black**: Obstacles.

---

## **Code Example**

Here’s a simplified example of the DFS implementation and visualization code in C++ with SFML:

```cpp
#include <SFML/Graphics.hpp>
#include <stack>
#include <vector>

const int gridSize = 20;  // Size of the grid
const int cellSize = 30;  // Size of each cell
const sf::Color exploredColor = sf::Color::Yellow;  // Cells currently being explored
const sf::Color pathColor = sf::Color::Blue;        // Cells confirmed as part of the path
const sf::Color startColor = sf::Color::Green;      // Start point
const sf::Color endColor = sf::Color::Red;          // End point
const sf::Color obstacleColor = sf::Color::Black;   // Obstacles
const sf::Color defaultColor = sf::Color::White;    // Default cell color

// Main function
int main() {
    sf::RenderWindow window(sf::VideoMode(gridSize * cellSize, gridSize * cellSize), "DFS Visualizer");
    std::vector<std::vector<sf::RectangleShape>> grid(gridSize, std::vector<sf::RectangleShape>(gridSize));
    std::stack<std::pair<int, int>> dfsStack;

    // Initialize the grid
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            grid[i][j].setSize(sf::Vector2f(cellSize, cellSize));
            grid[i][j].setFillColor(defaultColor);
            grid[i][j].setOutlineThickness(1);
            grid[i][j].setOutlineColor(sf::Color::Black);
            grid[i][j].setPosition(i * cellSize, j * cellSize);
        }
    }

    // Event loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Additional input handling for grid interaction...
        }

        window.clear();
        for (const auto& row : grid) {
            for (const auto& cell : row) {
                window.draw(cell);
            }
        }
        window.display();
    }
    return 0;
}
