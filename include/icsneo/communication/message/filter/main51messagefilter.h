#ifndef __MAIN51MESSAGEFILTER_H_
#define __MAIN51MESSAGEFILTER_H_

#include "icsneo/communication/message/filter/messagefilter.h"
#include "icsneo/communication/network.h"
#include "icsneo/communication/communication.h"
#include "icsneo/communication/message/main51message.h"
#include <memory>
#include <iostream>

namespace icsneo {

class Main51MessageFilter : public MessageFilter {
public:
	Main51MessageFilter() : MessageFilter(Network::NetID::Main51), command(INVALID_COMMAND) {}
	Main51MessageFilter(Command command) : MessageFilter(Network::NetID::Main51), command(command) {}

	bool match(const std::shared_ptr<Message>& message) const {
		if(!MessageFilter::match(message)) {
			//std::cout << "message filter did not match base for " << message->network << std::endl;
			return false;
		}
		const auto main51Message = std::dynamic_pointer_cast<Main51Message>(message);
		return main51Message && matchCommand(main51Message->command);
	}

private:
	static constexpr Command INVALID_COMMAND = (Command)0xff;
	Command command;
	bool matchCommand(Command mcommand) const {
		if(command == INVALID_COMMAND)
			return true;
		return command == mcommand;
	}
};

}

#endif