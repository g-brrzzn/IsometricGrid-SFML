# 🗺️ IsometricGrid-SFML

A C++ 2D isometric grid application using SFML that features a dynamic camera system to navigate through an isometric map, showcasing an integration of grid layout, map structure, camera movement, and rendering culling. This technical demo builds upon previous work by exploring these features in an isometric perspective, offering a robust foundation for further experimentation.

## 🎥 Demonstration  
Example image showcasing an isometric layout with randomly generated tiles and dynamic camera control.  
![isometric2](https://github.com/user-attachments/assets/872275c6-f3eb-4d86-afb9-6e4f4089b7fc)
![isometric1](https://github.com/user-attachments/assets/522c33e8-7ae0-4555-a152-323bc05d9119)
![isometric3](https://github.com/user-attachments/assets/b038ae4f-c140-4692-86cd-5e6b57acf730)


## 🚀 Usage  
- **Navigate the Map:** Use the camera controls to explore the isometric grid.
- **Refresh the Grid:** Press **R** to regenerate the grid with a new layout.
- Use **WASD** to move the camera and explore the grid.

## 📦 Installation  

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
