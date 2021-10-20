#include <windows.h>
#include <winuser.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void delay(int seconds) { 
    int milliSeconds = 1000 * seconds; 
    clock_t startTime = clock(); 
    while (clock() < startTime + milliSeconds); 
}


int main() {
	FILE *registerPoints;
	FILE *pointsGeo;
	POINT p;
	int i = 0;
	int numOfPoints = 27;
	long int positionX[numOfPoints];
	long int positionY[numOfPoints];
	
	sleep(10); //Delay antes de iniciar a contagem de pontos
	
	registerPoints = fopen("points.txt", "w");
		
	while(i < numOfPoints) {
		delay(2);
		GetCursorPos(&p);
		printf("X = %ld\t Y = %ld \n", p.x, p.y);
		fprintf(registerPoints, "X = %ld\t Y = %ld \n", p.x, p.y);
		positionX[i] = p.x;
		positionY[i] = p.y;
		i++;
	}
	
	fclose(registerPoints);
	pointsGeo = fopen("positions.geo", "w");

	i = 0;
	fprintf(pointsGeo, "lc=0.3;\n\n");
	
	while(i < numOfPoints) {
		fprintf(pointsGeo, "Point(%d)={%ld, %ld, 0, lc};\n", i+1, positionX[i], positionY[i]);
		i++;
	}

	i = 0;
	fprintf(pointsGeo, "\n\n");
	
	while(i < numOfPoints-1) {
		fprintf(pointsGeo, "Line(%d)={%d, %d};\n", i+1, i+1, i+2);
		i++;
	}
	
	fprintf(pointsGeo, "Line(%d)={%d, 1};\n", i+1, numOfPoints);
	i=0;
	fprintf(pointsGeo, "\n\n");
	fprintf(pointsGeo,"Curve Loop(1) = {");
	
	while(i < numOfPoints-1) {
		fprintf(pointsGeo, "%d,", i+1);
		i++;
	}
	
	fprintf(pointsGeo,"%d};\n", numOfPoints);
	fprintf(pointsGeo,"Plane Surface(1) = {1}; \n");
	fprintf (pointsGeo, "Physical Surface (1)={1};");
	
	fclose(pointsGeo);
	
	printf("\n Arquivo criado com sucesso!\n");
	
	system("pause");
	return 0;
}


