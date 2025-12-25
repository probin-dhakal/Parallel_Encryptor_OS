# 🔐 Parallel File Encryptor (C++17, Multithreaded)

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](#)
[![Build With CMake](https://img.shields.io/badge/Build-CMake-informational.svg)](#)
[![OS Compatible](https://img.shields.io/badge/OS-Linux%20%7C%20Windows%20%7C%20Mac-black.svg)](#)


# 📌 Overview
  This project is a parallel file encryption and decryption system implemented in modern C++17, designed to apply operating system and concurrency concepts in practice.
  
  The system encrypts and decrypts multiple files concurrently using:
  
  A custom thread pool
  
  A thread-safe job queue
  
  Mutexes and condition variables
  
  Accurate performance benchmarking against a sequential baseline
  
  The project evolved iteratively by identifying real concurrency problems (output interleaving, synchronization overhead) and addressing them with measured, engineering-driven solutions.

---

## ✨ Features

| Feature | Description |
|--------|-------------|
| ✅ Parallel Encryption | Encrypts multiple files simultaneously using worker threads |
| 🔄 Thread-Safe Scheduling | Uses a synchronized job queue with mutex + condition variables |
| 🔑 Educational Cipher | Simple XOR logic for clarity and extendability |
| 📊 Performance Measurement | Displays accurate execution time |
| 🧱 Modular Architecture | Plug-and-play replacement for AES, ChaCha20, etc. |

---

## 📁 Project Structure

parallel_encryptor/
│
├── main.cpp
├── encryptor.cpp
├── job_thread.cpp
├── CMakeLists.txt
│
└── (input files: a.txt, b.txt, etc.)


---

## ⚙️ Build Instructions

### 1) Clone the Repository
```bash
git clone https://github.com/<your-username>/parallel_encryptor.git
cd parallel_encryptor

2) Create and Enter Build Directory
  mkdir build && cd build
3) Configure and Build
  cmake ..
  cmake --build .
  This produces an executable named: ./main


🚀 Usage

Place the input files (a.txt, b.txt, etc.) in the build directory, then run:
  ./main

Example Interaction

Enter encryption key: secret
Enter files to encrypt (space separated, end with #): a.txt b.txt #
[Thread 1] Encrypting a.txt -> a.txt.enc
[Thread 2] Encrypting b.txt -> b.txt.enc
✅ Encryption done in 0.041 seconds!

=== Decryption Stage ===
[Decrypted Data from a.txt.enc]: hey dude how are you
[Decrypted Data from b.txt.enc]: i am fine thank you

✅ Decryption Complete. Files restored.
Encrypted files are saved as:
  filename.txt.enc
Decrypted files are saved as:
  filename.txt.dec


🧠 How It Works

| Component    | Responsibility                                        |
| ------------ | ----------------------------------------------------- |
| `Encryptor`  | Reads/writes files, applies XOR encryption/decryption |
| `JobQueue`   | Thread-safe FIFO queue for task dispatch              |
| `ThreadPool` | Launches worker threads that process encryption jobs  |
| `main.cpp`   | Collects input, schedules tasks, measures performance |

Worker count = number of input files → maximized parallel throughput.

.

📜 License

  This project is licensed under the MIT License.
  You may freely use, modify, and distribute it for learning or personal use.

👤 Author

  Probin Dhakal
  📧 Email: probindhakal5@gmail.com

⭐ Support the Project

If this helped you in your OS or Systems Programming coursework:
⭐ Star the repository to support development!
