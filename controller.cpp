// AI-SG TESTING ONLY
#include "LogReader.h"
#include "ImageMessage.h"
bool runCam()
{
    const int numCameras = 5;

    std::vector<std::string> cameraIds(numCameras);
    cameraIds[0] = "DEV_000F31036107";//left fisheye
    cameraIds[1] = "DEV_000F31039323";//front left pinhole
    cameraIds[2] = "DEV_000F31039324";//front center pinhole
    cameraIds[3] = "DEV_000F31039325";//front right pinhole
    cameraIds[4] = "DEV_000F3103C81E";//right fisheye

    const int64_t cameraTimeToUTCOffset = static_cast<int64_t>(18 * 1.0e7);
    std::string filename = "/home/nuc/liufen/reader/group1-2025-01-08-14-57-10.log";//full path to where the log file is
    cereal_log::LogReader logReader;
    
    if (!logReader.openLog(filename))
    {
        std::cout << "Failed to open " << filename.c_str() << " for reading." << std::endl;
        return false;
    }
    int index=0;
    while (!logReader.eof())
    {
        std::string topic;
        cereal_log::Message::Ptr message;
        std::cout<< index << std::endl;
        index ++;
        if (logReader.read(topic, message))
        {
        std::cout << "Topic: " << topic << std::endl;
            if (topic ==  "DEV_000A4709857A") //cameraIds[0])//only interested in centre pinhole
            {
                cereal_log::ImageMessage::Ptr imageMessage = std::static_pointer_cast<cereal_log::ImageMessage>(message);
 		
                //note: image in GPS time in nanosecs. This is to convert to UTC time in 100 nanosecs
                int64_t tsUTC = imageMessage->timeStamp.getRelativeTime().count() / 100 - cameraTimeToUTCOffset;

                if (imageMessage->encoding.substr(0, 5) == "Bayer")
                {
                    cv::Mat imgTmp;
                    cv::Mat imgTmpSmall;

                    if (imageMessage->encoding == "BayerRG8")
                    {
                        cv::cvtColor(imageMessage->image, imgTmp, cv::COLOR_BayerRG2BGR);
                        cv::resize(imgTmp, imgTmpSmall, cv::Size(), 0.25, 0.25, cv::INTER_AREA);
                        cv::imshow("BayerRG8", imgTmpSmall);
                        cv::waitKey(5);
                    }
                    else if (imageMessage->encoding == "BayerBG8")
                    {
                        cv::cvtColor(imageMessage->image, imgTmp, cv::COLOR_BayerBG2BGR);
                        cv::resize(imgTmp, imgTmpSmall, cv::Size(), 0.25, 0.25, cv::INTER_AREA);
                        cv::imshow("BayerBG8", imgTmpSmall);
                        cv::waitKey(5);
                    }
                    else
                    {//error: image data should only be RGB 8 bit


                    }
                }
            }
        }
    }

    return true;

}


int main()
{
    if (runCam())
    {
        std::cout << "Camera run successful." << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Camera run failed." << std::endl;
        return 1;
    }
}
