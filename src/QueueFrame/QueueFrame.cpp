#include "QueueFrame.h"

void QueueFrame::push(cv::Mat& frame)
{
	std::unique_lock<std::mutex> lg(_mut);
	_queueFrame.push(frame);
	_cond.notify_one();
}

cv::Mat QueueFrame::front()
{
	cv::Mat temp;
	std::unique_lock<std::mutex> lg(_mut);
	_cond.wait(lg,
		[this]() { return !_queueFrame.empty(); });
	temp = _queueFrame.front();
	_queueFrame.pop();
	return temp;
}

bool QueueFrame::empty() const { return _queueFrame.empty(); }



