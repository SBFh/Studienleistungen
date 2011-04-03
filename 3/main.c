#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

void *loadLibrary(char *name);
void *loadMethod(void *handle, char *name);
void closeLibrary(char *handle);
double calcCircleArea(double radius);
double calcRectArea(double width, double height);
double calcNewton(double (*function)(double), double start, double end, unsigned int segments, unsigned int degree, unsigned int divisor, const double coeff[]);
void log(char *message);
void loadLogConfiguration();

char* logLibrary;

double testFunction(double x)
{
  return x * x;
}

int main()
{
  loadLogConfiguration();
  
  char output[200];
  
  sprintf(output, "Fläche eines Kreises mit Radius 4: %f", calcCircleArea(4));
  log(output);
  
  sprintf(output, "Fläche eines Rechtecks mit Breite 10 und Höhe 4: %f", calcRectArea(10,4));
  log(output);
  
  const unsigned int degree = 4;
  const unsigned int divisor = 90;
  const double coeff[] = {7., 32., 12., 32., 7.};
  
  sprintf(output, "Ungefähre Flache der Kurve x² von x = 0 bis x = 100: %f", calcNewton(*testFunction, 0, 100, 100, degree, divisor, coeff));
  log(output);
}

void loadLogConfiguration()
{
  FILE *configurationFile;
  if ((configurationFile = fopen("log.config", "r")) == NULL)
  {
    printf("No Log Configuration found using default console logger\n");
    logLibrary = "logConsole.so";
    return;
  }
  char configuration[20];
  
  fgets(configuration, sizeof configuration, configurationFile);
  
  fclose(configurationFile);
  
  if (strcmp(configuration, "Console") == 0)
  {
   logLibrary = "logConsole.so"; 
  }
  else if (strcmp(configuration, "File") == 0)
  {
    logLibrary = "logFile.so";
  }
  else 
  {
    printf("Invalid Log Configuration found. Using default console logger\n");
    logLibrary = "logConsole.so";
    return;
  }
  
  printf("Log Configuration found, using log library: %s\n", logLibrary);
}

void log(char *message)
{
 void *handle;
 handle = loadLibrary(logLibrary);
 
 void (*logCall)(char*);
 logCall = loadMethod(handle, "log");
 
 (*logCall)(message);
 
 closeLibrary(handle);
}

char* libCalcFile = "libCalc.so";

double calcCircleArea(double radius)
{
  void *handle;
  handle = loadLibrary(libCalcFile);
  
  double (*calcCircleAreaCall)(double);
  calcCircleAreaCall = loadMethod(handle, "calcCircleArea");
  
  double result = (*calcCircleAreaCall)(radius);
  
  closeLibrary(handle);
  
  return result;
}

double calcRectArea(double width, double height)
{
  void *handle;
  handle = loadLibrary(libCalcFile);
  
  double (*calcRectAreaCall)(double,double);
  calcRectAreaCall = loadMethod(handle, "calcRectArea");
  
  double result = (*calcRectAreaCall)(width, height);
  
  closeLibrary(handle);
  
  return result;
}

double calcNewton(double (*function)(double), double start, double end, unsigned int segments, unsigned int degree, unsigned int divisor, const double coeff[])
{
  void *handle;
  handle = loadLibrary(libCalcFile);
  
  double (*calcNewtonCall)(double (*function)(double), double start, double end, unsigned int segments, unsigned int degree, unsigned int divisor, const double coeff[]);
  calcNewtonCall = loadMethod(handle, "calcNewton");
  
  double result = (*calcNewtonCall)(function, start, end, segments, degree, divisor, coeff);
  
  closeLibrary(handle);
  
  return result;
}

void *loadLibrary(char *name)
{
  return dlopen(name, RTLD_LAZY);
}

void *loadMethod(void *handle, char *name)
{
  return dlsym(handle, name);
}

void closeLibrary(char *handle)
{
  dlclose(handle);
}