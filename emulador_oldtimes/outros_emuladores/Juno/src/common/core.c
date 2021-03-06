// $Id: core.c,v 1.1.1.1 2004/09/10 17:44:49 MagicalTux Exp $
// original : core.c 2003/02/26 18:03:12 Rev 1.7

#include <stdio.h>
#include <stdlib.h>
#ifndef _WIN32
#include <unistd.h>
#endif
#include <signal.h>
#include <string.h>

#include "core.h"
#include "../common/db.h"
#include "../common/mmo.h"
#include "../common/malloc.h"
#include "../common/socket.h"
#include "../common/timer.h"
#include "../common/graph.h"
#include "../common/grfio.h"
#include "../common/plugins.h"
#include "../common/version.h"
#include "../common/showmsg.h"

#ifndef _WIN32
	#include "svnversion.h"
#endif

int runflag = 1;
int arg_c = 0;
char **arg_v = NULL;

char *SERVER_NAME = NULL;
char SERVER_TYPE = ATHENA_SERVER_NONE;
static void (*term_func)(void) = NULL;

/*======================================
 *	CORE : Set function
 *--------------------------------------
 */
void set_termfunc(void (*termfunc)(void))
{
	term_func = termfunc;
}

#ifndef MINICORE	// minimalist Core
// Added by Gabuzomeu
//
// This is an implementation of signal() using sigaction() for portability.
// (sigaction() is POSIX; signal() is not.)  Taken from Stevens' _Advanced
// Programming in the UNIX Environment_.
//
#ifdef WIN32	// windows don't have SIGPIPE
#define SIGPIPE SIGINT
#endif

#ifndef POSIX
#define compat_signal(signo, func) signal(signo, func)
#else
sigfunc *compat_signal(int signo, sigfunc *func)
{
	struct sigaction sact, oact;

	sact.sa_handler = func;
	sigemptyset(&sact.sa_mask);
	sact.sa_flags = 0;
#ifdef SA_INTERRUPT
	sact.sa_flags |= SA_INTERRUPT;	/* SunOS */
#endif

	if (sigaction(signo, &sact, &oact) < 0)
		return (SIG_ERR);

	return (oact.sa_handler);
}
#endif

/*======================================
 *	CORE : Signal Sub Function
 *--------------------------------------
 */
static void sig_proc(int sn)
{
	static int is_called = 0;

	switch (sn) {
	case SIGINT:
	case SIGTERM:
		if (++is_called > 3)
			exit(0);
		runflag = 0;
		break;
#ifndef _WIN32
	case SIGXFSZ:
		// ignore and allow it to set errno to EFBIG
		ShowWarning ("Tamanho do arquivo maximo alcancado!\n");
		//run_flag = 0;	// should we quit?
		break;
	case SIGPIPE:
		ShowMessage ("Quebra de Conexao encontrada... fechando socket\n");	// set to eof in socket.c
		break;	// does nothing here
#endif
	}
}

void signals_init (void)
{
	compat_signal(SIGTERM, sig_proc);
	compat_signal(SIGINT, sig_proc);

	// Signal to create coredumps by system when necessary (crash)
	compat_signal(SIGSEGV, SIG_DFL);
	compat_signal(SIGFPE, SIG_DFL);
	compat_signal(SIGILL, SIG_DFL);
	#ifndef _WIN32
		compat_signal(SIGXFSZ, sig_proc);
		compat_signal(SIGPIPE, sig_proc);
		compat_signal(SIGBUS, SIG_DFL);
		compat_signal(SIGTRAP, SIG_DFL);
	#endif
}
#endif

#ifdef SVNVERSION
	#define xstringify(x) stringify(x)
	#define stringify(x) #x
	const char *get_svn_revision()
	{
		return xstringify(SVNVERSION);
	}
#else
const char* get_svn_revision()
{
	static char version[10];
	FILE *fp;

	if ((fp = fopen(".svn/entries", "r")) != NULL) {
		char line[1024];
		int rev;
		while (fgets(line,1023,fp))
			if (strstr(line,"revision=")) break;
		fclose(fp);
		if (sscanf(line," %*[^\"]\"%d%*[^\n]", &rev) == 1) {
			sprintf(version, "%d", rev);
			return version;
		}
	}

	// if getting revision has failed
	return "Desconhecido";
}
#endif

/*======================================
 *	CORE : Display title
 *--------------------------------------
 */

static void display_title(void)
{
	ClearScreen(); // clear screen and go up/left (0, 0 position in text)
	ShowMessage(""CL_WTBL"          (=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=)"CL_CLL""CL_NORMAL"\n"); // white writing (37) on blue background (44), \033[K clean until end of file
	ShowMessage(""CL_XXBL"          ("CL_BOLD"      _________                  v%2d.%02d.%02d               "CL_XXBL")"CL_CLL""CL_NORMAL"\n", ATHENA_MAJOR_VERSION, ATHENA_MINOR_VERSION, ATHENA_REVISION); // 1: bold char, 0: normal char
	ShowMessage(""CL_XXBL"          ("CL_BOLD"      \\_   ___ \\_______  ____   ____  __ __  ______      "CL_XXBL")"CL_CLL""CL_NORMAL"\n"); // 1: bold char, 0: normal char
	ShowMessage(""CL_XXBL"          ("CL_BOLD"      /    \\  \\/\\_  __ \\/  _ \\ /    \\|  |  \\/  ___/      "CL_XXBL")"CL_CLL""CL_NORMAL"\n"); // 1: bold char, 0: normal char
	ShowMessage(""CL_XXBL"          ("CL_BOLD"      \\     \\____|  | \\(  <_> )   |  \\  |  /\\___ \\       "CL_XXBL")"CL_CLL""CL_NORMAL"\n"); // 1: bold char, 0: normal char
	ShowMessage(""CL_XXBL"          ("CL_BOLD"       \\______  /|__|   \\____/|___|  /____//____  >      "CL_XXBL")"CL_CLL""CL_NORMAL"\n"); // 1: bold char, 0: normal char
	ShowMessage(""CL_XXBL"          ("CL_BOLD"              \\/                   \\/           \\/       "CL_XXBL")"CL_CLL""CL_NORMAL"\n"); // 1: bold char, 0: normal char
	ShowMessage(""CL_XXBL"          ("CL_BOLD"                     Usando Fusion Advanced maps         "CL_XXBL")"CL_CLL""CL_NORMAL"\n"); // 1: bold char, 0: normal char
	ShowMessage(""CL_XXBL"          ("CL_BT_YELLOW"        Baseado em eAthena (c) 2005 Projeto Cronus       "CL_XXBL")"CL_CLL""CL_NORMAL"\n"); // yellow writing (33)
	ShowMessage(""CL_WTBL"          (=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=)"CL_CLL""CL_NORMAL"\n\n"); // reset color

	ShowInfo("Revisao SVN: '"CL_WHITE"%s"CL_RESET"'.\n", get_svn_revision());
}

//Do not run as superuser (root)
void usercheck(void){
}

/*======================================
 *	CORE : MAINROUTINE
 *--------------------------------------
 */
#ifndef MINICORE	// minimalist Core
int main (int argc, char **argv)
{
	int next;

	// initialise program arguments
	{
		char *p = SERVER_NAME = argv[0];
		while ((p = strchr(p, '/')) != NULL)
			SERVER_NAME = ++p;
		arg_c = argc;
		arg_v = argv;
	}

         usercheck();

	set_server_type();
	display_title();
	malloc_init(); /* 一番最初に実行する必要がある */
	signals_init();

	timer_init();
	socket_init();
	plugins_init();

	do_init(argc,argv);
	graph_init();
	plugin_event_trigger("Athena_Init");

	while (runflag) {
		next = do_timer(gettick_nocache());
		do_sendrecv(next);
#ifndef TURBO
		do_parsepacket();
#endif
	}

	plugin_event_trigger("Athena_Final");
	graph_final();
	do_final();

	exit_dbn();
	timer_final();
	plugins_final();
	socket_final();
	malloc_final();

	return 0;
}
#else
int main (int argc, char **argv)
{
	// initialise program arguments
	{
		char *p = SERVER_NAME = argv[0];
		while ((p = strchr(p, '/')) != NULL)
			SERVER_NAME = ++p;
		arg_c = argc;
		arg_v = argv;
	}

         usercheck();

	display_title();
	do_init(argc,argv);
	do_final();

	return 0;
}
#endif

#ifdef BCHECK
unsigned int __invalid_size_argument_for_IOC;
#endif
