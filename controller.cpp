#include "LogReader.h"
#include "ImageMessage.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <map>
#include <set>
#include <vector>
#include <iomanip>
#include <sstream>

namespace fs = std::filesystem;

/**
 * @brief Extract, display and/or save multi-camera image feeds from Cetran log.
 *
 * @param logPath Full path to the log file (.log)
 * @param targetWidth Resized width for each camera frame
 * @param targetHeight Resized height for each camera frame
 * @param outputDir Root directory for saving images (only used if saveImages = true)
 * @param showImages Whether to visualize 3x2 combined feed in real time
 * @param saveImages Whether to save each frame into per-camera folders
 */
void processCameraFeeds(
    const std::string &logPath,
    int targetWidth = 320,
    int targetHeight = 240,
    const std::string &outputDir = "./camera_frames",
    bool showImages = true,
    bool saveImages = true)
{
    cereal_log::LogReader logReader;
    if (!logReader.openLog(logPath))
    {
        std::cerr << "❌ Failed to open log file: " << logPath << std::endl;
        return;
    }

    std::cout << "✅ Opened log file: " << logPath << std::endl;
    if (saveImages)
        std::cout << "📁 Saving images under: " << fs::absolute(outputDir) << std::endl;
    if (showImages)
        std::cout << "🖼️ Display enabled (press ESC to exit)" << std::endl;

    std::map<std::string, cv::Mat> frameMap;
    std::set<std::string> cameraTopics;
    int frameCount = 0;

    while (!logReader.eof())
    {
        std::string topic;
        cereal_log::Message::Ptr message;
        if (!logReader.read(topic, message))
            continue;

        // 仅处理相机 topics
        if (topic.find("DEV_") == std::string::npos)
            continue;

        cameraTopics.insert(topic);

        cereal_log::ImageMessage::Ptr imageMessage;
        try { imageMessage = std::static_pointer_cast<cereal_log::ImageMessage>(message); }
        catch (...) { continue; }

        if (imageMessage->image.empty()) continue;

        cv::Mat imgColor;
        if (imageMessage->encoding == "BayerRG8")
            cv::cvtColor(imageMessage->image, imgColor, cv::COLOR_BayerRG2BGR);
        else if (imageMessage->encoding == "BayerBG8")
            cv::cvtColor(imageMessage->image, imgColor, cv::COLOR_BayerBG2BGR);
        else
            imgColor = imageMessage->image.clone();

        if (imgColor.empty()) continue;

        // Resize for display grid
        cv::Mat resized;
        cv::resize(imgColor, resized, cv::Size(targetWidth, targetHeight));
        frameMap[topic] = resized;

        // Save images if enabled
        if (saveImages)
        {
            std::ostringstream seqStream;
            seqStream << std::setw(6) << std::setfill('0') << frameCount;
            long long ts = imageMessage->timeStamp.getRelativeTime().count();
            std::string filename = seqStream.str() + "_" + std::to_string(ts) + ".png";

            fs::path camDir = fs::path(outputDir) / topic;
            if (!fs::exists(camDir)) fs::create_directories(camDir);
            fs::path savePath = camDir / filename;
            cv::imwrite(savePath.string(), imgColor);
        }

        frameCount++;
        if (frameCount % 50 == 0)
            std::cout << "Frame " << frameCount << " | Topic: " << topic << " | " << imgColor.cols << "x" << imgColor.rows << std::endl;

        // Display combined grid if enabled
        if (showImages)
        {
            std::vector<std::string> sortedTopics(cameraTopics.begin(), cameraTopics.end());
            std::vector<cv::Mat> cells;
            for (const auto &t : sortedTopics)
            {
                if (frameMap.count(t))
                    cells.push_back(frameMap[t]);
                else
                    cells.push_back(cv::Mat::zeros(targetHeight, targetWidth, CV_8UC3));
            }

            while (cells.size() < 6)
                cells.push_back(cv::Mat::zeros(targetHeight, targetWidth, CV_8UC3));

 // --- 上排：3 个 pinhole ---
            cv::Mat top;
            cv::hconcat(std::vector<cv::Mat>{cells[0], cells[1], cells[4]}, top);

            // --- 下排：2 个 fisheye，占满整行宽度 ---
            int totalWidth = top.cols;
            int fisheyeW = totalWidth / 2;
            int fisheyeH = static_cast<int>(targetHeight * 1.3);  // fisheye 稍微高一点

            cv::Mat fisheyeL, fisheyeR;
            cv::resize(cells[3], fisheyeL, cv::Size(fisheyeW, fisheyeH));
            cv::resize(cells[2], fisheyeR, cv::Size(fisheyeW, fisheyeH));

            cv::Mat bottom;
            cv::hconcat(std::vector<cv::Mat>{fisheyeL, fisheyeR}, bottom);

            // --- 拼接完整画面 ---
            cv::Mat combined;
            cv::vconcat(top, bottom, combined);

            cv::imshow("All Camera Feeds (3 Pinhole + 2 Fisheye)", combined);
            if (cv::waitKey(1) == 27)
                break;
        }
    }

    std::cout << "\n✅ Done. Total frames processed: " << frameCount << std::endl;
    std::cout << "Cameras detected: " << cameraTopics.size() << std::endl;
    for (auto &t : cameraTopics)
        std::cout << "   " << t << std::endl;
}

int main()
{
    std::string logPath = "/home/aisg/library/Cetran_AGV_Data_Parser-main/cycle3_run1.log";
    std::string outputDir = "./camera_frames";

    // 🔧 设置控制开关
    bool SHOW = true;   // 是否显示视频
    bool SAVE = false;   // 是否保存图片

    processCameraFeeds(logPath, 320, 240, outputDir, SHOW, SAVE);
    return 0;
}

