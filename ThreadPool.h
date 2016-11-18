#ifndef THREADPOOL_H
#define THREADPOOL_H
#include "JobQueue.h"

#include <thread>
#include <vector>

typedef std::shared_ptr<std::thread> ThreadPtr;
typedef std::vector<ThreadPtr> Threads;

class ThreadPool
{
public:
    ThreadPool(size_t p_size);
    ~ThreadPool();

    void start();
    void stop();
    void add(const Task & task, const PixelXY & pixel);
    int getTaskQueueSize() const;

private:
    void threadFunc();
    mutable JobQueue queue;
    Threads threads;
    size_t size;

    ThreadPool(const ThreadPool&);
    ThreadPool& operator=(const ThreadPool&);
};

#endif // THREADPOOL_H
