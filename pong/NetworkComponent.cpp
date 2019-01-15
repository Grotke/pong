#include "ComponentManager.h"
#include "NetworkComponent.h"



NetworkComponent::NetworkComponent()
{
	socket.setBlocking(false);
	if(socket.bind(port, ipAddress) != sf::Socket::Done){
		//error
	}
}


NetworkComponent::~NetworkComponent()
{
}

void NetworkComponent::update(float secondsPassed) {
	if (mode == NetworkMode::Send) {
		send();
	}
	else {
		receive();
	}
}

void NetworkComponent::send() {
	sf::Packet packet;
	auto movement = ComponentManager::getMovementById(parentId);
	auto moveDirection = movement.getMoveDirection();
	packet << nextPacketToSend << moveDirection.x << moveDirection.y;
	nextPacketToSend++;
	socket.send(packet, ipAddress, port);
}

void NetworkComponent::receive() {
	sf::Packet packet;
	socket.receive(packet, ipAddress, port);
	unsigned int packetNumber;
	float x;
	float y;
	if (packet >> packetNumber >> x >> y) {
		if (packetNumber > lastPacketReceived) {
			auto movement = ComponentManager::getMovementById(parentId);
			movement.setMoveDirection(sf::Vector2f(x, y));
			lastPacketReceived = packetNumber;
		}
	}
	else {
		//error
	}
}
