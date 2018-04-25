#ifndef THREADPOOL_H
#define THREADPOOL_H
#include "JobQueue.h"

#include <thread>
#include <vector>
#include <QObject>

typedef std::shared_ptr<std::thread> ThreadPtr;
typedef std::vector<ThreadPtr> Threads;

class ThreadPool : public QObject
{
    Q_OBJECT
signals:
    void broadcastDataSize(unsigned);
    void brodcastCurrentPogress(unsigned);

public:
    ThreadPool(size_t p_size);
    ~ThreadPool();

    void start();
    void stop();
    void add(const Task & task, const PixelXY & pixel);

private:
    void threadFunc();
    JobQueue queue;
    Threads threads;
    size_t size;

    ThreadPool(const ThreadPool&);
    ThreadPool& operator=(const ThreadPool&);
};

#endif // THREADPOOL_H
