#define VERSION_NUMBER 1

program SIMP_PROG {
   version SIMP_VERSION {
     int ENQUEUEDETECTIONMODULE(string) = 1;
     int DEQUEUEDETECTIONMODULE(string) = 2;
     int ENQUEUENOTIFICATIONMODULE(string) = 3;
     int DEQUEUENOTIFICATIONMODULE(string) = 4;
     int STOPIDS(void) = 5;
     int LOADSHAREDOBJECT(string) = 6;
   } = VERSION_NUMBER;
} = 555555555;
