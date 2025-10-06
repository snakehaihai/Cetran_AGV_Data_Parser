# Cetran AGV Data Parser

This is the **deserializer and visualization tool** for AGV data collected from the NTU **CETRAN** center.
The raw data is serialized using the **Cereal** library and stored as `.log` files.
This program deserializes those logs, reconstructs the data, and optionally displays it with **OpenCV**.



<img width="948" height="504" alt="image" src="https://github.com/user-attachments/assets/9550f90a-49aa-4ba7-af95-0a97d0fa2f1a" />




---

## Build and Run Instructions

### 1. Clone the Repository

Clone the project repository to your local machine:

```bash
git clone https://github.com/snakehaihai/Cetran_AGV_Data_Parser
cd Cetran_AGV_Data_Parser
```

---

### 2. Install Dependencies

#### For Ubuntu / Debian:

```bash
sudo apt update
sudo apt install build-essential cmake libopencv-dev
```

#### Install Cereal (if not found)

Cereal is a header-only library.
You can install it easily with:

```bash
sudo apt install libcereal-dev
```

If that package is not available, clone it manually:

```bash
cd /usr/local/include
sudo git clone https://github.com/USCiLab/cereal.git
```

---

### 3. Set Up the Project

Create a new build folder and enter it:

```bash
mkdir build
cd build
```

If there are errors (e.g., missing OpenCV or Cereal),
install the missing dependencies and re-run the command.

---

### 4. Run CMake

```bash
cmake ..
```

If Cereal or OpenCV are not found automatically, specify the include path:

```bash
cmake -DCMAKE_INCLUDE_PATH=/usr/local/include ..
```

---

### 5. Build the Project

```bash
make
```

---

### 6. Run the Program

```bash
./reader
```

---

### 7. Additional Notes

#### Log File Location

Make sure the log file specified in your program exists and is accessible:

```cpp
std::string filename = "/path/to/your/log/group1-2024-XX-YY-HH-MM-SS.log";
```

You can also modify the program to accept this path as a runtime argument:

```bash
./reader /path/to/your/logfile.log
```

---

#### OpenCV Display

If `cv::imshow` does not display images:

* Verify you are running on a system with GUI support (X11 / Wayland).
* For headless servers, use a virtual display like **Xvfb**:

  ```bash
  sudo apt install xvfb
  xvfb-run ./reader
  ```

---

✅ **Summary**

* `libopencv-dev` → provides OpenCV headers and visualization support.
* `libcereal-dev` → provides Cereal headers for deserialization.
* Build steps follow standard `cmake` → `make` → `run` flow.
