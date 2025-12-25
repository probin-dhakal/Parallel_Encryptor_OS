#include <iostream>
#include <vector>
#include <string>
#include <chrono>

#include "config.h"
#include "encryptor.h"
#include "job_thread.h"

using namespace std;

int main()
{
    int mode;
    cout << "Select mode:\n";
    cout << "0 → Benchmark mode\n";
    cout << "1 → Learning mode\n";
    cout << "Choice: ";
    cin >> mode;

    verbose = (mode == 1);

    string key;
    cout << "\nEnter encryption key: ";
    cin >> key;

    vector<string> files;
    cout << "Enter files (end with #): ";
    string f;
    while (cin >> f && f != "#")
        files.push_back(f);

    // ---------- PARALLEL ----------
    JobQueue queue;
    ThreadPool pool(files.size(), queue, key);

    for (auto &x : files)
        queue.push({x, x + ".enc"});

    queue.setFinished();

    auto pStart = chrono::high_resolution_clock::now();
    pool.start();
    pool.join();
    auto pEnd = chrono::high_resolution_clock::now();

    double parallelTime =
        chrono::duration<double>(pEnd - pStart).count();

    cout << "\nParallel encryption time: "
         << parallelTime << " seconds\n";

    // ---------- DECRYPT ----------
    Encryptor dec(key);
    for (auto &x : files)
        dec.decryptFile(x + ".enc", x + ".dec");

    // ---------- SEQUENTIAL ----------
    auto sStart = chrono::high_resolution_clock::now();
    Encryptor seqEnc(key);

    for (auto &x : files)
        seqEnc.encryptFile(x, x + ".seq.enc");

    auto sEnd = chrono::high_resolution_clock::now();

    double sequentialTime =
        chrono::duration<double>(sEnd - sStart).count();

    cout << "\nSequential encryption time: "
         << sequentialTime << " seconds\n";

    // ---------- COMPARISON ----------
    cout << "\n========================================\n";
    cout << " PERFORMANCE COMPARISON\n";
    cout << "========================================\n";
    cout << "Sequential : " << sequentialTime << " s\n";
    cout << "Parallel   : " << parallelTime << " s\n";
    cout << "Speedup    : "
         << sequentialTime / parallelTime << "x\n";
    cout << "========================================\n";
}
