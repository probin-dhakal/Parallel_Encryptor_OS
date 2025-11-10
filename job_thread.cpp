#include <queue>
#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <iostream>
using namespace std;

#include "encryptor.cpp" // include Encryptor class

// ==================================================
// Job structure
// ==================================================
struct Job
{
    string inputFile;
    string outputFile;
};

// ==================================================
// Thread-safe JobQueue
// ==================================================
class JobQueue
{
public:
    void push(const Job &job)
    {
        {
            lock_guard<mutex> lock(mtx_);
            queue_.push(job);
        }
        cv_.notify_one();
    }

    bool pop(Job &job)
    {
        unique_lock<mutex> lock(mtx_);
        while (queue_.empty() && !finished_)
            cv_.wait(lock); // wait until either queue has a job or finished_ is true

        if (queue_.empty())
            return false; // finished and no jobs left

        job = queue_.front();
        queue_.pop();
        return true;
    }

    void setFinished()
    {
        {
            lock_guard<mutex> lock(mtx_);
            finished_ = true;
        }
        cv_.notify_all();
    }

private:
    queue<Job> queue_;
    mutex mtx_;
    condition_variable cv_;
    bool finished_ = false;
};

// ==================================================
// ThreadPool for concurrent encryption
// ==================================================
class ThreadPool
{
public:
    ThreadPool(int numThreads, JobQueue &queue, const string &key)
        : numThreads_(numThreads), queue_(queue), key_(key) {}

    void start()
    {
        for (int i = 0; i < numThreads_; ++i)
            workers_.emplace_back(&ThreadPool::worker, this, i);
    }

    void join()
    {
        for (auto &t : workers_)
            if (t.joinable())
                t.join();
    }

private:
    void worker(int id)
    {
        Encryptor enc(key_);
        Job job;
        while (queue_.pop(job))
        {
            cout << "[Thread " << id + 1 << "] Encrypting "
                 << job.inputFile << " -> " << job.outputFile << endl;
            enc.encryptFile(job.inputFile, job.outputFile);
        }
    }

    int numThreads_;
    JobQueue &queue_;
    vector<thread> workers_;
    string key_;
};
