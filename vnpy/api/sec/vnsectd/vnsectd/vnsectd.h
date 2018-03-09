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
#include "DFITCSECTraderApi.h"

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
#define ONRSPSTOCKUSERPASSWORDUPDATE 6
#define ONRSPSTOCKENTRUSTORDER 7
#define ONRSPSTOCKWITHDRAWORDER 8
#define ONRSPSTOCKQRYENTRUSTORDER 9
#define ONRSPSTOCKQRYREALTIMETRADE 10
#define ONRSPSTOCKQRYSERIALTRADE 11
#define ONRSPSTOCKQRYPOSITION 12
#define ONRSPSTOCKQRYCAPITALACCOUNTINFO 13
#define ONRSPSTOCKQRYACCOUNTINFO 14
#define ONRSPSTOCKQRYSHAREHOLDERINFO 15
#define ONRSPSTOCKTRANSFERFUNDS 16
#define ONRSPSTOCKENTRUSTBATCHORDER 17
#define ONRSPSTOCKWITHDRAWBATCHORDER 18
#define ONRSPSTOCKCALCABLEENTRUSTQTY 19
#define ONRSPSTOCKCALCABLEPURCHASEETFQTY 20
#define ONRSPSTOCKQRYFREEZEFUNDSDETAIL 21
#define ONRSPSTOCKQRYFREEZESTOCKDETAIL 22
#define ONRSPSTOCKQRYTRANSFERSTOCKDETAIL 23
#define ONRSPSTOCKQRYTRANSFERFUNDSDETAIL 24
#define ONRSPSTOCKQRYSTOCKINFO 25
#define ONRSPSTOCKQRYSTOCKSTATICINFO 26
#define ONRSPSTOCKQRYTRADETIME 27
#define ONSTOCKENTRUSTORDERRTN 28
#define ONSTOCKTRADERTN 29
#define ONSTOCKWITHDRAWORDERRTN 30
#define ONRSPSOPUSERLOGIN 31
#define ONRSPSOPUSERLOGOUT 32
#define ONRSPSOPUSERPASSWORDUPDATE 33
#define ONRSPSOPENTRUSTORDER 34
#define ONRSPSOPGROUPSPLIT 35
#define ONRSPSOPQRYGROUPPOSITION 36
#define ONRSPSOPLOCKOUNLOCKSTOCK 37
#define ONRSPSOPWITHDRAWORDER 38
#define ONRSPSOPQRYENTRUSTORDER 39
#define ONRSPSOPQRYSERIALTRADE 40
#define ONRSPSOPQRYPOSITION 41
#define ONRSPSOPQRYCOLLATERALPOSITION 42
#define ONRSPSOPQRYCAPITALACCOUNTINFO 43
#define ONRSPSOPQRYACCOUNTINFO 44
#define ONRSPSOPQRYSHAREHOLDERINFO 45
#define ONRSPSOPCALCABLEENTRUSTQTY 46
#define ONRSPSOPQRYABLELOCKSTOCK 47
#define ONRSPSOPQRYCONTACTINFO 48
#define ONRSPSOPEXECTUEORDER 49
#define ONRSPSOPQRYEXECASSIINFO 50
#define ONRSPSOPQRYTRADETIME 51
#define ONRSPSOPQRYEXCHANGEINFO 52
#define ONRSPSOPQRYCOMMISSION 53
#define ONRSPSOPQRYDEPOSIT 54
#define ONRSPSOPQRYCONTRACTOBJECTINFO 55
#define ONSOPENTRUSTORDERRTN 56
#define ONSOPTRADERTN 57
#define ONSOPWITHDRAWORDERRTN 58
#define ONRSPFASLUSERLOGIN 59
#define ONRSPFASLUSERLOGOUT 60
#define ONRSPFASLQRYABLEFININFO 61
#define ONRSPFASLQRYABLESLOINFO 62
#define ONRSPFASLTRANSFERCOLLATERAL 63
#define ONRSPFASLDIRECTREPAYMENT 64
#define ONRSPFASLREPAYSTOCKTRANSFER 65
#define ONRSPFASLENTRUSTCRDTORDER 66
#define ONRSPFASLENTRUSTORDER 67
#define ONRSPFASLCALCABLEENTRUSTCRDTQTY 68
#define ONRSPFASLQRYCRDTFUNDS 69
#define ONRSPFASLQRYCRDTCONTRACT 70
#define ONRSPFASLQRYCRDTCONCHANGEINFO 71
#define ONRSPFASLTRANSFERFUNDS 72
#define ONRSPFASLQRYACCOUNTINFO 73
#define ONRSPFASLQRYCAPITALACCOUNTINFO 74
#define ONRSPFASLQRYSHAREHOLDERINFO 75
#define ONRSPFASLQRYPOSITION 76
#define ONRSPFASLQRYENTRUSTORDER 77
#define ONRSPFASLQRYSERIALTRADE 78
#define ONRSPFASLQRYREALTIMETRADE 79
#define ONRSPFASLQRYFREEZEFUNDSDETAIL 80
#define ONRSPFASLQRYFREEZESTOCKDETAIL 81
#define ONRSPFASLQRYTRANSFERFUNDSDETAIL 82
#define ONRSPFASLWITHDRAWORDER 83
#define ONRSPFASLQRYSYSTEMTIME 84
#define ONRSPFASLQRYTRANSFERREDCONTRACT 85
#define ONRSPFASLDESIRABLEFUNDSOUT 86
#define ONRSPFASLQRYGUARANTEEDCONTRACT 87
#define ONRSPFASLQRYUNDERLYINGCONTRACT 88
#define ONFASLENTRUSTORDERRTN 89
#define ONFASLTRADERTN 90
#define ONFASLWITHDRAWORDERRTN 91



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
class TdApi : public DFITCSECTraderSpi
{
private:
	DFITCSECTraderApi *api;				//API����
	thread *task_thread;				//�����߳�ָ�루��python���������ݣ�
	ConcurrentQueue<Task*> task_queue;	//�������

public:
	TdApi()
	{
		function0<void> f = boost::bind(&TdApi::processTask, this);
		thread t(f);
		this->task_thread = &t;
	};

	~TdApi()
	{
	};

	//-------------------------------------------------------------------------------------
	//API�ص�����
	//-------------------------------------------------------------------------------------
	/**
	* SEC-��������������Ӧ
	*/
	virtual void OnFrontConnected();
	/**
	* SEC-�������Ӳ�������Ӧ
	*/
	virtual void OnFrontDisconnected(int nReason) ;
	/**
	* SEC-��Ϣ֪ͨ
	*/
	virtual void OnRtnNotice(DFITCSECRspNoticeField *pNotice) ;
	/**
	* ERR-����Ӧ��
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ַ
	*/
	virtual void OnRspError(DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-��¼��Ӧ
	* @param pData:ָ�����ǿ�,�����û���¼��Ӧ��Ϣ�ṹ��ĵ�ַ,������¼����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ��������¼����ʧ��
	*/
	virtual void OnRspStockUserLogin(DFITCSECRspUserLoginField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-�ǳ���Ӧ
	* @param pData:ָ�����ǿ�,�����û��ǳ���Ӧ��Ϣ�ṹ��ĵ�ַ,�����ǳ�����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ�������ǳ�����ʧ��
	*/
	virtual void OnRspStockUserLogout(DFITCSECRspUserLogoutField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-���������Ӧ
	* @param pData:ָ�����ǿ�,�����û����������Ӧ��Ϣ�ṹ��ĵ�ַ,���������������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ�����������������ʧ��
	*/
	virtual void OnRspStockUserPasswordUpdate(DFITCSECRspPasswordUpdateField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-ί�б�����Ӧ
	* @param pData:ָ�����ǿ�,�����û�ί�б�����Ӧ��Ϣ�ṹ��ĵ�ַ,������������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ������ί�б�������ʧ��
	*/
	virtual void OnRspStockEntrustOrder(DFITCStockRspEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-ί�г�����Ӧ
	* @param pData:ָ�����ǿ�,�����û�ί�г�����Ӧ��Ϣ�ṹ��ĵ�ַ,������������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ������ί�г�������ʧ��
	*/
	virtual void OnRspStockWithdrawOrder(DFITCSECRspWithdrawOrderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-ί�в�ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û�ί�в�ѯ��Ӧ��Ϣ�ṹ��ĵ�ַ,������ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ������ί�в�ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspStockQryEntrustOrder(DFITCStockRspQryEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-ʵʱ�ɽ���ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û�ʵʱ�ɽ���ѯ��Ӧ��Ϣ�ṹ��ĵ�ַ,����ʵʱ�ɽ���ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ������ʵʱ�ɽ���ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspStockQryRealTimeTrade(DFITCStockRspQryRealTimeTradeField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-�ֱʳɽ���ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û��ֱʳɽ���ѯ��Ӧ��Ϣ�ṹ��ĵ�ַ,�����ֱʳɽ���ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ�������ֱʳɽ���ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspStockQrySerialTrade(DFITCStockRspQrySerialTradeField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-�ֲֲ�ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û��ֲֲ�ѯ��Ӧ��Ϣ�ṹ��ĵ�ַ,�����ֲֲ�ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ�������ֲֲ�ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspStockQryPosition(DFITCStockRspQryPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-�ʽ��˺Ų�ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û��ʽ��˺Ų�ѯ��Ӧ��Ϣ�ṹ��ĵ�ַ,�����ʽ��˺Ų�ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ�������ʽ��˺Ų�ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspStockQryCapitalAccountInfo(DFITCStockRspQryCapitalAccountField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-�����˺Ų�ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û������˺Ų�ѯ��Ӧ��Ϣ�ṹ��ĵ�ַ,���������˺Ų�ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ�����������˺Ų�ѯ����ʧ��
	*/
	virtual void OnRspStockQryAccountInfo(DFITCStockRspQryAccountField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-�ɶ��Ų�ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û��ɶ��Ų�ѯ��Ӧ��Ϣ�ṹ��ĵ�ַ,�����ɶ��Ų�ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ�������ɶ��Ų�ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspStockQryShareholderInfo(DFITCStockRspQryShareholderField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-�ʽ������Ӧ
	* @param pData:ָ�����ǿ�,�����û��ʽ������Ӧ��Ϣ�ṹ��ĵ�ַ,�������ʽ��������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ�������ʽ��������ʧ��
	*/
	virtual void OnRspStockTransferFunds(DFITCStockRspTransferFundsField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-����ί����Ӧ
	* @param pData:ָ�����ǿ�,�����û�����ί����Ӧ��Ϣ�ṹ��ĵ�ַ,��������ί������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ����������ί������ʧ��
	*/
	virtual void OnRspStockEntrustBatchOrder(DFITCStockRspEntrustBatchOrderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-����������Ӧ
	* @param pData:ָ�����ǿ�,�����û�����������Ӧ��Ϣ�ṹ��ĵ�ַ,����������������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ������������������ʧ��
	*/
	virtual void OnRspStockWithdrawBatchOrder(DFITCStockRspWithdrawBatchOrderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-�����ί��������Ӧ
	* @param pData:ָ�����ǿ�,�����û������ί��������Ӧ��Ϣ�ṹ��ĵ�ַ,���������ί����������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ�����������ί����������ʧ��
	*/
	virtual void OnRspStockCalcAbleEntrustQty(DFITCStockRspCalcAbleEntrustQtyField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-�����깺ETF������Ӧ
	* @param pData:ָ�����ǿ�,�����û������깺ETF������Ӧ��Ϣ�ṹ��ĵ�ַ,���������깺ETF��������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ�����������깺ETF��������ʧ��
	*/
	virtual void OnRspStockCalcAblePurchaseETFQty(DFITCStockRspCalcAblePurchaseETFQtyField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-�����ʽ���ϸ��ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û������ʽ���ϸ��ѯ��Ӧ��Ϣ�ṹ��ĵ�ַ,���������ʽ���ϸ��ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ�����������ʽ���ϸ��ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspStockQryFreezeFundsDetail(DFITCStockRspQryFreezeFundsDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-����֤ȯ��ϸ��ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û�����֤ȯ��ϸ��ѯ��Ӧ��Ϣ�ṹ��ĵ�ַ,��������֤ȯ��ϸ��ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ����������֤ȯ��ϸ��ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspStockQryFreezeStockDetail(DFITCStockRspQryFreezeStockDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-����֤ȯ��ϸ��ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û�����֤ȯ��ϸ��ѯ��Ӧ��Ϣ�ṹ��ĵ�ַ,��������֤ȯ��ϸ��ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ����������֤ȯ��ϸ��ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspStockQryTransferStockDetail(DFITCStockRspQryTransferStockDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-�����ʽ���ϸ��ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û������ʽ���ϸ��ѯ��Ӧ��Ϣ�ṹ��ĵ�ַ,���������ʽ���ϸ��ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ�����������ʽ���ϸ��ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspStockQryTransferFundsDetail(DFITCStockRspQryTransferFundsDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-֤ȯ��Ϣ��ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û�֤ȯ��Ϣ��ѯ��Ӧ��Ϣ�ṹ��ĵ�ַ,����֤ȯ��Ϣ��ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ������֤ȯ��Ϣ��ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspStockQryStockInfo(DFITCStockRspQryStockField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-֤ȯ��̬��Ϣ��ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û�֤ȯ��̬��Ϣ��ѯ��Ӧ��Ϣ�ṹ��ĵ�ַ,����֤ȯ��̬��Ϣ��ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ������֤ȯ��̬��Ϣ��ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspStockQryStockStaticInfo(DFITCStockRspQryStockStaticField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* STOCK-����ʱ���ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û�����ʱ���ѯ��Ӧ��Ϣ�ṹ��ĵ�ַ,��������ʱ���ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ�ṹ��ĵ�ַ����������ʱ���ѯ����ʧ��
	*/
	virtual void OnRspStockQryTradeTime(DFITCStockRspQryTradeTimeField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* STOCK-ί�лر���Ӧ
	* @param pData:����ί�лر��ṹ��ĵ�ַ
	*/
	virtual void OnStockEntrustOrderRtn(DFITCStockEntrustOrderRtnField * pData);
	/**
	* STOCK-�ɽ��ر���Ӧ
	* @param pData:���سɽ��ر��ṹ��ĵ�ַ
	*/
	virtual void OnStockTradeRtn(DFITCStockTradeRtnField * pData);
	/**
	* STOCK-�����ر���Ӧ
	* @param pData:���س����ر��ṹ��ĵ�ַ
	*/
	virtual void OnStockWithdrawOrderRtn(DFITCStockWithdrawOrderRtnField * pData);

	/**
	* SOP-��¼��Ӧ
	* @param pRspUserLogin:ָ�����ǿ�,�����û���¼��Ӧ��Ϣ�ṹ��ַ,������¼����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ��������¼����ʧ��
	*/
	virtual void OnRspSOPUserLogin(DFITCSECRspUserLoginField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* SOP-�ǳ���Ӧ
	* @param pData:ָ�����ǿ�,�����û��ǳ���Ӧ��Ϣ�ṹ��ַ,�����ǳ�����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ǳ�����ʧ��
	*/
	virtual void OnRspSOPUserLogout(DFITCSECRspUserLogoutField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* SOP-�û����������Ӧ
	* @param pData:ָ�����ǿ�,�����û����������Ӧ��Ϣ�ṹ��ַ,�����û������������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������û������������ʧ��
	*/
	virtual void OnRspSOPUserPasswordUpdate(DFITCSECRspPasswordUpdateField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* SOP-������Ӧ
	* @param pData:ָ�����ǿ�,�����û�������Ӧ��Ϣ�ṹ��ַ,������������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ��������������ʧ��
	*/
	virtual void OnRspSOPEntrustOrder(DFITCSOPRspEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* SOP-��ϲ��ί����Ӧ
	* @param pData:ָ�����ǿ�,�����û���Ӧ��Ϣ�ṹ��ַ,������ϲ��ί������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ��������ϲ��ί������ʧ��
	*/
	virtual void OnRspSOPGroupSplit(DFITCSOPRspEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* SOP-��ѯ�ͻ���ϳֲ���ϸ��Ӧ
	* @param pData:ָ�����ǿ�,�����û���ѯ�ͻ���ϳֲ���ϸ��Ӧ�ṹ��ַ,������ѯ�ͻ���ϳֲ���ϸ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ��������ѯ�ͻ���ϳֲ���ϸ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspSOPQryGroupPosition(DFITCSOPRspQryGroupPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-֤ȯ����������Ӧ
	* @param pData:ָ�����ǿ�,�����û�֤ȯ����������Ӧ��Ϣ�ṹ��ַ,����֤ȯ������������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ������֤ȯ������������ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspSOPLockOUnLockStock(DFITCSOPRspLockOUnLockStockField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-������Ӧ
	* @param pData:ָ�����ǿ�,�����û�������Ӧ��Ϣ�ṹ��ַ,������������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ��������������ʧ��
	*/
	virtual void OnRspSOPWithdrawOrder(DFITCSECRspWithdrawOrderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* SOP-ί�в�ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û�ί�в�ѯ��Ӧ��Ϣ�ṹ��ַ,����ί�в�ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ������ί�в�ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspSOPQryEntrustOrder(DFITCSOPRspQryEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-�ֱʳɽ���ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û��ֱʳɽ���ѯ��Ӧ��Ϣ�ṹ��ַ,�����ֱʳɽ���ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ֱʳɽ���ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspSOPQrySerialTrade(DFITCSOPRspQrySerialTradeField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-�ֲֲ�ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û��ֲֲ�ѯ��Ӧ��Ϣ�ṹ��ַ,�����ֲֲ�ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ֲֲ�ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspSOPQryPosition(DFITCSOPRspQryPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-�ͻ������ֲֲ�ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û��ͻ������ֲֲ�ѯ��Ӧ��Ϣ�ṹ��ַ,�����ͻ������ֲֲ�ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ������ֲֲ�ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspSOPQryCollateralPosition(DFITCSOPRspQryCollateralPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-�ͻ��ʽ��ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û��ͻ��ʽ��ѯ��Ӧ��Ϣ�ṹ��ַ,�����ͻ��ͻ��ʽ��ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ��ͻ��ʽ��ѯ����ʧ��
	*/
	virtual void OnRspSOPQryCapitalAccountInfo(DFITCSOPRspQryCapitalAccountField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* SOP-�ͻ���Ϣ��ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û��ͻ���Ϣ��ѯ��Ӧ��Ϣ�ṹ��ַ,�����ͻ��ͻ���Ϣ��ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ��ͻ���Ϣ��ѯ����ʧ��
	*/
	virtual void OnRspSOPQryAccountInfo(DFITCSOPRspQryAccountField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* SOP-�ɶ���Ϣ��ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û��ɶ���Ϣ��ѯ��Ӧ��Ϣ�ṹ��ַ,�����ͻ��ɶ���Ϣ��ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ��ɶ���Ϣ��ѯ����ʧ��
	*/
	virtual void OnRspSOPQryShareholderInfo(DFITCSOPRspQryShareholderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* SOP-��ί��������ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û���ί��������ѯ��Ӧ��Ϣ�ṹ��ַ,�����ͻ���ί��������ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ���ί��������ѯ����ʧ��
	*/
	virtual void OnRspSOPCalcAbleEntrustQty(DFITCSOPRspCalcAbleEntrustQtyField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* SOP-�ͻ�������֤ȯ��ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û��ͻ�������֤ȯ��ѯ��Ӧ��Ϣ�ṹ��ַ,�����ͻ��ͻ�������֤ȯ��ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ��ͻ�������֤ȯ��ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspSOPQryAbleLockStock(DFITCSOPRspQryAbleLockStockField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-��Ȩ��Լ�����ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û���Ȩ��Լ�����ѯ��Ӧ��Ϣ�ṹ��ַ,�����ͻ���Ȩ��Լ�����ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ���Ȩ��Լ�����ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspSOPQryContactInfo(DFITCSOPRspQryContactField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-ִ��ί����Ӧ
	* @param pData:ָ�����ǿ�,�����û�ִ��ί����Ӧ��Ϣ�ṹ��ַ,�����ͻ�ִ��ί������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ�ִ��ί������ʧ��
	*/
	virtual void OnRspSOPExectueOrder(DFITCSOPRspExectueOrderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* SOP-�ͻ���Ȩָ����Ϣ��ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û��ͻ���Ȩָ����Ϣ��ѯ��Ӧ��Ϣ�ṹ��ַ,�����ͻ��ͻ���Ȩָ����Ϣ��ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ��ͻ���Ȩָ����Ϣ��ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspSOPQryExecAssiInfo(DFITCSOPRspQryExecAssiInfoField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-��ѯ����ʱ����Ӧ
	* @param pData:ָ�����ǿ�,�����û���ѯ����ʱ����Ӧ��Ϣ�ṹ��ַ,�����ͻ���ѯ����ʱ������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ���ѯ����ʱ������ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspSOPQryTradeTime(DFITCSOPRspQryTradeTimeField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-��ȡ���н�����������Ӧ
	* @param pData:ָ�����ǿ�,�����û���ȡ���н�����������Ӧ��Ϣ�ṹ��ַ,�����ͻ���ȡ���н�������������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ���ȡ���н�������������ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspSOPQryExchangeInfo(DFITCSOPRspQryExchangeInfoField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-��ѯ�����Ѳ�����Ӧ
	* @param pData:ָ�����ǿ�,�����û���ѯ�����Ѳ�����Ӧ��Ϣ�ṹ��ַ,�����ͻ���ѯ�����Ѳ�������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ���ѯ�����Ѳ�������ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspSOPQryCommission(DFITCSOPRspQryCommissionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-��ѯ��֤���ʲ�����Ӧ
	* @param pData:ָ�����ǿ�,�����û���ѯ��֤���ʲ�����Ӧ��Ϣ�ṹ��ַ,�����ͻ���ѯ��֤���ʲ�������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ���ѯ��֤���ʲ�������ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspSOPQryDeposit(DFITCSOPRspQryDepositField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-��Ȩ�����Ϣ��ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û���Ȩ�����Ϣ��ѯ��Ӧ��Ϣ�ṹ��ַ,�����ͻ���Ȩ�����Ϣ��ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ���Ȩ�����Ϣ��ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspSOPQryContractObjectInfo(DFITCSOPRspQryContractObjectField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* SOP-ί�лر���Ӧ
	* @param pData:����ί�лر��ṹ��ĵ�ַ
	*/
	virtual void OnSOPEntrustOrderRtn(DFITCSOPEntrustOrderRtnField * pData);
	/**
	* SOP-�ɽ��ر���Ӧ
	* @param pData:���سɽ��ر��ṹ��ĵ�ַ
	*/
	virtual void OnSOPTradeRtn(DFITCSOPTradeRtnField * pData);
	/**
	* SOP-�����ر���Ӧ
	* @param pData:���س����ر��ṹ��ĵ�ַ
	*/
	virtual void OnSOPWithdrawOrderRtn(DFITCSOPWithdrawOrderRtnField * pData);

	/**
	* FASL-��¼��Ӧ
	* @param pData:ָ�����ǿ�,�����û�������ȯ��¼��Ӧ��Ϣ�ṹ��ַ,�����ͻ�������ȯ��¼����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ�������ȯ��¼����ʧ��
	*/
	virtual void OnRspFASLUserLogin(DFITCSECRspUserLoginField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-�ǳ���Ӧ
	* @param pData:ָ�����ǿ�,�����û�������ȯ�ǳ���Ӧ��Ϣ�ṹ��ַ,�����ͻ�������ȯ�ǳ�����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ�������ȯ�ǳ�����ʧ��
	*/
	virtual void OnRspFASLUserLogout(DFITCSECRspUserLogoutField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-�ͻ���������Ϣ��Ӧ
	* @param pData:ָ�����ǿ�,�����û��ͻ���������Ϣ��Ӧ��Ϣ�ṹ��ַ,�����ͻ��ͻ���������Ϣ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ��ͻ���������Ϣ����ʧ��
	*/
	virtual void OnRspFASLQryAbleFinInfo(DFITCFASLRspAbleFinInfoField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-�ͻ�����ȯ��Ϣ��Ӧ
	* @param pData:ָ�����ǿ�,�����û��ͻ�����ȯ��Ϣ��Ӧ��Ϣ�ṹ��ַ,�����ͻ��ͻ�����ȯ��Ϣ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ��ͻ�����ȯ��Ϣ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspFASLQryAbleSloInfo(DFITCFASLRspAbleSloInfoField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-�����ﻮת��Ӧ
	* @param pData:ָ�����ǿ�,�����û������ﻮת��Ӧ��Ϣ�ṹ��ַ,�����ͻ������ﻮת����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ������ﻮת����ʧ��
	*/
	virtual void OnRspFASLTransferCollateral(DFITCFASLRspTransferCollateralField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-ֱ�ӻ�����Ӧ
	* @param pData:ָ�����ǿ�,�����û�ֱ�ӻ�����Ӧ��Ϣ�ṹ��ַ,�����ͻ�ֱ�ӻ�������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ�ֱ�ӻ�������ʧ��
	*/
	virtual void OnRspFASLDirectRepayment(DFITCFASLRspDirectRepaymentField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-��ȯ��ת��Ӧ
	* @param pData:ָ�����ǿ�,�����û���ȯ��ת��Ӧ��Ϣ�ṹ��ַ,�����ͻ���ȯ��ת����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ���ȯ��ת����ʧ��
	*/
	virtual void OnRspFASLRepayStockTransfer(DFITCFASLRspRepayStockTransferField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-���ý�����Ӧ
	* @param pData:ָ�����ǿ�,�����û����ý�����Ӧ��Ϣ�ṹ��ַ,�����ͻ����ý�������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ����ý�������ʧ��
	*/
	virtual void OnRspFASLEntrustCrdtOrder(DFITCFASLRspEntrustCrdtOrderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-������ȯ������Ӧ
	* @param pData:ָ�����ǿ�,�����û�������ȯ������Ӧ��Ϣ�ṹ��ַ,�����ͻ�������ȯ��������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ�������ȯ��������ʧ��
	*/
	virtual void OnRspFASLEntrustOrder(DFITCFASLRspEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-���ÿ�ί��������ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û����ÿ�ί��������ѯ��Ӧ��Ϣ�ṹ��ַ,�����ͻ����ÿ�ί��������ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ����ÿ�ί��������ѯ����ʧ��
	*/
	virtual void OnRspFASLCalcAbleEntrustCrdtQty(DFITCFASLRspCalcAbleEntrustCrdtQtyField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-��ѯ�����ʽ���Ӧ
	* @param pData:ָ�����ǿ�,�����û���ѯ�����ʽ���Ӧ��Ϣ�ṹ��ַ,�����ͻ���ѯ�����ʽ�����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ���ѯ�����ʽ�����ʧ��
	*/
	virtual void OnRspFASLQryCrdtFunds(DFITCFASLRspQryCrdtFundsField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-���ú�Լ��Ϣ��Ӧ
	* @param pData:ָ�����ǿ�,�����û����ú�Լ��Ϣ��Ӧ��Ϣ�ṹ��ַ,�����ͻ����ú�Լ��Ϣ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ����ú�Լ��Ϣ����ʧ��
	*/
	virtual void OnRspFASLQryCrdtContract(DFITCFASLRspQryCrdtContractField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLat) ;
	/**
	* FASL-���ú�Լ�䶯��Ϣ��ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û����ú�Լ�䶯��Ϣ��ѯ��Ӧ��Ϣ�ṹ��ַ,�����ͻ����ú�Լ�䶯��Ϣ��ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ����ú�Լ�䶯��Ϣ��ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspFASLQryCrdtConChangeInfo(DFITCFASLRspQryCrdtConChangeInfoField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-�ʽ��ת��Ӧ
	* @param pData:ָ�����ǿ�,�����û��ʽ��ת��Ӧ��Ϣ�ṹ��ַ,�����ͻ��ʽ��ת����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ��ʽ��ת����ʧ��
	*/
	virtual void OnRspFASLTransferFunds(DFITCStockRspTransferFundsField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-�ͻ���Ϣ��ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û��ͻ���Ϣ��ѯ��Ӧ��Ϣ�ṹ��ַ,�����ͻ��ͻ���Ϣ��ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ��ͻ���Ϣ��ѯ����ʧ��
	*/
	virtual void OnRspFASLQryAccountInfo(DFITCStockRspQryAccountField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-�ͻ��ʽ��ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û��ͻ��ʽ��ѯ��Ӧ��Ϣ�ṹ��ַ,�����ͻ��ͻ��ʽ��ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ��ͻ��ʽ��ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspFASLQryCapitalAccountInfo(DFITCStockRspQryCapitalAccountField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-�ɶ���Ϣ��ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û��ɶ���Ϣ��ѯ��Ӧ��Ϣ�ṹ��ַ,�����ͻ��ɶ���Ϣ��ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ��ɶ���Ϣ��ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspFASLQryShareholderInfo(DFITCStockRspQryShareholderField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-�ֲֲ�ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û��ֲֲ�ѯ��Ӧ��Ϣ�ṹ��ַ,�����ͻ��ֲֲ�ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ��ֲֲ�ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspFASLQryPosition(DFITCStockRspQryPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-ί�в�ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û�ί�в�ѯ��Ӧ��Ϣ�ṹ��ַ,�����ͻ�ί�в�ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ�ί�в�ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspFASLQryEntrustOrder(DFITCStockRspQryEntrustOrderField * pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-�ֱʳɽ���ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û��ֱʳɽ���ѯ��Ӧ��Ϣ�ṹ��ַ,�����ͻ��ֱʳɽ���ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ��ֱʳɽ���ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspFASLQrySerialTrade(DFITCStockRspQrySerialTradeField * pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-ʵʱ�ɽ���ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û�ʵʱ�ɽ���ѯ��Ӧ��Ϣ�ṹ��ַ,�����ͻ�ʵʱ�ɽ���ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ�ʵʱ�ɽ���ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspFASLQryRealTimeTrade(DFITCStockRspQryRealTimeTradeField * pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-�ʽ𶳽���ϸ��ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û��ʽ𶳽���ϸ��ѯ��Ӧ��Ϣ�ṹ��ַ,�����ͻ��ʽ𶳽���ϸ��ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ��ʽ𶳽���ϸ��ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspFASLQryFreezeFundsDetail(DFITCStockRspQryFreezeFundsDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-֤ȯ������ϸ��ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û�֤ȯ������ϸ��ѯ��Ӧ��Ϣ�ṹ��ַ,�����ͻ�֤ȯ������ϸ��ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ�֤ȯ������ϸ��ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspFASLQryFreezeStockDetail(DFITCStockRspQryFreezeStockDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-�ʽ������ϸ��ѯ��Ӧ
	* @param pData:ָ�����ǿ�,�����û��ʽ������ϸ��ѯ��Ӧ��Ϣ�ṹ��ַ,�����ͻ��ʽ������ϸ��ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ��ʽ������ϸ��ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspFASLQryTransferFundsDetail(DFITCStockRspQryTransferFundsDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-������Ӧ
	* @param pData:ָ�����ǿ�,�����û�������Ӧ��Ϣ�ṹ��ַ,������������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ��������������ʧ��
	*/
	virtual void OnRspFASLWithdrawOrder(DFITCFASLRspWithdrawOrderField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-��ǰϵͳʱ���ѯ������Ӧ
	* @param pData:ָ�����ǿ�,�����û�ϵͳʱ���ѯ��Ӧ��Ϣ�ṹ��ַ,����ϵͳʱ���ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ������ϵͳʱ���ѯ����ʧ��
	*/
	virtual void OnRspFASLQrySystemTime(DFITCFASLRspQryTradeTimeField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-��ת�뵣��֤ȯ��ѯ������Ӧ
	* @param pData:ָ�����ǿ�,���ؿ�ת�뵣��֤ȯ��ѯ��Ӧ��Ϣ�ṹ��ַ,������ת�뵣��֤ȯ��ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ��������ת�뵣��֤ȯ��ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspFASLQryTransferredContract(DFITCFASLRspQryTransferredContractField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-�ͻ���ȡ�ʽ����������Ӧ
	* @param pData:ָ�����ǿ�,���ؿͻ���ȡ�ʽ������Ӧ��Ϣ�ṹ��ַ,�����ͻ���ȡ�ʽ��������ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ�������ͻ���ȡ�ʽ��������ʧ��
	*/
	virtual void OnRspFASLDesirableFundsOut(DFITCFASLRspDesirableFundsOutField *pData, DFITCSECRspInfoField *pRspInfo) ;
	/**
	* FASL-����֤ȯ��ѯ������Ӧ
	* @param pData:ָ�����ǿ�,���ص���֤ȯ��ѯ��Ӧ��Ϣ�ṹ��ַ,��������֤ȯ��ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ����������֤ȯ��ѯ����ʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspFASLQryGuaranteedContract(DFITCFASLRspQryGuaranteedContractField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-���֤ȯ��ѯ������Ӧ
	* @param pData:ָ�����ǿ�,���ر��֤ȯ��ѯ��Ӧ��Ϣ�ṹ��ַ,�������֤ȯ��ѯ����ɹ�
	* @param pRspInfo:ָ�����ǿգ����ش�����Ϣ��ַ���������֤ȯ��ѯʧ��
	* @param bIsLast:����ֵ�����Ƿ������һ����Ӧ��Ϣ(0-��,1-��)
	*/
	virtual void OnRspFASLQryUnderlyingContract(DFITCFASLRspQryUnderlyingContractField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast) ;
	/**
	* FASL-ί�лر���Ӧ
	* @param pData:����ί�лر��ṹ��ĵ�ַ
	*/
	virtual void OnFASLEntrustOrderRtn(DFITCStockEntrustOrderRtnField *pData);
	/**
	* FASL-�ɽ��ر���Ӧ
	* @param pData:���سɽ��ر��ṹ��ĵ�ַ
	*/
	virtual void OnFASLTradeRtn(DFITCStockTradeRtnField *pData);
	/**
	* FASL-�����ر���Ӧ
	* @param pData:���س����ر��ṹ��ĵ�ַ
	*/
	virtual void OnFASLWithdrawOrderRtn(DFITCStockWithdrawOrderRtnField *pData);

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

	void processRspStockUserPasswordUpdate(Task *task);

	void processRspStockEntrustOrder(Task *task);

	void processRspStockWithdrawOrder(Task *task);

	void processRspStockQryEntrustOrder(Task *task);

	void processRspStockQryRealTimeTrade(Task *task);

	void processRspStockQrySerialTrade(Task *task);

	void processRspStockQryPosition(Task *task);

	void processRspStockQryCapitalAccountInfo(Task *task);

	void processRspStockQryAccountInfo(Task *task);

	void processRspStockQryShareholderInfo(Task *task);

	void processRspStockTransferFunds(Task *task);

	void processRspStockEntrustBatchOrder(Task *task);

	void processRspStockWithdrawBatchOrder(Task *task);

	void processRspStockCalcAbleEntrustQty(Task *task);

	void processRspStockCalcAblePurchaseETFQty(Task *task);

	void processRspStockQryFreezeFundsDetail(Task *task);

	void processRspStockQryFreezeStockDetail(Task *task);

	void processRspStockQryTransferStockDetail(Task *task);

	void processRspStockQryTransferFundsDetail(Task *task);

	void processRspStockQryStockInfo(Task *task);

	void processRspStockQryStockStaticInfo(Task *task);

	void processRspStockQryTradeTime(Task *task);

	void processStockEntrustOrderRtn(Task *task);

	void processStockTradeRtn(Task *task);

	void processStockWithdrawOrderRtn(Task *task);

	void processRspSOPUserLogin(Task *task);

	void processRspSOPUserLogout(Task *task);

	void processRspSOPUserPasswordUpdate(Task *task);

	void processRspSOPEntrustOrder(Task *task);

	void processRspSOPGroupSplit(Task *task);

	void processRspSOPQryGroupPosition(Task *task);

	void processRspSOPLockOUnLockStock(Task *task);

	void processRspSOPWithdrawOrder(Task *task);

	void processRspSOPQryEntrustOrder(Task *task);

	void processRspSOPQrySerialTrade(Task *task);

	void processRspSOPQryPosition(Task *task);

	void processRspSOPQryCollateralPosition(Task *task);

	void processRspSOPQryCapitalAccountInfo(Task *task);

	void processRspSOPQryAccountInfo(Task *task);

	void processRspSOPQryShareholderInfo(Task *task);

	void processRspSOPCalcAbleEntrustQty(Task *task);

	void processRspSOPQryAbleLockStock(Task *task);

	void processRspSOPQryContactInfo(Task *task);

	void processRspSOPExectueOrder(Task *task);

	void processRspSOPQryExecAssiInfo(Task *task);

	void processRspSOPQryTradeTime(Task *task);

	void processRspSOPQryExchangeInfo(Task *task);

	void processRspSOPQryCommission(Task *task);

	void processRspSOPQryDeposit(Task *task);

	void processRspSOPQryContractObjectInfo(Task *task);

	void processSOPEntrustOrderRtn(Task *task);

	void processSOPTradeRtn(Task *task);

	void processSOPWithdrawOrderRtn(Task *task);

	void processRspFASLUserLogin(Task *task);

	void processRspFASLUserLogout(Task *task);

	void processRspFASLQryAbleFinInfo(Task *task);

	void processRspFASLQryAbleSloInfo(Task *task);

	void processRspFASLTransferCollateral(Task *task);

	void processRspFASLDirectRepayment(Task *task);

	void processRspFASLRepayStockTransfer(Task *task);

	void processRspFASLEntrustCrdtOrder(Task *task);

	void processRspFASLEntrustOrder(Task *task);

	void processRspFASLCalcAbleEntrustCrdtQty(Task *task);

	void processRspFASLQryCrdtFunds(Task *task);

	void processRspFASLQryCrdtContract(Task *task);

	void processRspFASLQryCrdtConChangeInfo(Task *task);

	void processRspFASLTransferFunds(Task *task);

	void processRspFASLQryAccountInfo(Task *task);

	void processRspFASLQryCapitalAccountInfo(Task *task);

	void processRspFASLQryShareholderInfo(Task *task);

	void processRspFASLQryPosition(Task *task);

	void processRspFASLQryEntrustOrder(Task *task);

	void processRspFASLQrySerialTrade(Task *task);

	void processRspFASLQryRealTimeTrade(Task *task);

	void processRspFASLQryFreezeFundsDetail(Task *task);

	void processRspFASLQryFreezeStockDetail(Task *task);

	void processRspFASLQryTransferFundsDetail(Task *task);

	void processRspFASLWithdrawOrder(Task *task);

	void processRspFASLQrySystemTime(Task *task);

	void processRspFASLQryTransferredContract(Task *task);

	void processRspFASLDesirableFundsOut(Task *task);

	void processRspFASLQryGuaranteedContract(Task *task);

	void processRspFASLQryUnderlyingContract(Task *task);

	void processFASLEntrustOrderRtn(Task *task);

	void processFASLTradeRtn(Task *task);

	void processFASLWithdrawOrderRtn(Task *task);

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

	virtual void onRspStockUserPasswordUpdate(dict data, dict error){};

	virtual void onRspStockEntrustOrder(dict data, dict error){};

	virtual void onRspStockWithdrawOrder(dict data, dict error){};

	virtual void onRspStockQryEntrustOrder(dict data, dict error, bool flag){};

	virtual void onRspStockQryRealTimeTrade(dict data, dict error, bool flag){};

	virtual void onRspStockQrySerialTrade(dict data, dict error, bool flag){};

	virtual void onRspStockQryPosition(dict data, dict error, bool flag){};

	virtual void onRspStockQryCapitalAccountInfo(dict data, dict error, bool flag){};

	virtual void onRspStockQryAccountInfo(dict data, dict error){};

	virtual void onRspStockQryShareholderInfo(dict data, dict error, bool flag){};

	virtual void onRspStockTransferFunds(dict data, dict error){};

	virtual void onRspStockEntrustBatchOrder(dict data, dict error){};

	virtual void onRspStockWithdrawBatchOrder(dict data, dict error){};

	virtual void onRspStockCalcAbleEntrustQty(dict data, dict error){};

	virtual void onRspStockCalcAblePurchaseETFQty(dict data, dict error){};

	virtual void onRspStockQryFreezeFundsDetail(dict data, dict error, bool flag){};

	virtual void onRspStockQryFreezeStockDetail(dict data, dict error, bool flag){};

	virtual void onRspStockQryTransferStockDetail(dict data, dict error, bool flag){};

	virtual void onRspStockQryTransferFundsDetail(dict data, dict error, bool flag){};

	virtual void onRspStockQryStockInfo(dict data, dict error, bool flag){};

	virtual void onRspStockQryStockStaticInfo(dict data, dict error, bool flag){};

	virtual void onRspStockQryTradeTime(dict data, dict error){};

	virtual void onStockEntrustOrderRtn(dict data){};

	virtual void onStockTradeRtn(dict data){};

	virtual void onStockWithdrawOrderRtn(dict data){};

	virtual void onRspSOPUserLogin(dict data, dict error){};

	virtual void onRspSOPUserLogout(dict data, dict error){};

	virtual void onRspSOPUserPasswordUpdate(dict data, dict error){};

	virtual void onRspSOPEntrustOrder(dict data, dict error){};

	virtual void onRspSOPGroupSplit(dict data, dict error){};

	virtual void onRspSOPQryGroupPosition(dict data, dict error, bool flag){};

	virtual void onRspSOPLockOUnLockStock(dict data, dict error, bool flag){};

	virtual void onRspSOPWithdrawOrder(dict data, dict error){};

	virtual void onRspSOPQryEntrustOrder(dict data, dict error, bool flag){};

	virtual void onRspSOPQrySerialTrade(dict data, dict error, bool flag){};

	virtual void onRspSOPQryPosition(dict data, dict error, bool flag){};

	virtual void onRspSOPQryCollateralPosition(dict data, dict error, bool flag){};

	virtual void onRspSOPQryCapitalAccountInfo(dict data, dict error){};

	virtual void onRspSOPQryAccountInfo(dict data, dict error){};

	virtual void onRspSOPQryShareholderInfo(dict data, dict error){};

	virtual void onRspSOPCalcAbleEntrustQty(dict data, dict error){};

	virtual void onRspSOPQryAbleLockStock(dict data, dict error, bool flag){};

	virtual void onRspSOPQryContactInfo(dict data, dict error, bool flag){};

	virtual void onRspSOPExectueOrder(dict data, dict error){};

	virtual void onRspSOPQryExecAssiInfo(dict data, dict error, bool flag){};

	virtual void onRspSOPQryTradeTime(dict data, dict error, bool flag){};

	virtual void onRspSOPQryExchangeInfo(dict data, dict error, bool flag){};

	virtual void onRspSOPQryCommission(dict data, dict error, bool flag){};

	virtual void onRspSOPQryDeposit(dict data, dict error, bool flag){};

	virtual void onRspSOPQryContractObjectInfo(dict data, dict error, bool flag){};

	virtual void onSOPEntrustOrderRtn(dict data){};

	virtual void onSOPTradeRtn(dict data){};

	virtual void onSOPWithdrawOrderRtn(dict data){};

	virtual void onRspFASLUserLogin(dict data, dict error){};

	virtual void onRspFASLUserLogout(dict data, dict error){};

	virtual void onRspFASLQryAbleFinInfo(dict data, dict error){};

	virtual void onRspFASLQryAbleSloInfo(dict data, dict error, bool flag){};

	virtual void onRspFASLTransferCollateral(dict data, dict error){};

	virtual void onRspFASLDirectRepayment(dict data, dict error){};

	virtual void onRspFASLRepayStockTransfer(dict data, dict error){};

	virtual void onRspFASLEntrustCrdtOrder(dict data, dict error){};

	virtual void onRspFASLEntrustOrder(dict data, dict error){};

	virtual void onRspFASLCalcAbleEntrustCrdtQty(dict data, dict error){};

	virtual void onRspFASLQryCrdtFunds(dict data, dict error){};

	virtual void onRspFASLQryCrdtContract(dict data, dict error, bool flag){};

	virtual void onRspFASLQryCrdtConChangeInfo(dict data, dict error, bool flag){};

	virtual void onRspFASLTransferFunds(dict data, dict error){};

	virtual void onRspFASLQryAccountInfo(dict data, dict error){};

	virtual void onRspFASLQryCapitalAccountInfo(dict data, dict error, bool flag){};

	virtual void onRspFASLQryShareholderInfo(dict data, dict error, bool flag){};

	virtual void onRspFASLQryPosition(dict data, dict error, bool flag){};

	virtual void onRspFASLQryEntrustOrder(dict data, dict error, bool flag){};

	virtual void onRspFASLQrySerialTrade(dict data, dict error, bool flag){};

	virtual void onRspFASLQryRealTimeTrade(dict data, dict error, bool flag){};

	virtual void onRspFASLQryFreezeFundsDetail(dict data, dict error, bool flag){};

	virtual void onRspFASLQryFreezeStockDetail(dict data, dict error, bool flag){};

	virtual void onRspFASLQryTransferFundsDetail(dict data, dict error, bool flag){};

	virtual void onRspFASLWithdrawOrder(dict data, dict error){};

	virtual void onRspFASLQrySystemTime(dict data, dict error){};

	virtual void onRspFASLQryTransferredContract(dict data, dict error, bool flag){};

	virtual void onRspFASLDesirableFundsOut(dict data, dict error){};

	virtual void onRspFASLQryGuaranteedContract(dict data, dict error, bool flag){};

	virtual void onRspFASLQryUnderlyingContract(dict data, dict error, bool flag){};

	virtual void onFASLEntrustOrderRtn(dict data){};

	virtual void onFASLTradeRtn(dict data){};

	virtual void onFASLWithdrawOrderRtn(dict data){};


	//-------------------------------------------------------------------------------------
	//req:���������������ֵ�
	//-------------------------------------------------------------------------------------

	void createDFITCSECTraderApi(string logAddr);

	void init(string svrAddr);

	void release();

	int exit();

	int subscribePrivateTopic(int type);

	int reqStockUserLogin(dict req);

	int reqStockUserLogout(dict req);

	int reqStockUserPasswordUpdate(dict req);

	int reqStockEntrustOrder(dict req);

	int reqStockWithdrawOrder(dict req);

	int reqStockQryEntrustOrder(dict req);

	int reqStockQryRealTimeTrade(dict req);

	int reqStockQrySerialTrade(dict req);

	int reqStockQryPosition(dict req);

	int reqStockQryCapitalAccountInfo(dict req);

	int reqStockQryAccountInfo(dict req);

	int reqStockQryShareholderInfo(dict req);

	int reqStockTransferFunds(dict req);

	int reqStockEntrustBatchOrder(dict req);

	int reqStockWithdrawBatchOrder(dict req);

	int reqStockCalcAbleEntrustQty(dict req);

	int reqStockCalcAblePurchaseETFQty(dict req);

	int reqStockQryFreezeFundsDetail(dict req);

	int reqStockQryFreezeStockDetail(dict req);

	int reqStockQryTransferFundsDetail(dict req);

	int reqStockQryTransferStockDetail(dict req);

	int reqStockQryStockInfo(dict req);

	int reqStockQryStockStaticInfo(dict req);

	int reqStockQryTradeTime(dict req);

	int reqSOPUserLogin(dict req);

	int reqSOPUserLogout(dict req);

	int reqSOPUserPasswordUpdate(dict req);

	int reqSOPEntrustOrder(dict req);

	int reqSOPGroupSplit(dict req);

	int reqSOPQryGroupPosition(dict req);

	int reqSOPLockOUnLockStock(dict req);

	int reqSOPWithdrawOrder(dict req);

	int reqSOPQryEntrustOrder(dict req);

	int reqSOPQrySerialTrade(dict req);

	int reqSOPQryPosition(dict req);

	int reqSOPQryCollateralPosition(dict req);

	int reqSOPQryCapitalAccountInfo(dict req);

	int reqSOPQryAccountInfo(dict req);

	int reqSOPQryShareholderInfo(dict req);

	int reqSOPCalcAbleEntrustQty(dict req);

	int reqSOPQryAbleLockStock(dict req);

	int reqSOPQryContactInfo(dict req);

	int reqSOPExectueOrder(dict req);

	int reqSOPQryExecAssiInfo(dict req);

	int reqSOPQryTradeTime(dict req);

	int reqSOPQryExchangeInfo(dict req);

	int reqSOPQryCommission(dict req);

	int reqSOPQryDeposit(dict req);

	int reqSOPQryContractObjectInfo(dict req);

	int reqFASLUserLogin(dict req);

	int reqFASLUserLogout(dict req);

	int reqFASLQryAbleFinInfo(dict req);

	int reqFASLQryAbleSloInfo(dict req);

	int reqFASLTransferCollateral(dict req);

	int reqFASLDirectRepayment(dict req);

	int reqFASLRepayStockTransfer(dict req);

	int reqFASLEntrustCrdtOrder(dict req);

	int reqFASLEntrsuctOrder(dict req);

	int reqFASLWithdrawOrder(dict req);

	int reqFASLCalcAbleEntrustCrdtQty(dict req);

	int reqFASLQryCrdtFunds(dict req);

	int reqFASLQryCrdtContract(dict req);

	int reqFASLQryCrdtConChangeInfo(dict req);

	int reqFASLTransferFunds(dict req);

	int reqFASLQryAccountInfo(dict req);

	int reqFASLQryCapitalAccountInfo(dict req);

	int reqFASLQryShareholderInfo(dict req);

	int reqFASLQryPosition(dict req);

	int reqFASLQryEntrustOrder(dict req);

	int reqFASLQrySerialTrade(dict req);

	int reqFASLQryRealTimeTrade(dict req);

	int reqFASLQryFreezeFundsDetail(dict req);

	int reqFASLQryFreezeStockDetail(dict req);

	int reqFASLQryTransferFundsDetail(dict req);

	int reqFASLQrySystemTime(dict req);

	int reqFASLQryTransferredContract(dict req);

	int reqFASLDesirableFundsOut(dict req);

	int reqFASLQryGuaranteedContract(dict req);

	int reqFASLQryUnderlyingContract(dict req);
};
