#include "namegen.h"

/*int main(int argc, char *argv[]) {
  name_gen testing;
  printf("Result for DARTH: %i\n", testing.check_name("DARTH"));
  printf("Result for shIT: %i\n", testing.check_name("shIT"));
  printf("Result for XeNoZePhYr: %i\n", testing.check_name("XeNoZePhYr"));
  system("pause");
  return 0;
}*/

name_gen::name_gen() {
  for (int i = 0; i < 3; i++) {
    fRestrictions[i] = NULL;
  }
  fRestrictions[0] = fopen("conf/reserved.conf", "r");
  fRestrictions[1] = fopen("conf/fictional.conf", "r");
  fRestrictions[2] = fopen("conf/profane.conf", "r");
}

name_gen::~name_gen() {
  for (int i = 0; i < 3; i++) {
    if (fRestrictions[i] != NULL) {
      fclose(fRestrictions[i]);
    }
  }
}

int name_gen::check_name(char *input_name) {
  // Returns 0 for approved, 1 for reserved, 2 for fictional, 3 for profane
  int buffer_size = 128;
  char *temp1 = trim_and_lower(input_name, ' ');
  char *buffer = new char[buffer_size];
  for (int i = 1; i < 4; i++) {
    fseek(fRestrictions[i-1], 0, SEEK_SET);
    int filesize = ftell(fRestrictions[i-1]);
    while (!feof(fRestrictions[i-1])) {
      buffer[0] = '\0';
      fgets(buffer, buffer_size, fRestrictions[i-1]);
      char *temp2 = trim_and_lower(buffer, '\n');
      if (strncmp(temp2, temp1, strlen(temp1)) == 0) {
        delete [] temp1;
        delete [] temp2;
        delete [] buffer;
        return i;
      }
      delete [] temp2;
    }
  }
  delete [] temp1;
  delete [] buffer;
  return 0;
}

char *name_gen::trim_and_lower(char *input, char character) {
  char *output = new char[strlen(input)+1];
  output[0] = '\0';
  int j = 0;
  for (int i = 0; i < strlen(input); i++) {
    if (input[i] != character) {
      if ((int)input[i] >= 65 && (int)input[i] <= 90) {
        output[j] = input[i] + 32;
      }
      else {
        output[j] = input[i];
      }
      output[j+1] = '\0';
      j++;
    }
  }
  return output;
}


