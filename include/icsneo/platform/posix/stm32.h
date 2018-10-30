#ifndef __STM32_POSIX_H_
#define __STM32_POSIX_H_

#include "icsneo/communication/icommunication.h"
#include "icsneo/device/neodevice.h"
#include "icsneo/api/errormanager.h"
#include <chrono>
#include <stdint.h>

namespace icsneo {

class STM32 : public ICommunication {
public:
	STM32(device_errorhandler_t err, neodevice_t& forDevice) : device(forDevice), err(err) {}
	static std::vector<neodevice_t> FindByProduct(int product);

	bool open();
	bool isOpen();
	bool close();

private:
	neodevice_t& device;
	device_errorhandler_t err;
	int fd = -1;
	static constexpr neodevice_handle_t HANDLE_OFFSET = 10;

	void readTask();
	void writeTask();
};

}

#endif