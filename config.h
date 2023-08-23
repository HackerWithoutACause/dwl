/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const int smartgaps                 = 0;  /* 1 means no outer gap when there is only one window */
static const int smartborders              = 1;
static const unsigned int borderpx         = 3;  /* border pixel of windows */
static const unsigned int gappx            = 6; /* horiz inner gap between windows */
static const float bordercolor[]           = {0.082, 0.082, 0.082, 1.0};
static const float focuscolor[]            = {0.415, 0.623, 0.709, 1.0};
/* To conform the xdg-protocol, set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.1, 0.1, 0.1, 1.0};

/* Autostart */
static const char *const autostart[] = {
	"foot", "--server", NULL,
	"swayidle", "timeout", "300", "gtklock -t %I:%M %p -b /home/me/pictures/wallpaper-blured.png", "timeout", "600", "/home/me/.cache/cargo/release/dpms-off", NULL,
	"swaybg", "-m", "fill", "-i", "/home/me/pictures/wallpaper.png", NULL,
	NULL /* terminate */
};

/* tagging - tagcount must be no greater than 31 */
#define TAGCOUNT (9)

static const Rule rules[] = {
	/* app_id     title       tags mask     alwaysborder  iscentered  isfloating  scratchkey  isterm  noswallow  monitor */
	{ "firefox",  NULL,       1 << 8,       0,            0,          0,          0,          0,      1,         -1 },
	{ "foot",     NULL,       0,            1,            0,          0,          0,          1,      1,         -1 },
	{ "wev",      NULL,       0,            0,            0,          0,          0,          0,      1,         -1 },
	{ NULL,     "scratchpad", 0,            1,            1,          1,          's',        1,      1,         -1 },
	{ "fuzzel",   NULL,       0,            0,            1,          1,          'm',        1,      1,         -1 },
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "[M]",      monocle },
	{ NULL,       NULL },
};

/* monitors */ 
static const MonitorRule monrules[] = {
	/* name       mfact nmaster scale layout       rotate/reflect                x    y */
	/* example of a HiDPI laptop monitor:
	{ "eDP-1",    0.5,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	*/
	/* defaults */
	{ NULL,       0.6, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
	.options = NULL,
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;

/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT;
static const double accel_speed = -0.2;
static const int cursor_timeout = 5;

/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key for SUPER, use WLR_MODIFIER_LOGO */
#define SHIFT  WLR_MODIFIER_SHIFT
#define SUPER  WLR_MODIFIER_LOGO 
#define ALT    WLR_MODIFIER_ALT

#define TAGKEYS(KEY,SKEY,TAG) \
	{ SUPER,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ SUPER|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ SUPER|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ SUPER|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[] = { "footclient", NULL };
static const char *menucmd[] = { "m", "fuzzel", NULL };

/* named scratchpads - First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = { "s", "footclient", "-T", "scratchpad", "-w", "850x500", NULL };

static const char *lower_volume[] = { "change-volume-on-active", "-0.1", NULL };
static const char *raise_volume[]  = { "change-volume-on-active", "+0.1", NULL };

static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  key                 function        argument */
	{ SUPER,                    XKB_KEY_Return,     spawn,          { .v = termcmd } },
	{ SUPER,                    XKB_KEY_space,      togglescratch,  { .v = scratchpadcmd } },
	{   ALT,                    XKB_KEY_space,      togglescratch,  { .v = menucmd } },
	{   ALT,                    XKB_KEY_Tab,        focusstack,     { .i = +1} },
	{ SUPER|SHIFT,              XKB_KEY_h,          setmfact,       { .f = -0.05} },
	{ SUPER|SHIFT,              XKB_KEY_l,          setmfact,       { .f = +0.05} },
	{ SUPER,                    XKB_KEY_Tab,        view,           { 0 } },
	{ SUPER,                    XKB_KEY_q,          killclient,     { 0 } },
	{ SUPER,					XKB_KEY_minus,		spawn,			{ .v = lower_volume } },
	{ SUPER,					XKB_KEY_equal,		spawn,			{ .v = raise_volume } },
	{ SUPER|SHIFT,              XKB_KEY_F,          togglefloating, { 0 } },
	{ SUPER|SHIFT,              XKB_KEY_E,        togglefullscreen, { 0 } },
	{ SUPER,                    XKB_KEY_0,          view,           { .ui = ~0} },
	{ SUPER|SHIFT,              XKB_KEY_parenright, tag,            { .ui = ~0} },
	{ SUPER,                    XKB_KEY_backslash,  cyclelayout,    { .i = +1 } },
	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                     0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_at,                         1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_numbersign,                 2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                     3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                    4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_asciicircum,                5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                  6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                   7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                  8),
	{ SUPER|WLR_MODIFIER_SHIFT, XKB_KEY_Q,          quit,           {0} },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ SUPER, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ SUPER, BTN_MIDDLE, togglefloating, {0} },
	{ SUPER, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};
