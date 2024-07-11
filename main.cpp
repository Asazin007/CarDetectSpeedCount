#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <iostream>
#include <cmath>
#include <vector>

using namespace cv;
using namespace std;

struct Car
{
    Ptr<Tracker> tracker;
    Rect bbox; // Use cv::Rect
    Point2d prev_center;
    double speed;
};

bool isOverlapping(const Rect &rect1, const Rect &rect2)
{
    return (rect1 & rect2).area() > 0;
}

int main()
{
    // Open video file
    VideoCapture cap("Cars.mp4");
    if (!cap.isOpened())
    {
        cerr << "Error: Couldn't open video file." << endl;
        return -1;
    }

    // Load Haar Cascade classifier for car detection
    CascadeClassifier car_cascade;
    if (!car_cascade.load("cars.xml"))
    {
        cerr << "Error: Couldn't load Haar Cascade classifier." << endl;
        return -1;
    }

    Mat frame, gray;
    vector<Car> cars;
    double fps = cap.get(CAP_PROP_FPS);
    double scale = 1.2; // Scale factor for car detection

    int test = 0;      // counting frames
    int car_count = 0; // counting cars per frame at specfic location

    while (cap.read(frame))
    {
        test++;
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        equalizeHist(gray, gray);

        // Detect cars in the frame
        vector<Rect> detected_cars;
        car_cascade.detectMultiScale(gray, detected_cars, scale);

        // Filter out overlapping detections to avoid multiple rectangles on the same car
        for (const auto &detected_car : detected_cars)
        {
            bool overlap = false;
            for (const auto &car : cars)
            {
                if (isOverlapping(car.bbox, detected_car))
                {
                    overlap = true;
                    break;
                }
            }
            if (!overlap)
            {
                Car car;
                car.bbox = detected_car;
                car.tracker = TrackerKCF::create();
                car.tracker->init(frame, car.bbox);
                car.prev_center = Point2d(car.bbox.x + car.bbox.width / 2, car.bbox.y + car.bbox.height / 2);
                car.speed = 0;
                cars.push_back(car);
            }
        }

        for (size_t i = 0; i < detected_cars.size(); i++)
        {
            // Count cars
            if ( detected_cars[i].y >= 80 && detected_cars[i].y <= 80)
            {
                car_count++;
            }
        }

        // Update tracking for existing cars
        for (auto it = cars.begin(); it != cars.end();)
        {
            Rect int_bbox = it->bbox; // Convert to cv::Rect
            if (it->tracker->update(frame, int_bbox))
            {
                it->bbox = int_bbox; // Update bbox with the new integer bbox
                Point2d current_center = Point2d(it->bbox.x + it->bbox.width / 2, it->bbox.y + it->bbox.height / 2);
                it->speed = norm(current_center - it->prev_center) * fps / it->bbox.width;
                it->prev_center = current_center;

                // Draw bounding box and speed
                rectangle(frame, it->bbox, Scalar(255, 0, 0), 2);
                putText(frame, "Speed: " + to_string(it->speed) + " px/frame", Point(it->bbox.x, it->bbox.y - 10),
                        FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);
                ++it;
            }
            else
            {
                // Remove the car if tracking fails
                it = cars.erase(it);
            }
        }

        // Display the frame
        imshow("Car Tracking", frame);

        //used for getting image for readme file
        // if(test == 30)
        // {
        //     imwrite("Car.jpg",frame);
        // }

        // Exit if ESC is pressed
        if (waitKey(27) == 27)
            break;
    }

    cap.release();
    destroyAllWindows();

    std::cout << car_count << " No. of Car Present in this Video\n";
    return 0;
}
