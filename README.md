# Build and Run Instructions

## 1. Clone the Repository
Clone the project repository to your local machine:
```bash
git clone <your-repository-url>
cd <your-repository-directory>


2. Install Dependencies
For Ubuntu/Debian:
bash
Copy
Edit
sudo apt update
sudo apt install build-essential cmake libopencv-dev
For Other Systems:
Refer to your system's package manager or manually download and install:

OpenCV
Cereal


3. Set Up the Project
bash
Copy
Edit
mkdir build
cd build
4. Run CMake
bash
Copy
Edit
cmake ..
If there are errors (e.g., missing OpenCV or Cereal), install the missing dependencies and re-run the command.

5. Build the Project
bash
Copy
Edit
make
6. Run the Program
bash
Copy
Edit
./reader
7. Additional Notes
Log File Location:
Ensure the log file specified in your program exists and is accessible:

cpp
Copy
Edit
std::string filename = "C:/Sensor_Logs/group1-2024-XX-YY-HH-MM-SS.log";
Update this path in your program or modify the program to accept it as a runtime argument.

OpenCV Display:
If cv::imshow doesn’t display images:

Verify you are running on a system with GUI support.
For headless systems, use a virtual display like Xvfb.
Example Full Commands
bash
Copy
Edit
git clone <your-repository-url>
cd <your-repository-directory>
mkdir build
cd build
cmake ..
make
./reader
Replace <your-repository-url> with your repository URL and <your-repository-directory> with your local directory name.

kotlin
Copy
Edit

Let me know if this format works for you!
