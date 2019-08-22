/*----------------------------------------------------------------*/
#include "opencv_basic.h"
#include "cpp_def.h"
/*----------------------------------------------------------------*/
#include <SGV/SGV_Method.h>
#include <SGV/SGV_CFG_DBG.h>
#include <SGV/SGV_CFG_ARITHMETIC.h>
/*----------------------------------------------------------------*/

/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	int EXEC_RESULT = 0;

	QApplication a(argc, argv);
	{
		std::string file_name = "X:\\ImageDataBase\\1920.1080\\r.jpeg";
		//std::string file_name = "X:\\ImageDataBase\\640.480\\r.jpeg";
		
		SGV_Method::METHOD_FILE(file_name);
	
	}
	
	return  a.exec();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/