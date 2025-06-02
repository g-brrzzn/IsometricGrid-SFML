# 🗺️ IsometricGrid-SFML

A C++ 2D isometric grid application using SFML that features a dynamic camera system to navigate through an isometric map, showcasing an integration of grid layout, infinite world generation, chunk system, camera movement, and rendering culling. This technical demo builds upon previous work by exploring these features in an isometric perspective, offering a robust foundation for further experimentation.

## 🎥 Demonstration  
![demo1](https://github.com/user-attachments/assets/66fb2219-d74d-4632-bec4-ad71196c5298)
![demo2](https://github.com/user-attachments/assets/cfa0223f-8883-40d8-9866-30e18d61697f)

https://github.com/user-attachments/assets/0db2be88-87f5-426b-b0e5-aca779bfac3f

## 🚀 Usage  
- Use **WASD** to move the camera and explore the grid.
- **Refresh the Grid:** Press **R** to refresh the grid.

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
