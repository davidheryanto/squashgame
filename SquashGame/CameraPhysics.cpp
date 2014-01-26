#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"

#include <iostream>
#include <stdio.h>

#include <Box2D.h>

using namespace std;
using namespace cv;


int thresh = 100;
int max_thresh = 255;
RNG rng(12345);


b2Vec2 gravity(0.0f, 9.0f);
b2World world(gravity);

float pixel = 30;
float space = 50;

class MyContactListener : public b2ContactListener
{
	void endcontact(b2Contact* contact)
	{
		b2Body* bodyA = contact->GetFixtureA()->GetBody();
		bodyA->ApplyLinearImpulse(b2Vec2(0.0f, 4.0f), bodyA->GetPosition(), true);

		b2Body* bodyB = contact->GetFixtureB()->GetBody();
		bodyB->ApplyLinearImpulse(b2Vec2(0.0f, 4.0f), bodyB->GetPosition(), true);
	}
};

Mat getskin(Mat input)
{
	int y_min = 0;
	int y_max = 121;
	int cr_min = 71;
	int cr_max = 119;
	int cb_min = 69;
	int cb_max = 117;

	Mat skin;
	//first convert our rgb image to ycrcb
	cvtColor(input, skin, CV_BGR2YCrCb);

	//uncomment the following line to see the image in ycrcb color space
	//cv::imshow("ycrcb color space",skin);

	//filter the image in ycrcb color space
	cv::inRange(skin, Scalar(y_min, cr_min, cb_min), Scalar(y_max, cr_max, cb_max), skin);
}


void createTrackbars()
{

}

class ball
{
public:
	ball();
	~ball() {};
	b2Body* body;
};

ball::ball()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(space / pixel, 50.0f / pixel);
	space += 10;
	body = world.CreateBody(&bodyDef);
	b2CircleShape dynamicBox;
	dynamicBox.m_radius = 20.0f / pixel;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.8f;
	body->CreateFixture(&fixtureDef);
};

int main(int argc, const char** argv)
{
	MyContactListener myContactListener;
	world.SetContactListener(&myContactListener);

	b2Body* floorBody;
	b2BodyDef floorDef;
	b2FixtureDef floorFixtureDef;
	b2PolygonShape floorBox;

	floorBox.SetAsBox(640.0f / 2.0f / pixel, 0.0f / pixel);
	floorFixtureDef.shape = &floorBox;
	floorFixtureDef.restitution = 0;
	floorFixtureDef.density = 0.0f;
	floorFixtureDef.friction = 0.3f;

	floorDef.position.Set(640.0f / 2.0f / pixel, 480.0f / pixel);
	floorBody = world.CreateBody(&floorDef);
	floorBody->CreateFixture(&floorFixtureDef);

	b2Body* leftBody;
	floorBox.SetAsBox(0.0f, 480.0f / 2.0f / pixel);
	floorDef.position.Set(0 / pixel, 480.0f / 2.0f / pixel);
	leftBody = world.CreateBody(&floorDef);
	leftBody->CreateFixture(&floorFixtureDef);

	b2Body* rightBody;
	floorDef.position.Set(640.0f / pixel, 480.0f / 2.0f / pixel);
	rightBody = world.CreateBody(&floorDef);
	rightBody->CreateFixture(&floorFixtureDef);

	ball Balls[10];

	float32 timeStep = 1.0f / 15.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 20;


	b2Body* bodyy;

	VideoCapture capture(0);
	if (!capture.isOpened()){
		return -1;
	}

	int key = 0;

	namedWindow("Capture ", CV_WINDOW_AUTOSIZE);
	namedWindow("Foreground ", CV_WINDOW_AUTOSIZE);

	Mat frame, foreground, image;
	BackgroundSubtractorMOG2 mog(5000, 16, false);

	waitKey(200);
	while (key != 'q'){
		capture >> frame;
		key = waitKey(1);

		GaussianBlur(frame, frame, Size(3, 3), 0, 0);

		image = frame.clone();
		mog(frame, foreground, -10);

		

		dilate(foreground, foreground, Mat());

		imshow("Foreground ", foreground);

		Mat threshold_output = foreground.clone();
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;

		// Find contours
		findContours(threshold_output, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

		// Draw contours + hull results
		Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
		double max = 0;
		int num = -1;
		Scalar color = CV_RGB(255, 0, 0);

		for (int i = 0; i< contours.size(); i++)
		{
			double temp = contourArea(contours[i]);
			if (temp > max && temp > 500)
			{
				max = temp;
				num = i;
			}

		}

		if (num != -1)
		{
			drawContours(image, contours, num, color, 3, 8, vector<Vec4i>(), 0, Point());

			int t = contours[num].size();
			b2Vec2* vs = new b2Vec2[t];
			for (int i = 0; i< contours[num].size(); i++) {

				vs[i].Set(contours[num][i].x / pixel, contours[num][i].y / pixel);
			}
			b2ChainShape chain;
			chain.CreateLoop(vs, t);

			b2BodyDef bd;
			bodyy = world.CreateBody(&bd);
			bodyy->CreateFixture(&chain, 0.0f);

			delete vs;
		}

		world.Step(timeStep, velocityIterations, positionIterations);

		for (int i = 0; i<10; i++)
		{
			b2Vec2 position = Balls[i].body->GetPosition();
			circle(image, Point(position.x * pixel, position.y * pixel), 20, CV_RGB(0, 255, 0), 3, 8, 0);
		}



		if (num != -1)
		{
			world.DestroyBody(bodyy);
		}

		flip(image, image, 1);
		imshow("Capture ", image);

	}

	capture.release();

	cv::destroyWindow("Capture ");
	cv::destroyWindow("Foreground ");
}
