#pragma once
#include <iomanip>

#include "QueueFrame.h"

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

class ObjectSearcher
{
private:

	std::shared_ptr<IQueueFrame> _queueFrame;
	cv::HOGDescriptor _hog;
public:
	ObjectSearcher(std::shared_ptr<IQueueFrame> frameStraeam) :
		_queueFrame(frameStraeam),
		_hog()
	{
		_hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
	};

	std::vector<cv::Rect> detect(cv::InputArray img)
	{
		std::vector<cv::Rect> found;
		_hog.detectMultiScale(img, found, 0, cv::Size(8, 8), cv::Size(), 1.05, 2, false);

		return found;
	}
	void adjustRect(cv::Rect& r) const
	{
		r.x += cvRound(r.width * 0.1);
		r.width = cvRound(r.width * 0.8);
		r.y += cvRound(r.height * 0.07);
		r.height = cvRound(r.height * 0.8);
	}

	void startSearch()
	{
		cv::Mat img;
		std::vector<cv::Rect> found;
		cv::Rect r;
		auto sc = cv::Scalar(0, 255, 0);
		for (;;)
		{
			img = _queueFrame->front();
			found = detect(img);
			if (!found.empty())
			{
				for (std::vector<cv::Rect>::iterator i = found.begin(); i != found.end(); ++i)
				{
					r = *i;
					adjustRect(r);
					cv::rectangle(img, r.tl(), r.br(), sc, 2);
				}
			}
			cv::imshow("People", img);
			if (cv::waitKey(1) == 'q')
			{
				break;
			}
			std::cout<<_queueFrame->size()<<std::endl;
		}
		cv::destroyWindow("People");
	}

};

