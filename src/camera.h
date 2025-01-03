/**
 * Deklaracja funkcji i klasy odpowiedzialnych za pracę z kamerą
 * Umożliwia lepszą organizację kodu i oddzielenie implementacji od deklaracji
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <opencv2/opencv.hpp>

namespace dl{
    class Camera{
        private:
            cv::VideoCapture capture;
            int cameraId;
            std::string windowName;

        public:
            Camera(int id, const std::string& name);

            ~Camera();

            bool open();
            void showFrame();
            void release();

    }
};

#endif
