# Shiokaze
Shiokaze framework (Shiokaze) is an open-source fluid simulation solver for computer graphics. See http://research.nii.ac.jp/~rand/shiokaze-en/index.html for the full documentation.

# Build on Windows
This project is modified in order to be built on Windows using Visual Studio 2017. Some thirdparty libraries need to be built and installed, including
- Boost 1.70.0
- GLFW 3.3
- FreeGLUT 3.0.0
- GLEW 2.0.0
- GSL 2.5
- zlib 1.2.8
- TBB 4.4

Then the `gen.bat` can be run to build a VS2017 solution using CMake. Thirdparty installation paths must be specified properly in this file.

# Demos
To run the demos from command console, the `resources` folder needs to be copied to the folder contianing the built dlls and `launcher.exe`, which is the entry for all demos. In the following are some demo arguments. 

---
Empty window demo
```
launcher.exe
```
---
2D levelset liquid demo
```
launcher.exe Target=macliquid2 Name=dambreak2
```

