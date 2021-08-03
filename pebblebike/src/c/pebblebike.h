#ifndef PEBBLEBIKE_H
#define PEBBLEBIKE_H

#include "pebble.h"
#include "config.h"
#include "colors.h"
#include "sizes.h"
#include "ovl/screen_map.h"

#ifndef PBL_IF_ROUND_ELSE
#define PBL_IF_ROUND_ELSE(if_true, if_false) (if_false)
#endif

enum {
  MSG_LOCATION_DATA = 0x13,  // TUPLE_BYTE_ARRAY
  STATE_CHANGED = 0x14,
  MSG_VERSION_PEBBLE = 0x15,
  MSG_VERSION_ANDROID = 0x16,
  MSG_LIVE_SHORT = 0x17,
  //MSG_LIVE_ASK_NAMES = 0x18,
  MSG_LIVE_NAME0 = 0x19,
  MSG_LIVE_NAME1 = 0x20,
  MSG_LIVE_NAME2 = 0x21,
  MSG_LIVE_NAME3 = 0x22,
  MSG_LIVE_NAME4 = 0x23,
  MSG_BATTERY_LEVEL = 0x24,
  MSG_LOCATION_DATA_V2 = 0x25,
  MSG_LOCATION_DATA_V3 = 0x26,
  MSG_SENSOR_TEMPERATURE = 0x27,
  MSG_CONFIG = 0x28,
  MSG_HR_MAX = 0x29,
  MSG_NAVIGATION = 0x31,
  MSG_P2HR = 0x32,
};

enum {
  STATE_STOP = 0,
  STATE_START = 1,
};

enum {
  PLAY_PRESS = 0x0,
  STOP_PRESS = 0x1,
  REFRESH_PRESS = 0x2,
  CMD_BUTTON_PRESS = 0x4,

  ORUXMAPS_START_RECORD_CONTINUE_PRESS = 0x5,
  ORUXMAPS_STOP_RECORD_PRESS = 0x6,
  ORUXMAPS_NEW_WAYPOINT_PRESS = 0x7,
};

enum {
  UNITS_IMPERIAL = 0x0,
  UNITS_METRIC = 0x1,
  UNITS_NAUTICAL_IMPERIAL = 0x2,
  UNITS_NAUTICAL_METRIC = 0x3,
  UNITS_RUNNING_IMPERIAL = 0x4,
  UNITS_RUNNING_METRIC = 0x5,
};

enum {
  PAGE_DATA = 0,
  PAGE_HEARTRATE = 1,
  PAGE_ALTITUDE = 2,
#ifdef ENABLE_FUNCTION_LIVE
  PAGE_LIVE_TRACKING,
#endif
  PAGE_MAP,
};
enum {
  SUBPAGE_A = 0,
  SUBPAGE_B = 1,
  SUBPAGE_UNDEF = 20
};
enum {
  PERSIST_UNITS_KEY = 0x0,
  PERSIST_CONFIG_KEY = 0x1,
  PERSIST_VERSION = 0x2,
};

#ifdef ENABLE_FUNCTION_LIVE
  #define NUMBER_OF_PAGES 5
#else
  #define NUMBER_OF_PAGES 4
#endif

#define NB_POINTS_PER_PAGE 5

#define SPEED_UNIT_IMPERIAL "mph"
#define SPEED_UNIT_METRIC "km/h"
#define SPEED_UNIT_NAUTICAL "kn"
#define SPEED_UNIT_RUNNING_IMPERIAL "min/m"
#define SPEED_UNIT_RUNNING_METRIC "min/km"
#define DISTANCE_UNIT_IMPERIAL "miles"
#define DISTANCE_UNIT_METRIC "km"
#define DISTANCE_UNIT_NAUTICAL "nm"
#define ALTITUDE_UNIT_METRIC "m"
#define ALTITUDE_UNIT_IMPERIAL "ft"
#define ASCENT_RATE_UNIT_METRIC "m/h"
#define ASCENT_RATE_UNIT_IMPERIAL "ft/h"
#define HEART_RATE_UNIT "bpm"
#define TEMPERATURE_UNIT_METRIC "°C"
#define TEMPERATURE_UNIT_IMPERIAL "°F"
// Don't use field values to sort (only to save - persistent)
enum {
  FIELD_ACCURACY,
  FIELD_ALTITUDE,
  FIELD_ASCENT,
  FIELD_ASCENTRATE,
  FIELD_AVGSPEED,
  FIELD_BEARING,
  FIELD_CADENCE,
  FIELD_DISTANCE,
  FIELD_DURATION,
  FIELD_HEARTRATE,
  //FIELD_LAT,
  //FIELD_LON,
  FIELD_MAXSPEED,
  //FIELD_NBASCENT,
  FIELD_SLOPE,
  FIELD_SPEED,
  FIELD_TEMPERATURE,
  FIELD_TIME,
#ifdef PBL_HEALTH
  FIELD_STEPS,
  FIELD_STEPS_CADENCE,
#endif
#ifdef PBL_COLOR
  FIELD_ALTITUDE_DATA_AND_GRAPH,
#endif
  FIELD_ALTITUDE_GRAPH_ONLY,
#ifdef PBL_COLOR
  FIELD_ASCENTRATE_DATA_AND_GRAPH,
#endif
  FIELD_ASCENTRATE_GRAPH_ONLY,
#ifdef PBL_COLOR
  FIELD_HEARTRATE_DATA_AND_GRAPH,
#endif
  FIELD_HEARTRATE_GRAPH_ONLY,
#ifdef PBL_COLOR
  FIELD_SPEED_DATA_AND_GRAPH,
#endif
  FIELD_SPEED_GRAPH_ONLY,
  FIELD_NAV_ESTIMATED_TIME_ARRIVAL,
  FIELD_NAV_DISTANCE_NEXT,
  FIELD_NAV_DISTANCE_TO_DESTINATION,
  FIELD_NAV_TIME_TO_DESTINATION,
  FIELD__UNUSED,
};

#define FIELD_NAV_NEXT_INDEX FIELD_TEMPERATURE
typedef struct FieldConfig {
  uint8_t type;
  ///todo remove type_index?
  uint8_t type_index;
} FieldConfig;
typedef struct ScreenConfig {
  FieldConfig field_top;
  FieldConfig field_top2;
  FieldConfig field_bottom_left;
  FieldConfig field_bottom_right;
  FieldConfig field_topbar_center;
} ScreenConfig;
typedef struct FieldLayer {
  TextLayer *data_layer;
  TextLayer *unit_layer;
} FieldLayer;

typedef struct TopBarLayer {
  Layer *layer;
  FieldLayer field_center_layer;
  TextLayer *accuracy_layer;
  GBitmap *bluetooth_image;
  BitmapLayer *bluetooth_layer;
} TopBarLayer;
typedef struct ScreenLayer {
  FieldLayer field_top;
  FieldLayer field_top2;
  FieldLayer field_bottom_left;
  FieldLayer field_bottom_right;
} ScreenLayer;

typedef struct AppData {
  Window *window;

  Layer *page_data;
  MenuLayer *page_live_tracking;
  Layer *page_map;

  TopBarLayer topbar_layer;
  ScreenLayer screenData_layer;

  ScreenConfig screen_config[2];

  TextLayer *live_tracking_layer;

  char time[6];  // xx:xx, \0 terminated
  char speed[16];
  char distance[6];
  char avgspeed[6];
  char altitude[6];
  char ascent[8];
  char ascentrate[8];
  char slope[8];
  char accuracy[5];
  char bearing[4];
  char elapsedtime[9]; // xx:xx:xx, \0 terminated
  char maxspeed[8];
  //char lat[8];
  //char lon[8];
  //char nbascent[8];
  char heartrate[8];
  char cadence[8];
  char temperature[7];
  char steps[7];
  char steps_cadence[7];

  char nav_next_distance[6];
  char nav_distance_to_destination[6];
  char nav_ttd[6];  // xx:xx, \0 terminated
  char nav_eta[6];  // xx:xx, \0 terminated

  char unitsSpeedOrHeartRate[8];
  char unitsSpeed[8];
  char unitsDistance[8];
  char unitsAltitude[8];
  char unitsAscentRate[8];
  char unitsTemperature[8];
  uint8_t state;
  uint8_t live;
  uint8_t debug;
  uint8_t refresh_code;
  uint8_t page_number;
  uint8_t data_subpage;

  int32_t android_version;
  int32_t phone_battery_level;

  uint8_t nav_notification;
} AppData;

typedef struct GPSData {
  int nb_received;
  uint8_t units;
  uint16_t time;
  int32_t speed100;
  int32_t maxspeed100;
  int32_t distance100;
  int32_t avgspeed100;
  int16_t altitude;
  int16_t ascent;
  int16_t ascentrate;

  int8_t slope;
  uint8_t accuracy;
  int16_t xpos;
  int16_t ypos;
  uint16_t bearing;
  uint8_t heartrate;
  uint8_t cadence;
  int16_t temperature10;

  uint16_t nav_next_distance1000;
  uint16_t nav_distance_to_destination100;
  uint16_t nav_bearing;
  uint16_t nav_error1000;
  uint8_t nav_nb_pages;
  //uint8_t nav_page_number;
  uint16_t nav_next_index;
  uint16_t nav_first_index_in_storage;

  int16_t nav_xpos[NAV_NB_POINTS_STORAGE];
  int16_t nav_ypos[NAV_NB_POINTS_STORAGE];

#ifdef PBL_HEALTH
  bool received_external_hr;
  bool received_internal_hr;
#endif
} GPSData;


//////////////
// Map
//////////////

#define MAP_VSIZE_X 4000
#define MAP_VSIZE_Y 4000

#define XINI MAP_VSIZE_X/2
#define YINI MAP_VSIZE_Y/2

extern GPoint pts[MAP_NUM_POINTS];
extern int cur_point;
extern int map_scale;
extern int nb_points;
extern int32_t xposprev, yposprev;


//////////////
// Live Data
//////////////
#define NUM_LIVE_FRIENDS 5
typedef struct LiveFriendData {
  char name[10];
  char subtitle[20];
  int16_t xpos;
  int16_t ypos;
  int32_t distance;
  uint16_t bearing;
  int16_t lastviewed;
  TextLayer *name_layer;
  GRect name_frame;
} LiveFriendData;
typedef struct LiveData {
  uint8_t nb;
  LiveFriendData friends[NUM_LIVE_FRIENDS];
  LiveFriendData *sorted_friends[NUM_LIVE_FRIENDS];
} LiveData;
#ifdef PBL_PLATFORM_CHALK
extern GFont font_roboto_bold_16;
#endif
extern GFont font_roboto_bold_62;
extern AppData s_data;
extern GPSData s_gpsdata;
extern LiveData s_live;
extern bool title_instead_of_units;
extern GColor bg_color_data_main;
extern bool need_launch_config;

void change_units(uint8_t units, bool first_time);
void change_state(uint8_t state);

#endif // PEBBLEBIKE_H
