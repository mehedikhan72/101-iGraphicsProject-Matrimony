#include "iGraphics.h"
#include <bits/stdc++.h>
#include "models.h"
#include <string.h>
#include "cJSON.h"
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int screen_height = 1920;
int screen_width = 1080;

char s1[100] = "Halal Tinder";

// testing cJSON

typedef struct
{
	char name[50];
	int age;
	int isMarried;
} User;

void SerializeUser(User user, cJSON *json)
{
	cJSON_AddStringToObject(json, "name", user.name);
	cJSON_AddNumberToObject(json, "age", user.age);
	cJSON_AddBoolToObject(json, "isMarried", user.isMarried);
}

User DeserializeUser(cJSON *json)
{
	User user;
	cJSON *name = cJSON_GetObjectItem(json, "name");
	cJSON *age = cJSON_GetObjectItem(json, "age");
	cJSON *isMarried = cJSON_GetObjectItem(json, "isMarried");
	if (name && name->type == cJSON_String)
	{
		strcpy(user.name, name->valuestring);
	}
	if (age && age->type == cJSON_Number)
	{
		user.age = age->valueint;
	}
	if (isMarried && isMarried->type == cJSON_True)
	{
		user.isMarried = 1;
	}
	else
	{
		user.isMarried = 0;
	}
	return user;
}

// Page Stats
// 0 = Intro Page
// 1 = Feed
// 2 = Data Form
//....so far.
int page_state = 0;

char bg[100] = {"static\\halal-tinder-home1.bmp"};
void iDraw()
{
	// place your drawing codes here
	iClear();
	if (page_state == 0)
	{
		// intro page here
		iShowBMP(0, 0, bg);
		iText(200, 1000, "Welcome to Halal Tinder!!");
	}
	else if (page_state == 1)
	{
		// Feed here
		iText(200, 1000, "Here are some matches for you!!");
	}
	else if (page_state == 2)
	{
		// Data form here.
		iText(200, 1000, "Fill out your form!!");
	}
	// iText(500, 500, p1.username);
	// iText(550, 550, p1.name);a
}

void iKeyboard(unsigned char key)
{
	if(key == '0'){
		page_state = 0;
	}
	else if(key == '1'){
		page_state = 1;
	}
	else if (key == '2')
	{
		page_state = 2;
	}

	if (key == 'q')
	{
		exit(0);
	}
}

void iMouseMove(int mx, int my)
{
	printf("x = %d, y= %d\n", mx, my);
	// place your codes here
}

void iMouse(int button, int state, int mx, int my)
{
}

void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
	// place your codes for other keys here
}

int main()
{
	User user1 = {"esty", 25, 0};

	// Serialize users to JSON
	cJSON *json1 = cJSON_CreateObject();
	SerializeUser(user1, json1);
	char *json1_str = cJSON_Print(json1);
	cJSON_Delete(json1);

	// Write JSON strings to file
	FILE *fp = fopen("data.json", "a");
	if (fp)
	{
		fseek(fp, -3, SEEK_END); // move file pointer to last character
		off_t pos = ftell(fp);
		ftruncate(fileno(fp), pos); // truncate file to current position of file pointer
		fputs(",", fp);
		fputs("\n", fp);
		fputs(json1_str, fp);
		fputs("\n]", fp);
		fclose(fp);
	}

	FILE *fpr = fopen("data.json", "r");
	if (fpr)
	{
		char buffer[1024];
		fread(buffer, 1, 1024, fpr);
		fclose(fpr);

		cJSON *root = cJSON_Parse(buffer);
		cJSON *userJson = NULL;
		cJSON_ArrayForEach(userJson, root)
		{
			User user = DeserializeUser(userJson);
			printf("Name: %s, Age: %d, Married: %s\n", user.name, user.age, user.isMarried ? "Yes" : "No");
		}
		cJSON_Delete(root);
	}

	// place your own initialization codes here.
	iInitialize(screen_height, screen_width, "Halal Tinder");
	return 0;
}
