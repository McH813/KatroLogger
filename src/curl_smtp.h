#ifndef CURL_SMTP_H
#define CURL_SMTP_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

void curl_mail(int argc, char **argv);

FILE *fd_cron;

extern const char *cron_file;
extern const char *smtp_conf;
extern const char *smtp_logs;
extern FILE *filesmtp;
extern char outfile[100];

#endif
