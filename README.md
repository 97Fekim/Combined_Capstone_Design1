# Combined Capstone Design1 (융합캡스톤디자인1)
# Project term (제작 기간)
2020.9. ~ 2020.12.
# Overview (개요)
MFC program that have PCB Solder Void defect inspection function and image processing function.
(반도체 PCB Solder Void 불량 검사와 이미지 변환 기능이 있는 MFC 프로그램.)
# Performance Display (구현 화면)
![내검사](https://user-images.githubusercontent.com/81150979/122421227-32a44500-cfc7-11eb-84c0-d5c9d0737992.PNG)
![메뉴 영상변환](https://user-images.githubusercontent.com/81150979/122421240-346e0880-cfc7-11eb-81f0-c73772956140.PNG)
# Main Function (주요 기능)
1) PCB Solder Void Inspection
- General Inspection (일반 검사)
- Fast Inspection (빠른검사, 이미지 불러오기시 즉시 검사)
2) Image scaling(1/2/3/4, 1/2, 1/5)
4) ROI Setting.
6) Create Histogram image.(히스토그램 이미지 생성)
7) View Histogram of image.
8) 영상 특성 변환 기능
- 영상 반전
- 영상 밝기, 명암비 조정
9) 블러링 기능
- 평균값 블러링
- 가우시안 블러링
- 중간값 블러링
10) 히스토그램 변환 기능
- 히스토그램 스트레칭
- 히스토그램 평활화
11) 모폴로지 기능
- 침식 기능
- 팽창 기능
12) 이진화 기능
- 트랙바를 이용한 미리보기가 가능한 전역 이진화
- 평균값 이진화
- 가우시안 이진화
- Otsu 이진화
13) 특징추출 기능
- 레이블링 검출
- Sobel 엣지 검출
- 허프 서클
# 참고문헌
- [openCV를 이용한 디지털 영상처리], 인피니티북스, 500
- [Visual C++ 영상처리 프로그래밍], 길벗, 816
- [쉽게 배우는 MFC 윈도우 프로그래밍], 한빛아카데미, 772
