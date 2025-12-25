#pragma once

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>

struct Job
{
    std::string inputFile;
    std::string outputFile;
};

class JobQueue
{
public:
    void push(const Job &job);
    bool pop(Job &job);
    void setFinished();

private:
    std::queue<Job> queue_;
    std::mutex mtx_;
    std::condition_variable cv_;
    bool finished_ = false;
};

class ThreadPool
{
public:
    ThreadPool(int threads, JobQueue &queue, const std::string &key);

    void start();
    void join();

private:
    void worker(int id);

    int numThreads_;
    JobQueue &queue_;
    std::vector<std::thread> workers_;
    std::string key_;
};
