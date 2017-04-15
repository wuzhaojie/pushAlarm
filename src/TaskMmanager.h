#ifndef _TASK_MANAGER_H_
#define _TASK_MANAGER_H_
#include <POCO\Mutex.h>
#include <Poco\Runnable.h>

//��pspace�ж�ȡ�������ݲ��浽program��ĳ�Ա������
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

//��program��ĳ�Ա������ȡ�������ݲ����͵�ָ����restful�ӿ���
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