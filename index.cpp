#include "raylib.h"
#include <vector>

#define ScreenWidth 900
#define ScreenHeight 600

#define MinWindowWidth 700
#define MinWindowHeight 500

#define FPS 120

#define NORMAL 0
#define COMPARING 1
#define SORTED 2
#define SELECTED 3
#define MINIMUM 4
#define PIVOT 5
#define LEFT 6
#define RIGHT 7


int NumberOfPillers = 50;

bool ShouldRandomizeArray = true;
bool ShouldShowMenuScreen = true;
bool SelectionSortPressed = false;
bool ShouldShowStartOptions = false;
std::vector<bool *> SortingChoice = {
    &SelectionSortPressed,
};

bool addSpeed = false;
bool subSpeed = false;
bool addSize = false;
bool subSize = false;
bool NormalSize = false;
bool NormalSpeed = false;



void ShowMenuScreen();
void ShowStartOptions();
void ChangeSize(char operation, int &value);
void ChangeSpeed(char operation, int &value);
void Button(float x, float y, char *Text, Color color, bool &state);
void Selection_Sort_Button(float size, char Selection_Sort_Text[]);
std::vector<std::pair<int, int>> arr(NumberOfPillers);

Color FindColorForPiller(int pillerState);
void DrawArray(std::vector<std::pair<int, int>> arr);
void RandomizeArray(std::vector<std::pair<int, int>> &arr);
int SortingSpeed = 61;

int main()
{

    // Window Configuration:
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(ScreenWidth, ScreenHeight, "Algo_Visualiser");
    SetWindowMinSize(MinWindowWidth, MinWindowHeight);

    // Set FPS
    SetTargetFPS(FPS);

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BROWN);
        if (ShouldRandomizeArray){
            RandomizeArray(arr);
        }
        if (ShouldShowMenuScreen){
            ShowMenuScreen();
        }
        ShouldShowStartOptions = false;
        for (bool *i : SortingChoice){
            if (*i == true)
                ShouldShowStartOptions = true;
        }

        if (ShouldShowStartOptions){
            ShowStartOptions();
        }
        
        

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void RandomizeArray(std::vector<std::pair<int, int >> &arr){
    // RandomizeArray
    if (ShouldRandomizeArray){
        for (int i = 0; i < NumberOfPillers; i++)
            arr[i] = {GetRandomValue(40, MinWindowHeight-80), NORMAL};
            
        ShouldRandomizeArray = false;
    }
}


void DrawArray(std::vector<std::pair<int, int>> arr){
    // Drawing the array / pillers:
    float BarWidth = (float) GetScreenWidth() / NumberOfPillers;


    for (int i = 0; i < NumberOfPillers; i++){ 
        Color color = FindColorForPiller(arr[i].second);

        DrawRectangleV (Vector2{(float) i*BarWidth, 
            (float) GetScreenHeight() - arr[i].first},
            Vector2{BarWidth, (float) arr[i].first}, color);
    }
}

Color FindColorForPiller(int pillerState){
    switch (pillerState)
    {
    case SELECTED:
        return BLUE;
        break;

    case COMPARING:
        return BLUE;
        break;
    
    case SORTED:
        return RAYWHITE;
        break;

    case MINIMUM:
        return SKYBLUE;
        break;


    case LEFT:
        return SKYBLUE;
        break;

    case RIGHT:
        return BLUE;
        break;

    case PIVOT:
        return BLUE;
        break;

    default:
        return BLACK;
        break;
    }
}

void ShowMenuScreen(){
    float font = (2.5 * GetScreenWidth()) / 100;
    char Selection_Sort_text[] = "Selection Sort!";            
    float tmp =MeasureText(Selection_Sort_text, font) ;
    Selection_Sort_Button(tmp, Selection_Sort_text);

    DrawArray(arr);
}

void Selection_Sort_Button(float size, char Selection_Sort_Text[]){
    Color color;
    if (SelectionSortPressed)
        color = BLACK;
    else
        color = RAYWHITE;

    Button(size, GetScreenHeight()/20, Selection_Sort_Text, color, 
        SelectionSortPressed);
}
void Button(float x, float y, char *Text, Color color, bool &state){
    float font = (2.5 * GetScreenWidth()) / 100;
    Rectangle r1 = {
        .x = x,
        .y = y,
        .width = (float) MeasureText(Text, font),
        .height = (float) font,
    };

    
    if (CheckCollisionPointRec(GetMousePosition(), r1)){
        
        DrawText(Text, x, y, font, RED);

        if (IsMouseButtonPressed(0)){
            if (state == true)
                state = false;
            else 
                state = true;
            return;
        }   
        

    } else {
        DrawText(Text, x, y, font, color);
    }

    return;
}

void ShowStartOptions(){
    float font = (2.5 * GetScreenWidth()) / 100;

    char StartText[] = "Start Game!";
    float tmp = (27*GetScreenWidth()) / 100; 

    tmp += MeasureText(StartText, font) + 75;
    char RandomizeArrayText[] = "Randomize Array!";
    Button(tmp, GetScreenHeight()/20 + font*2,
        RandomizeArrayText, BLUE, ShouldRandomizeArray);

    
    addSpeed = false;
    subSpeed = false;
    addSize = false;
    subSize = false;

    NormalSize = false;
    NormalSpeed = false;

    tmp = (84.2 * GetScreenWidth()) / 100;
    char TimeButtonText[] = "Speed";

 

    Button(tmp, GetScreenHeight()/20 + font*2,
        TimeButtonText, BLUE, NormalSpeed);

    if (NormalSpeed){
        ChangeSpeed('/', SortingSpeed);
        return;
    }


    tmp += MeasureText(TimeButtonText, font) + 20;
    char SpeedPlusButtonText[] = "+";
    Button(tmp, GetScreenHeight()/20 + font*2,
        SpeedPlusButtonText, BLACK, addSpeed); 


    if (addSpeed){
        ChangeSpeed('+', SortingSpeed);
        return;
    }

    tmp += MeasureText(SpeedPlusButtonText, font) + 20;
    char SpeedMinusButtonText[] = "-";
    Button(tmp, GetScreenHeight()/20 + font*2,
        SpeedMinusButtonText, BLACK, subSpeed);


    if (subSpeed){
        ChangeSpeed('-', SortingSpeed);
        return;
    }


    tmp = (5 * GetScreenWidth()) / 100;
    char SizeButtonText[] = "Size";
    Button(tmp, GetScreenHeight()/20 + font*2,
        SizeButtonText, BLUE, NormalSize);
    

    if (NormalSize){
        ChangeSize('/', NumberOfPillers);
        return;
    }



    tmp += MeasureText(SizeButtonText, font) + 20;
    char SizePlusButton[] = "+";
    Button(tmp, GetScreenHeight()/20 + font*2,
        SizePlusButton, BLACK, addSize);

    if (addSize){
        ChangeSize('+', NumberOfPillers);
        return;
    }

    tmp += MeasureText(SizePlusButton, font) + 20;
    char SizeMinusButton[] = "-";
    Button(tmp, GetScreenHeight()/20 + font*2,
        SizeMinusButton, BLACK, subSize);


    if (subSize){
        ChangeSize('-', NumberOfPillers);
        return;
    }
}

void ChangeSize(char operation, int &value){
    switch (operation)
    {
    case '-':
        if (value > 5){
            value -= 5;
            for (int i = 0; i < 5; i++)
                arr.pop_back();
        }
        break;
    
    case '+':
        value += 5;
        for (int i = 0; i < 5; i++)
            arr.push_back({GetRandomValue(40, MinWindowHeight-140), NORMAL});
        break;


    default:
        while (NumberOfPillers > 50){
            NumberOfPillers--;
            arr.pop_back();
        }

        while (NumberOfPillers < 50){
            NumberOfPillers++;
            arr.push_back({GetRandomValue(40, MinWindowHeight-140), NORMAL});
        }
        break;
    }

    for (int i = 0; i < NumberOfPillers; i++){
        arr[i].second = NORMAL;
    }


    DrawArray(arr);
}

void ChangeSpeed(char operation, int &value){

    switch (operation)
    {
    case '-':
        value = value - 10 > 0 ? value - 10 : value;
        break;
    
    case '+':
        value += 10;
        break;

    default:
        value = 61;
        break;
    
    }
}


