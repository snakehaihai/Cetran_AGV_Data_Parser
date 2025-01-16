# Build and Run Instructions

## 1. Clone the Repository
Clone the project repository to your local machine:
```bash
git clone https://github.com/snakehaihai/RS_Data_Collection_Code
cd RS_Data_Collection_Code
```

## 2. Install Dependencies

### For Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential cmake libopencv-dev
```

## 3. Set Up the Project
```bash
mkdir build
cd build
```

If there are errors (e.g., missing OpenCV or Cereal), install the missing dependencies and re-run the command.


## 4. Run CMake
```bash
cmake ..
```

## 5. Build the Project
```bash
make
```
## 6. Run the Program
```bash
./reader
```

## 7. Additional Notes

### Log File Location:
Ensure the log file specified in your program exists and is accessible:
```cpp
std::string filename = "C:/Sensor_Logs/group1-2024-XX-YY-HH-MM-SS.log";
```


cppUpdate this path in your program or modify the program to accept it as a runtime argument.

OpenCV Display:
If cv::imshow doesn’t display images:

Verify you are running on a system with GUI support.
For headless systems, use a virtual display like Xvfb.
