### Car Tracking Using OpenCV

#### Overview
This project demonstrates car tracking in a video using OpenCV and a Haar Cascade classifier for car detection. It utilizes the KCF (Kernelized Correlation Filters) tracker for tracking individual cars with there speed across frames.

#### Requirements
- OpenCV (version 2.x or higher)
- C++ compiler supporting C++11
- Cars.mp4 (video file containing cars for tracking)
- cars.xml (Haar Cascade classifier file for car detection)

#### Installation
1. **OpenCV**: Install OpenCV following the instructions for your operating system.
2. **C++ Compiler**: Ensure you have a C++ compiler that supports C++11.
3. **Video File**: Place the video file `Cars.mp4` in the project directory.
4. **Haar Cascade Classifier**: Download or generate `cars.xml` and place it in the project directory.

#### Usage
1. **Compile**: Compile the program using your C++ compiler. Example:
   ```bash
   g++ -std=c++11 car_tracking.cpp -o car_tracking `pkg-config --cflags --libs opencv`
   ```
2. **Run**: Execute the compiled binary:
   ```bash
   ./car_tracking
   ```
3. **Interact**: Press `ESC` to exit the program. The number of cars counted and their speeds are displayed in the console.

#### Example
- Below is a snapshot of car tracking in action:

  ![Car Tracking Example](https://github.com/Asazin007/CarDetectSpeedCount/blob/main/Car.jpg)

#### Notes
- Adjust parameters like `scale` for car detection sensitivity and region of interest (`detected_cars[i].y`) for specific areas.
- Customize the project further based on your requirements.

