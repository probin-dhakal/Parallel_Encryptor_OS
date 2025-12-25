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

    | Feature                   | Description                                                     |
    | ------------------------- | --------------------------------------------------------------- |
    | ⚡ Parallel Encryption     | Encrypts multiple files concurrently using worker threads       |
    | 🔄 Thread-Safe Scheduling | JobQueue implemented using mutex + condition variables          |
    | 🔐 Reversible Cipher      | XOR-based encryption for clarity and correctness                |
    | 📊 Benchmark Mode         | Measures clean parallel vs sequential performance               |
    | 🎓 Learning Mode          | Verbose, synchronized logging for understanding concurrency     |
    | 🧠 OS Concepts            | Demonstrates scheduling, synchronization, contention, I/O costs |

# 🧱 Architecture at a Glance
    main.cpp
     ├── Parses input & mode selection
     ├── Schedules jobs
     ├── Measures performance
     │
     ├── JobQueue
     │    ├── Thread-safe FIFO queue
     │    ├── Condition-variable based blocking
     │
     ├── ThreadPool
     │    ├── Fixed worker threads
     │    ├── Independent Encryptor per thread
     │
     └── Encryptor
          ├── Binary file I/O
          ├── XOR transformation
          └── Deterministic encryption/decryption

## 📁 Project Structure
    parallel_encryptor_os/
    │
    ├── main.cpp          # Program entry point & benchmarking logic
    ├── encryptor.h/.cpp  # Encryption & decryption logic
    ├── job_thread.h/.cpp # Thread pool and job queue
    ├── config.h/.cpp     # Global configuration (verbose mode)
    ├── CMakeLists.txt
    │
    └── build/             # Build output

## ⚙️ Build Instructions
  1️⃣ Clone the Repository
    git clone https://github.com/<your-username>/parallel_encryptor.git
    cd parallel_encryptor_os

  2️⃣ Configure & Build
    mkdir build
    cd build
    cmake ..
    cmake --build .
  This produces: 
    main.exe   (Windows)
  ./main     (Linux/macOS)

  # 🚀 Usage
     ./main

### 📊 Performance Benchmarking
 🔹 Small Files (Few KBs) -> Parallelism overhead dominates computation
   <img width="1160" height="499" alt="Screenshot 2025-12-25 145033" src="https://github.com/user-attachments/assets/d527728d-0bea-4266-a554-821e4c95e655" />

  Observed Result

            Parallel speedup ≈ 1.03×
            
            Nearly identical to sequential due to:
                Thread creation cost
                Scheduling overhead
                Minimal CPU work per file


  🔹 Large Files (~300,000 lines)
   <img width="1017" height="565" alt="Screenshot 2025-12-25 151222" src="https://github.com/user-attachments/assets/c8aba4ce-eda8-41bf-872b-270725acac26" />

   Observed Result

            Sequential: 13.89 seconds
            
            Parallel: 6.70 seconds
            
            Speedup: ~2.07×
            
            Why this matters
                Encryption becomes CPU-bound
                Thread overhead is amortized
                Parallelism meaningfully improves throughput

---
# 🧠 Why Two Modes Exist (Important Design Decision)
  ❌ Initial Problem

      Parallel encryption with logging caused:
          Interleaved output
          Unreadable encrypted data
      
      ✅ First Fix
      
          Introduced std::mutex for synchronized logging
          Output became correct
      
      ⚠️ New Issue
      
          Mutex contention severely reduced performance
          Benchmark results became misleading
      
      🧩 Final Solution
      
         Introduced two explicit modes:
         Learning Mode → correctness & visibility
         Benchmark Mode → performance accuracy

# 🧠 Concepts Demonstrated

      Thread pools vs task spawning
      Producer–consumer queues
      Condition-variable signaling
      Mutex contention costs
      I/O vs CPU-bound workloads
      Accurate benchmarking methodology
      Scalability limits of parallelism

# 🔐 Encryption Notes

    Uses XOR for educational clarity
    Easily replaceable with AES / ChaCha20
    Design intentionally keeps crypto logic isolated from threading logic

# 👤 Author

    Probin Dhakal
    📧 probindhakal5@gmail.com

# ⭐ Why This Project Matters

    This project is not just about encryption — it demonstrates:
    
        How concurrency problems emerge
        How performance tradeoffs are discovered
        How systems are iteratively improved
        How benchmarks must be interpreted correctly
        
    If you’re evaluating systems thinking, OS fundamentals, or engineering maturity, this project tells that story clearly.

# ⭐ Star the repository if it helped you learn or prepare for interviews.
