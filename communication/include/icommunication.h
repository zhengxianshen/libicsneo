#ifndef __ICOMMUNICATION_H_
#define __ICOMMUNICATION_H_

#include <vector>
#include <chrono>
#include <atomic>
#include <thread>
#include "third-party/concurrentqueue/blockingconcurrentqueue.h"

namespace icsneo {

class ICommunication {
public:
	virtual ~ICommunication() {}
	virtual bool open() = 0;
	virtual bool isOpen() = 0;
	virtual bool close() = 0;
	virtual bool read(std::vector<uint8_t>& bytes, size_t limit = 0);
	virtual bool readWait(std::vector<uint8_t>& bytes, std::chrono::milliseconds timeout = std::chrono::milliseconds(100), size_t limit = 0);
	virtual bool write(const std::vector<uint8_t>& bytes);

protected:
	class WriteOperation {
	public:
		WriteOperation() {}
		WriteOperation(std::vector<uint8_t> b) { bytes = b; }
		std::vector<uint8_t> bytes;
	};
	enum IOTaskState {
		LAUNCH,
		WAIT
	};
	virtual void readTask() = 0;
	virtual void writeTask() = 0;
	moodycamel::BlockingConcurrentQueue<uint8_t> readQueue;
	moodycamel::BlockingConcurrentQueue<WriteOperation> writeQueue;
	std::thread readThread, writeThread;
	std::atomic<bool> closing{false};
};

};

#endif