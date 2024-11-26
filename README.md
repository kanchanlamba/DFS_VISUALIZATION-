# DFS_VISUALIZATION-
This project is a Depth-First Search (DFS) Visualizer built using the SFML (Simple and Fast Multimedia Library). It provides an interactive and visually engaging way to learn and understand how the DFS algorithm works in a grid-based environment.

Features
🎨 Interactive Grid Setup
Left Click:
Set the start point (green), end point (red), and add obstacles (black).
Right Click:
Clear any cell, resetting it to its default state (white).
Experiment with different grid configurations to test a variety of scenarios.
🔍 Real-Time DFS Visualization
Press Enter to start the DFS traversal:
Cells being explored are marked in yellow.
Confirmed parts of the path are marked in blue.
The algorithm halts when the end point is found, highlighting the successful path.
If no path exists, a message is displayed.
💡 Dynamic Feedback
The program slows the traversal using small delays for a step-by-step view of how DFS works.
Instantly reflects changes in the grid, providing an interactive learning experience.
How It Works
DFS Implementation:

The algorithm is implemented using a stack-based approach.
Starting at the user-defined start point, it explores neighboring cells in a fixed order: right, down, left, up.
It avoids obstacles and cells that have already been visited.
Grid Visualization:

The grid updates dynamically during the algorithm’s execution.
Visual cues help users follow the algorithm's progression:
Yellow: Cells currently being explored.
Blue: Confirmed cells in the path.
Green: Start point.
Red: End point.
Black: Obstacles.
Code
Main Code
cpp
Copy code
#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include <iostream>
