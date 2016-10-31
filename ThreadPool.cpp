#include "ThreadPool.h"
#include <iostream>

ThreadPool::ThreadPool(size_t p_size) : size(p_size)
{

}

ThreadPool::~ThreadPool()
{
    stop();
}

void ThreadPool::start()
{
    if (!threads.empty())
    {
      throw std::runtime_error("ThreadPool started already");
    }

    std::string threadCreationError;
    for (size_t i = 0; (i < size) && threadCreationError.empty(); ++i)
    {
      try
      {
        auto funcCallable = std::bind(&ThreadPool::threadFunc, this);
        ThreadPtr newThread = std::make_shared<std::thread>(std::thread(funcCallable));
        threads.push_back(newThread);
      }
      catch (const std::exception e)
      {
        threadCreationError = e.what();
        break;
      }
    }

    if (!threadCreationError.empty())
    {
      std::cout << "ThreadPool thread creation error: " << threadCreationError << ", ThreadPool not started at all" << std::endl;
      throw std::runtime_error(threadCreationError);
    }
}

void ThreadPool::stop()
{
    for (auto job : threads)
    {
      (*job).join();
    }

    threads.clear();
}

void ThreadPool::add(const Task & task)
{
    queue.push(task);
}

void ThreadPool::threadFunc()
{
    while (1)
    {
      std::shared_ptr<Task> task = queue.waitForJob();
      (*task)();
    }
}
