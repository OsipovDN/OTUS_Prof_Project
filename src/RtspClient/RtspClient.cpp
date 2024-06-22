#include "RtspClient.h"

namespace client
{
	RtspClient* RtspClient::_client = nullptr;
	RtspClient::~RtspClient() {
		if (_client)
		{
			delete _client;
		}
	};
	RtspClient* RtspClient::getInstance()
	{
		if (_client == nullptr)
		{
			_client = new RtspClient();
		}
		return _client;
	}
	int RtspClient::addCapture(std::string& rtspUrl)
	{
		cv::VideoCapture capture(rtspUrl);
		if (!capture.isOpened())
		{
			std::cerr << "Error: Couldn't open the RTSP stream." << std::endl;
			return -1;
		}
		else
		{
			int id = _captors.size() + 1;
			sourceInfo src{ rtspUrl,"tratata" };
			_streamsInfo.insert(std::make_pair(id, src));
			_captors.emplace(id, std::move(capture));
			return id;
		}
	}

	void RtspClient::releaseCapture(int id)
	{
		_captors[id].release();
		_captors.erase(id);
	}

	void RtspClient::start(int id)
	{
		cv::Mat frame;
		std::string wiev = "Stream" + id;
		while (true)
		{
			_captors[id] >> frame;
			if (frame.empty())
			{
				std::cerr << "Error: Frame is empty." << std::endl;
				break;
			}

			cv::imshow(wiev, frame);
			if (cv::waitKey(1) == 'q')
			{
				break;
			}
		}
		releaseCapture(id);
		cv::destroyWindow(wiev);
	}
}