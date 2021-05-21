/*
 * Logic Sim GUI
 * Authors: Geir Anderson
 * Dear ImGui:TODO proper and clean citations here
 * 
 *
 *
 */
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <cstdio>
#include <SDL.h>
#include <GL/gl3w.h>

static void quintow(bool* is_done, bool* quit_win, int winw, int winh)
{
    ImGui::SetNextWindowPos(ImVec2(winw * 0.5f, winh * 0.5f), ImGuiCond_Once, ImVec2(0.5f,0.5f));
    ImGui::SetNextWindowSize(ImVec2(100,100),ImGuiCond_Once);
    //ImGui::SetNextWindowContentSize(ImVec2(winw+20,winh+20));
    ImGui::Begin("QUIT", quit_win, ImGuiWindowFlags_NoCollapse);
    if(ImGui::Button("Yes")){*is_done = true; *quit_win = false;}
    if(ImGui::Button("No")){*quit_win = false;}
    ImGui::End();
}

//Enable the menu bar at the top of the window's viewport
//The GUI element functions should be set to static void functions for the time being
static void menu_bar(bool* quit_win,
                     bool* show_demo_window,
                     bool* show_metrics)
{
    if(ImGui::BeginMainMenuBar())
    {
        if(ImGui::BeginMenu("File"))
        {
            //TODO Add code to make these work
            //Currently set to disabled
            if(ImGui::MenuItem("New", "CTRL+N", false, false)){}
            if(ImGui::MenuItem("Save", "CTRL+S", false, false)){}
            if(ImGui::MenuItem("Open", "CTRL+O", false, false)){}
            ImGui::Separator();
            if(ImGui::MenuItem("Quit", "CTRL+SHIFT+Q")){*quit_win = true;}
            ImGui::EndMenu();
        }
        //TODO Make toggled if dev mode on
        if(ImGui::BeginMenu("Debug"))
        {
            //TODO Add code to make these work too
            if(ImGui::MenuItem("Log", "CTRL+SHIFT+L", false, false)){}
            if(ImGui::MenuItem("Console", "CTRL+`", false, false)){}
            if(ImGui::MenuItem("DIG Demo", "CTRL+SHIFT+;")){*show_demo_window = true;}
            if(ImGui::MenuItem("DIG Metrics", "CTRL+ALT+;")){*show_metrics = true;}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

/*
   static void PH_thing()
   {
   ImGui::Begin("[PH]");
   ImGui::TextColored(ImVec4(0.50f, 0.11f, 0.68f, 1.00f), "[PH]");
   ImGui::End();
   }
   */

static void draw_zone(int winw, int winh)
{
    //Center and maintain window size
    ImGui::SetNextWindowPos(ImVec2(winw * 0.5f, winh * 0.5f), ImGuiCond_Always, ImVec2(0.5f,0.5f));
    ImGui::SetNextWindowSize(ImVec2(winw+30,winh+30),ImGuiCond_Always);
    ImGui::SetNextWindowContentSize(ImVec2(winw+20,winh+20));
    //ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    ImGui::Begin("Canvas", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | /*ImGuiWindowFlags_NoBackground |*/ /*ImGuiWindowFlags_MenuBar | */ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

    //menu_bar();

    //ImGui::Separator();
    //TODO adjust from example art style to
    //     drag and drop w/ drawing style
    //     
    //     look into mouse functions for drag and drop
    //     this is doable, but more work is needed
    //---------------CANVAS::START TODO--------------
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    static ImVector<ImVec2> points;

    //TODO drawing line stays for debug, but must alter for the drag-and-drop/draw feature
    static bool drawing_test_line = false; //Click left mouse, hold, move to 2nd point location, release
    bool drawing_preview = false; //Let's you see what you are even doing

    ImVec2 canvas_pos = ImGui::GetCursorScreenPos();
    ImVec2 canvas_size = ImGui::GetContentRegionAvail();

    if(canvas_size.x < 500.0f) canvas_size.x = 500.0f;
    if(canvas_size.y < 500.0f) canvas_size.y = 500.0f;

    draw_list->AddRectFilledMultiColor(canvas_pos,
                                       ImVec2(canvas_pos.x
                                             +canvas_size.x,
                                             canvas_pos.y
                                             +canvas_size.y),
                                       IM_COL32(0,0,0,0), 
                                       IM_COL32(0,0,0,0),
                                       IM_COL32(0,0,0,0),
                                       IM_COL32(0,0,0,0));
    draw_list->AddRect(canvas_pos,
                       ImVec2(canvas_pos.x
                             +canvas_size.x,
                             canvas_pos.y
                             +canvas_size.y),
                       IM_COL32(255,255,255,255));

    ImGui::InvisibleButton("canvas", canvas_size);//A little sneaky to get that drawing range

    ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x 
                                        -canvas_pos.x, 
                                        ImGui::GetIO().MousePos.y 
                                        -canvas_pos.y);
    if(drawing_test_line)
    {
        drawing_preview = true;
        points.push_back(mouse_pos_in_canvas);

        if(!ImGui::IsMouseDown(0))
        {
            drawing_test_line = drawing_preview = false;
        }
    }
    if(ImGui::IsItemHovered())
    {
        if(!drawing_test_line 
           && ImGui::IsMouseClicked(0))
        {
            points.push_back(mouse_pos_in_canvas);

            drawing_test_line = true;
        }
        if(ImGui::IsKeyPressed(ImGui::GetIO().KeyMap[ImGuiKey_Delete]) 
           && !points.empty())
        {
            drawing_test_line = drawing_preview = false;

            points.pop_back();
            points.pop_back();
        }
    }

    draw_list->PushClipRect(canvas_pos,
                            ImVec2(canvas_pos.x
                                   +canvas_size.x,
                                   canvas_pos.y
                                   +canvas_size.y), 
                            true);

    for(int i = 0; i < points.Size - 1; i+=2)
    {
        draw_list->AddLine(ImVec2(canvas_pos.x
                                 +points[i].x,
                                 canvas_pos.y
                                 +points[i].y),
                           ImVec2(canvas_pos.x
                                 +points[i+1].x,
                                 canvas_pos.y
                                 +points[i+1].y),
                           IM_COL32(89, 126, 185, 255), 
                           5.0f);
    }
    draw_list->PopClipRect();
    if(drawing_preview)
    {
        points.pop_back();
    }
    //TODO XXX TODO XXX TODO XXX
    //---------------CANVAS::END--------------------
    ImGui::End();
}

//TODO Maybe change from being "main"
//probably a void or something
int main(int argc, char** argv)
{
    int windowW, windowH;
    windowW = 820;
    windowH = 780;
    if(SDL_Init(SDL_INIT_VIDEO|
                SDL_INIT_TIMER|
                SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("ERROR: %s\n", SDL_GetError());
        return -1;
        //exit(-1);
    }
    //---------INIT SDL/GL----------------
    /* 
     * Initial SDL/GL declarations 
     * and settings based on example_sdl_opengl3 for Dear ImGui. 
     * TODO See if improvements or more specific settings could be used. 
     * TODO Design, implement, iterate and improve actual GUI.
     */

#if __APPLE__
    //-------------------Settings for MacOS------------
    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
            SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);//Required for MacOS
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    //--------------------------------------------------
#else
    //---------Settings not for MacOS------------------
    //Use GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    //--------------------------------------------------
#endif

    //Generates a window w/ graphical context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_WindowFlags window_flags = (SDL_WindowFlags)
                                   (SDL_WINDOW_OPENGL |
                                    SDL_WINDOW_RESIZABLE |
                                    SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_Window* window = SDL_CreateWindow("GLogic Sim v.proto-3",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        windowW,
                                        windowH,
                                        window_flags);

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); //Enables vsync

    //Init OpenGL loader
    bool error_gl_loader = gl3wInit() != 0;
    if(error_gl_loader)
    {
        //TODO error message
        return 1;
    }

    //---------End of SDL/GL init------

    //---------Apply Dear ImGui--------

    //Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    //ImGuiStyle& imstyle = ImGui::GetStyle();
    //imstyle.WindowBorderSize = 0.0f;
    //ImDrawData* imdd = ImGui::GetDrawData(); (void)imdd;
    //Enable the Keyboard for Navigation Support
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    //Setup Dear ImGui style
    //TODO Look into style system
    //TODO Light/Dark mode toggler

    //Geir: I set the style to "light" by default.
    //      Comment it out and uncomment "dark" for dark mode,
    //      or uncomment "classic" for the "classic" mode.

    //ImGui::StyleColorsLight();
    //ImGui::StyleColorsClassic();
    ImGui::StyleColorsDark();

    //Setup SDL2 and OpenGL3 bindings
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    //TODO Font (Dear ImGui suggests doing so here)

    //io.KeyMap[ImGuiKey_Q] = SDL_SCANCODE_Q;
    //Geir: Dear ImGui's demo window is good for testing the renderer.
    bool show_demo_window = false;
    bool show_metrics = false;

    //Background RGBA vals
    //TODO Determine a practical color range
    ImVec4 clear_color = ImVec4(0.39f, 0.21f, 0.40f, 1.00f);
    //Geir: I set the default to a purple color for testing.

    //------Setting Dear ImGui for use End----------

    //"Main" loop

    bool is_done = false;
    bool quit_win = false;
    while(!is_done)
    {
        //TODO Events
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            //End if quitting program
            if(event.type == SDL_QUIT)
                is_done = true;

            //End if window is closed
            if(event.type == SDL_WINDOWEVENT 
                          && event.window.event
                          == SDL_WINDOWEVENT_CLOSE
                          && event.window.windowID
                          == SDL_GetWindowID(window))
                is_done = true;
        }
        //Starts Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        //Runs Dear ImGui's demo if set to true
        if(show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
    
        if(!show_demo_window && io.KeyCtrl 
                             && io.KeyShift 
                             && ImGui::IsKeyPressed(SDL_SCANCODE_SEMICOLON))
            show_demo_window = true;

        //Run the GUI functions here unless problems occur
        //If problems occur contact teammates for reorganizing and fixing
        //PH_thing();
        menu_bar(&quit_win, &show_demo_window, &show_metrics);
        
        if(quit_win)
            quintow(&is_done, &quit_win, windowW, windowH);
        
        if(io.KeyCtrl && io.KeyShift 
                      && ImGui::IsKeyPressed(SDL_SCANCODE_Q))
            is_done = true;

        //TODO Design and implement GUI, function-by-function
        draw_zone(windowW,windowH);
        
        if(show_metrics)
            ImGui::ShowMetricsWindow(&show_metrics);
    
        if(!show_metrics && io.KeyCtrl 
                         && io.KeyAlt
                         && ImGui::IsKeyPressed(SDL_SCANCODE_SEMICOLON))
            show_metrics = true;

        //Rendering
        ImGui::Render();
        windowW = (int)io.DisplaySize.x;
        windowH = (int)io.DisplaySize.y;
        glViewport(0, 0, windowW, windowH);

        glClearColor(clear_color.x,
                     clear_color.y,
                     clear_color.z,
                     clear_color.w);

        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    //Destruct and end
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();

    ImGui::DestroyContext();
    SDL_GL_DeleteContext(gl_context);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
