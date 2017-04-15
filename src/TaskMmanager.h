#ifndef _TASK_MANAGER_H_
#define _TASK_MANAGER_H_
#include <POCO\Mutex.h>
#include <Poco\Runnable.h>

//从pspace中读取报警数据并存到program类的成员变量中
class ReadAlarm: public Poco::Runnable
{
public:
	ReadAlarm(Poco::Mutex& mtx):_mtx_read(mtx)
	{
	}
	~ReadAlarm();
	void run();
private:
	Poco::Mutex& _mtx_read;
};

//将program类的成员变量读取报警数据并推送到指定的restful接口中
class PushAlarm: public Poco::Runnable
{
public:
	PushAlarm(Poco::Mutex& mtx):_mtx_push(mtx)
	{
	}
	~PushAlarm();
	void run();
private:
	Poco::Mutex& _mtx_push;
};

#endif	//_TASK_MANAGER_H_