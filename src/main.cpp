//STL
#include <iostream>
//project include
#include "RtspClient.h"
#include "QueueFrame.h"
#include "ObjectSearcher.h"

int main() {
	// RTSP stream URL
	std::string rtsp_url = "rtsp://192.168.1.206:8554/mjpeg/1";
	//Читаем из стрима данные
	auto queue= std::make_shared<queue::QueueFrame>() ;
	auto client = client::RtspClient::getInstance(queue);
	
	if (client == nullptr)
	{
		std::cerr << "Streams client not created" << std::endl;
		return -1;
	}
	auto id = client->addCapture(rtsp_url);
	if (id == -1)
	{
		std::cerr << "Stream is not created" << std::endl;
		return -1;
	}
	else
	{
		std::cout << "Stream with id= " << id << " created" << std::endl;
	}
	
	client->start(id);

	//Обрабатываем данные полученные из стрима
	searcher::ObjectSearcher searcher(queue);
	searcher.startSearch();
	client->releaseCapture();
	//client->showAll();
	return 0;
}

