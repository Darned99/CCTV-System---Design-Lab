/**
 * Implementacja funkcji obsługujących strumień wideo na żywo (Video Capture) oraz wyświetlanie obrazu (imshow).
 * 
 * Dodanie obsługi błędów związanych z rozłączeniem kamery.
 * 
 * Możliwość wydzielenia klasy lub zestawu funkcji odpowiedzialnych za obsługę kamery
 *
 */

/**
 * Funkcje / metody do zaimplementowania
 * 
 *      initializaeCamera(int index):
 *          otwiera kamerę za pomocą cv::VideoCapture
 *          ustawia parametry (rozdzielczość, FPS)
 *          weryfikuje, czy kamera jest dostępna (isOpened())
 *          
 *      streamVideo()
 *          odczytuje klatki za pomocą read() i wyświetla je w oknie OpenCV (cv::imshow)
 *          obsługuje przypadki, gdy kamera przestaje dostarczać klatki
 * 
 *      handleError()
 *          loguje błędy związane z brakiem kamery lub jej rozłączeniem
 *          próbuje ponownie nawiązać połączenie z kamerą
 * 
 */

#include <iostream>
#include "camera.h"

namespace dl{

    dl::Camera::Camera(int id, 
    const std::string& name, 
    const std::string& faceCascadePath,
    const std::string& bodyCascadePath,
    const std::string& videoFilename
    ) : 
    cameraId(id), windowName(name) {

        if (!faceCascade.load(faceCascadePath)) {
            std::cerr << "Nie można załadować klasyfikatora twarzy!" << std::endl;
        }

        if (!bodyCascade.load(bodyCascadePath)) {
            std::cerr << "Nie można załadować klasyfikatora ciała!" << std::endl;
        }

        videoWriter.open(videoFilename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G', 20.0, cv::Size(640, 480)))

    }

    dl::Camera::~Camera() {
        release();
    }

    bool Camera::open() {
        capture.open(cameraId);
        return capture.isOpened();
    }


    void Camera::detectAndDisplay(cv::Mat& frame) {
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Detekcja twarzy
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(gray, faces, 1.1, 3, 0, cv::Size(30, 30));

        // Detekcja ciał
        std::vector<cv::Rect> bodies;
        bodyCascade.detectMultiScale(gray, bodies, 1.1, 3, 0, cv::Size(30, 30));

        // Rysowanie prostokątów wokół twarzy
        for (auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(255, 0, 0), 3);
        }

        // Rysowanie prostokątów wokół ciała
        for (auto& body : bodies) {
            cv::rectangle(frame, body, cv::Scalar(0, 255, 0), 3);
        }
    }

    void Camera::writeToFile(const cv::Mat& frame) {
        videoWriter.write(frame);
    }

    void Camera::showFrame(const cv::Mat& frame) {
        cv::imshow(windowName, frame);
    }

    void dl::Camera::release() {
        if (capture.isOpened()) {
            capture.release();
        }
    }

}