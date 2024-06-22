#pragma once
//STL
#include <string>
#include <map>
#include <memory>

#include <opencv2/opencv.hpp>

#include"IQueueFrame.h"

/**
 * @brief The class of connection to the camera via the RTSP protocol
 */
namespace client
{
	class RtspClient
	{
		using CaptorsMap = std::map<int, cv::VideoCapture>;
		struct sourceInfo
		{
			std::string url;
			std::string data;
		};

	public:

		RtspClient(RtspClient&) = delete;
		void operator =(RtspClient&) = delete;
		~RtspClient();
		static RtspClient* getInstance();
		int addCapture(std::string& rtspUrl);
		void releaseCapture(int id);
		void start(int id);

	protected:
		RtspClient() {};
		static RtspClient* _client;

	private:

		std::shared_ptr<IQueueFrame> _queueFrame;
		CaptorsMap _captors;
		std::map<int, sourceInfo> _streamsInfo;
	};	
}