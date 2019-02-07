#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv) {
  int fd = open("/dev/pts/9",O_WRONLY);
  if (fd > 0) {
    std::string tmp{"test-code"};
    int write_ans = write(fd, tmp.c_str(), tmp.size());
    close(fd);
  }
}
