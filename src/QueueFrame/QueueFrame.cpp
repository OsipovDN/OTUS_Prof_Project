#include "QueueFrame.h"

void QueueFrame::push(cv::Mat& frame)
{
	std::unique_lock<std::mutex> lg(_mut);
	_queue.push(frame);
	_cond.notify_one();
}

cv::Mat QueueFrame::front()
{
	cv::Mat temp;
	std::unique_lock<std::mutex> lg(_mut);
	_cond.wait(lock,
		[this]() { return !_queue.empty(); });
	temp = _queue.front();
	_queue.pop();
	return temp;
}

bool QueueFrame::empty() const { return _queue.empty(); }

void QueueFrame::print(cv::Mat& c)const
{
}


