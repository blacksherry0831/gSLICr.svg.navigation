/*----------------------------------------------------------------*/
#include "opencv_basic.h"
/*----------------------------------------------------------------*/
#include "TRAFFIC_SIGN_LIB/TrafficSignParam.hpp"
#include "TRAFFIC_SIGN_LIB/TrafficSignMethod.hpp"
#include "TRAFFIC_SIGN_LIB/TrafficSignTemplete.hpp"
/*----------------------------------------------------------------*/

/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void processTemplete()
{
	const std::string path_st = "X:\\ImageDataBase\\TrafficSignSample\\Template";
	
	TrafficSignParam param;
	param.setSampleTempletePath(path_st);

	TrafficSignTemplete temp;
	temp.setTrafficSignParam(&param);
	
	temp.SampleTempletePreprocess();

	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void loadTemplete()
{
	const std::string path = "X:\\ImageDataBase\\TrafficSignSample\\TrafficSignTemplate";

	const std::string path_st = "X:\\ImageDataBase\\TrafficSignSample\\Testing";

	TrafficSignParam param;
	param.setTempletePath(path);
	param.setSampleTestingPath(path_st);

	TrafficSignTemplete temp;
	temp.setTrafficSignParam(&param);
	
	std::vector<std::shared_ptr<TrafficSignProperty>> properties=temp.TempleteLoad();
	
	temp.TempleteSift(properties);

	temp.TempleteSave(properties); 

	temp.SampleTestingPreprocess(properties);
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void sift() 
{
	processTemplete();

	loadTemplete();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void processTempleteHu()
{
	const std::string path_st = "X:\\ImageDataBase\\TrafficSignSample\\Template";

	TrafficSignParam param;
	param.setSampleTempletePath(path_st);

	TrafficSignTemplete temp;
	
	temp.setTrafficSignParam(&param);

	temp.SampleTempletePreprocessHu();
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void loadTempleteHu()
{
	const std::string path = "X:\\ImageDataBase\\TrafficSignSample\\TrafficSignTemplate";

	const std::string path_st = "X:\\ImageDataBase\\TrafficSignSample\\Testing";

	TrafficSignParam param;
	param.setTempletePath(path);
	param.setSampleTestingPath(path_st);

	TrafficSignTemplete temp;
	temp.setTrafficSignParam(&param);

	std::vector<std::shared_ptr<TrafficSignPropertyHu>> properties = temp.TempleteLoadHu();

	temp.TempleteSaveHu(properties);

	temp.SampleTestingPreprocessHu(properties);


}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void Hu() 
{

	processTempleteHu();
	loadTempleteHu();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	Hu();
	return  0;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*-----------------------------------------------------------------*/