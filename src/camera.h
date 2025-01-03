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
            cv::CascadeClassifier faceCascade;
            cv::CascadeClassifier bodyCascade;
            cv::VideoWriter videoWriter;

        public:
            Camera(
                int id, 
                const std::string& name,
                const std::string& faceCascadePath,
                const std::string& bodyCascadePath,
                const std::string& videoFilename
                );

            ~Camera();

            // Metoda otwierajaca kamerę
            bool open();

            //Metoda do detekcji twarzy i ciał
            void detectAndDisplay(cv::Mat& frame);

            // Zapis do pliku
            void writeToFile(const cv::Mat& frame);

            // Zwolnienie zasobów
            void release();

            // Metoda do wyświetlania okna kamery
            void showFrame();
            
    }
};

#endif
