#pragma once
//STL
#include <iomanip>
//external
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
//project include
#include "QueueFrame.h"

namespace searcher
{
	class ObjectSearcher
	{

	private:
		std::shared_ptr<IQueueFrame> _queueFrame;
		cv::HOGDescriptor _hog;

	public:
		ObjectSearcher(std::shared_ptr<IQueueFrame> frameStraeam);
		void adjustRect(cv::Rect& rect) const;
		void startSearch();

	};
}

