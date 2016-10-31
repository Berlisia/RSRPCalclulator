#ifndef JOBQUEUE_H
#define JOBQUEUE_H

#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <string>

typedef std::function<void()> Task;

class JobQueue
{
public:
    void push(Task task);
    std::shared_ptr<Task> waitForJob();
    bool empty() const;

private:
    mutable std::mutex mut;
    std::queue<Task> dataQueue;
    std::condition_variable dataCond;
};

#endif // JOBQUEUE_H
