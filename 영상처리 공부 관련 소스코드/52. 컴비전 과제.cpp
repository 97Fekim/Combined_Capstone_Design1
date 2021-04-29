#define _CRT_SECURE_NO_WARNINGS
#define strLen 256
#include "opencv2/opencv.hpp"
#include <GL/glui.h>
#include <GL/glut.h>
#include "OpenFileDialog.h"
#include "SaveFileDialog.h"


using namespace cv;
using namespace std;

int main_window;

Mat input_image, input_image_buffer;
Mat frame_img, frame_img_buffer;
Mat frame_camera, frame_camera_buffer;
Point2f ROI[4];

int radiosel_input = 0;
int radiosel_frame = 0;
char Filename[256];
int i = 0;

void setROI(int event, int x, int y, int, void* param);
void callback(int id);

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	GLUI* glui = GLUI_Master.create_glui("13주차 과제_60161801_전자공학과_김승철", 0, 300, 300);
	main_window = glui->get_glut_window_id();
	GLUI_Master.set_glutIdleFunc(NULL);

	glui->add_separator();

	GLUI_StaticText* box_input;
	box_input = glui->add_statictext("INPUT");
	GLUI_RadioGroup* radio_input;
	radio_input = glui->add_radiogroup(&radiosel_input);
	glui->add_radiobutton_to_group(radio_input, "IAMGE");

	GLUI_Button* button_read1;
	button_read1 = glui->add_button("READ", 0, callback);
	button_read1->set_w(250);

	glui->add_separator();

	GLUI_StaticText* box_frame;
	box_frame = glui->add_statictext("FRAME");
	GLUI_RadioGroup* radio_frame;
	radio_frame = glui->add_radiogroup(&radiosel_frame);
	glui->add_radiobutton_to_group(radio_frame, "IMAGE");
	glui->add_radiobutton_to_group(radio_frame, "CAMERA");

	GLUI_Button* button_read2;
	button_read2 = glui->add_button("READ", 1, callback);
	button_read2->set_w(250);

	glui->add_separator();

	GLUI_Button* button_excute;
	button_excute = glui->add_button("EXCUTE", 2, callback);

	GLUI_Button* button_ROI_INIT;
	button_ROI_INIT = glui->add_button("ROI INIT", 3, callback);

	GLUI_Button* button_exit;
	button_exit = glui->add_button("EXIT", 0, (GLUI_Update_CB)exit);

	glui->set_main_gfx_window(main_window);
	glutMainLoop();
	return EXIT_SUCCESS;

}

/* 프레임 READ시 호출되는 함수입니다. */
void setROI(int event, int x, int y, int, void* param)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		if (i > 3)
			i = 0;
		ROI[i] = Point2f(x, y);
		i++;

		if (radiosel_frame == 0)
		{
			circle(frame_img, Point(x, y), 2, Scalar(0, 0, 255), 2);
			imshow("Frame", frame_img);
		}
		else if (radiosel_frame == 1)
		{
			circle(frame_camera, Point(x, y), 2, Scalar(0, 0, 255), 2);
			imshow("Frame", frame_camera);
		}
	}
}

void callback(int id)
{
	/* Input Read */
	if (id == 0)
	{
		OpenFileDialog* openFileDialog = new OpenFileDialog();
		if (openFileDialog->ShowDialog())
		{
			WideCharToMultiByte(CP_ACP, 0, openFileDialog->FileName, strLen, Filename, strLen, NULL, NULL);
			input_image = imread(Filename);
			input_image_buffer = input_image.clone();
			imshow("input_image", input_image);
		}
	}
	/* Frame Read */
	else if (id == 1)
	{
		/* image frame */
		if (radiosel_frame == 0)
		{
			OpenFileDialog* openFileDialog = new OpenFileDialog();
			if (openFileDialog->ShowDialog())
			{
				WideCharToMultiByte(CP_ACP, 0, openFileDialog->FileName, strLen, Filename, strLen, NULL, NULL);
				frame_img = imread(Filename);
				frame_img_buffer = frame_img.clone();
				imshow("Frame", frame_img);
				setMouseCallback("Frame", setROI);
			}
		}
		/* camera frame */
		else if (radiosel_frame == 1)
		{

			VideoCapture cap;
			cap.open(0);
			if (!cap.isOpened())
			{
				cerr << "ERROR! Unable to open camera\n";
				return;
			}

			cout << "Start grabbing" << endl
				<< "Press any key to terminate" << endl;

			cap.read(frame_camera);
			frame_camera_buffer = frame_camera.clone();
			imshow("Frame", frame_camera);
			setMouseCallback("Frame", setROI);
		}
	}
	/* Excute */
	else if (id == 2)
	{
		/* 이미지에 이미지 출력 */
		if (radiosel_frame == 0)
		{
			Point2f inputp[4];

			inputp[0] = Point2f(0, 0);
			inputp[1] = Point2f(input_image_buffer.cols, 0);
			inputp[2] = Point2f(input_image_buffer.cols, input_image_buffer.rows);
			inputp[3] = Point2f(0, input_image_buffer.rows);

			Mat h = getPerspectiveTransform(inputp, ROI);
			warpPerspective(input_image_buffer, frame_img_buffer, h, frame_img_buffer.size(), INTER_LINEAR, BORDER_TRANSPARENT);

			imshow("Result", frame_img_buffer);
		}
		/* 카메라에 이미지 출력 */
		else if (radiosel_frame == 1)
		{
			VideoCapture cap;
			Mat live_frame;
			cap.open(0);

			if (!cap.isOpened())
			{
				cerr << "ERROR! Unable to open camera\n";
				return;
			}
			cout << "Start grabbing" << endl
				<< "Press any key to terminate" << endl;
			while (1)
			{
				cap.read(live_frame);
				if (live_frame.empty())
				{
					cerr << "ERROR! blank frame grabbed\n";	// 예외처리
					break;
				}

				Point2f inputp[4];
				inputp[0] = Point2f(0, 0);
				inputp[1] = Point2f(input_image_buffer.cols, 0);
				inputp[2] = Point2f(input_image_buffer.cols, input_image_buffer.rows);
				inputp[3] = Point2f(0, input_image_buffer.rows);

				Mat h = getPerspectiveTransform(inputp, ROI);
				warpPerspective(input_image_buffer, live_frame, h, live_frame.size(), INTER_LINEAR, BORDER_TRANSPARENT);
				imshow("Live", live_frame);


				if (waitKey(5) >= 0)
					break;
			}

		}
	}
	/* ROI INIT */
	else if (id == 3)
	{
		for (int i = 0; i < 4; ++i)
			ROI[i] = Point(0, 0);
	}
}