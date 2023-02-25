#include "cJSON.h"
#include "iGraphics.h"
#include "models.h"
#include <bits/stdc++.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

using namespace std;

int screen_height = 1920;
int screen_width = 1080;

char s1[100] = "Halal Tinder";

// testing cJSON

typedef struct
{
    int pk;            // unique field to retrieve data.
    char username[64]; // this field will be used to distinguish every user.
    char name[128];
    char age[56];
    char gender[7];
    char religion[24];
    char location[128];
    char education[256];
    char occupation[128];
    char net_worth[256]; // in bdt.
    char about[1000];
    char height[100];
    char weight[100];
    char body_color[24];
    char fathers_occupation[128];
    char mothers_occupation[128];
    char is_married_already[24];
    char is_divorcee[24];

} User;

void SerializeUser(User user, cJSON *json) {
    cJSON_AddNumberToObject(json, "pk", user.pk);
    cJSON_AddStringToObject(json, "username", user.username);
    cJSON_AddStringToObject(json, "name", user.name);
    cJSON_AddStringToObject(json, "age", user.age);
    cJSON_AddStringToObject(json, "gender", user.gender);
    cJSON_AddStringToObject(json, "religion", user.religion);
    cJSON_AddStringToObject(json, "location", user.location);
    cJSON_AddStringToObject(json, "education", user.education);
    cJSON_AddStringToObject(json, "occupation", user.occupation);
    cJSON_AddStringToObject(json, "net_worth", user.net_worth);
    cJSON_AddStringToObject(json, "about", user.about);
    cJSON_AddStringToObject(json, "height", user.height);
    cJSON_AddStringToObject(json, "weight", user.weight);
    cJSON_AddStringToObject(json, "body_color", user.body_color);
    cJSON_AddStringToObject(json, "fathers_occupation", user.fathers_occupation);
    cJSON_AddStringToObject(json, "mothers_occupation", user.mothers_occupation);
    cJSON_AddStringToObject(json, "is_married_already", user.is_married_already);
    cJSON_AddStringToObject(json, "is_divorcee", user.is_divorcee);
}

User DeserializeUser(cJSON *json) {
    User user;
    cJSON *pk = cJSON_GetObjectItem(json, "pk");
    cJSON *username = cJSON_GetObjectItem(json, "username");
    cJSON *name = cJSON_GetObjectItem(json, "name");
    cJSON *age = cJSON_GetObjectItem(json, "age");
    cJSON *gender = cJSON_GetObjectItem(json, "gender");
    cJSON *religion = cJSON_GetObjectItem(json, "religion");
    cJSON *location = cJSON_GetObjectItem(json, "location");
    cJSON *education = cJSON_GetObjectItem(json, "education");
    cJSON *occupation = cJSON_GetObjectItem(json, "occupation");
    cJSON *net_worth = cJSON_GetObjectItem(json, "net_worth");
    cJSON *about = cJSON_GetObjectItem(json, "about");
    cJSON *height = cJSON_GetObjectItem(json, "height");
    cJSON *weight = cJSON_GetObjectItem(json, "weight");
    cJSON *body_color = cJSON_GetObjectItem(json, "body_color");
    cJSON *fathers_occupation = cJSON_GetObjectItem(json, "fathers_occupation");
    cJSON *mothers_occupation = cJSON_GetObjectItem(json, "mothers_occupation");
    cJSON *is_married_already = cJSON_GetObjectItem(json, "is_married_already");
    cJSON *is_divorcee = cJSON_GetObjectItem(json, "is_divorcee");

    if (pk && pk->type == cJSON_Number) {
        user.pk = pk->valueint;
    }
    if (username && username->type == cJSON_String) {
        strcpy(user.username, username->valuestring);
    }
    if (name && name->type == cJSON_String) {
        strcpy(user.name, name->valuestring);
    }
    if (age && age->type == cJSON_String) {
        strcpy(user.age, age->valuestring);
    }
    if (gender && gender->type == cJSON_String) {
        strcpy(user.gender, gender->valuestring);
    }
    if (religion && religion->type == cJSON_String) {
        strcpy(user.religion, religion->valuestring);
    }
    if (location && location->type == cJSON_String) {
        strcpy(user.location, location->valuestring);
    }
    if (education && education->type == cJSON_String) {
        strcpy(user.education, education->valuestring);
    }
    if (occupation && occupation->type == cJSON_String) {
        strcpy(user.occupation, occupation->valuestring);
    }
    if (net_worth && net_worth->type == cJSON_String) {
        strcpy(user.net_worth, net_worth->valuestring);
    }
    if (about && about->type == cJSON_String) {
        strcpy(user.about, about->valuestring);
    }
    if (height && height->type == cJSON_String) {
        strcpy(user.height, height->valuestring);
    }
    if (weight && weight->type == cJSON_String) {
        strcpy(user.weight, weight->valuestring);
    }
    if (body_color && body_color->type == cJSON_String) {
        strcpy(user.body_color, body_color->valuestring);
    }
    if (fathers_occupation && fathers_occupation->type == cJSON_String) {
        strcpy(user.fathers_occupation, fathers_occupation->valuestring);
    }
    if (mothers_occupation && mothers_occupation->type == cJSON_String) {
        strcpy(user.mothers_occupation, mothers_occupation->valuestring);
    }
    if (is_married_already && is_married_already->type == cJSON_String) {
        strcpy(user.is_married_already, is_married_already->valuestring);
    }
    if (is_divorcee && is_divorcee->type == cJSON_String) {
        strcpy(user.is_divorcee, is_divorcee->valuestring);
    }

    return user;
}

// Page Stats
// 0 = Intro Page
// 1 = Feed
// 2 = Search
// 3 = Data Form
//....so far.
int page_state = 0;

char bg[4][100] = {"./static/halal-tinder-home1.png", "./static/halal-tinder-bg-people.png", "./static/halal-tinder-bg-search.png", "./static/halal-tinder-bg-add.png"};
char btns[7][30] = {"./static/Home.png", "./static/People.png", "./static/Search.png", "./static/Add.png", "./static/next-btn.png", "./static/previous-btn.png", "./static/submit-btn.png"};
char texts[1][200] = {"./static/mat-t1.png"};
char logo[2][100] = {"./static/male-logo.png", "./static/female-logo.png"};
char form[48] = "./static/sq-form2.png";

// User input setup
char input_box[17][256];
int index_for_input[17];
int input_state;

int btn_posX = 1700;
int btn_posY = 860;
int minusY = 0;

int getFile1Size() {
    FILE *fptr = fopen("data.json", "r");
    if (fptr == NULL) {
        printf("Error: could not open file.\n");
        return 1;
    }

    char buffer[1024000];
    size_t read_size = fread(buffer, 1, 1024000, fptr);
    fclose(fptr);

    if (read_size == 0) {
        printf("Error: could not read file.\n");
        return 1;
    }

    cJSON *root = cJSON_Parse(buffer);
    if (root == NULL) {
        printf("Error: could not parse JSON.\n");
        return 1;
    }

    int num_instances = cJSON_GetArraySize(root);
    printf("Number of instances in file: %d\n", num_instances);

    cJSON_Delete(root);
    return num_instances;
}

int file1_size = getFile1Size();
// Will show users randomly later and make sure noone is shown twice.
// For now let's just do it in order.
int order = 1;

// Logic for the btns
bool first_item = true;

void iDraw() {

    // place your drawing codes here
    iClear();
    if (page_state == 0) {
        // intro page here
        iShowBMP(0, 0, bg[0]);
    } else if (page_state == 1) {
        // Feed here
        iShowBMP(0, 0, bg[1]);

        // Next n prev btn logic
        if (order > file1_size) {
            iText(660, 520, "No candidates available at this moment. Please visit later.", GLUT_BITMAP_TIMES_ROMAN_24);
            iShowBMP(850, 100, btns[5]);
            return;
        }

        // Read from file
        FILE *fpr = fopen("data.json", "r");
        if (fpr) {
            char buffer[1024000];
            fread(buffer, 1, 1024000, fpr);
            fclose(fpr);

            cJSON *root = cJSON_Parse(buffer);
            cJSON *userJson = NULL;
            cJSON_ArrayForEach(userJson, root) {
                User user = DeserializeUser(userJson);
                // check if primary key matches
                if (user.pk == order) {
                    // Conversion
                    // char age[32];
                    // itoa(user.age, age, 10);
                    // char net_worth[32];
                    // itoa(user.net_worth, net_worth, 10);

                    if (strcmp(user.gender, "male") == 0) {
                        iShowBMP(50, 600, logo[0]);
                    } else {
                        iShowBMP(50, 600, logo[1]);
                    }

                    iText(370, 820, user.name, GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(370, 770, user.age, GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(390, 770, ",", GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(410, 770, user.gender, GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(370, 720, user.about, GLUT_BITMAP_TIMES_ROMAN_24);

                    // Show a gender specific image here!!
                    iText(100, 550, "Name: ", GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(300, 550, user.name, GLUT_BITMAP_TIMES_ROMAN_24);

                    iText(100, 500, "Gender: ", GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(300, 500, user.gender, GLUT_BITMAP_TIMES_ROMAN_24);

                    iText(100, 450, "Religion: ", GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(300, 450, user.religion, GLUT_BITMAP_TIMES_ROMAN_24);

                    iText(100, 400, "Lives at: ", GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(300, 400, user.location, GLUT_BITMAP_TIMES_ROMAN_24);

                    iText(100, 350, "Formal education: ", GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(300, 350, user.education, GLUT_BITMAP_TIMES_ROMAN_24);

                    iText(100, 300, "Occupation: ", GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(300, 300, user.occupation, GLUT_BITMAP_TIMES_ROMAN_24);

                    iText(100, 250, "Net worth(BDT): ", GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(300, 250, user.net_worth, GLUT_BITMAP_TIMES_ROMAN_24);

                    iText(600, 550, "Height: ", GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(850, 550, user.height, GLUT_BITMAP_TIMES_ROMAN_24);

                    iText(600, 500, "Weight: ", GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(850, 500, user.weight, GLUT_BITMAP_TIMES_ROMAN_24);

                    iText(600, 450, "Body Color: ", GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(850, 450, user.body_color, GLUT_BITMAP_TIMES_ROMAN_24);

                    iText(600, 400, "Father's Occupation: ", GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(850, 400, user.fathers_occupation, GLUT_BITMAP_TIMES_ROMAN_24);

                    iText(600, 350, "Mother's Occupation: ", GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(850, 350, user.mothers_occupation, GLUT_BITMAP_TIMES_ROMAN_24);

                    iText(600, 300, "Is Married Already? ", GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(850, 300, user.is_married_already, GLUT_BITMAP_TIMES_ROMAN_24);

                    iText(600, 250, "Is divorcee? ", GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(850, 250, user.is_divorcee, GLUT_BITMAP_TIMES_ROMAN_24);

                    if (first_item) {
                        iShowBMP(850, 100, btns[4]);
                    } else {
                        iShowBMP(750, 100, btns[5]);
                        iShowBMP(1000, 100, btns[4]);
                    }

                    break; // exit loop since we found the user
                }
            }
            cJSON_Delete(root);
        }
    } else if (page_state == 2) {
        // Search option here.
        iShowBMP(0, 0, bg[2]);
    } else if (page_state == 3) {
        // Data form here.
        iShowBMP(0, 0, bg[3]);
        iShowBMP2(50, 80, form, 255);
        // printf("%d\n", input_state);

        // Show user given input
        int diff_y2 = 0;
        for (int i = 0; i < 8; i++) {
            iText(80, 770 - diff_y2, input_box[i], GLUT_BITMAP_TIMES_ROMAN_24);
            diff_y2 += 83;
        }

        diff_y2 = 0;
        for (int i = 8; i < 16; i++) {
            iText(660, 770 - diff_y2, input_box[i], GLUT_BITMAP_TIMES_ROMAN_24);
            diff_y2 += 83;
        }

        iText(80, 105, input_box[16], GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP2(1210, 410, btns[6], 255);
    }
}

void iKeyboard(unsigned char key) {
    // User input
    if (page_state == 3) {
        if (key != '\b') {
            input_box[input_state][index_for_input[input_state]] = key;
            index_for_input[input_state]++;
            input_box[input_state][index_for_input[input_state]] = '\0';
        } else {
            if (index_for_input[input_state] <= 0) {
                index_for_input[input_state] = 0;
            } else {
                index_for_input[input_state]--;
                input_box[input_state][index_for_input[input_state]] = '\0';
            }
        }
    }

    if (key == 'q') {
        exit(0);
    }
}

void iMouseMove(int mx, int my) {
    printf("x = %d, y= %d\n", mx, my);
    // place your codes here
}

void submitForm() {
    int new_pk = file1_size + 1;
    printf("%d", new_pk);
    // User user1 = {new_pk, input_box[0], input_box[1], input_box[2], input_box[3], input_box[4], input_box[5], input_box[6], input_box[7],
    // input_box[8], input_box[16], input_box[9], input_box[10], input_box[11], input_box[12], input_box[13], input_box[14], input_box[15]};
    for (int i = 0; i < 17; i++) {
        printf("%s\n", input_box[i]);
    }

    char hm[5] = "segs";
    printf("%s\n", hm);
    User user1 = {0};
    user1 = {
        new_pk,
        strcpy(user1.name, *hm),
        "bruh",
        "bruh",
        "bruh",
        "bruh",
        "bruh",
        "bruh",
        "bruh",
        "bruh",
        "bruh",
        "bruh",
        "bruh",
        "bruh",
        "bruh",
        "bruh",
        "bruh",
        "bruh",
    };

    // Serialize users to JSON
    cJSON *json1 = cJSON_CreateObject();
    SerializeUser(user1, json1);
    char *json1_str = cJSON_Print(json1);
    cJSON_Delete(json1);

    // Write JSON strings to file
    FILE *fp = fopen("data.json", "a");
    if (fp) {
        fseek(fp, -3, SEEK_END); // move file pointer to last character
        off_t pos = ftell(fp);
        ftruncate(fileno(fp), pos); // truncate file to current position of file pointer
        fputs(",", fp);
        fputs("\n", fp);
        fputs(json1_str, fp);
        fputs("\n]", fp);
        fclose(fp);
    }
}

void iMouse(int button, int state, int mx, int my) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (mx > 1660 && mx < 1810 && my > 870 && my < 1010) {
            page_state = 0;
        } else if (mx > 1660 && mx < 1810 && my > 630 && my < 770) {
            page_state = 1;
        } else if (mx > 1660 && mx < 1810 && my > 390 && my < 530) {
            page_state = 2;
        } else if (mx > 1660 && mx < 1810 && my > 155 && my < 250) {
            page_state = 3;
        }

        if (page_state == 1 && order <= file1_size) {
            if (first_item && mx >= 850 && mx <= 1050 && my >= 100 && my <= 175) {
                first_item = false;
                order++;
            }

            if (!first_item && mx >= 750 && mx <= 950 && my >= 100 && my <= 175) {
                order--;
            } else if (!first_item && mx >= 1000 && mx <= 1200 && my >= 100 && my <= 175) {
                order++;
            }

            if (order == 1) {
                first_item = true;
            }
        }
        if (page_state == 1 && order > file1_size) {
            if (mx >= 850 && mx <= 1050 && my >= 100 && my <= 175) {
                order--;
            }
        }

        // User input
        if (page_state == 3) {
            input_state = -1; // That means no input box was clicked.
            // left part
            int diff_y = 0;
            for (int i = 0; i < 8; i++) {
                if (mx > 80 && mx < 550 && my > 750 - diff_y && my < 800 - diff_y) {
                    input_state = i;
                }
                diff_y += 80;
            }

            // right part
            diff_y = 0;
            for (int i = 8; i < 16; i++) {
                if (mx > 660 && mx < 1130 && my > 750 - diff_y && my < 800 - diff_y) {
                    input_state = i;
                }
                diff_y += 80;
            }

            // last one
            if (mx > 80 && mx < 1130 && my > 95 && my < 145) {
                input_state = 16;
            }
            // printf("%d\n", input_state);

            // form submit
            if (mx > 1210 && mx < 1360 && my > 410 && my < 560) {
                submitForm();
            }
        }
    }
}

void iSpecialKeyboard(unsigned char key) {

    if (key == GLUT_KEY_END) {
        exit(0);
    }
    // place your codes for other keys here
}

int main() {

    for (int i = 0; i < 17; i++) {
        index_for_input[i] = 0;
    }

    // place your own initialization codes here.
    iInitialize(screen_height, screen_width, "Halal Tinder");
    return 0;
}
