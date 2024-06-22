#include <iostream>

#include "RtspClient.h"

int main() {
	// RTSP stream URL
	std::string rtsp_url = "rtsp://192.168.1.206:8554/mjpeg/1";
	auto client = client::RtspClient::getInstance();
	if (client == nullptr)
	{
		std::cerr << "Streams client not created"<< std::endl;
	}
	auto id = client->addCapture(rtsp_url);
	if(id==-1)
	{
		std::cerr<< "Stream is not created"<< std::endl;
	}
	else
	{
		std::cout << "Stream with id= " << id << " created" << std::endl;

		client->start(id);

		// Release the VideoCapture object and close the OpenCV windows
		
	}

	return 0;
}
