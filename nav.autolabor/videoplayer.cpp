﻿#include "videoplayer.h"
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
static int interrupt_cb(void *ctx)
{

	// do something 
	return 0;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
static const AVIOInterruptCB int_cb = { interrupt_cb, NULL };
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
VideoPlayer::VideoPlayer()
{
	videoStreamIdx = -1;
	this->init_param();
	this->initFFMPEG();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
VideoPlayer::VideoPlayer(const std::string _url)
{
	videoStreamIdx = -1;
	this->init_param();
	this->initFFMPEG();
	this->SetRtspUrl(_url);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
VideoPlayer::~VideoPlayer()
{
	freePlayModule();
	mThreadRun = 0;
	mDecodeLoop = 0;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
int VideoPlayer::Width()
{
	if (pCodecCtx == NULL){
		return 0;			
	}else{
		return pCodecCtx->width;
	}	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
int VideoPlayer::Height()
{
	if (pCodecCtx == NULL) {
		return 0;
	}else {
		return pCodecCtx->height;
	}
}
/*----------------------------------------------------------------*/
void VideoPlayer::startPlay()
{
	mDecodeLoop = 1;
	mThreadRun = 1;
    //调用 QThread 的start函数 将会自动执行下面的run函数 run函数是一个新的线程
    this->start();

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::AllocAvFrame()
{
	pFrame = av_frame_alloc();
	pFrameRGB32 = av_frame_alloc();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::FreeAvFrame()
{
	av_frame_free(&pFrame);
	av_frame_free(&pFrameRGB32);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::initPacket()
{
	pPacket = av_packet_alloc(); //分配一个packet
	const int y_size = Width() * Height();
	av_new_packet(pPacket, y_size); //分配packet的数
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::initAVDictionary()
{
	Q_ASSERT(pAVDic == NULL);	
	av_dict_set(&pAVDic, "max_delay", "500000", 0);
	av_dict_set(&pAVDic, "stimeout", "3000000", 0);//设置超时3秒
	av_dict_set(&pAVDic, "rtsp_transport", "tcp", 0);

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::initAVFormatContext()
{
	//分配一个avformatcontext
	pFormatCtx = avformat_alloc_context();  //FFMEG的所有操作均要通过avformatcontext进行

	pFormatCtx->interrupt_callback = int_cb;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
int VideoPlayer::openRtspStream()
{
		while (mThreadRun){

				const int result_t = avformat_open_input(&pFormatCtx, rtsp_url.c_str(), NULL, &pAVDic);
				this->mDecodeLoop = Success2True(result_t);
				if (result_t!=0){
					PrintConsole("can't open rtsp. ");
				}else{
					break;//success
				}
		}
		
		return this->mDecodeLoop;

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::findRtspStream()
{
	Q_ASSERT(pFormatCtx != NULL);
	//查数据流
	const int stream_info_s=avformat_find_stream_info(pFormatCtx, NULL);

	if (stream_info_s< 0) {
		PrintConsole("Could't find stream infomation.\n");
		mDecodeLoop = 0;
	}else{
			//循环查找视频中包含的流信息，直到找到视频类型的流
			//便将其记录下来 保存到videoStream变量中
			//这里我们现在只处理视频流  音频流先不管他
			for (int i = 0; (unsigned)i < pFormatCtx->nb_streams; i++) {
				if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
					videoStreamIdx = i;
				}
			}

			//如果videoStream为-1 说明没有找到视频流
			if (videoStreamIdx == -1) {
				PrintConsole("Didn't find a video stream.\n");
				mDecodeLoop = 0;
			}


	}
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::findRtspCodec()
{
	Q_ASSERT(videoStreamIdx != -1);
	//查找解码器
	pCodecCtx = pFormatCtx->streams[videoStreamIdx]->codec;
	
	///2017.8.9---lizhen
	pCodecCtx->bit_rate = 0;   //初始化为0
	pCodecCtx->time_base.num = 1;  //下面两行：一秒钟25帧
	pCodecCtx->time_base.den = 10;
	pCodecCtx->frame_number = 1;  //每包一个视频帧
	
	const  AVCodecID CODEC_ID = pCodecCtx->codec_id;
	
	if (AV_CODEC_ID_NONE != CODEC_ID) {
	
				pCodec = avcodec_find_decoder(CODEC_ID);
								  
				if (pCodec == NULL) {
					PrintConsole("Codec not found.\n");
					mDecodeLoop = 0;
				}else{
					//打开解码器
					if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
						PrintConsole("Could not open codec.\n");
						mDecodeLoop = 0;
					}
				}
	
	}else{
		Q_ASSERT(0);
		mDecodeLoop = 0;
	}
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::init_param()
{
	pFormatCtx=NULL;
	pCodecCtx = NULL;
	pCodec = NULL;
	pFrame = NULL;
	pFrameRGB32 = NULL;
	pPacket = NULL;
	pAVDic = NULL;
	this->mDecodeLoop = false;
	this->mThreadRun = true;
	this->rtsp_url = "rtsp://192.168.99.201/stream1";
	this->mFpsOut = 1;
	this->mFrameCount=0;
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::stopPlayModule()
{
	avcodec_close(pCodecCtx);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::initPlayModule()
{

	this->initAVDictionary();
	this->initAVFormatContext();
	const int status_t =this->openRtspStream() ;
	if (status_t) {
		this->findRtspStream();
		this->findRtspCodec();
		this->initPacket();
		mSwsContextSafe.SetSwsContextSrc(Width(), Height());
	}
	this->AllocAvFrame();
		
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::freePlayModule()
{
	avformat_close_input(&pFormatCtx);
	av_packet_free(&pPacket);
	av_dict_free(&pAVDic);
	
	this->FreeAvFrame();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::releasePlayModule()
{
	stopPlayModule();
	freePlayModule();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::initFFMPEG()
{
	avformat_network_init();   //初始化FFmpeg网络模块
	av_register_all();         //初始化FFMPEG  调用了这个才能正常适用编码器和解码器
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
int VideoPlayer::run_video_decode()
{
	 //读取视频的一帧，并保存值packet中
	int  got_picture;
	if (av_read_frame(pFormatCtx, pPacket) < 0){
		mDecodeLoop = 0;
	}else{
			if (pPacket->stream_index == videoStreamIdx) {
						const int ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, pPacket);   //视频解码
				    		if (ret < 0) {
											printf("decode error.\n");
											mDecodeLoop = 0;
							}else {	//视频解码后的数据格式为YUV420，这里将其转为rgb数据格式，利于保存为图片												
											if (got_picture) {
														if (IncFrameIsOut()) 
															this->emit_RGB32_QImage();
											}
							}										
				}
				av_packet_unref(pPacket); //释放资源,否则内存会一直上升
	}	
	return mDecodeLoop;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/

/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::run()
{
   
			while (mThreadRun){
									
					this->initPlayModule();
					
					while (IsLoopRun()){
						
						run_video_decode();

					}		

					this->releasePlayModule();

			}

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
int VideoPlayer::IncFrameIsOut()
{
	return (this->mFrameCount++ % frameInterval() == 0);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
int VideoPlayer::fpsOut1()
{
	SetOutputFps(1);
	return 0;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
int VideoPlayer::fpsOut5()
{
	SetOutputFps(5);
	return 0;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
int VideoPlayer::fpsOut10()
{
	SetOutputFps(10);
	return 0;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
int VideoPlayer::fpsOut25()
{
	SetOutputFps(25);
	return 0;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::stopPaly()
{
	mThreadRun = 0;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
int VideoPlayer::Success2True(const int& _t)
{
	if (_t==0){
		return 1;
	}else{
		return 0;
	}
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
int VideoPlayer::PrintConsole(std::string _log)
{
	IPrintQ::printf_event("video rtsp decoder : ",_log);

	return 0;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::emit_RGB32_QImage()
{
		int WidthScale =0;
		int HeightScale =0;

		mSwsContextSafe.GetDstSize(WidthScale, HeightScale);

		QSharedPointer<QImage> img_ptr= QSharedPointer<QImage>(new QImage (WidthScale, HeightScale, QImage::Format_RGB32));
				
		Q_ASSERT(dbg_is_equal(img_ptr->byteCount(),avpicture_get_size(AV_PIX_FMT_RGB32, WidthScale, HeightScale)));
		
		avpicture_fill((AVPicture *)pFrameRGB32, img_ptr->bits(), AV_PIX_FMT_RGB32, WidthScale, HeightScale);
			
		mSwsContextSafe.SwsContextScaleEx(pFrame, pFrameRGB32);

		//把这个RGB数据 用QImage加载
		emit sig_1_frame_RGB32_ref(img_ptr,QDateTime::currentDateTime() );  //发送信号	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
int VideoPlayer::frameInterval()
{

	double fps_raw = getFpsRaw();
	double fps_out = mFpsOut;
	int frame_interval = std::round( fps_raw / fps_out);
	return frame_interval;

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
int VideoPlayer::dbg_is_equal(const int _s1, const int _s2)
{
	return _s1==_s2;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
int VideoPlayer::IsLoopRun()
{
	return mThreadRun &&  mDecodeLoop;;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::SetScale(const int _w, const int _h)
{
	mSwsContextSafe.SetSwsContextDst(_w, _h);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::SetRtspUrl(std::string _url)
{
	this->rtsp_url = _url;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
double VideoPlayer::getFpsRaw()
{
	double framerate = av_q2d(pFormatCtx->streams[videoStreamIdx]->r_frame_rate);
	return framerate;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::SetOutputFps(const int _fps)
{
	this->mFpsOut = _fps;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
