#pragma once
//STL
#include <iostream>
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable> 
//OpenCV
#include <opencv2/opencv.hpp>

#include "IQueueFrame.h"


/**
 * @brief Queue for storing frames
 */
class QueueFrame :public IQueueFrame
{
private:
	//Очередь сообщений для печати
	std::queue<cv::Mat> _queueFrame;

	std::condition_variable _cond;
	std::mutex _mut;

public:
	QueueFrame() { std::cout << __FUNCTION__ << std::endl; };
	QueueFrame(QueueFrame&) = delete;
	QueueFrame operator =(QueueFrame&) = delete;
	~QueueFrame() override { std::cout << __FUNCTION__ << std::endl; };

	//IQueue
	void push(cv::Mat& frame) override;
	cv::Mat front() override;
	bool empty() const override;
	//IQueue

	void print(cv::Mat& c)const;

};
