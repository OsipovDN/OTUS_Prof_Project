#pragma once

class IQueueFrame
{
public:

	virtual void push(cv::Mat& frame) = 0;
	virtual cv::Mat front() = 0;
	virtual bool empty() const = 0;
	virtual size_t size() const = 0;
	virtual ~IQueueFrame() = default;
};