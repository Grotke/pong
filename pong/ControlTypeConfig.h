#pragma once

#include <string>

/*Convenience struct to set whether a player is human or an AI. 
Generally passed between GUI and game loop.*/
struct ControlTypeConfig
{
	ControlTypeConfig(const std::string& p1, const std::string& p2) : p1ControlType(p1), p2ControlType(p2) {};
	std::string p1ControlType;
	std::string p2ControlType;
};
