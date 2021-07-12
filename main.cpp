#include <graphics.h>
#include <math.h>

void DigitalDifferentialAnalyzer(float start_x, float start_y, float end_x, float end_y, short color){
	short delta_x = end_x - start_x;
	short delta_y = end_y - start_y;
	short step = abs(delta_x) > abs(delta_y) ? abs(delta_x) : abs(delta_y);
	float incX = delta_x / (float)step;
	float incY = delta_y / (float)step;
	short i;
	for(i = 0; i < step; i++){
		putpixel(start_x, start_y, color);
		start_x += incX;
		start_y += incY;
	}
}

void rotate2D(float* arr, float theta){
	float temp[] = {0, 0};                    
	temp[0] = arr[0] * cos(theta) - arr[1] * sin(theta);
	temp[1] = arr[0] * sin(theta) + arr[1] * cos(theta); 
	short i;
	for (i = 0; i < sizeof(temp) / sizeof(float); i++){
		arr[i] = temp[i];
	} 
}

void DDARectangle(float x, float y, float w, float h, double theta, short color){
	theta *= M_PI / 180;
	float points0[] = {- w / 2, - h / 2};
	rotate2D(points0, theta);
	float points1[] = {w / 2, - h / 2};
	rotate2D(points1, theta);
	DigitalDifferentialAnalyzer(points0[0] + x, 
								points0[1] + y, 
								points1[0] + x, 
								points1[1] + y,
								color);
	float points2[] = {w / 2, h / 2};
	rotate2D(points2, theta);
	DigitalDifferentialAnalyzer(points1[0] + x, 
	 							points1[1] + y, 
								points2[0] + x, 
								points2[1] + y,
								color);
	float points3[] = {-w / 2, h / 2};
	rotate2D(points3, theta);
	DigitalDifferentialAnalyzer(points2[0] + x, 
	 							points2[1] + y, 
								points3[0] + x, 
								points3[1] + y,
								color);
								 
	DigitalDifferentialAnalyzer(points3[0] + x, 
	 							points3[1] + y, 
								points0[0] + x, 
								points0[1] + y,
								color);
}

int main(){
	
	int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    short w = 100;
	short h = 50; 
    short theta = 0;
    short color = 0;
			
	while(1){
		cleardevice();
		DDARectangle(300, 100, w, h, theta % 360, color % 15 + 1);                                   
		DDARectangle(400, 300, w, h, -theta % 360, color % 15 + 1);
		theta += 5;
		color++;
		delay(1);          
	}
	
    getch();
    closegraph();
	return 0;
}
