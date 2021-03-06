/* See LICENSE file for copyright and license details. */


static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 16;       /* snap pixel */

static const unsigned int barhpad  = 16;        /* bar height padding */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* fonts */
static const char *fonts[]          = {"DejaVu Sans Mono:style=Book:size=12"};
static const char dmenufont[]       = "DejaVu Sans Mono:style=Book:size=20";
static const char editorfont[]      = "DejaVu Sans Mono:style=Book:size=14";
static const char termfont[]        = "DejaVu Sans Mono:style=Book:size=14";

/* color scheme */
const char bg[]      = "#0a1016"; /* background color */
const char fg[]      = "#FFFFFF"; /* foreground color */
const char sel[]     = "#29333c"; /* selection color */
const char bd[]      = "#29333c"; /* selection color */

/* status bar colors */
static const char red[]       = "#ff0000";
static const char yellow[]    = "#FFFF00";
static const char green[]     = "#00ff00";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeBar] = { bg, fg, bd},
	[SchemeNorm] = { fg, bg, bd},
	[SchemeSel] = { fg, sel, sel},
	[SchemeReg] = { fg, bg, bd},
	[SchemeRed] = { red, bg, bd},
	[SchemeYellow] = { yellow, bg, bd},
	[SchemeGreen] = { green, bg, bd},
};


typedef struct {
	const char *name;
	const void *cmd;
} Sp;

static const char *stermcmd[]  = { "st", "-T", "Terminal", "-n", "sterm", "-f", termfont, NULL };
static const char *sbrwsr[]  = { "qutebrowser", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"sterm",      stermcmd},
	{"sbrwsr",      sbrwsr},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",	  NULL,			NULL,		0,		        1,			 -1 },
	{ NULL,		  "sterm",		NULL,		SPTAG(0),		1,			 -1 },
	{ "qutebrowser",  NULL,			NULL,		SPTAG(1),		0,			 -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "M",      monocle },
	{ "T",      tile },    /* first entry is default */
	{ "X",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", bg, "-nf", fg, "-sb", sel, "-sf", green, NULL };
static const char *termcmd[]  = { "st", "-T", "Terminal", "-f", termfont, NULL };
static const char *editorcmd[]  = { "st", "-f", editorfont, "-e", "vim", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             		XK_v,      spawn,          {.v = editorcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,            		XK_y,  	   togglescratch,  {.ui = 0 } },
	{ MODKEY,            		XK_u,	   togglescratch,  {.ui = 1 } },
	{ MODKEY,            		XK_x,	   togglescratch,  {.ui = 2 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,         	Button1,        view,  		{0} },
	{ ClkClientWin,         MODKEY,         Button4,        focusstack,     {.i = +1 } },
	{ ClkClientWin,         MODKEY,         Button5,        focusstack,     {.i = -1 } },
};

