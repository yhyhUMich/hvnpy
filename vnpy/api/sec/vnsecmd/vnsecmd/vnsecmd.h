//˵������

//ϵͳ
#include "stdafx.h"
#include <string>
#include <queue>

//Boost
#define BOOST_PYTHON_STATIC_LIB
#include <boost/python/module.hpp>	//python��װ
#include <boost/python/def.hpp>		//python��װ
#include <boost/python/dict.hpp>	//python��װ
#include <boost/python/object.hpp>	//python��װ
#include <boost/python.hpp>			//python��װ
#include <boost/thread.hpp>			//������е��̹߳���
#include <boost/bind.hpp>			//������е��̹߳���

//API
#include "DFITCSECMdApi.h"

//�����ռ�
using namespace std;
using namespace boost::python;
using namespace boost;

//����
#define ONFRONTCONNECTED 0
#define ONFRONTDISCONNECTED 1
#define ONRTNNOTICE 2
#define ONRSPERROR 3
#define ONRSPSTOCKUSERLOGIN 4
#define ONRSPSTOCKUSERLOGOUT 5
#define ONRSPSOPUSERLOGIN 6
#define ONRSPSOPUSERLOGOUT 7
#define ONRSPFASLUSERLOGIN 8
#define ONRSPFASLUSERLOGOUT 9
#define ONRSPSTOCKSUBMARKETDATA 10
#define ONRSPSTOCKUNSUBMARKETDATA 11
#define ONRSPSOPSUBMARKETDATA 12
#define ONRSPSOPUNSUBMARKETDATA 13
#define ONSTOCKMARKETDATA 14
#define ONSOPMARKETDATA 15
#define ONRSPSTOCKAVAILABLEQUOT 16
#define ONRSPSOPAVAILABLEQUOT 17
#define ONRSPUSERMDPASSWORDUPDATE 18


///-------------------------------------------------------------------------------------
///API�еĲ������
///-------------------------------------------------------------------------------------

//GILȫ�����򻯻�ȡ�ã�
//���ڰ���C++�̻߳��GIL�����Ӷ���ֹpython����
class PyLock
{
private:
	PyGILState_STATE gil_state;

public:
	//��ĳ�����������д����ö���ʱ�����GIL��
	PyLock()
	{
		gil_state = PyGILState_Ensure();
	}

	//��ĳ��������ɺ����ٸö���ʱ�����GIL��
	~PyLock()
	{
		PyGILState_Release(gil_state);
	}
};


//����ṹ��
struct Task
{
	int task_name;		//�ص��������ƶ�Ӧ�ĳ���
	void *task_data;	//���ݽṹ��
	void *task_error;	//����ṹ��
	int task_id;		//����
	bool task_last;		//�Ƿ�Ϊ��󷵻�
};


///�̰߳�ȫ�Ķ���
template<typename Data>

class ConcurrentQueue
{
private:
	queue<Data> the_queue;								//��׼�����
	mutable mutex the_mutex;							//boost������
	condition_variable the_condition_variable;			//boost��������

public:

	//�����µ�����
	void push(Data const& data)
	{
		mutex::scoped_lock lock(the_mutex);				//��ȡ������
		the_queue.push(data);							//������д�������
		lock.unlock();									//�ͷ���
		the_condition_variable.notify_one();			//֪ͨ���������ȴ����߳�
	}

	//�������Ƿ�Ϊ��
	bool empty() const
	{
		mutex::scoped_lock lock(the_mutex);
		return the_queue.empty();
	}

	//ȡ��
	Data wait_and_pop()
	{
		mutex::scoped_lock lock(the_mutex);

		while (the_queue.empty())						//������Ϊ��ʱ
		{
			the_condition_variable.wait(lock);			//�ȴ���������֪ͨ
		}

		Data popped_value = the_queue.front();			//��ȡ�����е����һ������
		the_queue.pop();								//ɾ��������
		return popped_value;							//���ظ�����
	}

};


//���ֵ��л�ȡĳ����ֵ��Ӧ������������ֵ������ṹ������ֵ��
void getInt(dict d, string key, int* value);

//���ֵ��л�ȡĳ����ֵ��Ӧ������������ֵ������ṹ������ֵ��
void getLong(dict d, string key, int* value);

//���ֵ��л�ȡĳ����ֵ��Ӧ�ĸ�����������ֵ������ṹ������ֵ��
void getDouble(dict d, string key, double* value);

//���ֵ��л�ȡĳ����ֵ��Ӧ���ַ���������ֵ������ṹ������ֵ��
void getString(dict d, string key, char* value);


///-------------------------------------------------------------------------------------
///C++ SPI�Ļص���������ʵ��
///-------------------------------------------------------------------------------------

//API�ļ̳�ʵ��
class MdApi : public DFITCSECMdSpi
{
private:
	DFITCSECMdApi *api;					//API����
	thread *task_thread;				//�����߳�ָ�루��python���������ݣ�
	ConcurrentQueue<Task*> task_queue;	//�������

public:
	MdApi()
	{
		function0<void> f = boost::bind(&MdApi::processTask, this);
		thread t(f);
		this->task_thread = &t;
	};

	~MdApi()
	{
	};

	//-------------------------------------------------------------------------------------
	//API�ص�����
	//-------------------------------------------------------------------------------------

	/**
	* ��������������Ӧ
	*/
	virtual void OnFrontConnected();

	/**
	* �������Ӳ�������Ӧ
	*/
	virtual void OnFrontDisconnected(int nReason);

	/**
	* SEC-��Ϣ֪ͨ
	*/
	virtual void OnRtnNotice(DFITCSECRspNoticeField *pNotice);

	/**
	* ERR-����Ӧ��
	* @param pRspInfo:������ʧ�ܣ����ش�����Ϣ��ַ
	*/
	virtual void OnRspError(struct DFITCSECRspInfoField *pRspInfo);

	/**
	* STOCK-��¼��Ӧ
	* @param pRspUserLogin:ָ�����ǿ�,�����û���¼��Ӧ��Ϣ�ṹ��ַ,������¼����ɹ�
	* @param pRspInfo::ָ�����ǿգ����ش�����Ϣ��ַ��������¼����ʧ��
	*/
	virtual void OnRspStockUserLogin(struct DFITCSECRspUserLoginField * pRspUserLogin, struct DFITCSECRspInfoField * pRspInfo);

	/**
	* STOCK-�ǳ���Ӧ
	* @param pRspUsrLogout:ָ�����ǿ�,�����û��ǳ���Ӧ��Ϣ�ṹ��ַ,�����ǳ�����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ǳ�����ʧ��
	*/
	virtual void OnRspStockUserLogout(struct DFITCSECRspUserLogoutField * pRspUsrLogout, struct DFITCSECRspInfoField * pRspInfo);

	/**
	* SOP-��¼��Ӧ
	* @param pRspUserLogin:ָ�����ǿ�,�����û���¼��Ӧ��Ϣ�ṹ��ַ,������¼����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ��������¼����ʧ��
	*/
	virtual void OnRspSOPUserLogin(struct DFITCSECRspUserLoginField * pRspUserLogin, struct DFITCSECRspInfoField * pRspInfo);

	/**
	* SOP-�ǳ���Ӧ
	* @param pRspUsrLogout:ָ�����ǿ�,�����û��ǳ���Ӧ��Ϣ�ṹ��ַ,�����ǳ�����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ǳ�����ʧ��
	*/
	virtual void OnRspSOPUserLogout(struct DFITCSECRspUserLogoutField * pRspUsrLogout, struct DFITCSECRspInfoField * pRspInfo);

	/**
	* FASL-��¼��Ӧ
	* @param pRspUserLogin:ָ�����ǿ�,�����û���¼��Ӧ��Ϣ�ṹ��ַ,������¼����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ��������¼����ʧ��
	*/
	virtual void OnRspFASLUserLogin(struct DFITCSECRspUserLoginField * pRspUserLogin, struct DFITCSECRspInfoField * pRspInfo);

	/**
	* FASL-�ǳ���Ӧ
	* @param pRspUsrLogout:ָ�����ǿ�,�����û��ǳ���Ӧ��Ϣ�ṹ��ַ,�����ǳ�����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ǳ�����ʧ��
	*/
	virtual void OnRspFASLUserLogout(struct DFITCSECRspUserLogoutField * pRspUsrLogout, struct DFITCSECRspInfoField * pRspInfo);

	/**
	* STOCK-���鶩����Ӧ
	* @param pSpecificInstrument:ָ�����ǿ�,�����û�ָ����Լ���鶩����Ӧ�ṹ��ַ,����ָ����Լ���鶩�ĳɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ������ָ����Լ���鶩��ʧ��
	*/
	virtual void OnRspStockSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo);

	/**
	* STOCK-ȡ������������Ӧ
	* @param pSpecificInstrument:ָ�����ǿ�,�����û�ָ����Լ����ȡ��������Ӧ�ṹ��ַ,����ָ����Լ����ȡ�����ĳɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ������ָ����Լ����ȡ������ʧ��
	*/
	virtual void OnRspStockUnSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo);

	/**
	* SOP-���鶩����Ӧ
	* @param pSpecificInstrument:ָ�����ǿ�,�����û�ָ����Լ���鶩����Ӧ�ṹ��ַ,����ָ����Լ���鶩�ĳɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ������ָ����Լ���鶩��ʧ��
	*/
	virtual void OnRspSOPSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo);

	/**
	* SOP-ȡ������������Ӧ
	* @param pSpecificInstrument:ָ�����ǿ�,�����û�ָ����Լ����ȡ��������Ӧ�ṹ��ַ,����ָ����Լ����ȡ�����ĳɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ������ָ����Լ����ȡ������ʧ��
	*/
	virtual void OnRspSOPUnSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo);

	/**
	* STOCK-����������Ӧ
	* @param pMarketDataField:ָ�����ǿ�,��������������Ӧ�ṹ��ַ
	*/
	virtual void OnStockMarketData(struct DFITCStockDepthMarketDataField * pMarketDataField);

	/**
	* SOP-����������Ӧ
	* @param pMarketDataField:ָ�����ǿ�,��������������Ӧ�ṹ��ַ
	*/
	virtual void OnSOPMarketData(struct DFITCSOPDepthMarketDataField * pMarketDataField);

	/**
	* STOCK-����������Ӧ
	* @param pAvailableQuotInfo:ָ�����ǿ�,���ؿ��õ�������Ϣ
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ������ָ����Լ����ȡ������ʧ��
	* @param flag  Ϊ���Ǳ�ʾ���һ����Ϊ��ʱ��ʾ���к�����
	*/
	virtual void OnRspStockAvailableQuot(struct DFITCRspQuotQryField * pAvailableQuotInfo, struct DFITCSECRspInfoField * pRspInfo, bool flag);

	/**
	* SOP-����������Ӧ
	* @param pAvailableQuotInfo:ָ�����ǿ�,���ؿ��õ�������Ϣ
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ������ָ����Լ����ȡ������ʧ��
	* @param flag  Ϊ���Ǳ�ʾ���һ����Ϊ��ʱ��ʾ���к�����
	*/
	virtual void OnRspSopAvailableQuot(struct DFITCRspQuotQryField * pAvailableQuotInfo, struct DFITCSECRspInfoField * pRspInfo, bool flag);

	/**
	* �������������Ӧ
	* @param pMDPasswordUpdate:ָ�����ǿ�,�����û�����������Ӧ��Ϣ�ṹ��ַ,���������޸ĳɹ���
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�����������޸�ʧ�ܡ�
	*/
	virtual void OnRspUserMDPasswordUpdate(struct DFITCSECRspMDPasswordUpdateField *pMDPasswordUpdate, struct DFITCSECRspInfoField * pRspInfo);

	//-------------------------------------------------------------------------------------
	//task������
	//-------------------------------------------------------------------------------------

	void processTask();

	void processFrontConnected(Task *task);

	void processFrontDisconnected(Task *task);

	void processRtnNotice(Task *task);

	void processRspError(Task *task);

	void processRspStockUserLogin(Task *task);

	void processRspStockUserLogout(Task *task);

	void processRspSOPUserLogin(Task *task);

	void processRspSOPUserLogout(Task *task);

	void processRspFASLUserLogin(Task *task);

	void processRspFASLUserLogout(Task *task);

	void processRspStockSubMarketData(Task *task);

	void processRspStockUnSubMarketData(Task *task);

	void processRspSOPSubMarketData(Task *task);

	void processRspSOPUnSubMarketData(Task *task);

	void processStockMarketData(Task *task);

	void processSOPMarketData(Task *task);

	void processRspStockAvailableQuot(Task *task);

	void processRspSopAvailableQuot(Task *task);

	void processRspUserMDPasswordUpdate(Task *task);

	//-------------------------------------------------------------------------------------
	//data���ص������������ֵ�
	//error���ص������Ĵ����ֵ�
	//flag���Ƿ�Ϊ��󷵻�
	//-------------------------------------------------------------------------------------

	virtual void onFrontConnected(){};

	virtual void onFrontDisconnected(int reason){};

	virtual void onRtnNotice(dict data){};

	virtual void onRspError(dict error){};

	virtual void onRspStockUserLogin(dict data, dict error){};

	virtual void onRspStockUserLogout(dict data, dict error){};

	virtual void onRspSOPUserLogin(dict data, dict error){};

	virtual void onRspSOPUserLogout(dict data, dict error){};

	virtual void onRspFASLUserLogin(dict data, dict error){};

	virtual void onRspFASLUserLogout(dict data, dict error){};

	virtual void onRspStockSubMarketData(dict data, dict error){};

	virtual void onRspStockUnSubMarketData(dict data, dict error){};

	virtual void onRspSOPSubMarketData(dict data, dict error){};

	virtual void onRspSOPUnSubMarketData(dict data, dict error){};

	virtual void onStockMarketData(dict data){};

	virtual void onSOPMarketData(dict data){};

	virtual void onRspStockAvailableQuot(dict data, dict error, bool flag){};

	virtual void onRspSopAvailableQuot(dict data, dict error, bool flag){};

	virtual void onRspUserMDPasswordUpdate(dict data, dict error){};


	//-------------------------------------------------------------------------------------
	//req:���������������ֵ�
	//-------------------------------------------------------------------------------------

	void createDFITCMdApi(string logAddr);

	void init(string svrAddr);

	void release();

	int exit();

	int subscribeStockMarketData(string instrumentID, int nRequestID);

	int unSubscribeStockMarketData(string instrumentID, int nRequestID);

	int subscribeSOPMarketData(string instrumentID, int nRequestID);

	int unSubscribeSOPMarketData(string instrumentID, int nRequestID);

	int reqStockUserLogin(dict req);

	int reqStockUserLogout(dict req);

	int reqSOPUserLogin(dict req);

	int reqFASLUserLogin(dict req);

	int reqSOPUserLogout(dict req);

	int reqFASLUserLogout(dict req);

	int reqStockAvailableQuotQry(dict req);

	int reqSopAvailableQuotQry(dict req);

	int reqUserMDPasswordUpdate(dict req);
};
