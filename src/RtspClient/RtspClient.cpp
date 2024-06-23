#include "RtspClient.h"

namespace client
{
	RtspClient* RtspClient::_client = nullptr;
	RtspClient::~RtspClient() {
		if (_client)
		{
			for (auto i = 0; i < _streams.size(); ++i)
				_streams[i].join();
			delete _client;
		}
	};
	RtspClient* RtspClient::getInstance(std::shared_ptr<IQueueFrame> queueFrame)
	{
		if (_client == nullptr)
		{
			_client = new RtspClient(queueFrame);
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
			SourceInfo src{ id, rtspUrl,"tratata" };
			_streamsInfo.push_back(src);
			_captors.emplace(id, std::move(capture));
			std::cout << "Create capture id: " << id << std::endl;
			return id;
		}
	}

	void RtspClient::releaseCapture(int id)
	{
		if (id != -1)
		{
			_captors[id].release();
			auto InfoIt = _streamsInfo.begin();
			while (InfoIt != _streamsInfo.end())
			{
				if (InfoIt->id == id)
				{
					_streamsInfo.erase(InfoIt);
					break;
				}
				InfoIt++;
			}
			_captors.erase(id);
		}
		else
		{
			for (auto capture : _captors)
				capture.second.release();
			_captors.clear();
			_streamsInfo.clear();
		}
	}
	void RtspClient::start(int id)
	{
		_streams.push_back(std::thread(&RtspClient::toStart, this, id));
	}
	void RtspClient::toStart(int id)
	{
		cv::Mat frame;
		
		while (true)
		{
			_captors[id] >> frame;
			if (frame.empty())
			{
				std::cerr << "Error: Frame is empty." << std::endl;
				continue;
			}
			_queueFrame->push(frame);
		}
		
	}
}