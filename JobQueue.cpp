#include "JobQueue.h"
using namespace std;

void JobQueue::push(Task task)
{
    lock_guard<mutex> lk(mut);
    dataQueue.push(task);
    dataCond.notify_one();
}

std::shared_ptr<Task> JobQueue::waitForJob()
{
    unique_lock<mutex> lk(mut);
    dataCond.wait(lk,[this]{return !dataQueue.empty();});
    shared_ptr<Task> res(make_shared<Task>(dataQueue.front()));
    dataQueue.pop();
    return res;
}

bool JobQueue::empty() const
{
    lock_guard<mutex> lk(mut);
    return dataQueue.empty();
}
