#include "TimeMeasure.hpp"
/*-----------------------------------------*/
const std::string	TimeMeasure::mFile="TimeMweasure.dbg.txt";
int					TimeMeasure::mDebug=1;
int					TimeMeasure::mSave = 1;
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
TimeMeasure::TimeMeasure(std::string _event)
{
	if (mDebug) {
		this->start(_event);	
	}
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
TimeMeasure::TimeMeasure()
{
	this->IsTimeMeasure = FALSE;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
TimeMeasure::~TimeMeasure(void)
{
	if (mDebug) {
		if (this->IsTimeMeasure)
		{
			this->stop();
		}
	}

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void TimeMeasure::Write2File(std::string _msg)
{
	std::ofstream outfile;

	outfile.open(mFile,std::ios::app);
	
	if (outfile.is_open()){
		
		outfile << _msg << std::endl;
		outfile.close();

	}

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void TimeMeasure::start(std::string _event)
{
	mEVENT = _event;
#if _MSC_VER
	
	QueryPerformanceFrequency(&litmp);
	dfFreq = (double)litmp.QuadPart;// ��ü�������ʱ��Ƶ��
	QueryPerformanceCounter(&litmp);
	QPart1 = litmp.QuadPart;// ��ó�ʼֵ
							/////////////////////////////////////////////
#endif

#if TRUE
	start_time = clock();
#endif // TRUE

	
	this->IsTimeMeasure = TRUE;

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::string TimeMeasure::stop()
{
	std::string msg_t;
#if _MSC_VER
	///////////////////////////////////////////////
	QueryPerformanceCounter(&litmp);
	QPart2 = litmp.QuadPart;//�����ֵֹ
	dfMinus = (double)(QPart2 - QPart1);
	dfTim = dfMinus / dfFreq;// ��ö�Ӧ��ʱ��ֵ����λΪ��

	msg_t.append("TimeMeasure --> ")
		.append(mEVENT).append(" : ")
		.append(Base::float2str(dfTim * 1000)).append("(ms)");
#endif

#if defined(linux) || defined(__linux) || defined(__linux__) ||defined( __GNUC__)
	end_time = clock(); 
	dur = (double)(end_time - start_time);	

	msg_t.append("TimeMeasure --> ")
		.append(mEVENT).append(" : ")
		.append(Base::float2str(dur / CLOCKS_PER_SEC)).append("(ms)");

#endif

	this->IsTimeMeasure = FALSE;

	if (mDebug){

			std::cout << msg_t << std::endl;
			
			if (mSave)
			{
				Write2File(msg_t);
			}
			
	}

	return msg_t;

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void TimeMeasure::Config(const int _debug, const int _save)
{
	mDebug = _debug;
	mSave = _save;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/