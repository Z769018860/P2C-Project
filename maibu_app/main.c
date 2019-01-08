#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#include "maibu_sdk.h"
#include "maibu_res.h"



/************ Macro *************/
#define TITLE   "多通道输入"
#define AUTHOR  "King"
#define EMAIL   "769018860@qq.com"
#define VERSION "0.0.1"



#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   128



#define TIMER_INTERVAL  30



//Accelerator
#define ACCER_BASE              2048
#define ACCER_THRESHOLD_HIGH    25
#define ACCER_THRESHOLD_LOW     50




/* Enumeration */
enum GameState {
    UCAS_init,
    UCAS_mode1,
    UCAS_mode2,
    UCAS_exit,
    UCAS_choose1,
    UCAS_choose2
};



/* Global Variables */
static uint8_t g_gamestate = UCAS_init;



//Window/Layer ID
static int32_t g_window_id;



//Game menu
static int8_t g_banner_layer_id;
static int8_t g_mode1_layer_id;
static int8_t g_mode2_layer_id;
static int8_t g_exit_layer_id;
static int8_t g_cmode1_layer_id;
static int8_t g_cmode2_layer_id;
static int8_t g_copyright_layer_id;



//表示当前为什么模式
static int8_t choose_mode;




/* Function */
void do_mode1(void);
void do_mode2(void);
void do_exit(P_Window pwindow);
void initVariables(void);
void upPressed(void *context);
void backPressed(void *context);
void downPressed(void *context);
void selectPressed(void *context);
void timeDisplay(P_Window pwindow, uint32_t millis);
void gameMessageUpdate(P_Window pwindow, int8_t id, char *str);
P_Layer textOut(char *str, uint8_t x, uint8_t y, uint8_t height, uint8_t width, enum GAlign alignment, uint8_t type);
P_Layer bmpOut(uint8_t x, uint8_t y, uint8_t height, uint8_t wdith, uint16_t res);
void gameLayer(P_Window pwindow, int8_t *layer_id, P_Layer layer);
void gameResult(P_Window pwindow);
void layerVisible(P_Window pwindow, int8_t id, bool status);
void gameLayerVisible(P_Window pwindow, enum GameState stat);
void gameStateSet(enum GameState stat);
enum GameState gameStateGet(void);




//Init global variables
void initVariables(void)
{
    //window
    g_window_id = -1;



    //Menu
    g_banner_layer_id = -1;
    g_mode1_layer_id = -1;
    g_mode2_layer_id = -1;
    g_exit_layer_id = -1;
    g_cmode1_layer_id = -1;
    g_cmode2_layer_id = -1;



    //mode choose
    choose_mode=0;//未选择模式
}



//uint32_t maibu_comm_send_msg(const char *link_id, const uint8_t *buff,  uint16_t size)
//选择打字模式，传输数据
void do_mode1()
{
    int16_t x=0, y=0, z=0;
    int16_t msg[4];//存储需要传输的数据
    uint32_t recv_ID;
    uint16_t size;
    uint8_t *buff;
    enum GameState stat = gameStateGet();
    char *LinkId;
    char buf[30] = "";
    int i;
    LinkId="19ad8176"; 
    choose_mode=1;
    //当前为模式1
    //获取三轴数据
    sprintf(buf, "%s", "进入模式1！");
    //for (i=0;i<10;i++)
    while(stat == UCAS_choose1)
    {
        maibu_get_accel_data(&x, &y, &z);
        msg[0]=choose_mode;
        msg[1]=x;
        msg[2]=y;
        msg[3]=z;
        size=4*sizeof(uint16_t);
        buff=(uint8_t *)msg;
        //maibu_comm_register_msg_callback(maibu_comm_send_msg);
        if (x!=0 || y!=0 || z!=0)
        {
            recv_ID=maibu_comm_send_msg(LinkId,buff,size);
            //break;
        }    
        
    }
    return;
}



void do_mode2()
{
    int16_t x=0, y=0, z=0;
    int16_t msg[4];//存储需要传输的数据
    uint32_t recv_ID;
    uint16_t size;
    uint8_t *buff;
    enum GameState stat = gameStateGet();
    char *LinkId;
    char buf[30] = "";
    int i;
    LinkId="19ad8176"; 
    choose_mode=2;
    //当前为模式1
    //获取三轴数据
    sprintf(buf, "%s", "进入模式2！");
    //for (i=0;i<10;i++)
    while (stat == UCAS_choose2)
    {
        maibu_get_accel_data(&x, &y, &z);
        msg[0]=choose_mode;
        msg[1]=x;
        msg[2]=y;
        msg[3]=z;
        size=4*sizeof(uint16_t);
        buff=(uint8_t *)msg;
        //maibu_comm_register_msg_callback(maibu_comm_send_msg);
        if (x!=0 || y!=0 || z!=0)
        {
            recv_ID=maibu_comm_send_msg(LinkId,buff,size);
            //break;
        }
            
    }
    return;
}


void do_exit(P_Window pwindow)
{
    choose_mode=0;
    app_window_stack_pop(pwindow);
    return;
}



//返回键
void backPressed(void *context)
{
    P_Window pwindow = (P_Window)context;



    enum GameState stat = gameStateGet();

    if (stat==UCAS_init)
    {
        //quit
        app_window_stack_pop(pwindow);
    }
    else
    {
        gameStateSet(UCAS_init);
        gameLayerVisible(pwindow, UCAS_init);
        choose_mode=0;        
    }


}




void upPressed(void *context)
{
    P_Window pwindow = (P_Window)context;



    enum GameState stat = gameStateGet();



    if (stat == UCAS_init) {
        gameStateSet(UCAS_mode1);
        gameLayerVisible(pwindow, UCAS_mode1);
    } else if (stat == UCAS_mode1) {
        gameStateSet(UCAS_mode1);
    } else if (stat == UCAS_mode2) {
        //TODO: menu select up
        gameStateSet(UCAS_mode1);
        gameLayerVisible(pwindow, UCAS_mode1);
    }else if (stat == UCAS_exit) {
        //TODO: menu select up
        gameStateSet(UCAS_mode2);
        gameLayerVisible(pwindow, UCAS_mode2);
    }
}




void downPressed(void *context)
{
    P_Window pwindow = (P_Window)context;
    
    enum GameState stat = gameStateGet();
    int i;



    if (stat == UCAS_init) {
        gameStateSet(UCAS_mode1);
        gameLayerVisible(pwindow, UCAS_mode1);
    } else if (stat == UCAS_mode1) {
        gameStateSet(UCAS_mode2);
        gameLayerVisible(pwindow, UCAS_mode2);
    } else if (stat == UCAS_mode2) {
        //TODO: menu select up
        gameStateSet(UCAS_exit);
        gameLayerVisible(pwindow, UCAS_exit);
    }else if (stat == UCAS_exit) {
        //TODO: menu select up
        gameStateSet(UCAS_exit);
        gameLayerVisible(pwindow, UCAS_exit);
    }
}



void selectPressed(void *context)
{
    P_Window pwindow = (P_Window)context;



    enum GameState stat = gameStateGet();



    if (stat == UCAS_mode1) {
        gameLayerVisible(pwindow, UCAS_choose1);
        do_mode1();
    } else if (stat == UCAS_mode2) {
        gameLayerVisible(pwindow, UCAS_choose2);
        do_mode2();
    }else if (stat == UCAS_exit) {
        gameLayerVisible(pwindow, UCAS_exit);
        gameStateSet(UCAS_exit);
        do_exit(pwindow);
    }
}



void gameMessageUpdate(P_Window pwindow, int8_t id, char *str)
{
    if (pwindow == NULL) {
        return;
    }



    if (id == -1) {
        return;
    }



    P_Layer layer = app_window_get_layer_by_id(pwindow, id);
    if (NULL == layer) {
        maibu_service_vibes_pulse(VibesPulseTypeLong, 0);
        return;
    }



    app_layer_set_text_text(layer, str);
}




P_Layer textOut(char *str, uint8_t x, uint8_t y, uint8_t height, uint8_t width, enum GAlign alignment, uint8_t type)
{
    GRect frame = {{x, y}, {height, width}};
    LayerText lt = {str, frame, alignment, type, 0};
    P_Layer layer = app_layer_create_text(&lt);



    return layer;
}



P_Layer bmpOut(uint8_t x, uint8_t y, uint8_t height, uint8_t wdith, uint16_t res)
{
    GRect frame = {{x, y}, {height, wdith}};
    GBitmap bitmap;



    res_get_user_bitmap(res, &bitmap);



    LayerBitmap layer_bitmap = {bitmap, frame, GAlignCenter};



    P_Layer layer = app_layer_create_bitmap(&layer_bitmap);



    return layer;
}



void gameLayer(P_Window pwindow, int8_t *layer_id, P_Layer layer)
{
    if (pwindow == NULL) {
        return;
    }



    if (layer == NULL) {
        return;
    }



    if (*layer_id == -1) {
        *layer_id =  app_window_add_layer(pwindow, layer);
    } else {
        P_Layer old_layer = app_window_get_layer_by_id(pwindow, *layer_id);
        app_window_replace_layer(pwindow, old_layer, layer);
    }
}



void gameLayerInit(P_Window pwindow)
{
    P_Layer layer;
    //char buf[30] = "";

    //sprintf(buf, "%s", "多通道输入");
    /* Menu */
    //banner
    layer = bmpOut(0, 0, 176, 176, RES_BITMAP_BG);
    gameLayer(pwindow, &g_banner_layer_id, layer);
    //mode1
    layer = bmpOut(0, 0, 176, 176, RES_BITMAP_BG1);
    gameLayer(pwindow, &g_mode1_layer_id, layer);
    //mode2
    layer = bmpOut(0, 0, 176, 176, RES_BITMAP_BG2);
    gameLayer(pwindow, &g_mode2_layer_id, layer);
    //exit
    layer = bmpOut(0, 0, 176, 176, RES_BITMAP_BG3);
    gameLayer(pwindow, &g_exit_layer_id, layer);
    //mode1
    layer = bmpOut(0, 0, 176, 176, RES_BITMAP_MODE1);
    gameLayer(pwindow, &g_cmode1_layer_id, layer);
    //mode2
    layer = bmpOut(0, 0, 176, 176, RES_BITMAP_MODE2);
    gameLayer(pwindow, &g_cmode2_layer_id, layer);

    //layer = textOut("多通道输入",50, 80, 40, 100, GAlignCenter, 30);
    //gameLayer(pwindow, &g_banner_layer_id, layer);
    //mode1
    //layer = textOut("MODE 1",50, 80, 20, 80, GAlignCenter,30);
    //gameLayer(pwindow, &g_mode1_layer_id, layer);
    //mode2
    //layer = textOut("MODE 2",50, 110, 20, 80, GAlignCenter,30);
    //gameLayer(pwindow, &g_mode2_layer_id, layer);
    //exit
    //layer = textOut("EXIT",50, 150, 20, 40, GAlignCenter, 30);
    //gameLayer(pwindow, &g_exit_layer_id, layer);


    //copyright
   // layer = textOut("Copyright@2019 king",50, 170, 10, 80, GAlignCenter, 30);
    //gameLayer(pwindow, &g_copyright_layer_id, layer);    
}

void layerVisible(P_Window pwindow, int8_t id, bool status)
{
    if (pwindow == NULL) {
        return;
    }

    if (id == -1) {
        return;
    }

    P_Layer layer = app_window_get_layer_by_id(pwindow, id);
    maibu_layer_set_visible_status(layer, status);
}

void gameLayerVisible(P_Window pwindow, enum GameState stat)
{
    //Game menu
    bool banner;
    bool mode1;
    bool mode2;
    bool exit;
    bool choose1;
    bool choose2;
    //bool copyright;
        //banner = true;


    if (stat == UCAS_init) {
        banner = true;
        mode1 = false;
        mode2 = false;
        exit = false;
        choose1 = false;
        choose2 = false;
        //copyright = true;



    } else if (stat == UCAS_mode1) {
        banner = false;
        mode1 = true;
        mode2 = false;
        exit = false;
        choose1 = false;
        choose2 = false;
        //copyright = true;



    } else if (stat == UCAS_mode2) {
        banner = false;
        mode1 = false;
        mode2 = true;
        exit = false;
        choose1 = false;
        choose2 = false;
        //copyright = true;
    }else if (stat == UCAS_exit) {
        banner = false;
        mode1 = false;
        mode2 = false;
        exit = true;
        choose1 = false;
        choose2 = false;
        //copyright = true;
    }else if (stat == UCAS_choose1) {
        banner = false;
        mode1 = false;
        mode2 = false;
        exit = false;
        choose1 = true;
        choose2 = false;
        //copyright = true;



    } else if (stat == UCAS_choose2) {
        banner = false;
        mode1 = false;
        mode2 = false;
        exit = false;
        choose1 = false;
        choose2 = true;
        //copyright = true;
    }



    //Menu
    layerVisible(pwindow, g_banner_layer_id, banner);
    layerVisible(pwindow, g_mode1_layer_id, mode1);
    layerVisible(pwindow, g_mode2_layer_id, mode2);
    layerVisible(pwindow, g_exit_layer_id, exit);
    layerVisible(pwindow, g_cmode1_layer_id, choose1);
    layerVisible(pwindow, g_cmode2_layer_id, choose2);
    //layerVisible(pwindow, g_copyright_layer_id, copyright);
    app_window_update(pwindow);

    //layerVisible(pwindow, g_banner_layer_id, banner);

}



void gameStateSet(enum GameState stat)
{
    g_gamestate = stat;
}



enum GameState gameStateGet(void)
{
    return g_gamestate;
}



// Function: main()
int main(int argc, char ** argv)
{
    //simulator_init();
    P_Window pwindow = NULL;



    initVariables();



    //Create main window
    pwindow = app_window_create();
    if (NULL == pwindow) {
        return 0;
    }



    gameLayerInit(pwindow);

    gameLayerVisible(pwindow, UCAS_init);



    app_window_click_subscribe(pwindow, ButtonIdUp, upPressed);
    app_window_click_subscribe(pwindow, ButtonIdBack, backPressed);
    app_window_click_subscribe(pwindow, ButtonIdDown, downPressed);
    app_window_click_subscribe(pwindow, ButtonIdSelect, selectPressed);



    g_window_id = app_window_stack_push(pwindow);



    gameStateSet(UCAS_init);


    //simulator_wait();
    return 0;
} // End of main()


