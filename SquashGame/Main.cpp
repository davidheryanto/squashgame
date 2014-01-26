//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/video/background_segm.hpp"
//
//#include <time.h>
//#include <iostream>
//#include <stdio.h>
//
//#include <Box2D.h>
//
//using namespace std;
//using namespace cv;
//
////
////const int alpha_slider_max = 255;
////const int beta_slider_max = 255;
////const int charlie_slider_max = 255;
////int alpha_slider;
////int beta_slider;
////int charlie_slider;
////
////int d_slider;
////int e_slider;
////int f_slider;
//
//
////Mat dst;
////int cntr = 0;
//
//int Y_MIN = 0;
//int Y_MAX = 121;
//int Cr_MIN = 71;
//int Cr_MAX = 119;
//int Cb_MIN = 69;
//int Cb_MAX = 117;
//
////
////void on_trackbar(int, void*) {
////	Y_MIN = alpha_slider;
////}
////void on_trackbar2(int, void*) {
////	Cr_MIN = beta_slider;
////}
////void on_trackbar3(int, void*) {
////	Cb_MIN = charlie_slider;
////}
////
////void on_trackbar4(int, void*) {
////	Y_MAX = d_slider;
////}
////void on_trackbar5(int, void*) {
////	Cr_MAX = e_slider;
////}
////void on_trackbar6(int, void*) {
////	Cb_MAX = f_slider;
////}
//
//float batRadius = 2.0f;;
//float ballRadius = 9.0f;
//
//float flyRadius = 3.0 / 30.0;
//
//int thresh = 100;
//int max_thresh = 255;
//RNG rng(12345);
//
//b2Vec2 gravity(0.0f, 7.0f);
//b2World world(gravity);
//
//float pixel = 30;
//float space = 50;
//
//class MyContactListener : public b2ContactListener
//{
//	void EndContact(b2Contact* contact)
//	{
//		b2Body* bodyA = contact->GetFixtureA()->GetBody();
//		bodyA->ApplyLinearImpulse(b2Vec2(0.0f, 2.0f), bodyA->GetPosition(), true);
//
//		b2Body* bodyB = contact->GetFixtureB()->GetBody();
//		bodyA->ApplyLinearImpulse(b2Vec2(0.0f, 2.0f), bodyB->GetPosition(), true);
//	}
//};
//
//class ball
//{
//public:
//	ball();
//	~ball() {};
//	b2Body* body;
//};
//
//ball::ball()
//{
//	b2BodyDef bodyDef;
//	bodyDef.userData = "ball";
//	bodyDef.type = b2_dynamicBody;
//
//	bodyDef.bullet = true;
//	int randomx = rand() % 15 + 3;
//	int randomy = rand() % 12 + 3;
//
//
//	bodyDef.position.Set(randomx, randomy); //space / pixel, 300.0f / pixel
//	body = world.CreateBody(&bodyDef);
//	b2CircleShape dynamicBox;
//	dynamicBox.m_radius = ballRadius / pixel;
//	b2FixtureDef fixtureDef;
//	fixtureDef.shape = &dynamicBox;
//	fixtureDef.density = 1.0f;
//	fixtureDef.friction = 5.0f;
//	fixtureDef.restitution = 1.0f;
//	body->CreateFixture(&fixtureDef);
//
//};
//
//class Fly
//{
//public:
//	Fly();
//	~Fly() {};
//	b2Body* body;
//};
//
//Fly::Fly()
//{
//	b2BodyDef bodyDef;
//	bodyDef.userData = "fly";
//	bodyDef.position.Set(10, 10);
//	bodyDef.type = b2_dynamicBody;
//
//	
//	body = world.CreateBody(&bodyDef);
//	b2CircleShape bodyShape;
//	bodyShape.m_radius = flyRadius;
//
//	b2FixtureDef fixtureDef;
//	fixtureDef.shape = &bodyShape;
//	body->CreateFixture(&fixtureDef);
//}
//
//class Wall
//{
//public:
//	Wall(int x, int y, int w, int h);
//	~Wall() {};
//	b2Body* body;
//	b2BodyDef bodyDef;
//};
//
//Wall::Wall(int x, int y, int w, int h)
//{
//
//	bodyDef.position.Set(x / pixel, y / pixel);
//	body = world.CreateBody(&bodyDef);
//
//	b2PolygonShape boxShape;
//	boxShape.SetAsBox(w / pixel, h / pixel);
//
//	body->CreateFixture(&boxShape, 0.0f);
//}
//
//
//class Bat
//{
//public:
//	Bat(int x, int y, int w, int h);
//	~Bat() {};
//	b2Body* body;
//	b2BodyDef bodyDef;
//};
//
//Bat::Bat(int x, int y, int w, int h)
//{
//	bodyDef.bullet = true;
//	bodyDef.position.Set(x, y);
//	body = world.CreateBody(&bodyDef);
//
//	/*b2PolygonShape boxShape;
//	boxShape.SetAsBox(w, h);*/
//
//	b2CircleShape boxShape;
//	boxShape.m_radius = batRadius;
//
//	b2FixtureDef fixtureDef;
//	fixtureDef.shape = &boxShape;
//	fixtureDef.density = 30.0f;
//	fixtureDef.friction = 3.0f;
//	fixtureDef.restitution = 1.0f;
//
//	body->CreateFixture(&fixtureDef);
//}
//
////this function will return a skin masked image
//Mat getSkin(cv::Mat input)
//{
//	//YCrCb threshold
//	// You can change the values and see what happens
//
//
//	Mat skin;
//	//first convert our RGB image to YCrCb
//	cv::cvtColor(input, skin, cv::COLOR_BGR2YCrCb);
//
//	//uncomment the following line to see the image in YCrCb Color Space
//	//cv::imshow("YCrCb Color Space",skin);
//
//	//filter the image in YCrCb color space
//	cv::inRange(skin, cv::Scalar(Y_MIN, Cr_MIN, Cb_MIN), cv::Scalar(Y_MAX, Cr_MAX, Cb_MAX), skin);
//
//	return skin;
//}
//
//bool ballHitFly(ball ball, Fly fly)
//{
//
//	return false;
//}
//
//int main(int argc, const char** argv)
//{
//	MyContactListener myContactListener;
//	world.SetContactListener(&myContactListener);
//
//
//	double totalX;
//	double totalY;
//
//	float32 avgX;
//	float32 avgY;
//
//	Fly fly;
//
//
//	b2Body* floorBody;
//	b2BodyDef floorDef;
//	b2FixtureDef floorFixtureDef;
//	b2PolygonShape floorBox;
//
//	b2Vec2 prevBatPosition;
//
//	floorBox.SetAsBox(640.0f / 2.0f / pixel, 0.0f / pixel);
//	floorFixtureDef.shape = &floorBox;
//	floorFixtureDef.restitution = 0.3f;
//	floorFixtureDef.density = 0.0f;
//	floorFixtureDef.friction = 0.2f;
//
//	// Bottom Wall
//	//floorDef.position.Set(640.0f / 2.0f / pixel, 480.0f / pixel);
//	//floorBody = world.CreateBody(&floorDef);
//	//floorBody->CreateFixture(&floorFixtureDef);
//
//	//// Right wall
//	//b2Body* leftBody;
//	//floorBox.SetAsBox(0.0f, 480.0f / 2.0f / pixel);
//	//floorDef.position.Set(0 / pixel, 480.0f / 2.0f / pixel);
//	//leftBody = world.CreateBody(&floorDef);
//	//leftBody->CreateFixture(&floorFixtureDef);
//
//	//// Left wall
//	//b2Body* rightBody;
//	//floorDef.position.Set(640.0f / pixel, 480.0f / 2.0f / pixel);
//	//rightBody = world.CreateBody(&floorDef);
//	//rightBody->CreateFixture(&floorFixtureDef);
//
//	ball Balls[1];
//
//	Bat bat(10, 10, 2.0, 2.0);
//
//	Wall wallTop(5, 5, 640, 1);
//	Wall wallBottom(5, 475, 640, 1);
//
//	Wall wallRight(5, 5, 1, 640);
//	Wall wallLeft(635, 5, 1, 640);
//
//
//	float32 timeStep = 1.0f / 13.0f;
//	int32 velocityIterations = 20;
//	int32 positionIterations = 20;
//
//
//	b2Body* bodyy;
//
//	VideoCapture capture(0);
//	if (!capture.isOpened()){
//		return -1;
//	}
//
//	int key = 0;
//
//	namedWindow("Capture ", CV_WINDOW_AUTOSIZE);
//	namedWindow("Foreground ", CV_WINDOW_AUTOSIZE);
//
//	Mat frame, foreground, image;
//	BackgroundSubtractorMOG2 mog(500, 16, false);
//
//	srand(time(NULL));
//	waitKey(200);
//	while (key != 'q') {
//		capture >> frame;
//		key = waitKey(30);
//
//		b2Vec2 flyCurPos = fly.body->GetPosition();
//
//		//if fly got hit move to a new position
//		if (ballHitFly(Balls[0], fly))
//		{
//
//		}
//
//
//		foreground = getSkin(frame);
//
//		Mat erodeElement = getStructuringElement(MORPH_RECT, Size(2, 2));
//		// dilate with larger element so make sure object is nicely visible
//		Mat dilateElement = getStructuringElement(MORPH_RECT, Size(5, 5));
//
//		erode(foreground, foreground, erodeElement);
//		erode(foreground, foreground, erodeElement);
//
//		dilate(foreground, foreground, dilateElement);
//		dilate(foreground, foreground, dilateElement);
//
//
//		//GaussianBlur(frame, frame, Size(5, 5), 0, 0);
//
//		image = frame.clone();
//
//		// draw fly
//		circle(image, Point(flyCurPos.x * pixel, flyCurPos.y * pixel), flyRadius * pixel, CV_RGB(50, 0, 200), 2, 8, 0);
//
//		//mog(frame, foreground, -10);
//
//		//Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));
//		//// dilate with larger element so make sure object is nicely visible
//		//Mat dilateElement = getStructuringElement(MORPH_RECT, Size(5, 5));
//
//		//erode(foreground, foreground, erodeElement);
//		//erode(foreground, foreground, erodeElement);
//
//		//dilate(foreground, foreground, dilateElement);
//		//dilate(foreground, foreground, dilateElement);
//
//
//		//imshow("Foreground ", foreground);
//
//		cv::imshow("Foreground", foreground);
//
//
//		//Mat threshold_output = foreground.clone();
//		vector<vector<Point> > contours;
//		vector<Vec4i> hierarchy;
//
//
//		//// Find contours
//		contours.clear();
//		//findContours(threshold_output, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
//		findContours(foreground, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
//
//		// Draw contours + hull results
//		Mat drawing = Mat::zeros(foreground.size(), CV_8UC3);
//		double max = 0;
//		int num = -1;
//		Scalar color = CV_RGB(255, 0, 0);
//
//		int size = contours.size();
//		if (size > 20) size = 20;
//		for (int i = 0; i < size; i++)
//		{
//			double temp = contourArea(contours[i]);
//			if (temp > max && temp > 500)
//			{
//				max = temp;
//				num = i;
//			}
//
//		}
//
//		if (num != -1)
//		{
//			drawContours(image, contours, num, color, 3, 8, vector<Vec4i>(), 0, Point());
//
//			int t = contours[num].size();
//
//
//			totalX = 0;
//			totalY = 0;
//
//			for (int i = 0; i < contours[num].size(); i++) {
//
//				//totalX += vs[i].Set(contours[num][i].x / pixel, contours[num][i].y / pixel);
//				totalX += contours[num][i].x;
//				totalY += contours[num][i].y;
//			}
//			totalX /= pixel;
//			totalY /= pixel;
//
//
//			/*b2ChainShape chain;
//			chain.CreateLoop(vs, t);
//
//			b2BodyDef bd;
//			bd.type = b2_dynamicBody;
//			bodyy = world.CreateBody(&bd);
//			b2Vec2 pos = bodyy->GetPosition();*/
//
//			if (totalX > 0 && totalY > 0)
//			{
//				float32 avgX = totalX / contours[num].size();
//				float32 avgY = totalY / contours[num].size();
//
//
//				/*avgX = 5.0;
//				avgY = 5.0;*/
//
//				b2Vec2 curBatPosition;
//				curBatPosition.x = avgX;
//				curBatPosition.y = avgY;
//
//				// Adjust the postiion of the bat
//				bat.body->SetTransform(b2Vec2(avgX, avgY), 0);
//
//				// Adjust the force / velocity
//				if (prevBatPosition.x > -1 && prevBatPosition.y > -1) {
//					b2Vec2 direction;
//					direction.x = (curBatPosition.x - prevBatPosition.x) * 20;
//					direction.y = (curBatPosition.y - prevBatPosition.y) * 20;
//					direction.Normalize();
//					
//					// bat.body->SetLinearVelocity(direction);
//					//bat.body->SetLinearVelocity(direction);
//					//bat.body->ApplyLinearImpulse(direction, b2Vec2(0, 1), true);
//
//					
//					printf("DIRECTION -- %.2f, %.2f\n", direction.x, direction.y);
//				}
//
//				prevBatPosition = curBatPosition;
//			}
//		}
//
//		world.Step(timeStep, velocityIterations, positionIterations);
//
//		for (int i = 0; i < 1; i++)
//		{
//			b2Vec2 position = Balls[i].body->GetPosition();
//			int x = position.x >= 0 ? position.x : 2;
//			int y = position.y >= 0 ? position.y : 2;
//			circle(image, Point(x * pixel, y * pixel), ballRadius, CV_RGB(0, 255, 0), 3, 8, 0);
//		}
//
//		b2Vec2 batPos = bat.body->GetPosition();
//		/*Point points[2] =
//		{
//			Point(batPos.x * pixel - pixel, batPos.y * pixel - pixel),
//			Point(batPos.x * pixel + pixel, batPos.y * pixel + pixel)
//		};*/
//
//		//rectangle(image, points[0], points[1], Scalar(0, 255, 255)
//		circle(image, Point(batPos.x * pixel, batPos.y * pixel), batRadius * pixel, CV_RGB(200, 0, 200), 3, 8, 0);
//
//
//		// rectangle(image, points[0], points[1], Scalar(0, 255, 255), -1, 8);
//		// circle(image, Point(10*pixel, 10*pixel), 15, CV_RGB(0, 255, 255), 3, 8, 0);
//
//		//
//		//if (cntr != 0) {
//		//	namedWindow("Linear", 1);
//		//	char TrackbarName[50];
//		//	char TrackbarName2[50];
//		//	char TrackbarName3[50];
//
//
//
//		//	sprintf(TrackbarName, "slider1 %f", alpha);
//		//	sprintf(TrackbarName2, "slider2 %f", beta);
//		//		sprintf(TrackbarName3, "slider3 %f", charlie);
//
//
//
//		//	createTrackbar(TrackbarName, "Linear", &alpha_slider, alpha_slider_max, on_trackbar);
//		//	createTrackbar(TrackbarName2, "Linear", &beta_slider, beta_slider_max, on_trackbar2);
//		//	createTrackbar(TrackbarName3, "Linear", &charlie_slider, charlie_slider_max, on_trackbar3);
//
//		//	createTrackbar("slider 4 d", "Linear", &d_slider, alpha_slider_max, on_trackbar4);
//		//	createTrackbar("slider 5 e", "Linear", &e_slider, beta_slider_max, on_trackbar5);
//		//	createTrackbar("slider 6 f", "Linear", &f_slider, charlie_slider_max, on_trackbar6);
//
//
//		//	on_trackbar(alpha_slider, 0);
//		//	on_trackbar2(beta_slider, 0);
//		//	on_trackbar3(charlie_slider, 0);
//
//
//
//		//	on_trackbar4(d_slider, 0);
//		//	on_trackbar5(e_slider, 0);
//		//	on_trackbar6(f_slider, 0);
//
//		//	// dst = frame.clone();
//		//	// imshow("Linear", dst);
//		//	cntr = 0;
//		//}
//
//
//		/*if (num != -1)
//		{
//		world.DestroyBody(bodyy);
//		}*/
//
//		flip(image, image, 1);
//		cv::imshow("Capture ", image);
//
//	}
//
//	capture.release();
//
//	cv::destroyWindow("Capture ");
//	cv::destroyWindow("Foreground ");
//}
