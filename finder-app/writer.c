#include <syslog.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

    openlog(0, LOG_ODELAY, LOG_USER);

    if (argc != 3)
    {
        syslog(LOG_ERR, "Required parameters were not found - %d", argc);
        return 1;
    }

    char *writepath = argv[1];
    char *writestr = argv[2];

    syslog(LOG_DEBUG, "Writing %s to file %s", writestr, writepath);

    FILE *file = fopen(writepath, "w+");
    if (!file)
    {
        syslog(LOG_ERR, "Unexpected exception when opening file - %m");
        return 1;
    }

    if(!fwrite(writestr, sizeof(char), strlen(writestr), file))
    {
        syslog(LOG_ERR, "Unable to write to file - %m");
    }

    syslog(LOG_DEBUG, "Successfully wrote to file");

    fclose(file);

    return 0;
}