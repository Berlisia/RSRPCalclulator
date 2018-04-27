#include "JobQueue.h"

void JobQueue::push(const Task task, const PixelXY & pixel)
{
    std::pair<Task, PixelXY> p(task, pixel);
    std::lock_guard<std::mutex> lk(mut);
    dataQueue.push(p);
    //dataCond.notify_one();
}

std::pair<Task, PixelXY> JobQueue::waitForJob()
{
    std::unique_lock<std::mutex> lk(mut);
    //dataCond.wait(lk,[this]{return !dataQueue.empty();});
    auto res = std::pair<Task, PixelXY>(Task(), PixelXY(0,0));
    if(!dataQueue.empty())
    {
        res = dataQueue.front();
        dataQueue.pop();
    }
    return res;
}

bool JobQueue::empty() const
{
    std::lock_guard<std::mutex> lk(mut);
    return dataQueue.empty();
}

int JobQueue::size() const
{
   std::unique_lock<std::mutex> lk(mut);
   return dataQueue.size();
}
