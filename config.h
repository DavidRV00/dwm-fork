/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;       /* vert inner gap between windows */
static const unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "Ubuntu Mono:size=10" };
static const char dmenufont[]       = "Ubuntu Mono:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	//[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	//[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeNorm] = { "#bbbbbb", "#162023", "#162023" },
	[SchemeSel] = { "#000000", "#5f87d7", "#5f87d7" },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered   isfloating   monitor    scratch key */
	{ NULL,       NULL,       NULL,       0,            1,           0,           -1,        0 },
	//{ NULL,     "scratchpad", NULL,       0,            1,           1,           -1,       's' },
	{ "Gimp",     NULL,       NULL,       0,            0,           1,           -1,        0 },
	{ "mpv",      NULL,       NULL,       0,       			0,           0,           -1,        's' },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
//static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *dmenucmd[] = { "dmenu_run", "-b", "-m", dmenumon, "-fn", dmenufont, "-nb",  "#162023", "-nf",  "#bbbbbb", "-sb",  "#5f87d7", "-sf",  "#000000", NULL };
static const char *termcmd[]  = { "terminal", NULL };
static const char *edcmd[]  = {  "editor", NULL };
static const char *termfmcmd[]  = {  "termfm", NULL };
static const char *guifmcmd[]  = {  "guifm", NULL };
static const char *browsercmd[]  = { "browser", NULL };
static const char *browsersesscmd[]  = { "browsersess", NULL };
static const char *powercmd[] = { "power", "-b", NULL };
static const char *notewindowcmd[] = { "notewindow", NULL };
static const char *tempnotewindowcmd[] = { "tempnotewindow", NULL };
static const char *mkexecwindowcmd[] = { "mkexecwindow", NULL };
static const char *passmenucmd[] = { "passmenu", "-b", NULL };


/*First arg only serves to match against key in rules*/
//static const char *scratchpadcmd[] = {"s", "alacritty", "--class", "scratchpad", NULL};
static const char *scratchpadcmd[] = {"s", "umpv", NULL};

// TODO: media actions (like, pause-toggle, shuf, etc)
// TODO: pipeclip
// TODO: nice summoning/desummoning of apps (email, chat, calendar, feeds, notes and other priveleged data)
// TODO: fix up movement and resizing?
// TODO: convenient search/menus (radio, spotsearch, browser-open, ...)
// TODO: fullscreen
// TODO: simultaneous monitor switching
static Key keys[] = {
	/* modifier                     key        		function        argument */
	{ MODKEY|ShiftMask,             XK_semicolon, spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, 		spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask|ShiftMask, XK_Return, 		spawn,          {.v = edcmd } },
	{ MODKEY|ShiftMask,             XK_m, 		    spawn,          {.v = termfmcmd } },
	{ MODKEY|ControlMask|ShiftMask, XK_m, 		    spawn,          {.v = guifmcmd } },
	{ MODKEY,                       XK_i, 		    spawn,          {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_i, 		    spawn,          {.v = browsersesscmd } },
	{ MODKEY|ShiftMask,             XK_n,      		spawn,          {.v = notewindowcmd } },
	{ MODKEY|ShiftMask,             XK_t,      		spawn,          {.v = tempnotewindowcmd } },
	{ MODKEY|ShiftMask,             XK_x,      		spawn,          {.v = mkexecwindowcmd } },
	{ MODKEY,             					XK_p,      		spawn,          {.v = passmenucmd } },
	{ MODKEY,                       XK_grave,  		togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      		togglebar,      {0} },
	{ MODKEY,                       XK_j,      		focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      		focusstack,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_j,      		pushdown,       {0} },
	{ MODKEY|ControlMask,           XK_k,      		pushup,         {0} },
	{ MODKEY,                       XK_n,      		incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      		incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      		setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      		setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      		setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      		setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      		setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_Return, 		zoom,           {0} },
	{ MODKEY,                       XK_Tab,    		view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      		killclient,     {0} },
	{ MODKEY,                       XK_t,      		setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      		setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      		setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  		setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  		togglefloating, {0} },
	{ MODKEY,                       XK_0,      		view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      		tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  		focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, 		focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  		tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 		tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,      		                0)
	TAGKEYS(                        XK_2,      		                1)
	TAGKEYS(                        XK_3,      		                2)
	TAGKEYS(                        XK_4,      		                3)
	TAGKEYS(                        XK_5,      		                4)
	TAGKEYS(                        XK_6,      		                5)
	TAGKEYS(                        XK_7,      		                6)
	TAGKEYS(                        XK_8,      		                7)
	TAGKEYS(                        XK_9,      		                8)
	{ MODKEY|ShiftMask,             XK_q,      		spawn,          {.v = powercmd } },
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
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

