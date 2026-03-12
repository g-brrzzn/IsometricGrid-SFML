# 🗺️ IsometricGrid-SFML

A C++ 2D isometric grid application using SFML that features a dynamic camera system to navigate through an isometric map, showcasing an integration of grid layout, infinite world generation, chunk system, camera movement, and rendering culling. This technical demo builds upon previous work by exploring these features in an isometric perspective, offering a robust foundation for further experimentation.

## 🎥 Demonstration  
![demo1](https://github.com/user-attachments/assets/66fb2219-d74d-4632-bec4-ad71196c5298)
![demo2](https://github.com/user-attachments/assets/cfa0223f-8883-40d8-9866-30e18d61697f)

https://github.com/user-attachments/assets/0db2be88-87f5-426b-b0e5-aca779bfac3f

**Key Features:**

-   **Infinite & Async World Generation:** Chunked world generation with caching. Uses `std::future` / `std::async` for background generation so it doesn't block the main render loop.

-   **Procedural Terrain:** Perlin noise--based terrain height creates natural-looking variations across multi-layer isometric tiles (`GRID_LAYERS`), including variants for water, dirt, and ground.

-   **Optimized Rendering:** Implements strict view culling and visible-chunk calculation to ensure the engine only draws what's strictly needed.

-   **Resource Management:** Features a built-in texture manager (simple loader and scaling) alongside a flexible `cell` type that optionally holds a sprite.

-   **Smooth Navigation & Testing:** Smooth camera controls (WASD) with an FPS counter in the window title. Includes an easy regeneration feature (press `R`) to re-seed and refresh the world for quick testing.

-   **Educational Architecture:** A clean, small codebase specifically suited for learning SFML rendering, chunk systems, and coordinate transforms (cartesian ↔ isometric).

## 🚀 Usage  
- Use **WASD** to move the camera and explore the grid.
- **Refresh the Grid:** Press **R** to refresh the grid.


## 📦 Quick build

### Windows (PowerShell)
1\. Download SFML SDK from https://www.sfml-dev.org/download/ and extract to some folder (example `C:\libs\SFML-3.0.0`).\
2\. In your project root (where `CMakeLists.txt` is), run:

```powershell
# optional: remove old build
Remove-Item -Recurse -Force build

# configure (point to the SFML SDK)
cmake -S . -B build -DSFML_DIR="C:/libs/SFML-3.0.0/lib/cmake/SFML"

# build (Release)
cmake --build build --config Release
```

-   Resulting executable: `build/bin/Release/IsometricGrid-SFML.exe`

-   The included `CMakeLists.txt` will automatically try to copy SFML `.dll` files (when `-DSFML_DIR` is provided) and all `.png` assets next to the executable to make the result run out-of-the-box.

If the exe complains about missing DLLs, either:

-   make sure you used `-DSFML_DIR` pointing at the SDK, or

-   manually copy `SFML_ROOT/bin/*.dll` to `build/bin/Release`.

* * * * *

### Linux (Bash --- Ubuntu example)

On Debian/Ubuntu you can install SFML via apt:

```powershell
sudo apt update\
sudo apt install build-essential cmake libsfml-dev

# from project root\
rm -rf build\
cmake -S . -B build\
cmake --build build --config Release
```

Executable usually at `build/bin/IsometricGrid-SFML` (or `build/bin/Release/IsometricGrid-SFML` depending on generator).

* * * * *

✅ What the project CMake does for you
-------------------------------------

-   Detects project layout (works if `CMakeLists.txt` is in repo root or inside `IsometricGrid-SFML/`)

-   Tries SFML 3 (`Graphics`, `Window`, `System`) and falls back to SFML 2 component names when needed

-   Copies `.png` assets from the source folder into the runtime directory after build

-   If you pass `-DSFML_DIR=".../lib/cmake/SFML"`, CMake will attempt to locate SFML's `bin` folder and copy `.dll` files to the executable's folder (Windows), making the binary runnable without manual DLL copy

* * * * *

⚠️ Troubleshooting
------------------

-   **Missing `sfml-window-3.dll` / other SFML DLLs**

    -   Ensure you invoked `cmake` with `-DSFML_DIR` pointing to the SFML SDK.

    -   Or copy `SFML_ROOT/bin/*.dll` to the exe folder manually.

-   **CMake can't find SFML**

    -   Use: `-DSFML_DIR="C:/path/to/SFML/lib/cmake/SFML"` or `-DCMAKE_PREFIX_PATH="C:/path/to/SFML"`.

-   **Executable opens then immediately closes**

    -   Run the executable from a terminal to see errors (DLLs, runtime prints).


## 📦 Visual Studio Configuration

1. **Download and extract SFML**  
   - Download the SFML SDK (ZIP file) from the [SFML Download Page](https://www.sfml-dev.org/download/)  
   - Extract it to your preferred location (e.g., `D:\libs\SFML-3.0.0`)  

2. **Configure Visual Studio**  
   In **Project's properties**, update the following paths:  

   - `C/C++ > General > Additional Include Directories` → `"<sfml-install-path>/include"`  
   - `Linker > General > Additional Library Directories` → `"<sfml-install-path>/lib"`  
   - `Linker > Input > Additional Dependencies` → Add `"sfml-graphics.lib"`, `"sfml-window.lib"`, `"sfml-system.lib"`  

3. **Need help setting up SFML?**  
   Check out my **SFML Visual Studio Template** for a preconfigured project: [SFML-VS-Template](https://github.com/g-brrzzn/SFML-VS-Template)

## 🛠️ Requirements  

- C++17  
- SFML 3.0+  
- Visual Studio
