# Maximum Flow Algorithms Project

This project implements two algorithms for solving the **Maximum Flow problem**:
- **Edmonds–Karp Algorithm** (deterministic)
- **Karger’s Algorithm (adapted)** (randomized)

The goal is to explore and compare deterministic and probabilistic approaches to verifying the **Minimum Cut–Maximum Flow Theorem**.

---

## ⚙️ Build Instructions (Windows)

### Prerequisites
- **CMake** (version 3.10 or higher)
- **Visual Studio** or another C++17-compatible compiler
- **GoogleTest** (gtest)

### Steps
1. Open a terminal (PowerShell or Command Prompt) in the project root.
2. Run the following commands:
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build . --config Release
   ```
3. Build the project
   ```bash
   cmake --build . --config Release
   ```
4. The compiled executables will appear in
   ```bash
   build/Release/
   ```