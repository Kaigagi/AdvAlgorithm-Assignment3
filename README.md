# Maximum Flow Algorithms Project

This project implements two algorithms for solving the **Maximum Flow problem**:
- **Edmonds–Karp Algorithm** (deterministic)
- **Karger’s Algorithm (adapted)** (randomized)

The goal is to explore and compare deterministic and probabilistic approaches to verifying the **Minimum Cut–Maximum Flow Theorem**.

---

## ⚙️ Build Instructions (Windows)

### Prerequisites
- **CMake** (version 3.10 or higher)
- A C++17 compatible compiler (e.g. `g++`, `clang++`, or MSVC)  
- **GoogleTest** (gtest)

### Steps
1. Clone or download this project.  
2. Ensure that the provided `CMakeLists.txt` file is in the root of the project directory.  
3. Build the file with ```cmake --build .```

---

## 🧪 Running / Tests
Once built, navigate to the build directory and run the test executable
```bash
cd build
.\tests.exe
```

---

## Notes
If you are having trouble running the executables after they are built:
- Open Developer Command Prompt for VS (requires having VS Build Tools installed)
- Navigate to the project root
- Open the folder in your code editor