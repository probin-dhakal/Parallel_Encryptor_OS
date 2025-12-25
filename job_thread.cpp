#include "job_thread.h"
#include "encryptor.h"
#include "config.h"

#include <iostream>

std::mutex coutMutex;

void JobQueue::push(const Job &job)
{
    {
        std::lock_guard<std::mutex> lock(mtx_);
        queue_.push(job);
    }
    cv_.notify_one();
}

bool JobQueue::pop(Job &job)
{
    std::unique_lock<std::mutex> lock(mtx_);
    cv_.wait(lock, [&]
             { return !queue_.empty() || finished_; });

    if (queue_.empty())
        return false;

    job = queue_.front();
    queue_.pop();
    return true;
}

void JobQueue::setFinished()
{
    {
        std::lock_guard<std::mutex> lock(mtx_);
        finished_ = true;
    }
    cv_.notify_all();
}

ThreadPool::ThreadPool(int threads, JobQueue &queue, const std::string &key)
    : numThreads_(threads), queue_(queue), key_(key) {}

void ThreadPool::start()
{
    for (int i = 0; i < numThreads_; ++i)
        workers_.emplace_back(&ThreadPool::worker, this, i);
}

void ThreadPool::join()
{
    for (auto &t : workers_)
        t.join();
}

void ThreadPool::worker(int id)
{
    Encryptor enc(key_);
    Job job;

    while (queue_.pop(job))
    {
        if (verbose)
        {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << "[Thread " << id + 1 << "] Encrypting "
                      << job.inputFile << "\n";
        }

        enc.encryptFile(job.inputFile, job.outputFile);

        if (verbose)
        {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << "[Thread " << id + 1 << "] Finished "
                      << job.outputFile << "\n";
        }
    }
}
