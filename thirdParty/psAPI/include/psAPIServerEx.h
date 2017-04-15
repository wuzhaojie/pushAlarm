#ifndef __PS_APISERVEREX_H__
#define __PS_APISERVEREX_H__

#include "psAPICommon.h"

/*
	��ͷ�ļ��ڲ�ר�ã������ⷢ�����ṩ�����ÿͻ������ͺ�����,��ʱ����
*/

#ifdef __cplusplus
extern "C"
{
#endif

	/* 
	<summary>
	[API] ����ʵʱ���ݿ�(�������ÿͻ������ͺ�����,��ʱ����)
	</summary>
	<param name="pszServer">
	�����ӵķ������������ַ
	֧��IP��ַ��DNS���ƣ����ؾݿ�����Ϊ"127.0.0.1"�� "localhost"
	�����Ҫָ���������˿ں�,�ڵ�ַ�����ð�ź���˿ں� ��192.168.0.1:8889
	���û��ָ���������˿ں�,ʹ��8889Ĭ�϶˿�
	</param>
	<param name="pszUserName">
	�û����� ��Сд���У�֧������
	</param>
	<param name="pszPassword">
	�û����� ��Сд���У��ո�����
	</param>
	<param name="pszAppName">
	�ͻ��˳������ƣ���������Ϊ�մ���PSNULL��û������ã��ṩ���¼���־��¼��ʱ��ʹ��
	</param>
	<param name="nAppType">
	PS_APPTYPE_ENUMӦ�ó������ͣ���ͬ���͵�Ӧ�ó��������е�Ȩ�޿��ܲ�һ��
	</param>
	<param name="nConnectTimeout">
	���ӳ�ʱʱ�䣬ʱ�䵥λΪ�� ,�����Ϊ0����Ĭ��ʱ��Ϊ10��
	</param>
	<param name="nExcuteTimeout">
	ִ�г�ʱʱ�䣬ʱ�䵥λΪ�� ,�����Ϊ0����Ĭ��ʱ��Ϊ10��
	</param>
	<param name="bUseProxy">
	�Ƿ�ʹ�ô�������ΪFALSE, ��ʱû���� 
	</param>
	<param name="phServer">
	����ɹ����򷵻����ݿ����Ӿ��
	</param>
	<returns>
	�ɹ�ʱ����PSRET_OK��ʧ��ʱ������Ӧ�Ĵ������
	</returns>
	<remarks>
		���psAPI_Server_Connect���ÿͻ������ͺ�����,��ʱ����
		ʹ��psAPI_Server_Connect�ͻ�������ΪPS_APPTYPE_USERCUSTOM,
			�ͻ�������Ϊ�մ�,ʹ��3����������ӳ�ʱ��3�������ִ�б�������ʱ
	</remarks> */
	PSDLL PSAPIStatus PSAPI psAPI_Server_ConnectEx(
		PSIN PSSTR pszServer,
		PSIN PSSTR pszUserName,
		PSIN PSSTR pszPassword,
		PSIN PSSTR pszAppName,
		PSIN PSUINT32 nAppType,
		PSIN PSUINT16 nConnectTimeout,
		PSIN PSUINT16 nExcuteTimeout,
		PSIN PSBOOL bUseProxy,
		PSOUT PSHANDLE *phServer
		);

#ifdef  __cplusplus
}
#endif

#endif	/* __PS_APISERVEREX_H__ */