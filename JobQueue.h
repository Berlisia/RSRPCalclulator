#ifndef JOBQUEUE_H
#define JOBQUEUE_H

#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <string>

#include "Core/PixelXY.h"

typedef std::function<void(PixelXY)> Task;

class JobQueue
{
public:
    void push(const Task task, const PixelXY&);
    std::pair<Task, PixelXY> waitForJob();
    bool empty() const;
    int size();

private:
    mutable std::mutex mut;
    std::queue<std::pair<Task, PixelXY>> dataQueue;
    //std::condition_variable dataCond;
};

#endif // JOBQUEUE_H
