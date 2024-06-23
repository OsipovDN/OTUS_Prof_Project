#pragma once
//STL
#include <string>
#include <map>
#include <memory>
#include <thread>

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
		struct SourceInfo
		{
			int				id;
			std::string		url;
			std::string		data;
		};

	public:

		RtspClient(RtspClient&) = delete;
		void operator =(RtspClient&) = delete;
		~RtspClient();

		static RtspClient* getInstance(std::shared_ptr<IQueueFrame> queueFrame);
		int addCapture(std::string& rtspUrl);
		void releaseCapture(int id=-1);
		void start(int id);
		void showAll()
		{
			cv::Mat frame;
			while (true) {
				for (auto capture : _captors)
				{
					if (capture.second.read(frame))
					{
						cv::imshow("RTSP Stream " + std::to_string(capture.first), frame);
					}
				}
				if (cv::waitKey(1) == 'q')
				{
					break;
				}
			}
			releaseCapture();
			cv::destroyAllWindows();
		}

	protected:
		RtspClient(std::shared_ptr<IQueueFrame> queueFrame):_queueFrame(queueFrame){};

		static RtspClient* _client;

	private:
		void toStart(int id);

		std::shared_ptr<IQueueFrame>	_queueFrame;
		CaptorsMap						_captors;
		std::list<SourceInfo>			_streamsInfo;
		std::vector<std::thread>		_streams;
	};
}