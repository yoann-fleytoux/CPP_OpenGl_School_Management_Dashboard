#include <math.h>
#include <gl/glut.h>
#include <windows.h>
#include <mmsystem.h>

#ifndef RESOURCEMANAGEMENT_H_
#include "resourceManagement.h"
#endif // RESOURCEMANAGEMENT_H_
GLint width = 1300;
GLint height = 700;

//Variables for pie chart
const GLdouble twoPi = 6.283185;
int triangleAmount = 100; //# of triangles used to draw circle
float radius;
float centerCircleX;
float centerCircleY;

//Scatter plot start points
float START_X = 700;
float START_Y = 50;

//Color declarations
GLfloat redElec = 0.9;
GLfloat greenElec = 1.0;
GLfloat blueElec = 0.0;
GLfloat redWater = 0.0;
GLfloat greenWater = 0.0;
GLfloat blueWater = 1.0;
GLfloat redGas = 0.0;
GLfloat greenGas = 1.0;
GLfloat blueGas = 0.0;
GLfloat redCulture = 1.0;
GLfloat greenCulture = 0.0;
GLfloat blueCulture = 1.0;

//Helps for iterating
GLfloat pieColors[4][3] = {{redElec, greenElec, blueElec},
{redWater, greenWater, blueWater},
{redGas, greenGas, blueGas},
{redCulture,greenCulture,blueCulture}};

//Initializes
void init(void) {
    glClearColor(0.3,0.3,0.3,0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    gluOrtho2D(0.0,width,0.0,height);
    glColor3f(0.5,0.5,0.5);
}

//Key function
void key(unsigned char key, int x, int y) {
    switch (key) {
        case 27 :
        case 'q':
            exit(0);
        break;
        case 's':
            writeToCsv();
        break;
        case 'l':
            getFromCsv();
        break;
        case 'y':
            if (timeBegin >= 8) {
                timeBegin-=1;
            } else {
                sndPlaySoundA ("buzina.wav", SND_ASYNC);
            }
        break;
        case 'u':
            if (timeBegin <= 10) {
                timeBegin+=1;
            } else {
                sndPlaySoundA ("buzina.wav", SND_ASYNC);
            }
        break;
        case 'h':
            if (timeEnd >= 14) {
                timeEnd-=1;
            } else {
                sndPlaySoundA ("buzina.wav", SND_ASYNC);
            }
        break;
        case 'j':
            if (timeEnd <= 17) {
                timeEnd +=1;
            } else {
                sndPlaySoundA ("buzina.wav", SND_ASYNC);
            }
        break;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glutPostRedisplay();
}

//Other key function
void specialKey(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_F2:
            if (costElectricity >= 50) {
                costElectricity-=50;
            } else {
                sndPlaySoundA ("buzina.wav", SND_ASYNC);
            }
        break;
        case GLUT_KEY_F3:
            if (costElectricity <= 1550) {
                costElectricity+=50;
            } else {
                sndPlaySoundA ("buzina.wav", SND_ASYNC);
            }
        break;
        case GLUT_KEY_F4:
            if (costWater >= 20) {
                costWater-=20;
            } else {
                sndPlaySoundA ("buzina.wav", SND_ASYNC);
            }
        break;
        case GLUT_KEY_F5:
            if (costWater <= 580) {
                costWater+=20;
            } else {
                sndPlaySoundA ("buzina.wav", SND_ASYNC);
            }
        break;
        case GLUT_KEY_F6:
            if (costGas >= 10) {
                costGas-=10;
            } else {
                sndPlaySoundA ("buzina.wav", SND_ASYNC);
            }
        break;
        case GLUT_KEY_F7:
            if (costGas <= 290) {
                costGas+=10;
            } else {
                sndPlaySoundA ("buzina.wav", SND_ASYNC);
            }
        break;
        case GLUT_KEY_F8:
            if (students >= 2) {
                students-=1;
            } else {
                sndPlaySoundA ("buzina.wav", SND_ASYNC);
            }
        break;
        case GLUT_KEY_F9:
            if (students <= 35) {
                students+=1;
            } else {
                sndPlaySoundA ("buzina.wav", SND_ASYNC);
            }
        break;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glutPostRedisplay();
}

//Manages writing
void writeText(string text, int x, int y) {
    int len = text.length();
    glRasterPos2i(x,y);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    }
}

void pieChart (void)
{
    string pieLabels[4] = {"Electricity","Water","Gas","Culture"};

    radius = width / 10;

    int startPos = 0;
    int pieAngles[4];

    GLfloat dataValues[4] = {costElectricity/monthlyBudget,costWater/monthlyBudget,costGas/monthlyBudget,getCulturalBudget()/monthlyBudget};
    GLfloat dataSum = 0.0;
    glColor3f(1.0,0.0,1.0);
    centerCircleX = width / 1.5;                  // Circle center position.
    centerCircleY = height / 1.3;

    for(int i = 0; i < 4; i++)
        dataSum += dataValues[i];

    for (int i = 0; i < 4; i++)
        pieAngles[i] = dataValues[i]*100;

    triangleAmount = 0;
    for (int i = 0; i < 4; i++)
        triangleAmount += pieAngles[i];

    for (int i = 0; i < 4; i++) {

        glColor3f(pieColors[i][0],pieColors[i][1],pieColors[i][2]);
        writeText(pieLabels[i],700+(i*100),390);
        glBegin(GL_TRIANGLE_FAN);

            glVertex3f(centerCircleX, centerCircleY, 0);
            float t;
            for (int j = startPos; j <= startPos + pieAngles[i]; j++) {
                t = (twoPi*(float)j/(float)triangleAmount) + 3.141592;
                glVertex3f(centerCircleX - sin(t) * radius, centerCircleY + cos(t) * radius, 0);
            }
            startPos += pieAngles[i];

        glEnd();
        glColor3f(1.0,1.0,1.0);
        writeText("Repartition of expenses this month", centerCircleX+100, centerCircleY+100);
    }
    glutPostRedisplay();

}

//Draws the axis for scatter plot and bar chart
void drawAxis(float width, float height, float START_X, float START_Y) {

    // end points for each axis.
	float endX = START_X + width;
	float endY = START_Y + height;

    glLineWidth(1.3f);
	glBegin(GL_LINES);

        // Draw X Axis
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(START_X, START_Y);
        glVertex2f(endX, START_Y);

        // Draw Y Axis
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(START_X, START_Y + 0.5f);
        glVertex2f(START_X, endY);

	glEnd();
}
//draws the bar chart
void BarChart(float width, float height) {

    string barLabels[4] = {"Electricity", "Water", "Gas", "Culture"};
    float lastYearAverages[4] = {lastYearAverageElectricity, lastYearAverageWater, lastYearAverageGas, lastYearAverageCulture};
    float thisMonthsBills[4] = {costElectricity, costWater, costGas, getCulturalBudget()};
    //Draw axis
    drawAxis(width, height, 70, START_Y);
    glColor3f(1.0,1.0,1.0);
    writeText("Comparison of expenses : last year (left), this year (right)", 70, START_Y-40);

    float top = getBiggestBill()/(getBiggestBill()+100)*height+START_Y;
    int toDisplay;
    //Write the number labels
    for (int i = 0; i < 7; i++) {
        stringstream ss;
        toDisplay = getBiggestBill() - i*(getBiggestBill()/6.0);
        ss << toDisplay;
        float tempY = top - ((top - START_Y)/6)*i;
        writeText(ss.str(), 40, tempY);
    }
    for (int i = 0; i < 4; i++) {
        glColor3f(pieColors[i][0],pieColors[i][1],pieColors[i][2]);

        //Print labels
        float tempXLabels = i * width / 4 + 120;
        writeText(barLabels[i], tempXLabels, START_Y-15);

        float tempX = i * width / 4 + 110;
        float tempY = lastYearAverages[i] / (getBiggestBill()+100) * height + START_Y;
        float tempYThisYear = thisMonthsBills[i] / (getBiggestBill()+100) * height + START_Y;

        glColor3f(pieColors[i][0]-0.3,pieColors[i][1]-0.3,pieColors[i][2]-0.3);
        glBegin(GL_POLYGON);
            glVertex2f(tempX, START_Y+1);
            glVertex2f(tempX+25, START_Y+1);
            glVertex2f(tempX+25, tempY);
            glVertex2f(tempX, tempY);
        glEnd();
        tempX+=30;

        glColor3f(pieColors[i][0],pieColors[i][1],pieColors[i][2]);

        glBegin(GL_POLYGON);
            glVertex2f(tempX, START_Y+1);
            glVertex2f(tempX+25, START_Y+1);
            glVertex2f(tempX+25, tempYThisYear);
            glVertex2f(tempX, tempYThisYear);
        glEnd();
    }
}


//Draws the scatter plot
void graph(float width, float height){

    string monthLabels[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	// end points for each axis.
	float endX = START_X + width;
	float endY = START_Y + height;

	//FontRenderer::RenderText(GetTitle(), 0.5f, START_X, endY + 90.0f, Vector3f(0.0f, 1.0f, 1.0f), true);

    glColor3f(1.0,1.0,1.0);
    writeText("Expenses by month (all above the line goes to culture)", START_X, START_Y-40);

    drawAxis(width, height, START_X, START_Y);

	glPointSize(5.0f);
	glBegin(GL_LINES);

	//Draw the lines between points
	glColor3f(0.0f, 0.0f, 1.0f);
	for (int i = 1; i < 12; i++) {
		float tempX = i * width / 12 + START_X+15;
		float tempY = historyByMonth[i] / (getHighestBudget()+200) * height + START_Y;
		float tempX2 = (i-1) * width / 12 + START_X+15;
		float tempY2 = historyByMonth[i-1] / (getHighestBudget()+200) * height + START_Y;
		glVertex2f(tempX, tempY);
		glVertex2f(tempX2,tempY2);
	}
	// Draw the points
	for (int i = 0; i < 12; i++) {
		float tempX = i * width / 12 + START_X+15;
		float tempY = historyByMonth[i] / (getHighestBudget()+200) * height + START_Y;

		glColor3f(1.0f, 1.0f, 1.0f);
		// Draw a cross
		glVertex2f(tempX - 6, tempY - 6);
		glVertex2f(tempX + 6, tempY + 6);
        glVertex2f(tempX - 6, tempY + 6);
		glVertex2f(tempX + 6, tempY - 6);

	}
    //Draw the line for the budget allowed
    float tempY = endY*(monthlyBudget/getHighestBudget());
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(START_X,tempY);
    glVertex2f(endX,tempY);

    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    stringstream budgetStream;
    budgetStream << "Monthly Budget (" << monthlyBudget << ")";
    writeText(budgetStream.str(), START_X, tempY+5);

    //Write the month labels
    for (int i = 0; i < 12; i++) {
        float tempX = i * width / 12 + START_X+5;
        writeText(monthLabels[i], tempX, START_Y-15);
    }

    float top = getHighestBudget()/(getHighestBudget()+200)*height+START_Y;
    int toDisplay = getHighestBudget();
    //Write the number labels
    for (int i = 0; i < 7; i++) {
        stringstream ss;
        toDisplay = getHighestBudget() - i*(getHighestBudget()/6.0);
        ss << toDisplay;
        float tempY = top - ((top - START_Y)/6)*i;
        writeText(ss.str(), START_X-30, tempY);
    }

}

//Prints all the text
void printInformations() {

    glColor3f(1.0,1.0,1.0);
    writeText("Use the buttons to change the data and update the pie chart.",50,650);
    glColor3f(redElec,greenElec,blueElec);

    stringstream ss;
    ss << "Electricity : " << costElectricity << " euros - F2 : -50 euros F3 : +50 euros.";
    writeText(ss.str(),50,625);
    ss.str("");

    glColor3f(redWater,greenWater,blueWater);
    ss << "Water : " << costWater << " euros - F4 : -20 euros F5 : +20 euros.";
    writeText(ss.str(),50,600);
    ss.str("");

    glColor3f(redGas,greenGas,blueGas);
    ss << "Gas : " << costGas << " euros - F6 : -10 euros F7 : +10 euros.";
    writeText(ss.str(),50,575);
    ss.str("");

    glColor3f(redCulture,greenCulture,blueCulture);
    ss << "The rest of the budget (" << getCulturalBudget() << ") is automatically dedicated to cultural events.";
    writeText(ss.str(),50,550);
    ss.str("");

    glColor3f(1.0,1.0,1.0);
    writeText("Press (s)ave to write this month's data to data.sav",50,525);

    writeText("Press (l)oad to get this month's data from data2.sav",50,500);

    ss << "Number of students : " << students << " - F8 : -1 F9 : +1.";
    writeText(ss.str(),50,475);
    ss.str("");

    writeText("Indicators : ",50,450);

    ss << "- Total electricity costs per student per hour : " << electricityPerStudentPerHour() << " euros.";
    writeText(ss.str(),80,425);
    ss.str("");

    ss << "- Total costs per student per month (outside of cultural activities) : " << totalCostsPerStudentPerMonth() << " euros.";
    writeText(ss.str(),80,400);
    ss.str("");

    ss << "Beginning of a day : " << timeBegin << " - (y) : -1 (u) : +1.";
    writeText(ss.str(),50,375);
    ss.str("");

    ss << "End of a day : " << timeEnd << " - (h) : -1 (j) : +1.";
    writeText(ss.str(),50,350);
    ss.str("");

    if (timeBegin == 7 && timeEnd == 18) {
        writeText("Your school is a prison.",50,325);
    }

    glutPostRedisplay();
}

//Calls the different functions to print
void display(void) {

    pieChart();
    printInformations();
    graph(500,230);
    BarChart(500,230);
    glFlush();
}

//Manages resizing
void reshape(int new_width, int new_height){
    if (new_height == 0) {
        new_height = 1;
    }
    glViewport(0,0,new_width,new_height);
    glFlush();
}

//Main
int main(int argc,char** argv) {
    glutInit(&argc,argv);

    FreeConsole();

    glutInitWindowSize(width,height);
    glutInitWindowPosition(0,0);

    glutCreateWindow("School management dashboard");
    init();
    computeAverages();

    glutReshapeFunc(reshape);

    glutKeyboardFunc(key);
    glutSpecialFunc(specialKey);
    glutDisplayFunc(display);

    glutMainLoop();
    return EXIT_SUCCESS;
}
