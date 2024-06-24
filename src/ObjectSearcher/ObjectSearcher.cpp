#include "ObjectSearcher.h"
namespace searcher
{
	ObjectSearcher::ObjectSearcher(std::shared_ptr<IQueueFrame> frameStraeam) :
		_queueFrame(frameStraeam),
		_hog()
	{
		_hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
	}

	void ObjectSearcher::adjustRect(cv::Rect& rect) const
	{
		rect.x += cvRound(rect.width * 0.1);
		rect.width = cvRound(rect.width * 0.8);
		rect.y += cvRound(rect.height * 0.07);
		rect.height = cvRound(rect.height * 0.8);
	}

	void ObjectSearcher::startSearch()
	{
		cv::Mat img;
		std::vector<cv::Rect> found;
		cv::Rect r;
		auto sc = cv::Scalar(0, 255, 0);
		for (;;)
		{
			img = _queueFrame->front();
			_hog.detectMultiScale(img, found, 0, cv::Size(8, 8), cv::Size(), 1.05, 2, false);;
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
			std::cout << _queueFrame->size() << std::endl;
		}
		cv::destroyWindow("People");
	}
}