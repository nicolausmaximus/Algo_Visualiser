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

void ShowMenuScreen();
void Button(float x, float y, char *Text, Color color, bool &state);

void Selection_Sort_Button(float size, char Selection_Sort_Text[]);
std::vector<std::pair<int, int>> arr(NumberOfPillers);

Color FindColorForPiller(int pillerState);
void DrawArray(std::vector<std::pair<int, int>> arr);
void RandomizeArray(std::vector<std::pair<int, int>> &arr);

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
        color = BLUE;
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
            
            return;
        }   
        

    } else {
        DrawText(Text, x, y, font, color);
    }

    return;
}

