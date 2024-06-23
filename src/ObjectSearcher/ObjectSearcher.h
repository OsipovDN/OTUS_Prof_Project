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
		// Run the detector with default parameters. to get a higher hit-rate
		// (and more false alarms, respectively), decrease the hitThreshold and
		// groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
		std::vector<cv::Rect> found;
		_hog.detectMultiScale(img, found, 0, cv::Size(8, 8), cv::Size(), 1.05, 2, false);

		return found;
	}
	void adjustRect(cv::Rect& r) const
	{
		// The HOG detector returns slightly larger rectangles than the real objects,
		// so we slightly shrink the rectangles to get a nicer output.
		r.x += cvRound(r.width * 0.1);
		r.width = cvRound(r.width * 0.8);
		r.y += cvRound(r.height * 0.07);
		r.height = cvRound(r.height * 0.8);
	}

	void startSearch()
	{
		cv::Mat img;
		for (;;)
		{
			img = _queueFrame->front();
			if (img.empty())
			{
				std::cout << "Finished reading: empty frame" << std::endl;
				break;
			}

			std::vector<cv::Rect> found = detect(img);
			for (std::vector<cv::Rect>::iterator i = found.begin(); i != found.end(); ++i)
			{
				cv::Rect& r = *i;
				adjustRect(r);
				cv::rectangle(img, r.tl(), r.br(), cv::Scalar(0, 255, 0), 2);
			}
			cv::imshow("People", img);
			if (cv::waitKey(1) == 'q')
			{
				break;
			}

		}
		cv::destroyWindow("People");
	}

};

