#pragma once
//STL
#include <iostream>
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable> 
//external
#include <opencv2/opencv.hpp>
//project include
#include "IQueueFrame.h"

/**
 * @brief Queue for storing frames
 */
namespace queue
{
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
		//{
		void push(cv::Mat& frame) override;
		cv::Mat front() override;
		size_t size() const override { return _queueFrame.size(); };
		bool empty() const override;
		//}
	};
}
