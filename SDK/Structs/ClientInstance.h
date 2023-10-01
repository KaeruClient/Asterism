#pragma once
class ClientInstance {
public:
	class Actor* getLocalPlayer() {
		return (class Actor*)Utils::callVirtualTable<25, class Actor*>(this);
	};
};