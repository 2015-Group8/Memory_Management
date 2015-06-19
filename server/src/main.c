/********************************/
/*    System software project   */
/*   2015.06.19                 */
/*   Kang Jin Hyun              */
/*   Kim Byoung Su              */
/*   Kwon Sun Kwan              */
/********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <sqlite3.h>
#include <math.h>
#include <sys/time.h>
//add
#include <sys/types.h>
#include "aul.h"

#include "my_list.h"
#include "util.h"

#ifndef MAX_ALPHA_RUN
#define MAX_ALPHA_RUN	4
#endif

#ifndef MAXCHAR
#define MAXCHAR	1024
#endif

#ifndef HIS_FILE_NAME
#define HIS_FILE_NAME	"/data/syslog.dat"
#endif

#ifndef OUT_FILE_NAME
#define OUT_FILE_NAME	"/data/out.dat"
#endif

#ifndef RUA_DB_NAME
#define	RUA_DB_NAME "/opt/dbspace/.rua.db"
#endif

#ifndef RUA_SQL
#define RUA_SQL "SELECT * FROM rua_history order by launch_time desc limit 20;"
#endif

#ifndef PID_OUT_NAME
#define PID_OUT_NAME "/pid.log"
#endif

#ifndef THRESHOLD
#define THRESHOLD 0.5
#endif

typedef struct _my_app {
	char* aname;
	int freq;

	my_list* head; // store page rank information
} my_app;

my_list *appList;
my_app *curApp;
my_app *prevApp;

float alpha[MAX_ALPHA_RUN] = {0,};

void pageRank_init (void);
my_app* insertAppList (char* name);
my_list* insertPageList (my_list* head, char* name);

void alphaCalculation (int flag); //flag == 1, print out

void showAppList(void);
void showPageRank (char* name, float ratio); 
void showPageRankInterneal (my_list* curMyList, float ratio); 

char* last_app (void);

// use glib
static GMainLoop* gMainLoop = NULL;

int last_lunchtime;

gboolean update_func_cb(gpointer data) {
	sqlite3 *db = NULL;
	char **pResult;
    int nrow, ncol, i, tmp = 0;
    char *errmsg = 0;
	FILE *oFile;

	if(gMainLoop) {
		LOGINFO("Update AppRank Table");

	    if(sqlite3_open (RUA_DB_NAME, & db)) {
			LOGINFO("Can't open database: %sn", sqlite3_errmsg(db));
    	    sqlite3_close(db);
			return TRUE;
		}
		if(!(oFile = fopen(HIS_FILE_NAME, "a+"))) {
			LOGINFO("Can't open log file\n");
			return TRUE;
		}

		if(sqlite3_get_table(db, RUA_SQL, &pResult, &nrow, &ncol, &errmsg) == SQLITE_OK) {
			for(i=(nrow+1)*ncol-4; i>5; i=i-5){
				//printf("%d %s %s\n", i, pResult[i], pResult[i+3]);
				tmp = atoi(pResult[i+3]);
				//printf("%d %d %d\n", tmp, last_lunchtime, time(NULL));
				if(tmp > last_lunchtime) {
					insertAppList(pResult[i]);
					fprintf(oFile, "%s\n", pResult[i]);
				}
			}
			tmp = atoi(pResult[9]);
			if(tmp!=last_lunchtime) {
				last_lunchtime = tmp;
			}
    	} else {
        	LOGINFO("SQLite Error : %sn", errmsg);
    	}

    	sqlite3_free_table(pResult);
    	sqlite3_close(db);
		fclose(oFile);
	}
	return TRUE;
}

gboolean memcheck_func_cb(gpointer data)
{
    FILE *fp = NULL;
    int pidVal = -1;
    char killofCmd[50] = {0};
	char *tmp;
	if(gMainLoop)
	{
		LOGINFO("Memory clearning");

		//alphaCalculation(0);
		//showAppList();
		tmp = last_app();
		if(tmp!=NULL) {
			showPageRank(tmp, alpha[2]);
			free(tmp);
        fp = fopen(PID_OUT_NAME, "r");
        while(1 )
        {
            fscanf(fp, "%d", &pidVal);
            if(feof(fp)) break;
            sprintf(killofCmd, "kill -9 %d", pidVal);
            system(killofCmd);
            printf("pid %d is terminated\n", pidVal);
        }
        fclose(fp);
		}
	}
	return TRUE;
}

static void sig_quit(int signo)
{
	LOGINFO("received %d signal : stops a main loop", signo);
	if (gMainLoop)
		g_main_loop_quit(gMainLoop);
}

int main (void) {
    my_list * curPageList = NULL;

    LOGINFO("Start my memory manager daemon");
	pageRank_init();
	//showAppList();
	//showPageRank(NULL);
	signal(SIGINT, sig_quit);
	signal(SIGTERM, sig_quit);
	signal(SIGQUIT, sig_quit);

	gMainLoop = g_main_loop_new(NULL, FALSE);

	g_timeout_add(2000, update_func_cb, gMainLoop); // Timeout callback: it will be called after 3000ms.
	g_timeout_add(10000, memcheck_func_cb, gMainLoop); // Timeout callback: it will be called after 3000ms.

	g_main_loop_run(gMainLoop);



   	return 0;
}

/* 
	Last update, 2015, 6, 7 BS Kim
*/

void pageRank_init (void){
	int i;
	FILE* iFile;
	char buff[MAXCHAR]= {0,}, *ptr;

	initial_list (appList);

	curApp = NULL;
	prevApp = NULL;

	last_lunchtime = 0;

	alphaCalculation(1);

	/* will change */
	if(!(iFile = fopen(HIS_FILE_NAME, "r+"))) {
		fprintf(stderr, "pin oder file open error!!\n");
		return;
	}

	while (fgets(buff, MAXCHAR, iFile)!=NULL) {
		ptr = strtok(buff, " \t\n");
		insertAppList(ptr);
	}
}

my_app* insertAppList (char* name) {
	my_list* curMyList;
	my_app *tmpApp;

	if(name == NULL) {
		return NULL;
	}

	curMyList = find_list(appList, name);
	if(curMyList!=NULL) {
		tmpApp = (my_app*)curMyList->item;
		tmpApp->freq = tmpApp->freq + 1;
	} else {
		tmpApp = (my_app*)malloc(sizeof(my_app));
		tmpApp->aname = str_malloc(name);
		tmpApp->freq = 1;
		tmpApp->head = NULL;

		appList = insert_list(appList, tmpApp->aname, (void*)tmpApp);
	}

	prevApp = curApp;
	curApp = tmpApp;

	if(prevApp==NULL) {
		curApp->head = insertPageList (curApp->head, name);
	} else {
		prevApp->head = insertPageList (prevApp->head, name);
	}
	return tmpApp;
}

my_list* insertPageList (my_list* head, char* name) {
	my_app *tmpApp;
	my_list* curMyList;

	curMyList = find_list(head, name);
	if(curMyList!=NULL) {
		tmpApp = (my_app*)curMyList->item;
		tmpApp->freq = tmpApp->freq + 1;
	} else {
		tmpApp = (my_app*)malloc(sizeof(my_app));
		tmpApp->aname = str_malloc(name);
		tmpApp->freq = 1;
		tmpApp->head = NULL;

		return insert_list(head, tmpApp->aname, (void*)tmpApp);
	}
	return head;
}

void showAppList(void) {
	my_list* curMyList;
	my_list* curPageList;
	my_app* tmpApp;

	printf("\n#APP list\n");
	curMyList = appList;
	while(curMyList!=NULL) {
		tmpApp = (my_app*)curMyList->item;
		printf("#%s %d\n", curMyList->key, tmpApp->freq);

		curPageList = tmpApp->head;
		while(curPageList!=NULL) {
			tmpApp = (my_app*)curPageList->item;
			printf("#\t%s %d\n", curPageList->key, tmpApp->freq);
			curPageList = curPageList->next;
		}
		curMyList = curMyList->next;
	}
	printf("\n");
}

void showPageRankInterneal (my_list* curMyList, float ratio) {
	my_list* curPageList;
	my_app* tmpApp, *tmpApp2;
	int total;
	FILE *oFile;
    //inser this code by kang
    char *ctmp=NULL, pidofCmd[50] = {0};
    float prob = 0.0;
    //

	if(curMyList==NULL) return;

	oFile = fopen(OUT_FILE_NAME, "w+");

	tmpApp = (my_app*)curMyList->item;
	printf("#%s %d\n", curMyList->key, tmpApp->freq);
	fprintf(oFile, "#%s\n", curMyList->key);

	curPageList = tmpApp->head;

	total = 0;
	while(curPageList!=NULL) {
		tmpApp2 = (my_app*)curPageList->item;
		total = total + tmpApp2->freq;
		curPageList = curPageList->next;
	}
	curPageList = tmpApp->head;
	while(curPageList!=NULL) {
		tmpApp2 = (my_app*)curPageList->item;
		printf("#\t%s %d %.3f\n", curPageList->key, tmpApp2->freq, ratio*(float)tmpApp2->freq/(float)total);
		fprintf(oFile, "\t%s %.3f\n",  curPageList->key, ratio*(float)tmpApp2->freq/(float)total);
        
        //start from org.tizen is not target
        //prob variable is added
        prob = ratio*(float)tmpApp2->freq/(float)total;
        if(prob < THRESHOLD){
            ctmp = strstr(curPageList->key, "org.tizen");
            if(ctmp != NULL)
            {
                ctmp = strrchr(curPageList->key, '.');
                ctmp = ctmp + sizeof(char);
            } else
                ctmp = curPageList->key;
            strcpy(pidofCmd, "pidof ");    
            strcat(pidofCmd, ctmp);
            if(curPageList == tmpApp->head)
                strcat(pidofCmd, " > /pid.log");
            else
                strcat(pidofCmd, " >> /pid.log");
            system(pidofCmd);
        }
        //insert this code by Kang
		curPageList = curPageList->next;
	}
	fclose(oFile);
}

void showPageRank (char* name, float ratio) {
	my_list* curMyList;
	my_list* curPageList;
	my_app* tmpApp, *tmpApp2;
	int total;

	printf("\n#Page Rank\n");

	if(name==NULL) {
		curMyList = appList;
		while(curMyList!=NULL) {
			showPageRankInterneal(curMyList, ratio);
			curMyList = curMyList->next;
		}
	} else {
		curMyList = find_list(appList, name);
		showPageRankInterneal(curMyList, ratio);
	}
	printf("\n");
}

void alphaCalculation (int flag) {
	int i;
	int total = 0;

	printf("\n#Alpha Probability\n");
	
	alpha[0] = 0.00;
	alpha[1] = 0.30;
	alpha[2] = 0.70;
	alpha[3] = 0.00;

	for (i=1;i<MAX_ALPHA_RUN;i++) {
		if(flag == 1) printf("#%d : %.3f\n",i, alpha[i]);
	}
}

char* last_app (void) {
	sqlite3 *db = NULL;
	char **pResult;
    int nrow, ncol;
    char *errmsg = 0;
	char *ptr = NULL;

    if(sqlite3_open (RUA_DB_NAME, & db)) {
		LOGINFO("Can't open database: %sn", sqlite3_errmsg(db));
   	    sqlite3_close(db);
		return NULL;
	}

	if(sqlite3_get_table(db, RUA_SQL, &pResult, &nrow, &ncol, &errmsg) == SQLITE_OK) {
		//printf("%s\n", pResult[6]);
		ptr = str_malloc(pResult[6]);
	} 

	sqlite3_free_table(pResult);
	sqlite3_close(db);

	return ptr;
}

/*
        	for(i=0;i<nrow+1;++i) {
            	for(j=0;j<ncol;++j) {
					printf("%d %s |", k, pResult[k++]);
            	}
            	printf("\n");
        	}
*/
