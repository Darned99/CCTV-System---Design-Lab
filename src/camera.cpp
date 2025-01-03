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

    dl::Camera::Camera(int id, const std::string& name) : cameraId(id), windowName(name) {}

    dl::Camera::~Camera() {
        release();
    }

    bool dl::Camera::open() {
        capture.open(cameraId);
        if (!capture.isOpened()) {
            std::cerr << "Nie można otworzyc kamery: " << cameraId << std::endl;
            return false;
        }
        return true;
    }

    void dl::Camera::showFrame() {
        cv::Mat frame;
        capture >> frame;
        if (!frame.empty()) {
            cv::imshow(windowName, frame);
        }
    }

    void dl::Camera::release() {
        if (capture.isOpened()) {
            capture.release();
        }
    }

}