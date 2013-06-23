#include <cstdio>
#include <cstdlib>
#include <cstring>

class name_gen {
  public:
    name_gen();
    ~name_gen();
    int check_name(char *input_name);
  protected:
    FILE *fRestrictions[3];
    char *trim_and_lower(char *input, char character);
};
