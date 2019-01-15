#pragma once
#include <SFML/Network.hpp>
#include "Component.h"
class NetworkComponent :
	public Component
{
public:
	enum class NetworkMode { Send, Receive };
	NetworkComponent(int parentId, NetworkMode mode);
	virtual void update(float secondsPassed);
	const NetworkMode & getMode() const;

private:
	NetworkMode mode;
	sf::UdpSocket socket;
	unsigned int nextPacketToSend = 0;
	unsigned int lastPacketReceived = -1;
	sf::IpAddress ipAddress;
	unsigned short port;
	void send();
	void receive();
};

