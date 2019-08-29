#include "MemcpyCv_gSLICr.hpp"
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
MemcpyCv_gSLICr::MemcpyCv_gSLICr(void)
{

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
MemcpyCv_gSLICr::~MemcpyCv_gSLICr(void)
{

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MemcpyCv_gSLICr::load_4Image_to_MatBGR_BGR(const gSLICr::UChar4Image* inimg, cv::Mat& outimg)
{
	TimeMeasure tm("load_4Image_to_MatBGR_BGR");
	const gSLICr::Vector4u* inimg_ptr = inimg->GetData(MEMORYDEVICE_CPU);

	for (int y = 0; y < inimg->noDims.y; y++)
		for (int x = 0; x < inimg->noDims.x; x++)
		{
			int idx = x + y * inimg->noDims.x;
			outimg.at<cv::Vec3b>(y, x)[0] = inimg_ptr[idx].b;
			outimg.at<cv::Vec3b>(y, x)[1] = inimg_ptr[idx].g;
			outimg.at<cv::Vec3b>(y, x)[2] = inimg_ptr[idx].r;
		}
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MemcpyCv_gSLICr::load_4Image_to_MatBGRA_BGRA(const gSLICr::UChar4Image* inimg, cv::Mat& outimg)
{
	TimeMeasure tm("load_4Image_to_MatBGR_BGR");
	const gSLICr::Vector4u* inimg_ptr = inimg->GetData(MEMORYDEVICE_CPU);

	for (int y = 0; y < inimg->noDims.y; y++)
		for (int x = 0; x < inimg->noDims.x; x++)
		{
			int idx = x + y * inimg->noDims.x;
			outimg.at<cv::Vec4b>(y, x)[0] = inimg_ptr[idx].b;
			outimg.at<cv::Vec4b>(y, x)[1] = inimg_ptr[idx].g;
			outimg.at<cv::Vec4b>(y, x)[2] = inimg_ptr[idx].r;
		}
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MemcpyCv_gSLICr::load_MatBGRA_to_4image_BGR(const cv::Mat& inimg, gSLICr::UChar4Image* outimg)
{
	TimeMeasure tm("load_MatBGRA_to_4image_BGR");
	gSLICr::Vector4u* outimg_ptr = outimg->GetData(MEMORYDEVICE_CPU);

	for (int y = 0; y < outimg->noDims.y; y++)
		for (int x = 0; x < outimg->noDims.x; x++)
		{
			int idx = x + y * outimg->noDims.x;
			outimg_ptr[idx].b = inimg.at<cv::Vec4b>(y, x)[0];
			outimg_ptr[idx].g = inimg.at<cv::Vec4b>(y, x)[1];
			outimg_ptr[idx].r = inimg.at<cv::Vec4b>(y, x)[2];
		}
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MemcpyCv_gSLICr::load_IplimageBGRA_to_4image_BGR(const IplImage* _inimg, gSLICr::UChar4Image * _outimg)
{
	TimeMeasure tm("load_IplimageBGRA_to_4image_BGR");
	gSLICr::Vector4u* outimg_ptr = _outimg->GetData(MEMORYDEVICE_CPU);
	const int nChs = _inimg->nChannels;
	for (int y = 0; y < _outimg->noDims.y; y++)
		for (int x = 0; x < _outimg->noDims.x; x++)
		{
			const int idx = x + y * _outimg->noDims.x;
			outimg_ptr[idx].b = CV_IMAGE_ELEM(_inimg, unsigned char, y, x * nChs + 0);
			outimg_ptr[idx].g = CV_IMAGE_ELEM(_inimg, unsigned char, y, x * nChs + 1);
			outimg_ptr[idx].r = CV_IMAGE_ELEM(_inimg, unsigned char, y, x * nChs + 2);
		}
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MemcpyCv_gSLICr::load_Iplimage4u_to_4image_4u(const IplImage * _inimg, gSLICr::UChar4Image * _outimg)
{
	TimeMeasure tm("load_Iplimage4u_to_4image_4u");
	gSLICr::Vector4u*	outimg_ptr	= _outimg->GetData(MEMORYDEVICE_CPU);
	char*				inimg_ptr = _inimg->imageData;
	const int src_SZ = _inimg->imageSize;
	const int dst_SZ = _outimg->dataSize*4;
	ASSERT(src_SZ == dst_SZ);
	memcpy(outimg_ptr,inimg_ptr,src_SZ);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MemcpyCv_gSLICr::load_4Image_to_MatBGRA_4u(const gSLICr::UChar4Image * _inimg, cv::Mat & _outimg)
{
	TimeMeasure tm("load_4Image_to_MatBGR_BGR");
	const gSLICr::Vector4u* inimg_ptr = _inimg->GetData(MEMORYDEVICE_CPU);
	uchar*				outimg_ptr = _outimg.ptr<uchar>(0);
	const int src_SZ = _inimg->dataSize*4;
	const int dst_SZ = _outimg.size().area()*_outimg.channels();
	ASSERT(src_SZ == dst_SZ);
	memcpy(outimg_ptr, inimg_ptr, src_SZ);

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MemcpyCv_gSLICr::load_4Image_to_MatBGRA_4u(const gSLICr::IntImage * _inimg, cv::Mat & _outimg)
{
	TimeMeasure tm("load_4Image_to_MatBGR_BGR");
	const int* inimg_ptr = _inimg->GetData(MEMORYDEVICE_CPU);
	uchar*				outimg_ptr = _outimg.ptr<uchar>(0);
	const int src_SZ = _inimg->dataSize * 4;

	const int dst_SZ = _outimg.size().area()*_outimg.channels()*_outimg.depth();
	
	ASSERT(src_SZ == dst_SZ);
	memcpy(outimg_ptr, inimg_ptr, src_SZ);

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
