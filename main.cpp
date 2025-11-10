#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

#include "job_thread.cpp" // includes everything (Encryptor + ThreadPool + JobQueue)

int main()
{
    string key;
    cout << "Enter encryption key: ";
    cin >> key;

    cout << "Enter files to encrypt (space separated, end with #): ";
    vector<string> files;
    string file;
    while (cin >> file && file != "#")
        files.push_back(file);

    if (files.empty())
    {
        cerr << "[Error] No files provided. Exiting." << endl;
        return 1;
    }
    // no. of threads equal to no of files
    int numThreads = files.size();

    // for holding jobs
    JobQueue queue;

    // created a thread pool to process jobs
    ThreadPool pool(numThreads, queue, key);

    // entered jobs into queue -> reference job str in job struct
    for (auto &f : files)
        queue.push({f, f + ".enc"});

    // indicate no more jobs will be added
    queue.setFinished();
    // start timer and processing
    // chrono for timing -> chrono is used for high resolution clock
    auto start = chrono::high_resolution_clock::now();
    // start thread pool
    pool.start();
    // join threads
    pool.join();
    // stop timer
    auto end = chrono::high_resolution_clock::now();

    // display duration
    double duration = chrono::duration<double>(end - start).count();
    cout << "✅ Encryption done in " << duration << " seconds!" << endl;

    cout << "\n=== Decryption Stage ===" << endl;
    Encryptor decryptor(key);
    for (auto &f : files)
    {
        string encFile = f + ".enc";
        string decFile = f + ".dec";
        decryptor.decryptFile(encFile, decFile);
    }

    cout << "\n✅ Decryption Complete. Files restored." << endl;
    return 0;
}
