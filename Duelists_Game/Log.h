#pragma once
#include <iostream>
#include <vector>

//enmu is enummeration
enum LogType
{
	LOG_DEFAULT,
	LOG_INFO,// 0        THESE ARE LOG TYPES
	LOG_WARNING,//1
	LOG_ERROR //2
};

//Struct
struct LogEntry // its own type of variable container class or datatype  
{// this defines what the struct is
	LogType Type; // this is our ENUM
	std::string Message;


};

class Log
{
public:

	static std::vector<LogEntry> LogEntries;
	static void LogMessage(LogType Type, const std::string& Message);
	static void Separator();
	static void PrintLog(LogEntry& Entry);
	static void NewLine();
	
	
};
//Log::LogMessage(LOG_INFO "Character has perished" )