/*
 * Copyright (c) 2017, Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
#include <vector>
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

namespace OCLRT {
class Event;

class AsyncEventsHandler {
  public:
    AsyncEventsHandler();
    virtual ~AsyncEventsHandler();
    void registerEvent(Event *event);
    void closeThread();

  protected:
    Event *processList();
    void asyncProcess();
    MOCKABLE_VIRTUAL void openThread();
    MOCKABLE_VIRTUAL void transferRegisterList();
    std::vector<Event *> registerList;
    std::vector<Event *> list;
    std::vector<Event *> pendingList;

    std::unique_ptr<std::thread> thread;
    std::mutex asyncMtx;
    std::condition_variable asyncCond;
    std::atomic<bool> allowAsyncProcess;
};
} // namespace OCLRT
