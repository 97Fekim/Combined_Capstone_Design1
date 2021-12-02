# Machine vision for semiconductor defect inspection
## 
## Description (개요)
>MFC program that have PCB Solder Void defect inspection function and image processing function.
>(반도체 PCB Solder Void 불량 검사와 이미지 변환 기능이 있는 MFC 프로그램.)
## Enviromnent (개발환경)
>* __구동환경__
>> _Window_
>* __주요 사용 패키지__
>>_C_&nbsp;&nbsp;&nbsp;_C++_&nbsp;&nbsp;&nbsp;_OpenCV_&nbsp;&nbsp;&nbsp;&nbsp;_MFC_
## Prerequisite
>
## Files
>
## Usage
>
## Performance Display (구현 화면)
![내검사](https://user-images.githubusercontent.com/81150979/122421227-32a44500-cfc7-11eb-84c0-d5c9d0737992.PNG)
---------------------
![메뉴 영상변환](https://user-images.githubusercontent.com/81150979/122421240-346e0880-cfc7-11eb-81f0-c73772956140.PNG)
----------------------
## Main Function (주요 기능)
>1) PCB Solder Void Inspection
>>- General Inspection (일반 검사)
>>- Fast Inspection (빠른검사, 이미지 불러오기시 즉시 검사)
>2) Image scaling(1/2/3/4, 1/2, 1/5)
>4) ROI Setting.
>6) Create Histogram image. (히스토그램 이미지 생성)
>7) View Histogram of image.
>8) Image characterastic change. (이미지 특성 변경)
>>- Image reverse (영상 반전)
>>- Brightness and contrast change (밝기, 명암비 변경)
>9) Bluring (블러링)
>>- Mean blur (평균값 블러링)
>>- Gaussian blur (가우시안 블러링)
>>- Median blur (중간값 블러링)
>10) Histogram transform (히스토그램 변환)
>>- Histogram stretching (히스토그램 스트레칭)
>>- Histogram equalization (히스토그램 평활화)
>11) Morphology (형태학적 변환)
>>- Erosion (침식)
>>- Dilatation (팽창)
>12) Thresholing (이진화)
>>- Global thresholding with trackbar preview (트랙바를 이용한 미리보기가 가능한 전역이진화)
>>- Mean thresholding (평균값 이진화)
>>- Gaussian thresholding (가우시안 이진화)
>>- Otsu thresholding (Otsu 이진화)
>13) Feature extraction (특징 추출)
>>- Connected component labeling (레이블링)
>>- Sobel edge extraction (소벨 엣지 추출)
>>- Hough circle (허프 서클)
## reference (참고문헌)
- [openCV를 이용한 디지털 영상처리], 인피니티북스, 500
- [Visual C++ 영상처리 프로그래밍], 길벗, 816
- [쉽게 배우는 MFC 윈도우 프로그래밍], 한빛아카데미, 772
- Technical document written by (주)쎄크
## Project term (제작 기간)
>2020.9. ~ 2020.12.
